#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>

// 버퍼 크기를 30바이트로 정의
#define BUF_SIZE 30

// 자식 프로세스 종료 시 호출되는 시그널 핸들러 함수
void read_childproc(int sig)
{
	pid_t pid;      // 프로세스 ID를 저장할 변수
	int status;     // 프로세스 종료 상태를 저장할 변수

	// waitpid로 종료된 자식 프로세스들을 모두 정리 (WNOHANG: 논블로킹)
	// 반환값이 0보다 크면 정리된 프로세스가 있다는 의미
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		// 정리된 프로세스 ID 출력
		printf("removed proc id : %d\n", pid);
	}
}

int main(int argc, char **argv) {
	int serv_sock, clnt_sock;           // 서버 소켓과 클라이언트 소켓 파일 디스크립터
	struct sockaddr_in serv_adr, clnt_adr;  // 서버와 클라이언트 주소 구조체

	pid_t pid;                          // fork() 반환값을 저장할 변수
	struct sigaction act;               // 시그널 핸들러 설정을 위한 구조체
	socklen_t adr_sz;                   // 주소 구조체 크기
	int str_len, state;                 // 문자열 길이, 상태값 저장 변수
	char buf[BUF_SIZE];                 // 데이터 송수신용 버퍼

	// 명령행 인자 개수 확인 (프로그램명 + 포트번호 = 2개)
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);  // 사용법 출력
		exit(1);                                 // 프로그램 종료
	}

	// 시그널 핸들러 설정
	act.sa_handler = read_childproc;    // SIGCHLD 시그널 처리 함수 지정
	sigemptyset(&act.sa_mask);          // 시그널 마스크 초기화 (빈 집합)
	act.sa_flags = 0;                   // 특별한 플래그 없음
	state = sigaction(SIGCHLD, &act, 0); // SIGCHLD 시그널에 대한 핸들러 등록
	
	// TCP 소켓 생성 (IPv4, 스트림 소켓, 기본 프로토콜)
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	
	// 서버 주소 구조체 초기화
	memset(&serv_adr, 0, sizeof(serv_adr));         // 구조체를 0으로 초기화
	serv_adr.sin_family = AF_INET;                  // IPv4 주소 체계
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);   // 모든 IP 주소에서 연결 허용
	serv_adr.sin_port = htons(atoi(argv[1]));       // 포트 번호 설정 (네트워크 바이트 순서로 변환)
	
	// 소켓에 주소 바인딩
	bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	
	// 연결 대기 상태로 설정 (최대 5개까지 대기큐에 저장)
	listen(serv_sock, 5);

	// 무한 루프로 클라이언트 연결 대기
	while (1)
	{
		adr_sz = sizeof(clnt_adr);      // 클라이언트 주소 구조체 크기 설정
		
		// 클라이언트 연결 대기 및 수락
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		
		puts("new client connected...");   // 새 클라이언트 연결 메시지 출력
		
		pid = fork();                      // 자식 프로세스 생성
		
		if (pid == 0)                      // 자식 프로세스인 경우
		{
			close(serv_sock);              // 자식 프로세스에서는 서버 소켓 닫기
			
			// 클라이언트로부터 데이터를 받아 다시 전송하는 에코 루프
			while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
				write(clnt_sock, buf, str_len);  // 받은 데이터를 그대로 전송
			
			close(clnt_sock);              // 클라이언트 소켓 닫기
			puts("client disconnected..."); // 클라이언트 연결 종료 메시지
			return (0);                    // 자식 프로세스 종료
		}
		else                               // 부모 프로세스인 경우
			close(clnt_sock);              // 부모 프로세스에서는 클라이언트 소켓 닫기
	}
	close(serv_sock);                      // 서버 소켓 닫기 (실제로는 실행되지 않음)
	return 0;
}
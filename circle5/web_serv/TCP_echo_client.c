#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 버퍼 크기를 1024바이트로 정의
#define BUF_SIZE 1024

int main (int argc, char **argv)
{
	int sock;                       // 소켓 파일 디스크립터
	char message[BUF_SIZE];         // 메시지를 저장할 버퍼
	int str_len;                    // 읽어온 문자열 길이
	struct sockaddr_in serv_adr;    // 서버 주소 구조체

	// TCP 소켓 생성 (IPv4, 스트림 소켓, 기본 프로토콜)
	sock = socket(PF_INET, SOCK_STREAM, 0);

	// 서버 주소 구조체 초기화
	memset(&serv_adr, 0, sizeof(serv_adr));         // 구조체를 0으로 초기화
	serv_adr.sin_family = AF_INET;                  // IPv4 주소 체계
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);  // 명령행 인자로 받은 서버 IP 주소
	serv_adr.sin_port = htons(atoi(argv[2]));       // 명령행 인자로 받은 포트 번호 (네트워크 바이트 순서로 변환)
	
	// 서버에 연결 요청
	connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

	// 메시지 송수신 무한 루프
	while (1) {
		// 사용자에게 메시지 입력 요청
		fputs("Input message (Q to quit) : ", stdout);
		
		// 사용자로부터 메시지 입력 받기
		fgets(message, BUF_SIZE, stdin);

		// 입력된 메시지가 'q' 또는 'Q'인지 확인
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break ;                     // 종료 조건이면 루프 탈출
		
		// 서버로 메시지 전송
		write(sock, message, strlen(message));
		
		// 서버로부터 에코된 메시지 수신
		str_len = read(sock, message, BUF_SIZE - 1);
		
		// 수신된 메시지 끝에 null 문자 추가
		message[str_len] = 0;
		
		// 서버로부터 받은 메시지 출력
		printf("Message from server: %s", message);
	}
	
	// 소켓 닫기
	close(sock);
	return (0);
}
# Pipex 프로젝트 학습 자료

## 프로그램 요구사항

### 실행 형태
```bash
./pipex file1 cmd1 cmd2 file2
```

### 필수 조건
- **4개의 인자만을 무조건 받아야 함**
- `file1`과 `file2`는 파일 이름
- `cmd1`과 `cmd2`는 쉘 명령어
- 명령어들은 `""`로 구분

---

## 함수 공부

### 1. open 함수

```c
int open(const char *filepath, int flag);
int open(const char *filepath, int flag, mode_t mode);
```

#### 매개변수
- **filepath**: 열고자 하는 파일의 경로
- **flag**: 파일 열 때 사용할 옵션

#### Flag 옵션
- `O_RDONLY`: 읽기 모드 (Read Only)
- `O_WRONLY`: 쓰기 모드 (Write Only)
- `O_RDWR`: 읽기/쓰기 모드
- `O_CREAT`: 파일 생성
- `O_APPEND`: 파일을 쓰되 기존 파일의 맨 끝부터 이어 쓰기
- `O_TRUNC`: 파일을 초기화
- `O_EXCL`: `O_CREAT`와 함께 사용되며, 이미 파일이 존재한다면 에러를 리턴

#### mode_t mode
`O_CREAT` 옵션을 쓸 때 필수적으로 사용해야 하는 옵션으로, 파일의 접근 권한을 명시

**기본 값**
- 파일: `0666`
- 디렉토리: `0777`

**권한 옵션** (bitwise 연산으로 여러개를 동시에 사용 가능)
- `S_IRWXU`: 유저 읽기, 쓰기, 실행 권한
- `S_IRUSR`: 유저 읽기 권한
- `S_IWUSR`: 유저 쓰기 권한
- `S_IXUSR`: 유저 실행 권한
- `S_IRWXG`: 그룹 읽기, 쓰기, 실행 권한
- `S_IRGRP`: 그룹 읽기 권한
- `S_IWGRP`: 그룹 쓰기 권한
- `S_IXGRP`: 그룹 실행 권한
- `S_IRWXO`: 기타 사용자 읽기, 쓰기, 실행 권한
- `S_IROTH`: 기타 사용자 읽기 권한
- `S_IWOTH`: 기타 사용자 쓰기 권한
- `S_IXOTH`: 기타 사용자 실행 권한

#### 반환값
- 성공 시: `0`
- 실패 시: `-1` (errno 설정)

---

### 2. read 함수

```c
ssize_t read(int fd, void *buf, size_t size);
```

- **fd**: open 함수로 받아온 파일 디스크립터
- **buf**: 데이터를 저장할 버퍼
- **size**: 읽을 데이터의 크기

#### 반환값
- 성공 시: 읽어온 데이터의 크기
- 실패 시: `-1`

---

### 3. close 함수

```c
int close(int fd);
```

open으로 연 파일을 닫아주는 기능

---

### 4. perror 함수

```c
void perror(const char* errmsg);
```

errno 메시지에 덮어씌워서 출력하는 함수 (print error)

**관련 함수**
- `strerror()`: 오류 메시지 스트링에 errnum의 오류 번호를 맵핑하고, 스트링에 대한 포인터를 리턴

---

### 5. access 함수

파일 존재 및 접근 권한 확인 함수

```c
int access(const char *pathname, int mode);
```

#### 매개변수
- **pathname**: 체크하고자 할 디렉토리 또는 파일명
- **mode**: 적절한 마스크 값

#### mode 옵션
- `R_OK`: 파일 존재 여부, 읽기 권한 여부
- `W_OK`: 파일 존재 여부, 쓰기 권한 여부
- `X_OK`: 파일 존재 여부, 실행 권한 여부
- `F_OK`: 파일 존재 여부

#### 반환값
- 성공 시: `0`
- 실패 시: `-1`

---

### 6. dup 함수

파일 서술자 복제 함수

```c
int dup(int fd);
```

- fd로 전달받은 파일 서술자를 복제하여 반환
- 가장 낮은 서술자를 반환

#### 반환값
- 성공 시: 새 파일 서술자
- 실패 시: `-1`

---

### 7. dup2 함수

[참고 링크](https://hump-mountain.tistory.com/4)

```c
#include <unistd.h>
int dup2(int oldfd, int newfd);
```

- 새 서술자의 값을 `newfd`로 지정
- 만일 `newfd`가 이미 열려있으면 `newfd`를 닫은 후 복제

#### 특징
**리다이렉션 구성 가능**
- 리다이렉션: 표준 입력을 키보드로 받고 표준 출력을 모니터로 주는 것이 아니라, 사용자가 임의로 표준 입출력 방향을 바꿔서 파일로부터 입력을 받거나 파일에 출력을 가능하게 해주는 명령어

#### dup vs dup2
- **dup**: FD를 복제하면 사용하지 않는 FD값이 자동으로 할당
- **dup2**: 사용자가 원하는 fd번호를 할당 가능. 그 번호가 이미 사용 중이라면 자동으로 그 파일을 닫은 다음 할당

#### 반환값
- 성공 시: 새로운 파일 디스크립터
- 실패 시: `-1`

---

### 8. execve 함수

#### exec 계열 함수란?
- 기존 실행 process 대신 executable file을 수행
- **새 프로세스를 생성하는 개념이 아님** (PID가 변하지 않음)
- 현재 process의 machine code, data, heap, stack은 새 program으로 대체
- 이 함수 호출 아래의 코드들은 비정상적인 에러가 발생하지 않는 한 수행되지 않음

#### exec 계열 함수들

```c
int execl(char const *path, char const *arg0, …);
int execle(char const *path, char const *arg0, …, char const *envp[]);
int execlp(char const *file, char const *arg0, …);
int execv(char const *path, char const *argv[]);
int execve(char const *path, char const *argv[], char const *envp[]);
int execvp(char const *file, char const *argv[]);
int fexecve(int fd, char *const argv[], char *const envp[]);
```

#### 함수명 뒤의 키워드 의미
- **e**: 새 process image에 환경 변수 배열에 대한 포인터를 넘겨줌
  - 실행하려는 프로그램이 환경변수를 사용한다면 e가 있는 함수 사용
  - 예: `echo $PATH` 같은 라인이 있다면 환경 변수 정보를 인자로 넘겨줘야 함

- **l**: command-line 인자를 독립적인 list 형태로 넘겨줌
  - 인자의 수가 가변적

- **p**: file 인자의 위치를 환경변수 PATH에서 찾아줌
  - 알아서 PATH라는 환경 변수에서 경로를 찾아서 실행
  - **pipex 프로젝트에서는 execve를 사용하므로 별도로 PATH를 찾아줘야 함**

- **v**: command-line 인자를 array 포인터로 넘김
  - 인자를 list 형태로 하나씩 넣어주는 l계열 함수와 달리 2차원 array로 인자를 넘겨줌

#### execve 함수

```c
#include <unistd.h>
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

pathname에 해당하는 program을 현재 process를 대체하여 실행

#### 매개변수
- **pathname**: binary executable이거나 script 파일이어야 함
- **argv**: new program에 command-line arguments로 넘겨줄 문자열들의 array pointer
- **envp**: new program에 환경변수로 넘겨줄 문자열들의 array pointer

#### 반환값
- 실패 시: `-1`

---

### 9. exit 함수

```c
void exit(int status);
```

#### 동작 과정
1. `atexit` 함수로 등록한 종료 핸들러가 있다면 이 핸들러를 모두 처리
2. 표준 입출력 스트림을 닫는 작업 수행
3. 커널의 종료작업 실행
   - 프로세스가 사용하던 메모리를 해제
   - 열어놓았던 파일의 descriptor 등을 닫음

---

### 10. fork 함수

[참고 링크](https://codetravel.tistory.com/23)

```c
pid_t fork(void);
```

#### 특징
- fork 함수를 호출하는 프로세스는 **부모 프로세스**
- 새롭게 생성되는 프로세스는 **자식 프로세스**
- 자식 프로세스는 부모 프로세스의 메모리를 그대로 복사하여 가짐
- fork 함수 호출 이후 코드부터 각자의 메모리를 사용하여 실행

#### 반환값
- **부모 프로세스**: 자식 프로세스의 PID 값 (0보다 큼)
- **자식 프로세스**: `0`

프로세스의 메모리 공간의 값은 서로 다름

---

### 11. pipe 함수

[참고 링크](https://nomad-programmer.tistory.com/110)

```c
int fd[2];
if (pipe(fd) == -1) {
    fprintf(stderr, "error");
}
```

#### 특징
- pipe 함수는 파이프를 생성하고 만들어진 디스크립터를 알려줌
- **fd[1]**: 파이프에 쓰는 디스크립터
- **fd[0]**: 파이프로부터 읽는 디스크립터

#### 사용 예시
자식 프로세스에서는 파이프의 읽는 쪽인 `fd[0]`을 닫고, 표준 출력이 `fd[1]` 디스크립터가 가리키는 스트림을 가리키게 변경

---

### 12. wait 함수

#### 동작
1. 자식 프로세스가 동작 중이면 호출이 차단되어 상태를 얻어올 때까지 대기
2. `wait()` 함수 호출자가 시그널을 받을 때까지 대기
3. 자식 프로세스가 종료된 상태라면 즉시 호출이 반환되어 상태를 얻음
   - 이때 wait 함수는 자식 프로세스의 프로세스 ID를 반환
4. 자식 프로세스가 없다면 호출이 즉시 반환되며 에러값을 반환

---

### 13. waitpid 함수

```c
pid_t waitpid(pid_t pid, int *statloc, int options);
```

#### 첫 번째 인자 (pid)
- **pid == -1**: 임의의 자식 프로세스를 기다림
- **pid > 0**: 프로세스 ID가 pid인 자식 프로세스를 기다림
- **pid < -1**: 프로세스 그룹 ID가 pid의 절댓값과 같은 자식 프로세스를 기다림
- **pid == 0**: waitpid를 호출한 프로세스의 프로세스 그룹 PID와 같은 프로세스 그룹 ID를 가진 프로세스를 기다림

#### 두 번째 인자 (statloc)
상태 정보를 저장할 포인터

#### 세 번째 인자 (options)
대기 옵션 설정
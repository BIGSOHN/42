# 함수 레퍼런스

미니쉘 구현에 사용되는 주요 시스템 함수들에 대한 레퍼런스입니다.

## 목차
- [readline](#1-readline-함수)
- [rl_clear_history](#2-rl_clear_history-함수)
- [rl_on_new_line](#3-rl_on_new_line-함수)
- [rl_replace_line](#4-rl_replace_line-함수)
- [rl_redisplay](#5-rl_redisplay-함수)
- [add_history](#6-add_history-함수)
- [access](#7-access-함수)
- [open](#8-open-함수)
- [read](#9-read-함수)
- [close](#10-close-함수)
- [fork](#11-fork-함수)
- [wait](#12-wait-함수)
- [waitpid](#13-waitpid-함수)
- [wait3](#14-wait3-함수)
- [wait4](#15-wait4-함수)
- [getcwd](#16-getcwd-함수)
- [execve](#17-execve-함수)
- [dup](#18-dup-함수)
- [dup2](#19-dup2-함수)
- [pipe](#20-pipe-함수)
- [opendir](#21-opendir-함수)
- [readdir](#22-readdir-함수)
- [closedir](#23-closedir-함수)
- [strerror](#24-strerror-함수)
- [perror](#25-perror-함수)
- [getenv](#26-getenv-함수)

---

## 1. readline 함수

```c
char *readline(const char *str);
```

#### 기능
- `str`을 출력하고 프롬프트를 열어서 표준 입력으로 문자열을 입력받습니다.
- 개행을 받으면 지금까지 입력된 문자열을 리턴합니다.
- 입력받은 문자열을 저장하고 그 메모리 주소를 반환합니다.

#### 반환값
- 정상: 입력받은 문자열의 주소
- EOF를 만나면: `NULL`

---

## 2. rl_clear_history 함수

```c
void rl_clear_history(void);
```

#### 기능
- 현재 history를 지웁니다.

---

## 3. rl_on_new_line 함수

```c
int rl_on_new_line(void);
```

#### 기능
- `rl_redisplay`를 실행하기 위해 필요한 함수입니다.
- 라인을 출력한 후 새 라인(빈 라인)으로 이동했다고 업데이트 기능에 알립니다.
- 개행문자 출력 이후에 이용됩니다.

#### 반환값
- 정상 수행: `0`
- 실패: `-1`

---

## 4. rl_replace_line 함수

```c
void rl_replace_line(const char *text, int clear_undo);
```

#### 기능
- `rl_line_buffer`의 내용을 `text`라는 문자열로 바꿉니다.
- 가능한 경우 포인트와 마크가 유지됩니다.

#### 매개변수
- **text**: 대체할 문자열
- **clear_undo**: 내부적으로 유지 중인 `undo_list`를 초기화할지의 여부를 결정
  - `0`: 초기화하지 않음
  - 이외의 값: 초기화함

---

## 5. rl_redisplay 함수

```c
void rl_redisplay(void);
```

#### 기능
- 현재 `rl_line_buffer`의 컨텐츠를 반영하여 현재 화면에 표시되는 내용을 변경합니다.
- 사용자가 입력하고 유지 중인 `rl_line_buffer`의 값을 프롬프트와 함께 출력합니다.
- 이때 프롬프트 값은 `readline` 함수에 프롬프트로 준 문자열로 이동합니다.
- 시그널을 받았을 때의 상황에서 `rl_redisplay`를 이용하게 됩니다.

#### 주의사항
- `rl_replace_line`을 호출하지 않으면 작동하지 않습니다.
- `readline` 함수의 인자로 넣은 문자열을 다시 출력합니다.

---

## 6. add_history 함수

```c
int add_history(const char *);
```

#### 기능
- 인자에 넣은 문자열을 history로 저장합니다.
- 프롬프트가 열린 상태에서 키보드 방향키 위/아래를 통해 이제껏 프롬프트에 입력한 문자열을 불러올 수 있습니다.
- 스택처럼 가장 마지막에 넣은 문자열부터 불러옵니다.

---

## 7. access 함수

```c
int access(const char *pathname, int mode);
```

#### 기능
파일 존재 및 접근 권한 확인 함수

#### 매개변수
- **pathname**: 체크하고자 할 디렉토리 또는 파일명
- **mode**: 적절한 마스크 값

#### mode 옵션
- `R_OK`: 파일 존재 여부, 읽기 권한 여부
- `W_OK`: 파일 존재 여부, 쓰기 권한 여부
- `X_OK`: 파일 존재 여부, 실행 권한 여부
- `F_OK`: 파일 존재 여부

#### 반환값
- 성공: `0`
- 실패: `-1`

---

## 8. open 함수

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
- `O_APPEND`: 파일을 쓰되 기존 파일의 맨 끝부터 이어 쓰는 기능
- `O_TRUNC`: 파일 초기화
- `O_EXCL`: `O_CREAT`와 함께 사용되며, 이미 파일이 존재한다면 에러를 리턴

#### mode_t mode
`O_CREAT` 옵션을 쓸 때 필수적으로 사용해야 하는 옵션으로, 파일의 접근 권한을 명시

**기본 값**
- 파일: `0666`
- 디렉토리: `0777`

**권한 옵션** (bitwise 연산으로 여러 개를 동시에 사용 가능)
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
- 성공: `0`
- 실패: `-1` (errno 설정)

---

## 9. read 함수

```c
ssize_t read(int fd, void *buf, size_t size);
```

#### 기능
- `fd`는 `open` 함수로 받아온 파일 디스크립터이며 이를 통해 파일을 구분합니다.
- `size` 크기만큼의 데이터를 읽은 후 `*buf` 저장공간에 할당합니다.

#### 반환값
- 성공: 읽어온 데이터의 크기
- 실패: `-1`

---

## 10. close 함수

```c
int close(int fd);
```

#### 기능
- `open`으로 연 파일을 닫아주는 기능

---

## 11. fork 함수

```c
pid_t fork(void);
```

#### 기능
- fork 함수를 호출하는 프로세스는 **부모 프로세스**가 됩니다.
- 새롭게 생성되는 프로세스는 **자식 프로세스**가 됩니다.
- 자식 프로세스는 부모 프로세스의 메모리를 그대로 복사하여 가집니다.
- fork 함수 호출 이후 코드부터 각자의 메모리를 사용하여 실행됩니다.

#### 반환값
- **부모 프로세스**: 자식 프로세스의 PID 값 (0보다 큼)
- **자식 프로세스**: `0`

프로세스의 메모리 공간의 값은 서로 다릅니다.

---

## 12. wait 함수

```c
wait(int *status);
```

#### 매개변수
- **status**: 종료 상태를 담을 포인터 (받을 필요가 없다면 `0`을 입력)

#### 반환값
- **pid**: 성공 시 종료된 child process의 pid 값
- **-1**: 실패 시

---

## 13. waitpid 함수

[참고 링크](https://tempdev.tistory.com/42)

```c
pid_t waitpid(pid_t pid, int *status, int options);
```

#### 기능
`wait`와 달리 원하는 pid의 child process를 기다릴 수 있습니다.

#### 첫 번째 인자 (pid)
- **pid == -1**: 임의의 자식 프로세스를 기다림
- **pid > 0**: 프로세스 ID가 pid인 자식 프로세스를 기다림
- **pid < -1**: 프로세스 그룹 ID가 pid의 절댓값과 같은 자식 프로세스를 기다림
- **pid == 0**: waitpid를 호출한 프로세스의 프로세스 그룹 pid와 같은 프로세스 그룹 ID를 가진 프로세스를 기다림

#### 두 번째 인자 (status)
`wait`에서의 status처럼 waitpid에 의해 기다려진 프로세스의 정보를 담게 됩니다.

#### 세 번째 인자 (options)
waitpid의 동작을 설정할 수 있습니다. 설정하지 않을 경우 `0`입니다.

**옵션**:
- `WNOHANG`: 기다리고자 하는 pid의 프로세스에 대해 모두 종료되지 않았으나 기다리지 않고 waitpid 이후의 코드를 실행하고자 할 때 사용. 기다리지 않았을 경우 waitpid의 반환값은 `0`
- `WUNTRACED`: Stop 된 process들에 대해서도 waitpid에서 처리
- `WCONTINUED`: Continue 된 process들에 대해서도 waitpid에서 처리

#### 반환값
- **pid > 0**: 성공할 때 status가 받아진 프로세스의 pid를 반환
- **0**: `WNOHANG` 옵션이 적용되어 있을 때, 프로세스가 종료되거나 상태가 변하지 않아 status를 받을 수 없을 때
- **-1**: 실패할 경우

`wait`가 종료된 child process들만 처리를 하였던 것에 비해 `waitpid`는 `WUNTRACED`와 `WCONTINUED` 옵션을 통하여 child process가 stop 하거나 다시 continue 하는 경우도 처리합니다.

---

## 14. wait3 함수

```c
pid_t wait3(int *statloc, int options, struct rusage *rusage);
```

#### 매개변수
- **statloc**: 자식 프로세스의 종료 상태를 나타내는 정보를 담아줍니다.
- **options**: 프로세스의 종료 상태 체크 시 옵션을 걸 수 있습니다.
- **rusage**: 자식 프로세스의 리소스 사용량에 대한 정보가 담깁니다.

#### 반환값
- 성공: 프로세스 ID
- 에러: `-1`
- 함수가 `WNOHANG` 옵션으로 실행되었고, 자식 프로세스가 아직 종료되지 않았을 때: `0`

---

## 15. wait4 함수

```c
pid_t wait4(pid_t pid, int *statloc, int options, struct rusage *rusage);
```

#### 매개변수
- **pid**: pid에 해당하는 프로세스만을 기다립니다.
- **statloc**: 자식 프로세스의 종료 상태를 나타내는 정보를 담아줍니다.
- **options**: 프로세스의 종료 상태 체크 시 옵션을 걸 수 있습니다.
- **rusage**: 자식 프로세스의 리소스 사용량에 대한 정보가 담깁니다.

#### 반환값
- 성공: 프로세스 ID
- 에러: `-1`
- 함수가 `WNOHANG` 옵션으로 실행되었고, 자식 프로세스가 아직 종료되지 않았을 때: `0`

---

## 16. getcwd 함수

```c
#include <unistd.h>
char *getcwd(char *buffer, size_t size);
```

#### 기능
- C언어에서 현재 디렉터리를 알려주는 함수
- 현재 작업하고 있는 디렉터리의 위치를 알려줍니다.

#### 매개변수
- **buffer**: 현재 디렉토리의 절대 경로를 저장할 버퍼의 주소
- **size**: 버퍼의 크기

#### 특징
- 버퍼의 주소가 NULL이면, `getcwd`는 직접 `malloc`으로 메모리를 할당하고 주소를 리턴합니다.

#### 반환값
- 성공: 현재 디렉토리 경로
- 실패: `NULL`

---

## 17. execve 함수

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

#### 기능
pathname에 해당하는 program을 현재 process를 대체하여 실행시킵니다.

#### 매개변수
- **pathname**: binary executable이거나 script여야 함
- **argv**: new program에 command-line arguments로 넘겨줄 문자열들의 array pointer
- **envp**: new program에 환경 변수로 넘겨줄 문자열들의 array pointer

#### 특징
- 매개변수로 들어온 경로에 위치한 파일을 실행해주는 시스템 콜 함수입니다.
- 파일은 반드시 바이너리 실행파일이거나 스크립트 파일이어야 합니다.

#### 반환값
- 실패: `-1`

---

## 18. dup 함수

```c
int dup(int fd);
```

#### 기능
파일 서술자 복제 함수

- `fd`로 전달받은 파일 서술자를 복제하여 반환합니다.
- 가장 낮은 서술자를 반환합니다.

#### 반환값
- 성공: 새 파일 서술자
- 실패: `-1`

---

## 19. dup2 함수

```c
int dup2(int oldfd, int newfd);
```

#### 기능
- 새 서술자의 값을 `newfd`로 지정합니다.
- 만일 `newfd`가 이미 열려있으면 `newfd`를 닫은 후 복제가 됩니다.
- **리다이렉션을 구성할 수 있습니다.**

#### 반환값
- 성공: 새로운 파일 디스크립터
- 실패: `-1`

---

## 20. pipe 함수

```c
int fd[2];

if (pipe(fd) == -1)
{
    fprintf(stderr, "error");
}
```

#### 기능
- pipe 함수는 파이프를 생성하고 만들어진 디스크립터를 알려줍니다.
- **fd[1]**: 파이프에 쓰는 디스크립터
- **fd[0]**: 파이프로부터 읽는 디스크립터

#### 사용 예시
자식 프로세스에서는 파이프의 읽는 쪽인 `fd[0]`을 닫고, 표준 출력이 `fd[1]` 디스크립터가 가리키는 스트림을 가리키게 변경합니다.

---

## 21. opendir 함수

```c
DIR *opendir(const char *name);
```

#### 기능
- 열고자 하는 디렉토리 경로를 입력으로 받습니다.

#### 반환값
- 성공: `DIR` 구조체에 대한 포인터
- 실패: `NULL` (해당 디렉토리 경로가 존재하지 않거나 퍼미션 등의 이유)

---

## 22. readdir 함수

```c
struct dirent *readdir(DIR *dir);
```

#### 기능
- 한 번에 하나의 엔트리만을 읽어들입니다.
- 디렉토리 포인터 `dir`가 가리키는 곳, 즉 해당 디렉토리에서 디렉토리 엔트리에 대한 포인터를 반환합니다.
- 해당 디렉토리에서 하나의 엔트리 정보가 구조체 포인터 `struct dirent*`에 포함되어 반환됩니다.

#### 반환값
- 정상: 디렉토리 엔트리 포인터
- 더 이상의 엔트리가 없으면: `NULL`

---

## 23. closedir 함수

```c
int closedir(DIR *dp);
```

#### 기능
- 열려있는 디렉토리를 안전하게 닫아줍니다.

---

## 24. strerror 함수

```c
char *strerror(int errnum);
```

#### 기능
- 오류 메시지 스트링에 `errnum`의 오류 번호를 맵핑합니다.
- NULL 값은 리턴하지 않습니다.

#### 반환값
- 인수 `errnum`에 전달된 오류 코드를 설명하는 문자열에 대한 포인터

---

## 25. perror 함수

```c
void perror(const char *string);
```

#### 기능
- 오류 메시지를 `stderr`로 출력합니다.
- `string`이 NULL이 아니고 NULL 문자를 가리키지 않는 경우, `string`에서 지정된 스트링은 표준 오류 스트림으로 출력되고 콜론과 간격이 이어집니다.
- `errno`의 값과 연관된 메시지가 출력된 다음 줄 바꾸기 문자가 이어집니다.

---

## 26. getenv 함수

환경 변수 값을 가져오는 함수입니다.

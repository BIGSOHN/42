# Minishell

Bash의 핵심 기능을 구현한 Unix 커맨드라인 인터프리터 프로젝트

## 프로젝트 개요

Minishell은 실제 shell의 동작 방식을 이해하고 구현하는 것을 목표로 하는 2인 팀 프로젝트입니다. 프롬프트 표시, 명령 실행, 파이프라인, 리다이렉션, 환경 변수, 시그널 처리 등 shell의 핵심 기능을 C언어로 구현했습니다.

### 팀 역할 분배
- **손승모**: 렉서/파서 (입력 처리 시스템) 전담, Built-in 함수 구현
- **한웅희**: 실행 로직 및 시그널 처리

## 주요 기능

### 1. 입력 처리 시스템 (Lexer & Parser)
- **상태 머신 기반 토크나이저**: 입력 문자열을 의미 있는 토큰으로 분리
- **따옴표 처리**:
  - 작은따옴표(`'`): 내부의 모든 메타문자를 일반 문자로 처리
  - 큰따옴표(`"`): `$`를 제외한 메타문자를 일반 문자로 처리
- **환경 변수 확장**: `$VAR`, `$?` (종료 상태 코드) 처리
- **문법 검증**: 파이프, 리다이렉션 등의 구문 오류 탐지

### 2. Built-in 명령어
다음 내장 명령어를 직접 구현했습니다:
- `echo` (옵션 `-n` 지원)
- `cd` (상대/절대 경로)
- `pwd`
- `export` (환경 변수 설정)
- `unset` (환경 변수 삭제)
- `env` (환경 변수 출력)
- `exit` (종료 코드 처리)

### 3. 리다이렉션
- `<` : 입력 리다이렉션
- `>` : 출력 리다이렉션
- `<<` : Here Document (구분자까지 입력 읽기)
- `>>` : 추가 모드 출력 리다이렉션

### 4. 파이프라인
- `|` 연산자를 통한 다중 명령어 연결
- 각 명령의 출력이 다음 명령의 입력으로 전달

### 5. 시그널 처리
Bash와 동일한 방식으로 시그널 처리:
- `Ctrl-C`: 새 프롬프트 표시
- `Ctrl-D`: 쉘 종료
- `Ctrl-\`: 무시

## 빌드 및 실행

### 요구사항
- GCC 컴파일러
- GNU Readline 라이브러리

### 빌드
```bash
make
```

### 실행
```bash
./minishell
```

### 정리
```bash
make clean   # 오브젝트 파일 삭제
make fclean  # 실행 파일 포함 전체 삭제
make re      # 재빌드
```

## 사용 예시

```bash
minishell$ echo "Hello, World!"
Hello, World!

minishell$ export USER=ssohn
minishell$ echo $USER
ssohn

minishell$ ls -la | grep minishell | wc -l
1

minishell$ cat < input.txt | grep "pattern" > output.txt

minishell$ cd /tmp && pwd
/tmp

minishell$ echo "Hello" > file.txt
minishell$ cat << EOF >> file.txt
> Line 1
> Line 2
> EOF
minishell$ cat file.txt
Hello
Line 1
Line 2
```

## 기술적 하이라이트

### 렉서/파서 아키텍처
프로그램은 3단계 파이프라인으로 구성됩니다:

1. **Lexer (렉서)**: 입력 문자열을 토큰 리스트로 변환
   - 따옴표 처리, 환경 변수 확장
   - 연산자 및 구분자 인식

2. **Parser (파서)**: 토큰을 명령 구조체로 변환
   - 구문 오류 검증
   - 명령, 인자, 리다이렉션 분리

3. **Executor (실행기)**: 파싱된 명령 구조체를 실행
   - 프로세스 생성 및 관리
   - 파이프라인 구성

### 프로세스 관리
- `fork()`: 자식 프로세스 생성
- `execve()`: 외부 명령 실행
- `waitpid()`: 프로세스 상태 관리 및 종료 코드 수집

### 파일 디스크립터 관리
- `pipe()`: 프로세스 간 통신
- `dup2()`: 입출력 리다이렉션 구현
- 각 명령마다 독립적인 입출력 설정

## 프로젝트 구조

```
minishell/
├── Makefile
├── minishell.h           # 헤더 파일
├── main.c                # 메인 함수
│
├── lexer.c               # 토큰화
├── lexer_utils.c         # 렉서 유틸리티
├── lexer_utils2.c
│
├── parser.c              # 구문 분석
├── parser2.c
├── parser_utils.c
├── syntax_check.c        # 구문 검증
│
├── generator.c           # 명령 구조체 생성
├── generator2.c
├── generator_*.c         # 제너레이터 유틸리티
│
├── built_in_func_*.c     # 내장 명령어 구현
├── execute_command*.c    # 명령 실행
├── shell_command*.c      # 쉘 명령 실행
├── simple_command*.c     # 단순 명령 처리
│
├── file_redirection*.c   # 리다이렉션
├── signal.c              # 시그널 처리
├── terminal.c            # 터미널 설정
│
├── *list_utils*.c        # 리스트 자료구조 유틸리티
├── error_*.c             # 에러 처리
└── libft/                # 커스텀 C 라이브러리
```

## 기술 스택

- **언어**: C
- **라이브러리**: readline, libft (커스텀 C 라이브러리)
- **시스템 콜**: fork, execve, pipe, dup2, wait/waitpid, open, close, read, write, access
- **빌드 시스템**: Makefile
- **컴파일 옵션**: `-Wall -Wextra -Werror`

## 학습 포인트

이 프로젝트를 통해 다음을 학습했습니다:

1. **인터프리터 설계**: Lexing → Parsing → Evaluation 파이프라인
2. **프로세스 관리**: fork, exec, wait 시스템 콜을 통한 프로세스 제어
3. **파일 디스크립터**: 리다이렉션과 파이프 구현
4. **시그널 처리**: 비동기 이벤트 핸들링
5. **모듈화 설계**: 명확한 책임 분리와 인터페이스 정의
6. **팀 협업**: 역할 분담과 데이터 구조 설계를 통한 병렬 개발

## 추가 자료

프로젝트 학습 과정에서 정리한 상세한 함수 설명과 개념 정리는 [STUDY_GUIDE.md](./STUDY_GUIDE.md)를 참고하세요.

---

**42 Gyeongsan | Circle 3 Project | 2024**

# C++ Module 08 - Templated containers, iterators, algorithms

| 개념                  | 설명                                  | 대표적 예시                            |
| --------------------- | ------------------------------------- | -------------------------------------- |
| 컨테이너(Containers)  | 여러 요소를 저장하는 자료구조         | `vector`, `list`, `map`                |
| 이터레이터(Iterators) | 컨테이너의 요소를 순회하는 객체       | `container.begin()`, `container.end()` |
| 알고리즘(Algorithms)  | 요소 범위에 대해 작업을 수행하는 함수 | `std::find`, `std::sort`               |

## Exercise 00 : Easy find

### 함수 탬플릿 (Function Templates)

- 템플릿 함수는 여러 타입에 대해 동일한 알고리즘을 적용
- 'template <typename T>' 구문으로 선언
- 컴파일 시점에 필요한 타입으로 인스턴스화 됨
- ```cpp
  template
  typename T::iterator easyfind(T& container, int value) {
      return std::find(container.begin(), container.end(), value);
  }
  ``
  ```

### STL 알고리즘 - find

- 헤더 : '<algorithm>'
- 값을 찾지 못하면 끝 이터레이터 반환
- 사용 예 : 'std::find(container.begin(), container.end(), value)'
- 반환값 확인: `if (result == container.end()) // 못 찾음`

### 타입 명시

- C++ 컴파일러는 템플릿에서 T::iterator가 타입인지 변수인지 모름
- typename 키워드를 사용해서 이것은 타입이다 라고 명시적으로 알려줌

## Exercise 01 : Span

### 컨테이너 설계

- 고정 크기 컨테이너 구현
- 내부적으로 STL 컨테이너 사용 ('vector', 'array' 등)
  - vector와 array의 차이
  - | 특성   | vector                   | array                     |
    | ------ | ------------------------ | ------------------------- |
    | 크기   | 동적 변경 가능           | 컴파일 타임에 고정        |
    | 메모리 | 힙 할당                  | 스택 할당                 |
    | 성능   | 약간 느림 (동적 할당)    | 빠름                      |
    | 사용   | `std::vector<int> v(10)` | `std::array<int, 10> arr` |
- 메모리 관리 자동화

## Exercise 02 : Mutuated abomination

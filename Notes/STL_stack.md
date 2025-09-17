# std::stack 알아야 할 것 정리

`std::stack`은 `<stack>` 헤더에 정의된 컨테이너 어댑터로, LIFO (Last In, First Out) 구조를 제공합니다. 내부적으로 다른 컨테이너(기본적으로 `std::deque`)를 사용합니다.

## 기본 개념
- **LIFO**: 마지막에 넣은 요소가 먼저 나옵니다.
- **어댑터**: 자체 컨테이너가 아니고, 다른 컨테이너를 감싸서 인터페이스를 제공합니다.
- **기본 컨테이너**: `std::deque` (변경 가능).

## 내부 컨테이너 변경
`std::stack`은 템플릿 매개변수로 내부 컨테이너를 지정할 수 있습니다. 기본은 `std::deque`지만, `std::vector`나 `std::list`로 변경 가능합니다.

### 예시
```cpp
#include <stack>
#include <vector>
#include <list>

std::stack<int, std::vector<int>> s_vec;  // std::vector 기반
std::stack<int, std::list<int>> s_list;   // std::list 기반
std::stack<int> s_deque;                  // 기본 std::deque 기반
```

### 고려사항
- **std::vector**: 끝에 추가/삭제가 빠름, 중간 삽입/삭제는 느림.
- **std::list**: 양방향 삽입/삭제가 빠름, 임의 접근은 느림.
- **std::deque**: 양 끝 삽입/삭제가 빠름 (스택에 적합).
- 컨테이너는 `push_back`, `pop_back`, `back`을 지원해야 합니다.

## 생성자
```cpp
std::stack<T> s;                    // 빈 스택
std::stack<T, Container> s;         // 빈 스택, 사용자 정의 컨테이너
std::stack<T> s(other);             // 복사 생성자
std::stack<T> s = other;            // 복사 대입
std::stack<T> s(std::move(other));  // 이동 생성자
```

## 주요 멤버 함수
- `push(const T& value)` / `push(T&& value)`: 요소 추가 (맨 위에).
- `pop()`: 맨 위 요소 제거 (반환 없음).
- `top()`: 맨 위 요소 참조 (const 및 비-const 버전).
- `empty()`: 스택이 비었는지 확인 (bool).
- `size()`: 요소 개수 (size_type).
- `swap(std::stack& other)`: 두 스택 교환.

## 비교 연산자
- `==`, `!=`, `<`, `<=`, `>`, `>=`: 요소별 비교.

## 사용 예시
```cpp
#include <stack>
#include <iostream>

std::stack<int> s;
s.push(1);
s.push(2);
s.push(3);

std::cout << s.top();  // 3
s.pop();
std::cout << s.top();  // 2
std::cout << s.size(); // 2
```

## 주의사항
- `pop()`은 요소를 제거만 하고 반환하지 않습니다. `top()`으로 먼저 확인하세요.
- 스택이 비었을 때 `top()` 호출은 정의되지 않은 동작입니다. `empty()`로 확인하세요.
- 사용자 정의 컨테이너: `std::stack<int, std::vector<int>>`처럼 지정 가능 (단, 지원하는 연산 필요).
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않습니다.
# std::pair 알아야 할 것 정리

`std::pair`은 `<utility>` 헤더에 정의된 클래스 템플릿으로, 두 개의 값을 하나의 객체로 묶어 관리합니다. 맵, 튜플 등에서 자주 사용됩니다.

## 기본 개념
- **두 값 저장**: `first`와 `second` 멤버로 접근.
- **템플릿**: `std::pair<T1, T2>` 형태.
- **용도**: 관련된 두 값을 함께 반환하거나 저장할 때 유용.

## 생성자
```cpp
std::pair<int, std::string> p;                    // 기본 생성자 (기본값)
std::pair<int, std::string> p(1, "hello");       // 값 생성자
std::pair<int, std::string> p = {1, "hello"};    // 초기화 리스트
std::pair<int, std::string> p(other);            // 복사 생성자
std::pair<int, std::string> p(std::move(other)); // 이동 생성자
```

## 주요 멤버
- `first`: 첫 번째 값 (T1 타입).
- `second`: 두 번째 값 (T2 타입).

## 헬퍼 함수
- `std::make_pair(T1, T2)`: pair 생성 (타입 추론).
  ```cpp
  auto p = std::make_pair(1, "hello");  // std::pair<int, const char*>
  ```
- `std::tie`: 구조적 바인딩 전 C++11 방식.
  ```cpp
  int a; std::string b;
  std::tie(a, b) = p;  // p의 first/second를 a, b에 할당
  std::tie(std::ignore, b) = p;  // first 무시
  ```

## 비교 연산자
- `==`, `!=`: 요소별 비교.
- `<`, `<=`, `>`, `>=`: 사전순 비교 (first 먼저, 같으면 second).

## 사용 예시
```cpp
#include <utility>
#include <iostream>

std::pair<int, std::string> p = {1, "hello"};
std::cout << p.first << ", " << p.second;  // 1, hello

// make_pair
auto q = std::make_pair(2, "world");

// tie
int x; std::string y;
std::tie(x, y) = q;  // x=2, y="world"

// 구조적 바인딩 (C++17)
auto [a, b] = p;  // a=1, b="hello"
```

## 주의사항
- 타입 불일치: make_pair는 const char*가 std::string으로 변환될 수 있음.
- 비교: 사용자 정의 타입은 operator< 필요.
- C++11 전: tie로 구조적 바인딩 대체.
- 메모리: 작은 객체에 적합, 큰 객체는 tuple 고려.
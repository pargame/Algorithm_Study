# std::deque 알아야 할 것 정리

`<deque>` 헤더에 정의된 양방향 큐 컨테이너. 양 끝에서 효율적으로 요소를 추가/제거할 수 있습니다.

## 기본 개념
- **양방향 큐**: push_front/pop_front, push_back/pop_back 모두 O(1).
- **임의 접근**: []로 인덱스 접근 가능 (벡터처럼).
- **용도**: 큐/스택 구현, 양 끝 조작 빈번한 경우.

## 생성자
```cpp
std::deque<int> d;                    // 빈 데크
std::deque<int> d(5);                 // 크기 5, 기본값 0
std::deque<int> d(5, 10);             // 크기 5, 값 10
std::deque<int> d = {1, 2, 3};        // 초기화 리스트
std::deque<int> d(other);             // 복사 생성자
std::deque<int> d(std::move(other));  // 이동 생성자
std::deque<int> d(begin, end);        // 이터레이터 범위
```

## 주요 멤버 함수
- `size()`: 요소 수.
- `empty()`: 비었는지 확인.
- `push_front(const T&)` / `push_front(T&&)`: 앞에 추가.
- `push_back(const T&)` / `push_back(T&&)`: 뒤에 추가.
- `pop_front()`: 앞 요소 제거.
- `pop_back()`: 뒤 요소 제거.
- `insert(iterator pos, const T&)`: 위치에 삽입 (오버로딩 다양).
- `erase(iterator pos)` / `erase(iterator first, iterator last)`: 요소 삭제.
- `clear()`: 모든 요소 제거.
- `at(size_type pos)`: 범위 체크 인덱스 접근 (범위 초과 시 std::out_of_range 예외).
- `front()` / `back()`: 앞/뒤 요소 참조.

## 연산자
- `[]`: 인덱스 접근 (범위 체크 없음).
- `==`, `!=`, `<`, `<=`, `>`, `>=`: 요소별 비교.

## 기타 (이터레이터)
- `begin()`, `end()`: 순방향.
- `rbegin()`, `rend()`: 역방향.
- `cbegin()`, `cend()`: const 버전.

## 사용 예시
```cpp
#include <deque>
#include <iostream>

std::deque<int> d = {1, 2, 3};
d.push_front(0);  // {0, 1, 2, 3}
d.push_back(4);   // {0, 1, 2, 3, 4}
d.pop_front();    // {1, 2, 3, 4}
std::cout << d.front() << ", " << d.back();  // 1, 4
```

## 주의사항
- `[]` vs `at()`: at()은 예외, []는 정의되지 않은 동작.
- 메모리: 벡터보다 메모리 오버헤드 (청크 기반).
- 성능: 양 끝 효율적, 중간 삽입/삭제 느림.
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않음.
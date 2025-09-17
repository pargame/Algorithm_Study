# std::list 알아야 할 것 정리

`<list>` 헤더에 정의된 양방향 연결 리스트 컨테이너. 양 끝에서 효율적으로 요소를 추가/제거할 수 있습니다.

## 기본 개념
- **양방향 연결 리스트**: 노드 기반, 임의 접근 불가.
- **양 끝 효율**: push_front/pop_front, push_back/pop_back O(1).
- **용도**: 빈번한 삽입/삭제, 순차 접근.

## 생성자
```cpp
std::list<int> l;                    // 빈 리스트
std::list<int> l(5);                 // 크기 5, 기본값 0
std::list<int> l(5, 10);             // 크기 5, 값 10
std::list<int> l = {1, 2, 3};        // 초기화 리스트
std::list<int> l(other);             // 복사 생성자
std::list<int> l(std::move(other));  // 이동 생성자
std::list<int> l(begin, end);        // 이터레이터 범위
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
- `front()` / `back()`: 앞/뒤 요소 참조.
- `splice(iterator pos, list& other)`: 다른 리스트 병합.
- `sort()`: 리스트 정렬.
- `reverse()`: 리스트 뒤집기.

## 연산자
- `==`, `!=`, `<`, `<=`, `>`, `>=`: 요소별 비교.

## 기타 (이터레이터)
- `begin()`, `end()`: 순방향.
- `rbegin()`, `rend()`: 역방향.
- `cbegin()`, `cend()`: const 버전.

## 사용 예시
```cpp
#include <list>
#include <iostream>

std::list<int> l = {1, 2, 3};
l.push_front(0);  // {0, 1, 2, 3}
l.push_back(4);   // {0, 1, 2, 3, 4}
l.pop_front();    // {1, 2, 3, 4}
std::cout << l.front() << ", " << l.back();  // 1, 4
```

## 주의사항
- 임의 접근 불가 ([] 없음).
- 메모리: 노드당 오버헤드.
- 성능: 중간 삽입/삭제 효율적, 검색 느림.
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않음.
# std::vector 알아야 할 것 정리

`std::vector`은 `<vector>` 헤더에 정의된 동적 배열 컨테이너로, 크기를 동적으로 조절할 수 있습니다. 연속 메모리에 요소를 저장합니다.

## 기본 개념
- **동적 배열**: 크기가 자동으로 늘어남.
- **연속 메모리**: 캐시 친화적, 임의 접근 O(1).
- **용도**: 배열처럼 사용하지만, 크기 변경 가능.

## 생성자
```cpp
std::vector<int> v;                    // 빈 벡터
std::vector<int> v(5);                 // 크기 5, 기본값 0
std::vector<int> v(5, 10);             // 크기 5, 값 10
std::vector<int> v = {1, 2, 3};        // 초기화 리스트
std::vector<int> v(other);             // 복사 생성자
std::vector<int> v(std::move(other));  // 이동 생성자
std::vector<int> v(begin, end);        // 이터레이터 범위
```

## 주요 멤버 함수
- `size()`: 현재 요소 수.
- `capacity()`: 할당된 메모리 크기.
- `empty()`: 비었는지 확인.
- `reserve(size_type n)`: 최소 n개의 요소를 저장할 수 있도록 메모리를 예약합니다. capacity를 늘리지만 size는 변경하지 않습니다. 빈번한 push_back 등으로 인한 재할당을 방지하여 성능을 향상시킬 수 있습니다.
- `resize(size_type n)`: 크기 변경 (기본값 추가).
- `assign(size_type n, const T& value)`: n개의 value로 벡터 채움.
- `assign(InputIt first, InputIt last)`: 이터레이터 범위로 벡터 채움.
- `assign(std::initializer_list<T>)`: 초기화 리스트로 벡터 채움.
- `push_back(const T&)` / `push_back(T&&)`: 끝에 추가.
- `pop_back()`: 끝 요소 제거.
- `insert(const_iterator pos, const T& value)`: 위치에 값 삽입 (반환: 삽입된 요소 이터레이터).
- `insert(const_iterator pos, T&& value)`: 이동 삽입.
- `insert(const_iterator pos, size_type count, const T& value)`: count 개의 값 삽입.
- `insert(const_iterator pos, InputIt first, InputIt last)`: 범위 삽입.
- `insert(const_iterator pos, std::initializer_list<T>)`: 초기화 리스트 삽입.
- `erase(const_iterator pos)`: 위치 요소 삭제 (반환: 삭제된 다음 요소 이터레이터).
- `erase(const_iterator first, const_iterator last)`: 범위 삭제.
- `clear()`: 모든 요소 제거.
- `at(size_type pos)`: 범위 체크 인덱스 접근 (범위 초과 시 std::out_of_range 예외 던짐).
- `front()` / `back()`: 첫/끝 요소 참조.

## 연산자
- `[]`: 인덱스 접근 (범위 체크 없음).
- `==`, `!=`, `<`, `<=`, `>`, `>=`: 요소별 비교.

## 이터레이터
- `begin()`, `end()`: 순방향.
- `rbegin()`, `rend()`: 역방향.
- `cbegin()`, `cend()`: const 버전.

## 사용 예시
```cpp
#include <vector>
#include <iostream>

std::vector<int> v = {1, 2, 3};
v.push_back(4);  // {1, 2, 3, 4}
v.pop_back();    // {1, 2, 3}
std::cout << v[0] << ", " << v.at(1);  // 1, 2

for (auto& elem : v) elem *= 2;  // {2, 4, 6}
```

## 주의사항
- `[]` vs `at()`: `at()`은 out_of_range 예외, `[]`는 정의되지 않은 동작.
- 재할당: push_back 시 capacity 초과하면 전체 복사 (비효율).
- reserve() 사용: 빈번한 크기 변경 시 미리 용량 할당.
- 메모리: 연속이라 캐시 효율 좋음, 하지만 큰 객체는 deque 고려.
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않음.
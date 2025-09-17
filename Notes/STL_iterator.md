# std::iterator 알아야 할 것 정리

`<iterator>` 헤더에 정의된 이터레이터 관련 클래스와 함수. 컨테이너를 순회하는 데 사용됩니다.

## 기본 개념
- **이터레이터**: 포인터처럼 컨테이너 요소를 가리키고 이동.
- **카테고리**: 입력, 출력, 전진, 양방향, 임의 접근.
- **용도**: 알고리즘과 컨테이너 연결.

## 이터레이터 카테고리
- **입력 이터레이터**: 읽기 전용, ++ 가능 (예: istream_iterator).
- **출력 이터레이터**: 쓰기 전용, ++ 가능 (예: ostream_iterator).
- **전진 이터레이터**: 읽기/쓰기, ++ 가능, 다중 패스 (예: forward_list).
- **양방향 이터레이터**: ++/-- 가능 (예: list, set).
- **임의 접근 이터레이터**: []로 인덱스 접근, +n 가능 (예: vector, deque).

## 주요 함수
- `std::advance(it, n)`: 이터레이터를 n만큼 이동.
- `std::next(it, n)`: it + n의 이터레이터 반환 (C++11).
- `std::prev(it, n)`: it - n의 이터레이터 반환 (C++11).
- `std::distance(first, last)`: 두 이터레이터 간 거리.
- `std::begin(container)`: 컨테이너 시작 이터레이터.
- `std::end(container)`: 컨테이너 끝 이터레이터.
- `std::rbegin(container)`: 역방향 시작.
- `std::rend(container)`: 역방향 끝.

## 연산자
- `++`: 다음 요소.
- `--`: 이전 요소 (양방향 이상).
- `*`: 역참조.
- `->`: 멤버 접근.
- `==`, `!=`: 비교.
- `+`, `-`, `[]`: 임의 접근.

## 기타
- **어댑터**: `std::reverse_iterator`, `std::back_insert_iterator` 등.
- **스트림 이터레이터**: `std::istream_iterator`, `std::ostream_iterator`.

## 사용 예시
```cpp
#include <vector>
#include <iterator>
#include <iostream>

std::vector<int> v = {1, 2, 3};
auto it = std::begin(v);
std::advance(it, 2);  // it points to 3
std::cout << *it;     // 3
auto dist = std::distance(std::begin(v), std::end(v));  // 3
```

## 주의사항
- 카테고리에 맞는 연산만 사용 (임의 접근에서만 []).
- 끝 이터레이터는 역참조 금지.
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않음.
# std::map 알아야 할 것 정리

`<map>` 헤더에 정의된 정렬된 연관 컨테이너. 키-값 쌍을 저장하며, 키로 자동 정렬됩니다.

## 기본 개념
- **연관 컨테이너**: 키-값 쌍, 키로 정렬 (레드블랙 트리).
- **고유 키**: 중복 키 불가.
- **용도**: 빠른 검색, 정렬된 데이터.

## 생성자
```cpp
std::map<int, std::string> m;                    // 빈 맵
std::map<int, std::string> m = {{1, "one"}, {2, "two"}};  // 초기화 리스트
std::map<int, std::string> m(other);             // 복사 생성자
std::map<int, std::string> m(std::move(other));  // 이동 생성자
std::map<int, std::string> m(begin, end);        // 이터레이터 범위
```

## 주요 멤버 함수
- `size()`: 요소 수.
- `empty()`: 비었는지 확인.
- `insert(const value_type&)`: 키-값 쌍 삽입.
- `erase(key_type key)` / `erase(iterator pos)`: 요소 삭제.
- `clear()`: 모든 요소 제거.
- `find(key_type key)`: 키로 요소 찾기 (이터레이터 반환).
- `count(key_type key)`: 키 개수 (0 또는 1).
- `lower_bound(key_type key)`: 키 이상 첫 요소.
- `upper_bound(key_type key)`: 키 초과 첫 요소.
- `equal_range(key_type key)`: lower/upper 쌍.
- `at(key_type key)`: 키로 값 접근 (범위 초과 시 std::out_of_range).
- `operator[](key_type key)`: 키로 값 접근 (없으면 기본값 삽입).

## 연산자
- `==`, `!=`, `<`, `<=`, `>`, `>=`: 키별 비교.

## 기타 (이터레이터)
- `begin()`, `end()`: 순방향 (키 순).
- `rbegin()`, `rend()`: 역방향.
- `cbegin()`, `cend()`: const 버전.

## 사용 예시
```cpp
#include <map>
#include <iostream>

std::map<int, std::string> m;
m[1] = "one";
m.insert({2, "two"});
std::cout << m[1];  // "one"
std::cout << m.at(2);  // "two"
auto it = m.find(1);
if (it != m.end()) std::cout << it->second;  // "one"
```

## 주의사항
- `[]` vs `at()`: at()은 예외, []는 기본값 삽입.
- 정렬: 키 타입에 operator< 필요.
- 성능: 삽입/삭제/검색 O(log n).
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않음.
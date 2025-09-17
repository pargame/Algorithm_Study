# std::sort 오버로딩 시그니처 정리

`std::sort`은 `<algorithm>` 헤더에 정의된 함수로, 범위의 요소를 정렬합니다. 두 가지 주요 오버로딩이 있습니다: 기본 오름차순과 사용자 정의 비교자.

## 1. 기본 오름차순 오버로딩
요소 타입의 `operator<`를 사용하여 오름차순으로 정렬합니다.

### 시그니처
```cpp
template<class RandomIt>
void sort(RandomIt first, RandomIt last);
```

### 매개변수
- `first`, `last`: 정렬할 범위의 시작과 끝 이터레이터 (RandomIt, 임의 접근 이터레이터).

### 반환값
- 없음 (void). 범위가 제자리에서 정렬됩니다.

### 예시
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> v = {3, 1, 4, 1, 5};
std::sort(v.begin(), v.end());
// v: {1, 1, 3, 4, 5}
```

## 2. 사용자 정의 비교자 오버로딩
제공된 비교 함수를 사용하여 정렬합니다.

### 시그니처
```cpp
template<class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);
```

### 매개변수
- `first`, `last`: 정렬할 범위의 시작과 끝 이터레이터 (RandomIt).
- `comp`: 비교 함수 (Compare, 두 요소를 비교하는 함수 객체, 람다 등). `comp(a, b)`가 true면 a가 b보다 앞에 옴.

### 반환값
- 없음 (void). 범위가 제자리에서 정렬됩니다.

### 예시
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> v = {3, 1, 4, 1, 5};
std::sort(v.begin(), v.end(), std::greater<int>());  // 내림차순
// v: {5, 4, 3, 1, 1}

std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });  // 람다로 내림차순
```

## std::stable_sort
`std::stable_sort`은 `<algorithm>` 헤더에 정의된 함수로, 범위의 요소를 안정적으로 정렬합니다. 동일한 요소의 상대적 순서를 유지합니다.

### 시그니처
```cpp
template<class RandomIt>
void stable_sort(RandomIt first, RandomIt last);

template<class RandomIt, class Compare>
void stable_sort(RandomIt first, RandomIt last, Compare comp);
```

### 매개변수
- `first`, `last`: 정렬할 범위의 시작과 끝 이터레이터 (RandomIt).
- `comp`: 비교 함수 (Compare, 선택적).

### 반환값
- 없음 (void). 범위가 제자리에서 안정 정렬됩니다.

### 예시
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<std::pair<int, int>> v = {{3, 1}, {1, 2}, {3, 3}};
std::stable_sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
    return a.first < b.first;  // first 기준 정렬, second 순서 유지
});
// v: {{1, 2}, {3, 1}, {3, 3}} (3의 순서 유지)
```

### 추가 설명
- 시간 복잡도: O(n log n) 최악.
- 메모리: 추가 메모리 사용 가능.
- 안정성: 동일 요소 순서 유지.

## 추가 설명
- `std::sort`와 `std::stable_sort` 모두 C++ 표준 라이브러리의 일부로, C++98부터 지원됩니다.
- 이터레이터는 RandomIt (임의 접근) 타입이어야 합니다 (벡터, 배열 등).
- `std::sort`: 평균 O(n log n), 최악 O(n log n), 불안정 정렬 (동일 요소의 상대적 순서 유지 안 함).
- `std::stable_sort`: O(n log n) 최악, 안정 정렬 (동일 요소 순서 유지), 추가 메모리 사용 가능.
- 안정 정렬이 필요하면 `std::stable_sort` 사용.
- 예외: 비교 함수가 예외를 던지면 정의되지 않은 동작.
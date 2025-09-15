
# STL 알고리즘 요약

이 문서는 자주 쓰는 STL 알고리즘의 간단한 사용법과 예시를 모아둔 노트입니다.

## sort

- 헤더: `#include <algorithm>`
- 시그니처(간단): `template<class RandomIt> void sort(RandomIt first, RandomIt last);`
- 복잡도: 평균/최악 O(n log n) (내부적으로 IntroSort 사용)
- 특징: 랜덤 접근 반복자(Random Access Iterator)를 요구합니다. 내림차순이나 사용자 정의 비교를 위해 비교함수를 전달할 수 있습니다. 순서를 보장해야 하면 `std::stable_sort` 사용.

예시:

```cpp
#include <algorithm>
#include <vector>
#include <functional>

std::vector<int> a = {3, 1, 4, 1, 5};
std::sort(a.begin(), a.end());                // 오름차순
std::sort(a.rbegin(), a.rend());              // 내림차순 (역방향 반복자 사용)
std::sort(a.begin(), a.end(), std::greater<>()); // 비교자 사용

// pair나 구조체 정렬: 커스텀 비교자 사용
std::vector<std::pair<int,int>> v = {{1,3},{1,2},{2,2}};
std::sort(v.begin(), v.end(), [](auto &x, auto &y){
	if (x.first != y.first) return x.first < y.first; // first 오름차순
	return x.second > y.second; // 동일한 first일 때 second 내림차순
});
```

팁: 부분 정렬이 필요하면 `std::partial_sort`나 k번째 원소를 찾을 때는 `std::nth_element`를 고려하세요.

## find

- 헤더: `#include <algorithm>`
- 시그니처(간단): `template<class InputIt, class T> InputIt find(InputIt first, InputIt last, const T& value);`
- 복잡도: 선형 탐색 O(n)
- 반환: 찾으면 해당 원소의 iterator, 못 찾으면 `last` 반환

예시:

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {10, 20, 30};
auto it = std::find(v.begin(), v.end(), 20);
if (it != v.end()) {
	// 찾음: *it == 20
}

// 조건으로 찾기
auto it2 = std::find_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });

// 정렬된 범위에서는 이진 탐색 계열 함수 사용 권장: std::binary_search, std::lower_bound 등
```

간단한 요약: 정렬이 필요하면 `std::sort`, 특정 값이나 조건을 빠르게 확인하려면 `std::find`/`std::find_if` (비정렬) 또는 정렬된 경우 `std::binary_search`/`lower_bound` 사용.

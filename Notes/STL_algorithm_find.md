
## std::find

### 헤더

```cpp
#include <algorithm>
```

### 시그니처 (대표)

```cpp
template <class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value);
```

### 동작

- [first, last) 범위에서 value와 == 로 비교하여 처음 만나는 요소의 반복자를 반환합니다.
- 찾지 못하면 last를 반환합니다.
- 복잡도: 최악의 경우 O(N) (선형 탐색)

### 사용 예제

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
	std::vector<int> v = {1,2,3,4,5};
	int target = 3;
	auto it = std::find(v.begin(), v.end(), target);
	if(it != v.end()){
		std::cout << "found at index: " << std::distance(v.begin(), it) << '\n';
	} else {
		std::cout << "not found\n";
	}
}
```

문자열에서도 사용할 수 있습니다:

```cpp
#include <string>
std::string s = "hello";
auto it = std::find(s.begin(), s.end(), 'e'); // 문자를 찾는다
```

### find를 이용한 존재 확인

```cpp
if(std::find(vec.begin(), vec.end(), x) != vec.end()){
	// 존재함
}
```

하지만 빈번한 존재 검사(많은 쿼리)가 필요하면 벡터에 대해 매번 선형 탐색을 하는 대신
`std::unordered_set`이나 정렬 후 `std::binary_search`를 사용하는 것이 더 효율적입니다.

---

## std::find_if / std::find_if_not

### 시그니처 (대표)

```cpp
template <class InputIt, class UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p);

template <class InputIt, class UnaryPredicate>
InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p);
```

### 동작

- `find_if`는 범위에서 조건자 p를 만족하는 처음 요소(즉, p(elem) == true)를 반환합니다.
- `find_if_not`는 p(elem) == false인 처음 요소를 반환합니다.
- 복잡도는 여전히 O(N).

### 예제

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

std::vector<int> a = {2,4,6,7,8};
auto it = std::find_if(a.begin(), a.end(), [](int x){ return x % 2 == 1; });
if(it != a.end()) std::cout << "first odd: " << *it << '\n';
```

---

## C++20: std::ranges::find

C++20부터는 ranges 버전이 추가되어 컨테이너 자체나 더 간결한 호출이 가능합니다:

```cpp
#include <algorithm>
#include <ranges>

auto it = std::ranges::find(v, target); // v가 컨테이너이면 begin/end 자동 사용
```

ranges 버전은 가독성이 좋고, projection 등의 추가 기능과 함께 사용하기 쉽습니다.

---

## 팁

- 단순 존재 검사: `std::find(...) != end` 또는 C++20 이후 `std::ranges::find` 사용.
- 많은 조회(검색) 작업이 요구되면 해시셋(`std::unordered_set`)이나 정렬 + 이진탐색(`std::binary_search`)을 고려하세요.
- find는 순차 탐색이므로 큰 컨테이너에서 자주 호출하면 성능 병목이 될 수 있습니다.


# STL 최대/최소 관련 알고리즘 정리

`<algorithm>` 헤더에 정의된 최대/최소 관련 함수들입니다. 두 값 비교와 범위 검색을 지원합니다.

## 1. std::min - 두 값 중 최소값
### 시그니처
```cpp
template<class T>
const T& min(const T& a, const T& b);

template<class T, class Compare>
const T& min(const T& a, const T& b, Compare comp);
```

### 설명
- 두 값 중 작은 값을 반환합니다.
- 두 번째 오버로딩은 사용자 정의 비교자를 사용합니다.

### 예시
```cpp
#include <algorithm>
#include <iostream>

int a = 3, b = 5;
int min_val = std::min(a, b);  // 3
int min_custom = std::min(a, b, std::greater<int>());  // 5 (내림차순 비교)
```

## 2. std::max - 두 값 중 최대값
### 시그니처
```cpp
template<class T>
const T& max(const T& a, const T& b);

template<class T, class Compare>
const T& max(const T& a, const T& b, Compare comp);
```

### 설명
- 두 값 중 큰 값을 반환합니다.
- 두 번째 오버로딩은 사용자 정의 비교자를 사용합니다.

### 예시
```cpp
#include <algorithm>
#include <iostream>

int a = 3, b = 5;
int max_val = std::max(a, b);  // 5
int max_custom = std::max(a, b, std::greater<int>());  // 3 (내림차순 비교)
```

## 3. std::minmax - 두 값의 최소/최대 쌍
### 시그니처
```cpp
template<class T>
std::pair<const T&, const T&> minmax(const T& a, const T& b);

template<class T, class Compare>
std::pair<const T&, const T&> minmax(const T& a, const T& b, Compare comp);
```

### 설명
- 두 값의 최소값과 최대값을 pair로 반환합니다.
- 두 번째 오버로딩은 사용자 정의 비교자를 사용합니다.

### 예시
```cpp
#include <algorithm>
#include <iostream>

int a = 3, b = 5;
auto [min_val, max_val] = std::minmax(a, b);  // min_val=3, max_val=5
```

## 4. std::min_element - 범위에서 최소 요소
### 시그니처
```cpp
template<class ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last);

template<class ForwardIt, class Compare>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp);
```

### 설명
- 범위에서 가장 작은 요소의 이터레이터를 반환합니다.
- 두 번째 오버로딩은 사용자 정의 비교자를 사용합니다.

### 예시
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> v = {3, 1, 4, 1, 5};
auto it = std::min_element(v.begin(), v.end());  // v[1] (값 1)
```

## 5. std::max_element - 범위에서 최대 요소
### 시그니처
```cpp
template<class ForwardIt>
ForwardIt max_element(ForwardIt first, ForwardIt last);

template<class ForwardIt, class Compare>
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp);
```

### 설명
- 범위에서 가장 큰 요소의 이터레이터를 반환합니다.
- 두 번째 오버로딩은 사용자 정의 비교자를 사용합니다.

### 예시
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> v = {3, 1, 4, 1, 5};
auto it = std::max_element(v.begin(), v.end());  // v[4] (값 5)
```

## 6. std::minmax_element - 범위에서 최소/최대 요소 쌍
### 시그니처
```cpp
template<class ForwardIt>
std::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last);

template<class ForwardIt, class Compare>
std::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last, Compare comp);
```

### 설명
- 범위에서 최소 요소와 최대 요소의 이터레이터를 pair로 반환합니다.
- 두 번째 오버로딩은 사용자 정의 비교자를 사용합니다.

### 예시
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> v = {3, 1, 4, 1, 5};
auto [min_it, max_it] = std::minmax_element(v.begin(), v.end());  // min_it=v[1], max_it=v[4]
```

## 추가 설명
- 모든 함수는 `<algorithm>` 헤더에 있습니다.
- 비교자는 `operator<`를 기본으로 사용하며, 사용자 정의로 변경 가능합니다.
- 범위 함수들은 ForwardIt (전진 이터레이터) 이상을 요구합니다.
- 빈 범위에 대해 min_element/max_element는 last를 반환합니다 (정의되지 않은 동작 주의).
# std::transform 오버로딩 시그니처 정리

`std::transform`은 `<algorithm>` 헤더에 정의된 함수로, 범위의 요소에 연산을 적용하여 결과를 다른 범위에 저장합니다. 두 가지 주요 오버로딩이 있습니다: 단항 연산과 이항 연산.

## 1. 단항 연산 오버로딩 (Unary Operation)
한 범위의 각 요소에 단항 연산을 적용합니다.

### 시그니처
```cpp
template<class InputIt, class OutputIt, class UnaryOperation>
OutputIt transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation unary_op);
```

### 매개변수
- `first`, `last`: 입력 범위의 시작과 끝 이터레이터 (InputIt).
- `d_first`: 출력 범위의 시작 이터레이터 (OutputIt).
- `unary_op`: 각 요소에 적용할 단항 연산 (UnaryOperation, 예: 람다, 함수 포인터).

### 반환값
- 출력 범위의 끝 이터레이터 (OutputIt).

### 예시
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> v = {1, 2, 3};
std::vector<int> result(3);

std::transform(v.begin(), v.end(), result.begin(), [](int x) { return x * 2; });
// result: {2, 4, 6}
```

## 2. 이항 연산 오버로딩 (Binary Operation)
두 범위의 대응 요소에 이항 연산을 적용합니다.

### 시그니처
```cpp
template<class InputIt1, class InputIt2, class OutputIt, class BinaryOperation>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOperation binary_op);
```

### 매개변수
- `first1`, `last1`: 첫 번째 입력 범위의 시작과 끝 이터레이터 (InputIt1).
- `first2`: 두 번째 입력 범위의 시작 이터레이터 (InputIt2).
- `d_first`: 출력 범위의 시작 이터레이터 (OutputIt).
- `binary_op`: 두 요소에 적용할 이항 연산 (BinaryOperation, 예: 람다, 함수 포인터).

### 반환값
- 출력 범위의 끝 이터레이터 (OutputIt).

### 예시
```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = {4, 5, 6};
std::vector<int> result(3);

std::transform(v1.begin(), v1.end(), v2.begin(), result.begin(), std::plus<int>());
// result: {5, 7, 9} (1+4, 2+5, 3+6)
```

## 추가 설명
- 두 오버로딩 모두 C++ 표준 라이브러리의 일부로, C++98부터 지원됩니다.
- 연산은 각 요소에 대해 호출되며, 출력 범위는 입력 범위와 크기가 같아야 합니다 (또는 충분히 커야 함).
- 이터레이터 타입은 입력/출력 요구사항을 만족해야 합니다 (InputIt는 읽기, OutputIt는 쓰기).
- 예외 안전성: 연산이 예외를 던지면 정의되지 않은 동작이 발생할 수 있습니다.
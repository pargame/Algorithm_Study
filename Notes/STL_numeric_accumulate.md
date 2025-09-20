# std::accumulate 알아야 할 것 정리

`<numeric>`에 정의된 범위 내 요소들의 누적 합계를 계산하는 함수. 초기값과 함께 이터레이터 범위를 순회하며 값을 누적함.

## 기본 개념
- **누적 연산**: 범위의 각 요소를 초기값에 더하거나 사용자 정의 연산으로 누적.
- **범용성**: 컨테이너, 배열 등 다양한 범위에 적용 가능.
- **용도**: 합계, 곱셈, 문자열 연결 등 다양한 누적 계산에 사용.

## 생성자 (또는 시그니처)
```cpp
// 기본 누적 (합계)
template<class InputIt, class T>
T accumulate(InputIt first, InputIt last, T init);

// 사용자 정의 연산
template<class InputIt, class T, class BinaryOperation>
T accumulate(InputIt first, InputIt last, T init, BinaryOperation op);
```

## 주요 멤버 함수 (또는 오버로딩)
- `accumulate(first, last, init)`: 범위 [first, last)의 요소들을 init에 더하여 반환.
- `accumulate(first, last, init, op)`: op 연산을 사용하여 누적 (예: 곱셈).

## 연산자
- 없음 (함수 기반).

## 기타 (이터레이터, 헬퍼 함수 등)
- **이터레이터**: InputIterator 타입 지원 (순차 접근).
- **헬퍼 함수**: 없음.
- **반환 타입**: init의 타입과 일치.

## 사용 예시
```cpp
#include <numeric>
#include <vector>
#include <iostream>

std::vector<int> v = {1, 2, 3, 4, 5};
int sum = std::accumulate(v.begin(), v.end(), 0);  // 15
std::cout << sum << std::endl;

// 곱셈 예시
int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());  // 120
std::cout << product << std::endl;

// 람다로 사용자 정의 연산 (예: 제곱 합)
int sum_squares = std::accumulate(v.begin(), v.end(), 0, [](int acc, int x) {
    return acc + x * x;
});  // 1+4+9+16+25 = 55

// pair의 second 합 (람다 사용)
std::vector<std::pair<int, int>> pairs = {{1, 10}, {2, 20}, {3, 30}};
int sum_seconds = std::accumulate(pairs.begin(), pairs.end(), 0, [](int acc, const std::pair<int, int>& p) {
    return acc + p.second;
});  // 10+20+30 = 60
```

## 주의사항
- **안전성**: 범위가 유효해야 함 (first <= last).
- **성능**: O(N) 시간 복잡도.
- **스레드**: 안전하지 않음 (컨테이너 공유 시).
- **기타**: init 타입이 요소 타입과 호환되어야 함, 오버플로우 주의.
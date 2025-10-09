# std::ranges::iota_view 알아야 할 것 정리

`<ranges>`에 정의된 연속된 정수 시퀀스를 생성하는 뷰. Python의 `range()`와 유사하게 동작하며, 지연 평가(lazy evaluation)로 메모리를 절약한다.

## 기본 개념
- **지연 평가**: 실제로 값이 필요할 때까지 생성하지 않음.
- **범위 기반**: C++20의 ranges 라이브러리의 일부.
- **용도**: 반복문이나 알고리즘에서 연속된 숫자 시퀀스가 필요할 때 사용.

## 생성자 (또는 시그니처)
```cpp
// 예시: 0부터 시작하는 무한 시퀀스
std::ranges::iota_view<int> iv(0);

// 예시: 시작과 끝 지정 (끝 값은 포함되지 않음)
std::ranges::iota_view<int, int> iv(1, 11);  // [1, 2, ..., 10]

// 예시: views::iota로 간단하게
auto iv = std::views::iota(1);      // 1부터 무한
auto iv = std::views::iota(1, 11);  // [1, 2, ..., 10]

// 예시: 파이프 연산자와 함께
auto result = std::views::iota(0, 10) 
            | std::views::filter([](int i) { return i % 2 == 0; });
```

## 주요 멤버 함수 (또는 오버로딩)
- `begin()`: 시퀀스의 시작 반복자 반환.
- `end()`: 시퀀스의 끝 반복자 반환 (끝 값이 지정된 경우).
- `size()`: 유한 범위의 경우 크기 반환.
- `empty()`: 범위가 비어있는지 확인.

## 연산자
- `*it`: 반복자 역참조로 현재 값 얻기.
- `++it`, `it++`: 다음 값으로 이동.
- `--it`, `it--`: 이전 값으로 이동 (양방향 반복자).
- `it + n`, `it - n`: n만큼 이동 (랜덤 액세스 반복자).
- `==`, `!=`: 반복자 비교.

## 기타 (이터레이터, 헬퍼 함수 등)
- **이터레이터**: 랜덤 액세스 반복자 지원.
- **헬퍼 함수**: `std::views::iota()`로 간편하게 생성.
- **파이프 연산자**: 다른 views와 조합 가능 (`|`).
- **무한 범위**: 끝 값을 생략하면 무한 시퀀스 생성.

## 사용 예시
```cpp
#include <ranges>
#include <vector>
#include <iostream>
#include <algorithm>

// 예시 1: vector로 변환
auto vec = std::views::iota(1, 11);
std::vector<int> v(vec.begin(), vec.end());  // [1, 2, ..., 10]

// 예시 2: 범위 기반 for문
for (int i : std::views::iota(1, 6)) {
    std::cout << i << " ";  // 출력: 1 2 3 4 5
}

// 예시 3: 다른 views와 조합
auto even_squares = std::views::iota(1, 11)
                  | std::views::filter([](int i) { return i % 2 == 0; })
                  | std::views::transform([](int i) { return i * i; });
// [4, 16, 36, 64, 100]

// 예시 4: 알고리즘과 함께
std::vector<int> indices;
std::ranges::copy(std::views::iota(0, 5), std::back_inserter(indices));
// indices = [0, 1, 2, 3, 4]

// 예시 5: 유틸리티 함수로 활용
std::vector<int> MakeRange(int start, int end) {
    auto range = std::views::iota(start, end);
    return std::vector<int>(range.begin(), range.end());
}
```

## 주의사항
- **C++20 이상**: C++20부터 사용 가능. 컴파일러가 ranges를 지원해야 함.
- **성능**: 지연 평가로 메모리 효율적이지만, 매번 계산이 필요한 경우 vector로 변환하는 것이 빠를 수 있음.
- **무한 범위 주의**: 끝 값을 생략하면 무한 시퀀스가 되므로 `take()` 등으로 제한 필요.
- **타입 추론**: `auto`를 사용하여 타입 추론을 권장.
- **컴파일러 플래그**: `-std=c++20` 이상 필요.

# std::cmath 알아야 할 것 정리

`<cmath>` 헤더에 정의된 수학 함수 라이브러리. 부동 소수점 연산을 위한 다양한 함수를 제공합니다.

## 기본 개념
- **수학 함수**: 삼각, 지수, 로그, 제곱근 등.
- **오버로딩**: float, double, long double 지원.
- **용도**: 과학 계산, 그래픽, 알고리즘 구현.

## 주요 함수 시그니처
- `sin(double x)`: 사인 (라디안).
- `cos(double x)`: 코사인 (라디안).
- `tan(double x)`: 탄젠트 (라디안).
- `asin(double x)`: 아크사인 (-1~1).
- `acos(double x)`: 아크코사인 (-1~1).
- `atan(double x)`: 아크탄젠트.
- `atan2(double y, double x)`: 아크탄젠트 (x, y 좌표).
- `exp(double x)`: e^x.
- `log(double x)`: 자연 로그 (x > 0).
- `log10(double x)`: 상용 로그 (x > 0).
- `pow(double base, double exp)`: base^exp.
- `sqrt(double x)`: 제곱근 (x >= 0).
- `abs(int x)` / `fabs(double x)`: 절대값.
- `floor(double x)`: 바닥 함수 (내림).
- `ceil(double x)`: 천장 함수 (올림).
- `round(double x)`: 반올림.
- `fmod(double x, double y)`: 나머지 (x / y).
- `hypot(double x, double y)`: sqrt(x^2 + y^2).

## 연산자
- 없음 (함수 기반).

## 기타
- **상수**: M_PI (파이, 일부 컴파일러), M_E (오일러 수).
- **오버로딩**: float/double/long double 버전 존재 (예: sinf, sinl).

## 사용 예시
```cpp
#include <cmath>
#include <iostream>

double angle = 1.57;  // ~90도
std::cout << sin(angle) << ", " << cos(angle);  // ~1, ~0
std::cout << pow(2, 3);  // 8
std::cout << sqrt(16);  // 4
```

## 주의사항
- **단위**: 삼각 함수는 라디안 (도 변환: x * M_PI / 180).
- **범위**: asin/acos는 [-1,1], 로그는 양수.
- **정확도**: 부동 소수점 오차 주의.
- **헤더**: <cmath> (C++), <math.h> (C).
- **컴파일러**: M_PI는 표준 아님 (define 필요).
# cmath 헤더: 수학 함수 정리

`<cmath>` 헤더는 C++에서 제공하는 수학 함수들의 모음입니다. 주로 부동소수점 연산을 위한 다양한 함수를 포함하며, 과학 계산, 그래픽스, 게임 개발 등에서 유용하게 사용됩니다.

## 주요 함수 카테고리

### 삼각함수 (Trigonometric Functions)
- `sin(x)`: x(라디안)의 사인 값을 반환합니다.
- `cos(x)`: x의 코사인 값을 반환합니다.
- `tan(x)`: x의 탄젠트 값을 반환합니다.

### 역삼각함수 (Inverse Trigonometric Functions)
- `asin(x)`: x의 아크사인 값을 반환합니다. (범위: [-1, 1])
- `acos(x)`: x의 아크코사인 값을 반환합니다.
- `atan(x)`: x의 아크탄젠트 값을 반환합니다.
- `atan2(y, x)`: (y, x) 점의 아크탄젠트 값을 반환합니다. (사분면 고려)

### 지수 및 로그 함수 (Exponential and Logarithmic Functions)
- `exp(x)`: e^x (자연지수 e의 x 거듭제곱)를 반환합니다.
- `log(x)`: x의 자연로그(ln)를 반환합니다. (x > 0)
- `log10(x)`: x의 상용로그(log10)를 반환합니다.

### 제곱근 및 거듭제곱 (Power and Root Functions)
- `sqrt(x)`: x의 제곱근을 반환합니다. (x >= 0)
- `pow(base, exponent)`: base의 exponent 거듭제곱을 반환합니다.

### 절대값 및 반올림 (Absolute Value and Rounding)
- `fabs(x)`: x의 절대값을 반환합니다.
- `ceil(x)`: x보다 크거나 같은 가장 작은 정수를 반환합니다. (올림)
- `floor(x)`: x보다 작거나 같은 가장 큰 정수를 반환합니다. (내림)
- `round(x)`: x를 가장 가까운 정수로 반올림합니다.

## 사용 예시

```cpp
#include <cmath>
#include <iostream>

int main() {
    double angle_deg = 90.0;
    double angle_rad = angle_deg * M_PI / 180.0;  // 도를 라디안으로 변환
    
    std::cout << "sin(90°): " << sin(angle_rad) << std::endl;  // 출력: 1
    std::cout << "cos(90°): " << cos(angle_rad) << std::endl;  // 출력: 0
    std::cout << "sqrt(16): " << sqrt(16.0) << std::endl;      // 출력: 4
    std::cout << "pow(2, 3): " << pow(2.0, 3.0) << std::endl; // 출력: 8
    std::cout << "log(10): " << log(10.0) << std::endl;        // 출력: 약 2.302
    
    return 0;
}
```

## 주의사항
- **단위 변환**: 삼각함수는 라디안을 사용하므로, 도 단위 입력 시 `x * M_PI / 180`으로 변환하세요.
- **입력 범위**: `log`와 `sqrt`는 양수 입력만 허용. `asin`과 `acos`는 [-1, 1] 범위.
- **부동소수점 정밀도**: 비교 시 epsilon(예: 1e-9)을 사용해 오차를 고려하세요.
- **오버플로우**: 큰 값 연산 시 오버플로우 가능성 있음.
- **상수**: `M_PI`(π), `M_E`(e) 등은 표준이 아니므로, `<numbers>` 헤더( C++20)나 직접 정의 권장.
- **스레드 안전**: 대부분의 함수는 스레드 안전합니다.

# <cmath> 주요 함수 요약

이 파일에는 `<cmath>`에 있는 자주 쓰는 함수들의 간단한 사용법과 주의점을 정리합니다.

## abs / fabs / llabs 등 (절대값)

- 헤더: `#include <cmath>` (정수형 오버로드는 `<cstdlib>`에서도 제공될 수 있음)
- 함수: `std::abs`는 정수, 부동소수점, 복소수 등 여러 오버로드가 있습니다. 또한 오래된 C 스타일로 `std::fabs`, `std::llabs` 등이 존재합니다.

예시:

```cpp
#include <iostream>
#include <cmath>

int main() {
	int i = -5;
	double d = -3.14;
	long long ll = -1234567890123LL;

	std::cout << std::abs(i) << '\n';   // int 오버로드
	std::cout << std::abs(d) << '\n';   // double 오버로드
	std::cout << std::abs(ll) << '\n';  // long long 오버로드 (C++11 이후 대부분 지원)

	// 복소수 절댓값(크기): std::abs(std::complex<T>)
	#include <complex>
	std::complex<double> z(3.0, 4.0);
	std::cout << std::abs(z) << '\n'; // 5
}
```

주의사항:
- 정수에서 최소값(INT_MIN 등)의 절대값은 같은 타입으로 표현할 수 없어 오버플로우(정의되지 않음)가 발생할 수 있습니다. 안전하려면 더 큰 타입으로 캐스트하세요.
- unsigned 타입에 std::abs를 쓰지 마세요(의미 없음).
- 복소수의 경우 `std::abs`는 magnitude(크기)를 반환합니다.

권장 패턴:
- 일반적인 경우 `<cmath>`의 `std::abs`를 사용하세요. 정수 최소값 문제를 피하거나 범용 템플릿을 작성할 때는 타입 별 처리를 추가하세요.

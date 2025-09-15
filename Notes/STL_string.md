
# STL string 관련 유틸 요약

간단한 문자열/숫자 변환 유틸 함수 사용법을 정리합니다.

## stoi / stol / stoll (문자열 -> 정수)

- 헤더: `#include <string>`
- 시그니처(예): `int stoi(const std::string& str, std::size_t* pos = 0, int base = 10);`
- 동작: 문자열을 정수로 변환합니다. 변환 가능한 접두(공백 허용, 부호 허용)를 처리하고, 변환되지 않은 나머지 부분의 시작 인덱스를 `pos`에 저장할 수 있습니다.
- 예외: 변환 불가 시 `std::invalid_argument`, 값이 범위를 벗어나면 `std::out_of_range`를 던집니다.

예시:

```cpp
#include <string>
#include <iostream>

std::string s = "  -123abc";
try {
	std::size_t idx;
	int x = std::stoi(s, &idx); // x == -123, idx == 6 (문자열에서 변환이 끝난 위치)
	std::cout << x << " remaining from " << idx << "\n";
} catch (const std::invalid_argument& e) {
	// 변환 불가
} catch (const std::out_of_range& e) {
	// 범위 초과
}

// 진법 지정 예: 16진수 문자열을 정수로
int y = std::stoi("ff", nullptr, 16); // y == 255
```

팁: 큰 정수형이 필요하면 `stol`, `stoll`을 사용하세요. 예외를 피하고 싶으면 변환 전 입력 검사나 `std::from_chars`(헤더 `<charconv>`, C++17)를 고려하세요.

## to_string (숫자 -> 문자열)

- 헤더: `#include <string>`
- 시그니처(예): `std::string to_string(int value);` (정수, 부동소수점 등 여러 오버로드)
- 동작: 숫자를 문자열로 간편히 변환합니다. 형식 제어(소수점 자릿수 등)는 제공하지 않으므로 포맷이 필요하면 `std::ostringstream`나 `std::format`(C++20)을 사용하세요.

예시:

```cpp
#include <string>
#include <iostream>

int a = 42;
double d = 3.14159;
std::string sa = std::to_string(a);   // "42"
std::string sd = std::to_string(d);   // "3.141590" (기본 포맷)

std::cout << sa << " " << sd << "\n";
```

팁: 부동소수점의 출력 형식을 제어하려면 `std::ostringstream`에서 `std::setprecision`을 사용하거나, C++20 이상에서는 `std::format`을 사용하세요.

---

간단 요약: 문자열->정수는 `stoi`/`stol`/`stoll` (예외 처리 필요), 정수->문자열은 `to_string` (포맷 제어는 제한적) 사용.

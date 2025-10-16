# C++ 기본 타입 메모

이 노트는 C++에서 자주 쓰이는 기본 타입들의 메모리 크기(대표적인 플랫폼 기준), 범위, 주의점, 추천 사용 방법을 정리합니다. 플랫폼(컴파일러, OS, 아키텍처)에 따라 크기와 범위가 다를 수 있으므로 실제 값은 `sizeof`로 확인하세요.

> 참고: 이 문서의 "typical" 값들은 x86_64 (Linux/macOS, 64-bit) 기준입니다. Windows(LLP64)나 32-bit 플랫폼에서는 차이가 있을 수 있습니다.

## 공통 헤더
- `<cstdint>`: `int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint*_t` 등 고정 폭 정수 타입
- `<climits>`: `CHAR_BIT`, `INT_MAX` 등 한계값
- `<cstddef>`: `size_t`, `ptrdiff_t`, `nullptr_t`
- `<limits>`: `std::numeric_limits<T>` 템플릿 (범위/정밀도 조회)

---

## char
- Typical size: 1 byte (by definition), `CHAR_BIT` (대부분 8)
- Signedness: 구현 정의(implementation-defined). `char`는 `signed char` 또는 `unsigned char`일 수 있음.
- Range: `CHAR_MIN`..`CHAR_MAX` (헤더 `<climits>` 참조)
- 주의: 텍스트/문자 처리에 흔히 사용되지만, 부호 여부가 모호하므로 바이트 데이터를 다룰 때는 `unsigned char` 사용 권장.
- 예: 넓은 문자열 처리/바이너리 버퍼에 `unsigned char` 또는 `std::byte` 권장.

## signed char / unsigned char
- Typical size: 1 byte
- Range: `signed char`는 보통 -128..127, `unsigned char`는 0..255
- 주의: 바이트 연산(비트 조작, 바이너리 데이터)에는 `unsigned char` 권장.

## short (short int)
- Typical size: 2 bytes (16-bit)
- Range: `-32768`..`32767` (signed), `0`..`65535` (unsigned)
- 사용처: 메모리 제약이 있거나, 외부 바이너리 포맷과 맞출 때.

## int
- Typical size: 4 bytes (32-bit) on most modern platforms (including x86_64 Linux/macOS)
- Range: `-2,147,483,648`..`2,147,483,647` (signed 32-bit)
- 주의: 알고리즘 문제(BOJ 등)에서는 `int`가 충분한 경우가 많지만 합계/곱셈에서 오버플로우 주의.

## long
- Typical size: 8 bytes (64-bit) on Unix-like x86_64 (LP64), but 4 bytes on Windows (LLP64) 64-bit
- Range: depends on platform. LP64: `-2^63`..`2^63-1`
- 주의: 포터블한 크기를 기대하면 `long` 대신 고정폭(`int64_t`) 사용 권장.

## long long
- Typical size: 8 bytes (64-bit) on most platforms
- Range: at least `-2^63`..`2^63-1` (signed)
- 사용처: 64-bit 정수가 필요할 때 (포터블)

## size_t
- 타입: 부호 없는 정수 타입 (implementation-defined)
- Typical size: 8 bytes on 64-bit 플랫폼
- 의미: 메모리 크기/컨테이너 크기(예: `sizeof`, `std::vector::size()`) 반환 타입
- 주의: signed/unsigned 혼합 연산에서 언더플로우/비교 버그 주의. 인덱스 계산이나 차감 시 음수 가능성 있으면 `ptrdiff_t` 또는 정수로 캐스트 고려.

## ptrdiff_t
- 타입: signed integer type for pointer differences
- Typical size: 8 bytes on 64-bit
- 의미: 포인터 뺄셈 결과, 컨테이너 인덱스 차이
- 권장: 인덱스 차이/음수 가능성이 있는 경우 `ptrdiff_t` 사용

## bool
- Typical size: 1 byte
- 값: `true` 또는 `false` (정수와 암묵적 변환 있음)
- 주의: 비트필드 또는 메모리 절약 목적이면 `std::bitset` 또는 `unsigned` 비트마스크 사용 권장

## float / double / long double
- Typical sizes: `float` 4 bytes (single precision), `double` 8 bytes (double precision), `long double` 플랫폼에 따라 16 bytes(실제 x86_64 GCC/Clang 80-bit 확장/또는 16바이트)
- 정밀도: `std::numeric_limits<T>::digits10`로 확인
- 주의: 부동소수점 비교는 절대/상대 오차 허용 필요. 리얼 계산에서 누적 오차 유의.

## 고정 폭 타입 (`<cstdint>`)
- `int8_t`, `int16_t`, `int32_t`, `int64_t` 및 unsigned 대응 타입
- 포터블하고 크기가 정확히 고정되어야 할 때 사용 (네트워크/파일 포맷 등)
- 주의: 구현에 따라 `intN_t`가 항상 존재하지 않을 수 있음(대부분 현대 플랫폼에서는 존재).

## 기타 타입
- `std::size_t`: `<cstddef>`에서 제공되는 이름(동일 설명)
- `std::intptr_t` / `std::uintptr_t`: 포인터를 정수로 저장할 때 (포인터 크기와 동일한 정수형)
- `std::byte` (C++17): 바이트 단위 데이터를 안전하게 다루기 위한 타입

---

## 정수 오버플로우
- Signed 정수 오버플로우는 정의되지 않음(UB). 항상 피할 것. (예: `INT_MAX + 1`는 UB)
- Unsigned 정수는 모듈로 연산(2^N)으로 정의되어 있음.
- 안전하게 다루려면 큰 타입으로 캐스팅하거나 `__int128`(GCC/Clang 확장) 사용.

## 추천 가이드
- 알고리즘/문제 풀이에서:
  - 범위가 명확하면 `int` 또는 `long long`을 쓰되, 합계/곱셈이 클 경우 `long long` 사용
  - 배열/버퍼 크기에는 `size_t` (또는 `int`로 충분하면 `int`) 사용
- 라이브러리/포맷/네트워크:
  - 고정 폭 타입(`int32_t`, `uint64_t`) 사용
- 포인터 산술/차이: `ptrdiff_t` 사용
- 바이트/바이너리 데이터: `unsigned char` 또는 `std::byte`

---

## 작은 예제: 현재 플랫폼에서 sizeof 출력
````cpp
#include <iostream>
#include <cstdint>
#include <cstddef>

int main() {
    std::cout << "sizeof(char) = " << sizeof(char) << '\n';
    std::cout << "sizeof(short) = " << sizeof(short) << '\n';
    std::cout << "sizeof(int) = " << sizeof(int) << '\n';
    std::cout << "sizeof(long) = " << sizeof(long) << '\n';
    std::cout << "sizeof(long long) = " << sizeof(long long) << '\n';
    std::cout << "sizeof(size_t) = " << sizeof(std::size_t) << '\n';
    std::cout << "sizeof(ptrdiff_t) = " << sizeof(std::ptrdiff_t) << '\n';
    std::cout << "sizeof(void*) = " << sizeof(void*) << '\n';
    std::cout << "sizeof(float) = " << sizeof(float) << '\n';
    std::cout << "sizeof(double) = " << sizeof(double) << '\n';
}
````

빌드: `clang++ -std=c++23 file.cpp -O2 -o a.out` (macOS/zsh)

---

## 참고자료
- cppreference.com: "Integral types", "Fundamental types"
- <climits>, <cstdint>, <cstddef>, <limits>


*작성자: 자동생성 노트*

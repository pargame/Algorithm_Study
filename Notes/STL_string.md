# std::string 알아야 할 것 정리

`std::string`은 `<string>` 헤더에 정의된 문자열 클래스입니다. 동적 크기의 문자 시퀀스를 관리하며, C++ 표준 라이브러리의 일부입니다.

## 기본 개념
- **문자열 관리**: null-terminated가 아니며, 크기를 동적으로 조절합니다.
- **타입**: `std::basic_string<char>`의 typedef.
- **인코딩**: 기본적으로 ASCII/UTF-8 호환, 하지만 인코딩을 보장하지 않습니다.

## 생성자
```cpp
std::string s;                          // 빈 문자열
std::string s("hello");                 // C-string에서 생성
std::string s("hello", 3);              // "hel"
std::string s(5, 'a');                  // "aaaaa"
std::string s(other);                   // 복사 생성자
std::string s(std::move(other));        // 이동 생성자
std::string s(begin, end);              // 이터레이터 범위
```

## 주요 멤버 함수
- `size()` / `length()`: 문자 수 (size_type).
- `empty()`: 비었는지 확인 (bool).
- `clear()`: 내용 지우기.
- `reserve(size_type n)`: 최소 용량을 n으로 설정 (재할당 최소화).
- `capacity()`: 현재 용량 반환 (size_type).
- `shrink_to_fit()`: 용량을 size()에 맞춤 (C++11).
- `resize(size_type n)`: 크기를 n으로 조절, 필요시 '\0'으로 채움.
- `resize(size_type n, char c)`: 크기를 n으로 조절, c로 채움.
- `append(const char* s)` / `append(std::string s)`: 뒤에 추가.
- `insert(size_type pos, const char* s)`: 위치에 삽입.
- `erase(size_type pos, size_type len)`: 부분 삭제.
- `substr(size_type pos, size_type len)`: 부분 문자열 추출.
- `find(const char* s)`: 부분 문자열 찾기 (size_type, 찾지 못하면 npos).
- `replace(size_type pos, size_type len, const char* s)`: 부분 교체.
- `compare(const std::string& s)`: 비교 (-1, 0, 1).
- `c_str()`: C-style 문자열 포인터 (const char*).
- `data()`: 내부 데이터 포인터 (C++17부터 non-const 가능).

## 연산자
- `+`: 연결 (std::string + std::string).
- `==`, `!=`, `<`, `<=`, `>`, `>=`: 비교.
- `[]`: 인덱스 접근 (char&).
- `at(size_type pos)`: 범위 체크 인덱스 접근.

## 기타 (이터레이터, 헬퍼 함수 등)
- **이터레이터**: `begin()`, `end()` 등 (순방향/역방향).
- **헬퍼 함수**:
  - `std::to_string(int value)`: 숫자를 문자열로 변환.
  - `std::stoi(const std::string& str)`: 문자열을 int로 변환.
  - `std::stol(const std::string& str)`: 문자열을 long으로 변환.
  - `std::stoll(const std::string& str)`: 문자열을 long long으로 변환.
  - `std::stoul(const std::string& str)`: 문자열을 unsigned long으로 변환.
  - `std::stoull(const std::string& str)`: 문자열을 unsigned long long으로 변환.
  - `std::stof(const std::string& str)`: 문자열을 float으로 변환.
  - `std::stod(const std::string& str)`: 문자열을 double으로 변환.

## 사용 예시
```cpp
#include <string>
#include <iostream>

std::string s = "hello";
s.append(" world");  // "hello world"
std::string sub = s.substr(0, 5);  // "hello"
size_t pos = s.find("world");  // 6
if (pos != std::string::npos) {
    s.replace(pos, 5, "C++");
}
std::cout << s;  // "hello C++"
```

## 주의사항
- `npos`: 찾기 실패 시 반환 값 (static const size_type).
- 메모리: 동적 할당, 큰 문자열은 성능 고려.
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않습니다.
- C-string 변환: `c_str()`는 null-terminated, `data()`는 아닐 수 있음 (C++17까지).
- 예외: `at()`은 out_of_range 예외, `[]`는 정의되지 않은 동작.
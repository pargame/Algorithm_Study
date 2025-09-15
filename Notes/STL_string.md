
## C++ std::string 빠른 레퍼런스

이 문서는 C++ 표준 라이브러리의 `std::string` 사용법을 빠르게 찾아 쓸 수 있게 정리한 페이지입니다.
예제 코드를 곧바로 복사해서 사용할 수 있도록 구성했습니다.

> 대상: C++11 이상 (권장: C++17/C++20). 모든 예제는 UTF-8을 기준으로 작성되었습니다.

---

### 1) 개요

`std::string`은 문자(char)의 동적 배열로, 길이, 용량, 수정자, 검색, 부분 문자열 추출 등을 제공합니다.
기본적으로 연속 메모리를 보장하므로 C 스타일 API와의 상호 운용도 쉽습니다 (`c_str()`/`data()`).

주요 장점
- 안전하고, RAII를 따름
- 다양한 편의 멤버 함수 제공
- 반복자 제공으로 알고리즘과 결합 가능

주의: 멀티바이트/유니코드(예: UTF-8) 문자를 문자 단위로 다루면 문제가 발생할 수 있음 — 바이트 단위임을 항상 인지하세요.

---

### 2) 생성자 / 초기화

```cpp
#include <string>

std::string s1;                    // 빈 문자열
std::string s2("hello");         // C-문자열로 초기화
std::string s3(5, 'x');            // "xxxxx"
std::string s4(s2);                // 복사 생성자
std::string s5(s2, 1, 2);         // s2의 [1,1+2) = "el"
std::string s6(std::begin(arr), std::end(arr)); // 반복자 기반
```

초기화 팁: 리터럴 연결은 컴파일타임에 가능하나 런타임 조합은 `+`를 사용합니다.

---

### 3) 크기와 용량

- `size()` / `length()` : 논리적 길이
- `capacity()` : 할당된 버퍼 크기
- `reserve(n)` : 최소 용량 확보
- `shrink_to_fit()` : 힌트로 용량 축소

```cpp
std::string s = "hello";
size_t n = s.size();
s.reserve(100);
// many appends
s.shrink_to_fit();
```

성능 팁: 많은 문자열 결합이 예상되면 `reserve`로 미리 공간을 확보하세요. `+=`와 `append()`는 효율적입니다.

---

### 4) 접근자

- `operator[]` : 경계 검사 없음
- `at(i)` : 경계 검사(예외)
- `front()` / `back()` : 첫/마지막 문자
- `c_str()` / `data()` : C 스타일 포인터 (C++17 이후 `data()`는 수정 불가 포인터, C++17부터 변경됨)

```cpp
char c = s[0];        // 빠름, 검사는 없음
char d = s.at(0);     // 범위 초과면 std::out_of_range
const char* p = s.c_str();
```

안전성: 입력 인덱스가 불확실하면 `at()` 사용을 권장합니다.

---

### 5) 수정자 (삽입/삭제/교체)

- `append`, `push_back`, `insert`, `erase`, `replace`, `clear`

```cpp
s.append(" world");          // "hello world"
s += '!';                      // push_back
s.insert(5, ", cruel");      // 삽입
s.erase(5, 7);                 // 시작위치, 길이
s.replace(0, 5, "HELLO");    // 부분 교체

// 예: 공백 트리밍
auto l = s.find_first_not_of(' ');
auto r = s.find_last_not_of(' ');
if (l != std::string::npos) s = s.substr(l, r - l + 1);
```

주의: `erase`와 `insert`는 인덱스를 기반으로 하며 유효성 검사를 직접 해주어야 함.

---

### 6) 검색과 비교

- `find`, `rfind`, `find_first_of`, `find_first_not_of`, `compare`
- `compare`는 사전적 비교(음수/0/양수)를 반환

```cpp
size_t pos = s.find("needle");
if (pos != std::string::npos) { /* found */ }

int cmp = s.compare("abc");
if (cmp == 0) { /* equal */ }
```

효율 팁: 단순 포함 검사만 할 때는 `find(...) != npos`를 사용하세요.

---

### 7) 부분 문자열(substring)

- `substr(pos, len)` : pos부터 len길이의 새 문자열 반환

```cpp
std::string t = s.substr(3, 4);
```

`substr`는 새 메모리를 할당하므로 고빈도 호출 시 비용을 고려하세요.

---

### 8) 숫자/문자열 변환

- `std::to_string`, `std::stoi`, `std::stol`, `std::stoll`, `std::stof`, `std::stod` 등

```cpp
int x = std::stoi("42");
std::string num = std::to_string(3.14);
```

예외: 변환 실패 시 `std::invalid_argument`, 범위 초과 시 `std::out_of_range` 발생.

---

### 9) 입출력

```cpp
std::string line;
std::getline(std::cin, line);    // 한 줄 읽기 (공백 포함)
std::cin >> token;               // 공백 기준 토큰
std::cout << s << '\n';
```

주의: `operator>>`는 공백에서 멈추므로 전체 라인을 원하면 `getline` 사용.

---

### 10) 반복자와 알고리즘

`std::string`은 RandomAccessIterator를 제공하므로 STL 알고리즘과 바로 사용 가능합니다.

```cpp
std::sort(s.begin(), s.end());     // 문자 정렬
auto it = std::find(s.begin(), s.end(), 'a');
```

---

### 11) 자주 쓰는 유틸리티 예제 모음

- split (간단한 구현)

```cpp
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> out;
	size_t start = 0, pos;
	while ((pos = s.find(delim, start)) != std::string::npos) {
		out.push_back(s.substr(start, pos - start));
		start = pos + 1;
	}
	out.push_back(s.substr(start));
	return out;
}
```

- join (C++에는 표준 제공 없음)

```cpp
std::string join(const std::vector<std::string>& v, const std::string& sep) {
	if (v.empty()) return {};
	std::string r = v.front();
	for (size_t i = 1; i < v.size(); ++i) r += sep + v[i];
	return r;
}
```

---

### 12) 성능 및 메모리 팁

- 불필요한 복사를 피하려면 `const std::string&`를 인자로 받습니다.
- 이동 생성자/대입(move)은 C++11 이상에서 빠른 대체 수단입니다.
- 큰 문자열을 조합할 때 `reserve()`로 버퍼를 확보하세요.
- 여러 작은 append 대신 `ostringstream`를 쓰는 경우도 있으나 `reserve` + `append`가 더 빠른 경우가 많습니다.

---

### 13) UTF-8 / 유니코드 주의사항

`std::string`은 바이트 시퀀스를 저장합니다. UTF-8 문자열에서 문자의 개수(유니코드 코드포인트)를 구하려면 바이트를 직접 파싱하거나 라이브러리(icu, utf8cpp 등)를 사용하세요.

예: 한글 한 글자는 UTF-8에서 3바이트입니다. 인덱스로 접근하면 바이트 단위입니다.

---

### 14) 안전과 예외

- 범위 검사 필요하면 `at()` 사용.
- 변환 함수(stoi 등)는 예외를 던짐 — 필요하면 try/catch 사용.

---

### 15) 빠르게 찾아볼 체크리스트

- 전체 라인 읽기: `std::getline`
- 공백 포함 문자열 추가: `append` 또는 `+=`
- 토큰 분리: `find` + `substr` 또는 위의 `split`
- 숫자 변환: `std::stoi`, `std::stoll`, `std::stod`
- C 인터페이스: `c_str()`

---

더 필요한 샘플(예: 정규식 기반 처리, locale/범용 문자 처리, 고성능 스트링 조합 패턴 등)이 있으면 알려주세요. 원하시면 한글/UTF-8 처리 예제나 성능 벤치마크도 추가해드리겠습니다.


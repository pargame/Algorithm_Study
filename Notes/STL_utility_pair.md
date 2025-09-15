
# std::pair 간단 사용법 및 임시 객체 생성

`std::pair`는 두 값(또는 객체)를 한 쌍으로 묶는 유틸리티입니다. 아래는 임시(pair) 객체를 만드는 여러 방법과 `pair<int, std::vector<int>>`처럼 중첩 컨테이너를 만들 때 자주 쓰는 패턴입니다.

1) 중괄호 초기화(간단하고 직관적)

```cpp
std::pair<int, std::vector<int>> p1 = {1, {2, 3}}; // 두번째 요소는 std::vector<int>{2,3}으로 생성되어 이동
// 또는
auto p2 = std::pair<int, std::vector<int>>{1, {4,5,6}};
```

2) std::make_pair 사용

```cpp
auto p3 = std::make_pair(1, std::vector<int>{7,8});
// make_pair는 타입을 유추해주며, 임시 벡터는 이동됩니다.
```

3) 생성자 직접 호출 (명시적)

```cpp
std::pair<int, std::vector<int>> p4(1, std::vector<int>{9,10});
```

4) C++17 CTAD (Class Template Argument Deduction)을 이용한 더 간결한 표기 (컴파일러가 템플릿 인자를 유추)

```cpp
std::pair p5 = {1, std::vector<int>{11,12}}; // C++17 이상
```

5) 컨테이너(예: std::vector<std::pair<...>> )에 바로 삽입/생성

```cpp
std::vector<std::pair<int,std::vector<int>>> vp;
// 복사/이동으로 삽입
vp.push_back(std::make_pair(1, std::vector<int>{1,2}));
// 또는 in-place 생성(불필요한 복사 없이 생성)
vp.emplace_back(2, std::vector<int>{3,4});
// emplace_back은 pair의 생성자에 인자를 전달하므로 두번째 인자는 std::vector<int>{...}로 명시하는 것이 안전
```

6) 이동을 이용해 비용 줄이기

```cpp
std::vector<int> big = /* 큰 데이터 */ {100,101,102};
auto p6 = std::make_pair(42, std::move(big)); // big는 비워짐(moved-from)
```

팁과 주의사항:
- 중첩 컨테이너의 경우 `{1, {2,3}}` 같은 중괄호 초기화가 직관적이고 보통 잘 동작합니다. 생성자가 모호해지는 경우에는 `std::vector<int>{2,3}` 처럼 타입을 명시하면 안전합니다.
- `emplace_back`은 내부에서 직접 생성하므로 불필요한 복사를 줄여 성능상 유리합니다. 다만 벡터의 두번째 인자를 중괄호로만 쓰면 컴파일러가 모호하다고 할 수 있으니 `std::vector<int>{...}` 형태로 명시하는 습관이 안전합니다.
- 이동(`std::move`)을 이용하면 큰 컨테이너를 복사하지 않고 소유권을 이전할 수 있습니다. 이동한 원본은 사용 전에 상태를 확인하세요.
- C++20 이후에는 구조적 바인딩이나 CTAD로 더 간결하게 쓸 수 있습니다.

간단 요약: 임시 `pair<int, vector<int>>`는 중괄호 초기화, `make_pair`, 생성자 직접 호출, CTAD, `emplace_back` 등 다양한 방법으로 만들 수 있고, 큰 컨테이너는 `std::move`로 이동시키면 비용을 줄일 수 있습니다.


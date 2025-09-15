
# STL vector 초기화 방법

자주 쓰는 `std::vector` 초기화 패턴을 간단히 정리합니다.

1) 기본 생성자

```cpp
std::vector<int> v; // 비어있는 벡터
```

2) 크기와 값으로 초기화

```cpp
std::vector<int> a(5);        // 크기 5, 기본값 0
std::vector<int> b(5, 7);     // 크기 5, 모든 원소가 7
```

3) 이니셜라이저 리스트

```cpp
std::vector<int> c = {1,2,3,4};
std::vector<std::string> s{"a","b","c"};
```

4) 배열 또는 다른 컨테이너의 범위로 초기화

```cpp
int arr[] = {10,20,30};
std::vector<int> d(std::begin(arr), std::end(arr));

std::list<int> L = {1,2,3};
std::vector<int> e(L.begin(), L.end());
```

5) 복사 / 이동 생성자

```cpp
std::vector<int> src = {1,2,3};
std::vector<int> f(src);        // 복사
std::vector<int> g(std::move(src)); // 이동 (src는 빈 상태가 될 수 있음)
```

6) assign 사용

```cpp
std::vector<int> h;
h.assign(4, 9); // 크기 4, 모든 원소 9
// 또는 범위 복사
h.assign(d.begin(), d.end());
```

7) reserve / resize (용량 vs 크기)

```cpp
std::vector<int> v2;
v2.reserve(100); // capacity를 미리 확보(크기는 변하지 않음)
v2.resize(10);    // 크기를 10으로 설정(새 원소는 기본값으로 초기화)
```

8) push_back / emplace_back 으로 단계적 초기화

```cpp
std::vector<std::pair<int,int>> vp;
vp.emplace_back(1,2); // 생성자를 호출해 직접 삽입
vp.push_back({3,4});  // 임시 객체를 복사 또는 이동
```

팁 요약:
- 정적 초기값이 있으면 이니셜라이저 리스트가 가장 간결합니다.
- 요소 수는 정해져 있지만 값은 같다면(size,value) 생성자가 편합니다.
- 성능상 반복 삽입 전에는 `reserve`로 capacity를 확보하세요.
- 포인터/배열 또는 다른 컨테이너 범위로 쉽게 초기화할 수 있습니다.

## 벡터의 일부 복사 (범위 복사)

자주 쓰는 부분 복사 패턴입니다. 모두 반복자 기반으로 동작합니다.

1) 새로운 벡터에 범위 복사 (생성자 사용)

```cpp
std::vector<int> src = {0,1,2,3,4,5,6};
// 인덱스 2 ~ 4 (2,3,4)를 복사
std::vector<int> part(src.begin() + 2, src.begin() + 5);
```

2) 기존 벡터에 범위 할당 (assign)

```cpp
std::vector<int> dest;
dest.assign(src.begin() + 2, src.begin() + 5); // dest = {2,3,4}
```

3) 기존 벡터 끝에 덧붙이기 (insert 또는 std::copy + back_inserter)

```cpp
std::vector<int> dest = {10,11};
// insert 사용
dest.insert(dest.end(), src.begin() + 2, src.begin() + 5);
// 또는 std::copy
std::copy(src.begin() + 2, src.begin() + 5, std::back_inserter(dest));
```

4) 일부만 n개 복사 (`std::copy_n`)

```cpp
std::vector<int> out;
std::copy_n(src.begin() + 3, 2, std::back_inserter(out)); // src[3], src[4]
```

5) 조건에 맞는 원소만 복사 (`std::copy_if`)

```cpp
std::vector<int> odd;
std::copy_if(src.begin(), src.end(), std::back_inserter(odd), [](int x){ return x % 2 == 1; });
```

6) 이동(move)으로 복사(대상에 소유권 이전)

```cpp
std::vector<std::string> a = {"a","b","c","d"};
std::vector<std::string> b;
// a의 일부를 b로 이동
b.insert(b.end(), std::make_move_iterator(a.begin()+1), std::make_move_iterator(a.begin()+3));
// a[1], a[2]는 빈 문자열로 변할 수 있음
```

팁/복잡도:
- 반복자 범위 복사는 O(n)입니다(복사 대상 원소 수에 비례).
- 범위를 복사할 때는 인덱스/범위가 유효한지(범위를 벗어나지 않는지) 확인하세요. 특히 빈 벡터나 경계값을 조심합니다.
- `reserve`를 사용하면 반복 삽입(insert/back_inserter/std::copy) 시 재할당을 줄여 성능을 개선할 수 있습니다.


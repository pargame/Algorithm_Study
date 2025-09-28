# C++ decltype 개념 정리

## 개요
- `decltype`은 C++11부터 도입된 키워드로, 주어진 표현식의 타입을 컴파일타임에 추론하여 반환하는 메타프로그래밍 도구입니다.
- 주로 템플릿 메타프로그래밍, 타입 추론, 또는 람다의 클로저 타입을 다룰 때 유용합니다.
- `auto`와 달리, `decltype`은 타입을 직접 추론하지만, 값 범주(참조, rvalue 등)를 고려하여 타입을 결정합니다.

## 기본 사용법
```cpp
decltype(expression) variable_name;
```
- `expression`의 타입을 `variable_name`의 타입으로 사용합니다.

## 값 범주 규칙 (Value Category Rules)
`decltype`은 표현식의 값 범주에 따라 타입을 다르게 추론합니다:
- **id-expression** (예: 변수 이름): 그 변수의 선언 타입을 그대로 반환합니다.
- **그 외 표현식**:
  - lvalue (좌측값): `T&` 형태로 반환 (참조 타입).
  - xvalue (eXpiring value): `T&&` 형태로 반환 (rvalue 참조).
  - prvalue (pure rvalue): `T` 형태로 반환 (값 타입).

### 예시
```cpp
int x = 10;
decltype(x) a = 5;        // int (id-expression: x의 타입)
decltype((x)) b = a;      // int& (괄호로 인해 lvalue로 추론)
decltype(x + 1) c = 20;   // int (prvalue: x+1의 결과)

const int& ref = x;
decltype(ref) d = ref;    // const int& (id-expression: ref의 타입)
```

## 람다와 함께 사용
람다는 고유한 무명 타입(클로저)을 가지며, `decltype`을 사용하여 그 타입을 템플릿 파라미터로 사용할 수 있습니다.

### 예시: priority_queue에서 comparator로 사용
```cpp
#include <queue>
#include <vector>

auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second > b.second;  // second 기준 오름차순 (작은 값이 top)
};

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);

// 사용 예
pq.push({1, 10});
pq.push({2, 5});
auto top = pq.top();  // {2, 5} (second가 작은 것이 우선)
```

- `decltype(cmp)`: 람다 `cmp`의 클로저 타입을 추론하여 템플릿 인수로 사용.
- 생성자에 `cmp` 인스턴스를 전달해야 합니다 (람다 객체가 필요).

## 주의사항
- `decltype`은 컴파일타임에 타입을 결정하므로, 런타임 비용이 없습니다.
- 복잡한 표현식에서는 값 범주를 정확히 이해해야 합니다. 예를 들어, 함수 호출 결과는 prvalue입니다.
- `auto`와 결합하여 `decltype(auto)`를 사용할 수 있습니다 (C++14부터), 이는 `decltype`의 규칙을 따릅니다.

## 관련 개념
- `auto`: 타입 추론 시 값 범주를 무시하고 선언 타입으로 결정.
- `std::decay`: 타입을 "decay"시켜 참조나 cv-qualifier를 제거.
- 메타프로그래밍: `decltype`은 SFINAE나 타입 트레이트와 함께 자주 사용됩니다.

## 참고
- C++ 표준: ISO/IEC 14882 (C++11 이상).
- 실무 팁: 디버깅 시 `typeid(expression).name()`으로 런타임 타입 확인 가능하지만, `decltype`은 컴파일타임입니다.
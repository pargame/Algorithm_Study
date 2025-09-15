
## std::stack (기본 활용법)

### 헤더

```cpp
#include <stack>
#include <deque> // 기본 내부 컨테이너
```

### 개요

- `std::stack`은 LIFO(후입선출) 동작을 제공하는 컨테이너 어댑터입니다. 내부적으로 컨테이너(기본: `std::deque`)를 사용하며, 필요에 따라 `std::vector`나 `std::list`를 지정할 수 있습니다.
- 이터레이터는 제공하지 않습니다(직접 순회 불가). 오직 상단 요소 접근/삽입/삭제 연산만 제공합니다.

### 주요 멤버 함수

- `empty()` : 컨테이너가 비어 있으면 true 반환
- `size()` : 요소 개수 반환
- `top()` : 가장 위 요소에 대한 참조 반환(읽기/쓰기 가능)
- `push(const T&)`, `push(T&&)` : 요소 삽입
- `emplace(args...)` : 제자리 생성 후 삽입
- `pop()` : 가장 위 요소 제거(반환값 없음)
- `swap(other)` : 두 스택의 내용 교환

모두 평균 시간 복잡도는 O(1)입니다.

### 선언 예

```cpp
std::stack<int> s; // 내부 컨테이너는 std::deque<int>
// 내부 컨테이너를 std::vector로 바꾸고 싶을 때
std::stack<int, std::vector<int>> s2;
```

### 사용 예제

```cpp
#include <iostream>
#include <stack>

int main(){
	std::stack<int> st;
	st.push(1);
	st.push(2);
	st.emplace(3); // 3을 제자리 생성하여 push

	while(!st.empty()){
		std::cout << st.top() << '\n';
		st.pop(); // pop은 값을 반환하지 않음에 주의
	}
}
```

### 루프에서 안전하게 요소 제거하기

- `pop()`은 값을 반환하지 않으므로, 값을 얻고 싶다면 `top()`으로 읽어온 뒤 `pop()`을 호출해야 합니다.

```cpp
while(!st.empty()){
	auto v = st.top();
	st.pop();
	// v 사용
}
```

### 주의사항 및 팁

- 이터레이터/순회를 지원하지 않으므로 내부 요소 전체를 검사해야 하는 알고리즘에는 부적합합니다. 그런 경우 `std::vector`/`std::deque`를 직접 사용하거나 내부 컨테이너를 교체하세요.
- 빈 스택에서 `top()`이나 `pop()`을 호출하면 정의되지 않은 동작(UB)이 발생합니다. 호출 전에 항상 `empty()` 체크를 하세요.
- 다수의 삽입/삭제가 예측되는 경우 `std::deque`(기본)이나 `std::vector` 중 어떤 것이 더 적합한지 고려하세요. 예를 들어, 메모리 연속성이 필요하고 자주 재할당이 없을 조건이면 `std::vector`를 내부 컨테이너로 사용할 수 있습니다.
- 스레드 안전성은 제공하지 않습니다. 멀티스레드 환경에서는 외부 동기화가 필요합니다.

### 활용 사례

- DFS(깊이 우선 탐색) 비재귀 구현
- 괄호 검사(올바른 괄호 짝 확인)
- 계산기(중위->후위 변환, 후위 계산) 등 LIFO가 필요한 알고리즘


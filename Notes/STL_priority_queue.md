# std::priority_queue 알아야 할 것 정리

`<queue>` 헤더에 정의된 우선순위 큐 컨테이너 어댑터. 최대 힙 기반으로 우선순위 높은 요소가 먼저 나옵니다.

## 기본 개념
- **우선순위 큐**: 우선순위 높은 요소 먼저 (기본 최대 힙).
- **어댑터**: 내부 컨테이너 사용 (기본 std::vector).
- **용도**: 힙 정렬, 다익스트라 등.

## 생성자
```cpp
std::priority_queue<int> pq;                    // 빈 우선순위 큐
std::priority_queue<int, Container, Compare> pq; // 사용자 정의 컨테이너/비교자
std::priority_queue<int> pq(other);             // 복사 생성자
std::priority_queue<int> pq(std::move(other));  // 이동 생성자
std::priority_queue<int> pq(begin, end);        // 범위 생성
```

## 주요 멤버 함수
- `push(const T&)` / `push(T&&)`: 요소 추가.
- `pop()`: 최상위 요소 제거 (반환 없음).
- `top()`: 최상위 요소 참조.
- `empty()`: 비었는지 확인.
- `size()`: 요소 수.

## 연산자
- 없음 (비교는 내부 비교자).

## 기타
- **비교자**: 기본 `std::less` (최대 힙), `std::greater`로 최소 힙.
- **내부 컨테이너 변경**: `std::priority_queue<int, std::deque<int>>` 등.

### 비교자 (Comparator)
- `operator()`는 `const` 멤버 함수여야 함: `bool operator()(const T &a, const T &b) const`.
- 반환값: `a`가 `b`보다 우선순위가 낮으면 `true` (최대 힙이면 `a < b`).

### 요소 저장 방식
- `pq.push(x)`는 `x`를 **복사**(또는 move)하여 내부 컨테이너에 저장.
- `for (const auto &p : vec) pq.push(p);` 처럼 참조 변수를 사용해도 무관 → `push`가 내부적으로 복사/이동 생성하므로 원본과 독립적.
- 복사 비용이 크면: `std::move` 사용하거나, 포인터/인덱스 저장 방식 고려.

### 참조처럼 사용하기 (원본 유지)
원본 컨테이너를 수정하지 않고 pq에서 참조처럼 다루려면:
- **인덱스 저장** (권장): pq에 `int` 인덱스를 저장, comparator에서 원본 참조.
- **포인터 저장**: `priority_queue<T*>` 사용. 수명 관리 주의.
- **reference_wrapper**: `std::reference_wrapper<T>` 사용. 원본 수명 보장 필요.

**예시: 인덱스 기반 최소힙**
```cpp
struct CmpIdx {
    const vector<vector<int>> *data;
    CmpIdx(const vector<vector<int>> *d) : data(d) {}
    bool operator()(int i, int j) const {
        // data[i][1] 기준 오름차순 (같으면 [0] 오름차순)
        if ((*data)[i][1] != (*data)[j][1]) 
            return (*data)[i][1] > (*data)[j][1];
        return (*data)[i][0] > (*data)[j][0];
    }
};

priority_queue<int, vector<int>, CmpIdx> pq((CmpIdx(&program)));
for (int i = 0; i < program.size(); ++i) pq.push(i);
```


## 사용 예시
```cpp
#include <queue>
#include <iostream>

std::priority_queue<int> pq;
pq.push(3);
pq.push(1);
pq.push(2);
std::cout << pq.top();  // 3
pq.pop();
std::cout << pq.top();  // 2
```

## 주의사항
- `pop()`은 반환 없음, `top()`으로 먼저 확인.
- 큐가 비었을 때 `top()`는 정의되지 않은 동작.
- 힙 속성: push/pop 시 자동 정렬.
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않음.
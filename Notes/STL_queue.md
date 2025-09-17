# std::queue 알아야 할 것 정리

`<queue>` 헤더에 정의된 FIFO 큐 컨테이너 어댑터. 먼저 들어온 요소가 먼저 나옵니다.

## 기본 개념
- **FIFO**: First In, First Out.
- **어댑터**: 내부 컨테이너 사용 (기본 std::deque).
- **용도**: 큐 구현, BFS 등.

## 생성자
```cpp
std::queue<int> q;                    // 빈 큐
std::queue<int, Container> q;         // 사용자 정의 컨테이너
std::queue<int> q(other);             // 복사 생성자
std::queue<int> q(std::move(other));  // 이동 생성자
```

## 주요 멤버 함수
- `push(const T&)` / `push(T&&)`: 뒤에 추가.
- `pop()`: 앞 요소 제거 (반환 없음).
- `front()`: 앞 요소 참조.
- `back()`: 뒤 요소 참조.
- `empty()`: 비었는지 확인.
- `size()`: 요소 수.

## 연산자
- `==`, `!=`, `<`, `<=`, `>`, `>=`: 요소별 비교.

## 기타
- **내부 컨테이너 변경**: `std::queue<int, std::list<int>>` 등.

## 사용 예시
```cpp
#include <queue>
#include <iostream>

std::queue<int> q;
q.push(1);
q.push(2);
std::cout << q.front();  // 1
q.pop();
std::cout << q.front();  // 2
```

## 주의사항
- `pop()`은 반환 없음, `front()`로 먼저 확인.
- 스택이 비었을 때 `front()`/`back()`는 정의되지 않은 동작.
- 스레드 안전: 표준 라이브러리는 스레드 안전하지 않음.

# std::vector 요약

이 문서는 C++ 표준 라이브러리의 컨테이너 `std::vector`에 대한 간단한 개요를 제공합니다. 복잡한 구현은 별도 파일로 분리할 예정이므로, 사용법과 주의사항 중심의 개요만 담았습니다.

## 핵심 특성

- 동적 배열을 감싸는 컨테이너
- 연속된 메모리(continuous storage)
- O(1) 임의 접근: operator[] / at()
- 끝에 추가/삭제: amortized O(1) (push_back/pop_back)

## 생성과 초기화

- 기본 생성자: `vector<T> v;`
- 크기 지정: `vector<T> v(n);` (기본값으로 T())
- 값으로 초기화: `vector<T> v(n, value);`
- 리스트 초기화: `vector<int> v = {1,2,3};`

## 원소 접근

- `v[i]` — 경계 검사 없음
- `v.at(i)` — 경계 검사(예외 발생)
- `v.front()`, `v.back()` — 첫/마지막 원소

## 용량 관련

- `v.size()` — 현재 원소 수
- `v.capacity()` — 할당된 용량
- `v.empty()` — 비어있는지
- `v.reserve(n)` — 최소 용량 보장 (재할당 방지)
- `v.shrink_to_fit()` — 권고에 의한 여유 메모리 반환

주의: `reserve`는 재할당 수를 줄여 성능을 개선하지만, `shrink_to_fit`은 구현별로 다르게 동작합니다.

## 수정자 (modifiers)

- `push_back`, `emplace_back` — 끝에 추가
- `pop_back` — 끝에서 제거
- `insert(pos, ...)` — 중간 삽입 (선형 시간)
- `erase(pos)` / `erase(first, last)` — 원소 제거 (선형 시간)
- `clear()` — 모든 원소 제거
- `swap(other)` — 상수 시간으로 내부 버퍼 교체

팁: 중간 삽입/삭제가 많은 경우 `std::list`/`std::deque` 또는 알고리즘 재설계 고려.

## 이터레이터와 무효화 규칙

- 재할당(reallocation)이 발생하면 모든 이터레이터, 참조, 포인터가 무효화됩니다.
- `push_back`이 capacity를 초과하지 않으면 기존 이터레이터는 유효.
- `insert`/`erase`는 삽입/삭제 위치 이후의 이터레이터를 무효화.

## 성능·복잡도 요약

- 임의 접근: O(1)
- push_back: amortized O(1)
- insert/erase(중간): O(n)
- reserve: O(1) (메모리 할당은 비용이므로 주의)

## 자주 쓰이는 패턴

- erase-remove idiom (값 제거):

- 정렬 후 중복 제거: `sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());`
- 미리 용량 예약: `v.reserve(estimate);` — push_back 반복 시 유용

## 간단 예시 (개요)

// 벡터 선언, 초기화, 반복 사용 예시(구체 구현은 별도 파일로)

## 주의사항 / 휴리스틱

- 큰 자료(heavy objects)는 `vector<T>`에 `move`/`emplace`로 삽입하거나 `vector<unique_ptr<T>>` 같은 포인터/스마트 포인터 사용을 고려
- 멀티스레드: 읽기 전용 접근은 안전하지만, 수정이 있는 경우 동기화 필요

---

더 자세한 예제 구현(복잡한 메서드)은 요청하시면 별도 파일로 분리하여 추가해 드립니다.


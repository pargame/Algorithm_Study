
# <algorithm> 모듈 요약

이 문서는 C++ 표준 라이브러리 헤더 `<algorithm>`의 주요 알고리즘과 사용상의 주의사항을 간단히 정리한 개요입니다. 각 알고리즘의 복잡한 예외/세부 구현은 별도 파일로 분리합니다.

## 분류

- 비수정 알고리즘 (non-modifying): `all_of`, `any_of`, `none_of`, `for_each`, `find`, `find_if`, `count`, `count_if`
- 수정 알고리즘 (modifying): `copy`, `copy_if`, `move`, `fill`, `generate`, `replace`, `remove`, `remove_if`, `unique`
- 정렬·정렬 관련: `sort`, `partial_sort`, `stable_sort`, `nth_element`, `is_sorted`
- 집합 연산: `merge`, `set_union`, `set_intersection`, `set_difference`, `includes`
- 이진 탐색 관련: `lower_bound`, `upper_bound`, `binary_search`, `equal_range`
- 힙 관련: `make_heap`, `push_heap`, `pop_heap`, `sort_heap`
- 범용 유틸리티: `swap`, `min`, `max`, `min_element`, `max_element`, `accumulate`(algorithm은 아니지만 자주 함께 사용)

## 복잡도 요약(일반적인 경우)

- 선형 탐색/변환: O(n)
- 정렬: 평균 O(n log n)
- 이진 탐색(lower/upper_bound): O(log n) (정렬된 범위에서)
- set_*-계열(두 정렬된 범위): O(n + m)

## 사용 팁

- 가능한 한 범위 기반(iterator pair)을 사용하세요: `begin/end`.
- 정렬이 필요한 알고리즘(예: binary_search, lower_bound, set_union)은 입력이 정렬되어 있어야 함을 항상 확인하세요.
- 사용자 정의 타입에 대해 비교자를 제공할 때에는 엄격 약순(Strict Weak Ordering)을 만족해야 합니다.
- 알고리즘은 일반적으로 iterator 종류(랜덤 접근, 양방향 등)에 따라 성능/제약이 달라집니다. 예: `random_access_iterator`가 아닌 경우 `nth_element`는 사용할 수 없음.

## 알고리즘 조합 패턴

- erase-remove idiom: `v.erase(remove(v.begin(), v.end(), val), v.end());`
- transform + copy: `transform(in.begin(), in.end(), out.begin(), func);`
- 파이프라인 스타일: 여러 알고리즘을 조합하여 깔끔한 코드 작성 가능 (중간 컨테이너 복사를 피하도록 주의)

## 예시 요약 (개요 수준)

- 값 찾기: `auto it = find(v.begin(), v.end(), value); if (it != v.end()) ...`
- 조건 기반 카운트: `int c = count_if(v.begin(), v.end(), [](auto &x){ return cond; });`
- 정렬 및 중복 제거: `sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());`
- lower_bound 사용: `auto it = lower_bound(v.begin(), v.end(), key);` (정렬 필요)

## 주의사항

- 일부 알고리즘은 입력 순서를 변경하거나(정렬 계열) 원본을 수정하는 부작용이 있음. 문서화된 동작을 확인하세요.
- 병렬 알고리즘: C++17 이후 병렬 실행 정책을 제공하는 알고리즘 오버로드(ex: `std::execution::par`)가 있으나, 사용시 스레드 안전성, 데이터 레이스에 주의해야 함.

---

더 상세한 코드 예시와 edge-case 처리(예: 안정성, 비교 함수의 요구사항 등)는 요청하시면 별도 예제 파일로 추가하겠습니다.



## std::vector::erase

### 헤더

```cpp
#include <vector>
#include <algorithm> // erase-remove idiom 또는 C++20 std::erase/erase_if 사용 시
```

### 시그니처

```cpp
iterator erase(const_iterator pos);
iterator erase(const_iterator first, const_iterator last);
```

### 동작

- `erase(pos)`는 반복자 `pos`가 가리키는 단일 요소를 제거합니다. 반환값은 제거된 요소 다음의 요소를 가리키는 반복자(없다면 `end()`)입니다.
- `erase(first,last)`는 [first, last) 범위의 요소들을 제거하고, 제거가 끝난 다음 요소를 가리키는 반복자를 반환합니다.
- 내부적으로는 제거된 뒤 남은 뒤쪽 요소들을 앞으로 이동(shift)시키므로, 제거 위치 뒤에 있는 요소들의 이동(복사/이동 생성자 호출)이 발생합니다.

### 복잡도

- 일반적으로 요소를 한 번 지우는 작업은 O(N) (삭제 위치 이후로 이동해야 하는 요소 수에 비례).
- 범위 삭제 `erase(first,last)`는 삭제 후에 이동해야 하는 요소 수에 따라 비용이 결정됩니다.

### iterator/참조 무효화 규칙

- `erase`는 삭제된 요소와 그 이후의 모든 요소에 대한 반복자, 참조, 포인터를 무효화합니다.
- 삭제 이전의 요소에 대한 반복자/참조는 유효합니다(단 컨테이너의 재할당이 발생하지 않는 상황에서).

### 사용 예시

단일 요소 삭제:

```cpp
std::vector<int> v = {1,2,3,4,5};
v.erase(v.begin() + 2); // 값 3이 제거, v == {1,2,4,5}
```

범위 삭제:

```cpp
v.erase(v.begin() + 1, v.begin() + 3); // 인덱스 1~2 요소 삭제
```

삭제하면서 반복자 안전하게 다음 요소로 진행하기:

```cpp
for(auto it = v.begin(); it != v.end(); ){
	if(should_remove(*it)){
		it = v.erase(it); // erase는 다음 요소의 iterator를 반환하므로 안전
	} else {
		++it;
	}
}
```

하지만 위와 같은 루프는 벡터의 중간에서 자주 삭제하면 비용이 높을 수 있습니다(각 삭제마다 뒤쪽 요소들이 이동됨).

### 삭제 관용구: erase-remove idiom

값이나 조건에 해당하는 모든 요소를 제거하려면 `std::remove`/`std::remove_if`와 `erase`를 함께 쓰는 것이 일반적입니다.

```cpp
// 값이 3인 모든 요소 제거
v.erase(std::remove(v.begin(), v.end(), 3), v.end());

// 조건(predicate)에 해당하는 모든 요소 제거
v.erase(std::remove_if(v.begin(), v.end(), [](int x){ return x%2==0; }), v.end());
```

이 방식은 불필요한 중간 erase 호출을 줄여 한 번의 선형 스캔과 몇 번의 이동으로 처리하므로, 여러 번 erase하는 것보다 효율적입니다.

### C++20: std::erase / std::erase_if (편의 함수)

C++20에서는 `<algorithm>`에 컨테이너에 대해 직접 호출할 수 있는 `std::erase`와 `std::erase_if`가 추가되어 위 erase-remove idiom을 더 편하게 쓸 수 있습니다.

```cpp
// C++20
std::erase(v, 3); // 값이 3인 모든 요소 제거
std::erase_if(v, [](int x){ return x%2==0; });
```

이 함수들은 내부적으로 erase-remove 기법을 사용합니다.

### 주의사항 요약

- 벡터에서 중간 요소를 자주 지우면 성능이 나빠질 수 있음. 많은 삭제 작업이 필요하면 리스트(list)나 다른 자료구조를 고려하거나 먼저 필터링(erase-remove)하는 것이 좋습니다.
- `erase`는 삭제 뒤의 요소들에 대한 모든 반복자/참조를 무효화합니다. 루프에서 제거할 때는 반환된 반복자를 사용해 안전하게 진행하세요.


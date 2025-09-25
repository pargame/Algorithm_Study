# [STL <functional>] 알아야 할 것 정리

`<functional>` 헤더에 정의된 함수 객체, 바인더, 래퍼 등을 제공하는 STL 라이브러리. 함수 포인터나 람다를 객체로 다루고, 함수 합성 및 바인딩을 지원한다.

## 기본 개념
- **함수 객체**: 함수 호출 연산자를 오버로딩한 클래스 객체로, 함수처럼 호출 가능.
- **std::function**: 다양한 호출 가능 객체를 래핑하는 다형성 래퍼. 람다, 함수 포인터, 함수 객체를 통일된 인터페이스로 다룸.
- **std::bind**: 함수의 인자를 바인딩하여 새로운 함수 객체 생성. 부분 적용 지원.
- **std::placeholders**: std::bind에서 자리 표시자로 사용.
- **용도**: 콜백, 이벤트 핸들러, 알고리즘에서 함수 객체 전달 등.

## 생성자 (또는 시그니처)
```cpp
// std::function: 호출 가능 객체 래핑
std::function<int(int)> f = [](int x) { return x * 2; };

// std::bind: 인자 바인딩
auto bound = std::bind(func, std::placeholders::_1, 10);

// 함수 객체 예시
struct Functor {
    int operator()(int x) { return x + 1; }
};
```

## 주요 멤버 함수 (또는 오버로딩)
- std::function: `operator()`, `target()`, `target_type()` 등.
- std::bind: 바인딩된 함수 객체 반환.
- 함수 객체: `operator()` 오버로딩.

## 연산자
- `()`: 호출 연산자, 함수처럼 호출.
- `==`, `!=`: std::function 간 비교 가능 (타입이 같을 때).

## 기타 (이터레이터, 헬퍼 함수 등)
- **std::ref/std::cref**: 참조 래퍼, std::bind에서 참조 전달.
- **std::mem_fn**: 멤버 함수를 함수 객체로 변환.
- **std::not_fn**: 함수 객체의 부정.
- **람다 활용**: 람다를 std::function으로 래핑하거나 std::bind와 결합.

## 사용 예시
```cpp
#include <functional>
#include <iostream>

void func(int a, int b) {
    std::cout << a + b << std::endl;
}

int main() {
    // std::function으로 람다 래핑
    std::function<int(int)> f = [](int x) { return x * 2; };
    std::cout << f(5) << std::endl;  // 10

    // std::bind로 인자 바인딩
    auto bound = std::bind(func, std::placeholders::_1, 10);
    bound(5);  // 15 출력

    // 함수 객체
    Functor fn;
    std::cout << fn(3) << std::endl;  // 4
}
```

## 주의사항
- **성능**: std::function은 타입 소거로 오버헤드 발생, 가능하면 직접 사용.
- **안전성**: 바인딩 시 참조 dangling 주의.
- **호환성**: C++11 이상 지원.
- **기타**: 재귀 함수는 std::function으로 래핑 필요.
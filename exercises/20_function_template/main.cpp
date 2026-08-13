#include "../exercise.h"
#include <cmath>

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// 模板化后，同一份代码可用于 int/unsigned/float/double 等所有支持 + 的类型
template<class T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // 0.1、0.2、0.3 都无法用二进制浮点精确表示，相加后必然有舍入误差，
    // 因此不能直接判等，只能判断差值是否小于可接受的误差。
    ASSERT(std::abs(plus(0.1, 0.2) - 0.3) < 1e-9, "How to make this pass?");

    return 0;
}

#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// (count, value) 构造：100 个 true
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    // 位压缩后的成员布局由标准库实现决定，两种实现都要能通过：
    // libc++ 是「起始指针 + size + 容量」三个字长 = 24；
    // libstdc++ 是两个 _Bit_iterator（各含指针与位偏移，对齐到 16 字节）
    // 加一个存储末尾指针 = 40。
#if defined(_LIBCPP_VERSION)
    ASSERT(sizeof(vec) == 3 * sizeof(void *), "Fill in the correct value.");
#else
    ASSERT(sizeof(vec) == 5 * sizeof(void *), "Fill in the correct value.");
#endif
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // vector<bool> 是位压缩特化，operator[] 返回的不是 bool&，
        // 而是一个指向那一位的代理对象。auto 推导出的是这个代理类型，
        // 所以对 ref 赋值等价于改写 vec[30] 本身。
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}

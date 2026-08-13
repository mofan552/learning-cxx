#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;
    // 记录缓存容量，复制时才能完整复刻源对象的可用空间
    int capacity;

public:
    DynFibonacci(int capacity) : cache(new size_t[capacity]{0, 1}), cached(2), capacity(capacity) {}

    // 深复制：另开一块同样大小的缓存，避免两个对象共享同一指针导致双重释放
    DynFibonacci(DynFibonacci const &other)
        : cache(new size_t[other.capacity]), cached(other.cached), capacity(other.capacity) {
        for (int i = 0; i < capacity; ++i) {
            cache[i] = other.cache[i];
        }
    }

    ~DynFibonacci() {
        delete[] cache;
    }

    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}

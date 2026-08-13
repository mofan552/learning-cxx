#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    // weak_ptr 不参与计数：持有者是 shared 和 ptrs 的三个元素
    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    // ptrs[2] 改指向另一个新对象，原对象只剩 shared 一个持有者
    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    // 移动赋值：shared 交出所有权，总持有者数不变，仍是三个数组元素
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");

    // std::ignore 的 operator= 只是绑定引用，并不真的移动，ptrs[0] 仍持有
    std::ignore = std::move(ptrs[0]);
    // 自移动赋值实现为「先移动构造临时量再 swap」，结果所有权原样回到 ptrs[1]
    ptrs[1] = std::move(ptrs[1]);
    // ptrs[1] 放弃自己那份，接管 ptrs[2]，净减一个持有者
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    // 对象已析构，weak_ptr 失效，lock 返回空指针
    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}

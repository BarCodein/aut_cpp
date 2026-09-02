#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr{
public:
    SharedPtr() noexcept;
    explicit SharedPtr(T* p) noexcept;
    ~SharedPtr() noexcept;

    SharedPtr(const SharedPtr& sptr) noexcept;
    SharedPtr& operator=(const SharedPtr& sptr) noexcept;

    explicit operator bool() const noexcept;

    size_t use_count() noexcept;

    T* get() const noexcept;
    T operator*() const noexcept;
    T* operator->() const noexcept;
    void reset() noexcept;
    void reset(T* p) noexcept;



private:
    T* _p;
    size_t* count;
};

template <typename T,typename... Args>
SharedPtr<T> make_shared(Args&&... args);

#include "shared_ptr.hpp"

#endif //SHARED_PTR
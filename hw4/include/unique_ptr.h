#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr{
public:
    UniquePtr() noexcept;
    explicit UniquePtr(T* p) noexcept;
    ~UniquePtr() noexcept;

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    T* get() const noexcept;
    T& operator*() const noexcept;
    T* operator->() const noexcept;

    explicit operator bool() const noexcept;

    void reset() noexcept;

    void reset(T* p) noexcept;

    T* release() noexcept;

private:
    T* _p;
};

template <typename T,typename... Args>
UniquePtr<T> make_unique(Args&&... args);

#include "unique_ptr.hpp"









#endif //UNIQUE_PTR
#pragma once
#include <utility>

template <typename T>
UniquePtr<T>::UniquePtr() noexcept : _p(nullptr){}

template <typename T>
UniquePtr<T>::UniquePtr(T* p) noexcept : _p(p){}

template <typename T>
UniquePtr<T>::~UniquePtr() noexcept{
    delete _p;
    _p = nullptr;
}

template <typename T>
UniquePtr<T>::operator bool() const noexcept{
    return _p!=nullptr;
}

template <typename T>
T* UniquePtr<T>::get() const noexcept{
    return _p;
}

template <typename T>
T& UniquePtr<T>::operator*() const noexcept{
    return *_p;
}

template <typename T>
T* UniquePtr<T>::operator->() const noexcept{
    return _p;
}

template <typename T>
void UniquePtr<T>::reset() noexcept{
    delete _p;
    _p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T* p) noexcept{
    delete _p;
    _p = p;
}

template <typename T>
T* UniquePtr<T>::release() noexcept{
    T* tmp = _p;
    _p = nullptr;
    return tmp;
}

template <typename T,typename... Args>
UniquePtr<T> make_unique(Args&&... args){
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
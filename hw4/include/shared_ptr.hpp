#pragma once

#include <utility>
#include "shared_ptr.h"

template<typename T>
SharedPtr<T>::SharedPtr() noexcept : _p(nullptr),count(new size_t(1)){}

template<typename T>
SharedPtr<T>::SharedPtr(T* p) noexcept : _p(p), count(new size_t(1)){}

template<typename T>
SharedPtr<T>::~SharedPtr() noexcept{
    (*count)--;
    if (*count==0){
        delete _p;
        _p = nullptr;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& sptr) noexcept: _p(sptr._p), 
    count(sptr.count){
        (*count)++;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& sptr) noexcept{
    if (&sptr == this)  return *this;
    _p = sptr._p;
    count = sptr.count;
    (*count)++;
    return *this;
}

template <typename T>
SharedPtr<T>::operator bool() const noexcept{
    return _p!=nullptr;
}

template <typename T>
size_t SharedPtr<T>::use_count() noexcept{
    return *count;
}

template <typename T>
T* SharedPtr<T>::get() const noexcept{
    return _p;
}

template <typename T>
T SharedPtr<T>::operator*() const noexcept{
    return *_p;
}

template <typename T>
T* SharedPtr<T>::operator->() const noexcept{
    return _p;
}

template <typename T>
void SharedPtr<T>::reset() noexcept{
    delete _p;
    _p = nullptr;
    (*count) = 0;
}

template <typename T>
void SharedPtr<T>::reset(T* p) noexcept{
    delete _p;
    _p = p;
}

template <typename T,typename... Args>
SharedPtr<T> make_shared(Args&&... args){
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}
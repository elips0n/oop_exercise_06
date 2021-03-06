#pragma once

#include <cstdlib>
#include <iostream>
#include <type_traits>
#include "vector.h"

namespace allocators {

    template<class T, size_t ALLOC_SIZE>//ALLOC_SIZE - размер, который требуется выделить
    struct my_allocator {

    private:
        char* pool_begin; //указатель на начало хранилища
        char* pool_end;//указатель на конец хранилища                   
        char* pool_tail;//указатель на конец заполненного пространства     
        Vector<char *> free_blocks;
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using is_always_equal = std::false_type;

        template<class U>
        struct rebind {
            using other = my_allocator<U, ALLOC_SIZE>;
        };

        my_allocator() :
            pool_begin(new char[ALLOC_SIZE]),
            pool_end(pool_begin + ALLOC_SIZE),
            pool_tail(pool_begin)
        {}

        my_allocator(const my_allocator&) = delete;
        my_allocator(my_allocator&&) = delete;

        ~my_allocator() {
            delete[] pool_begin;
			pool_begin = pool_end = pool_tail = nullptr;
			free_blocks.~Vector();

        }

        T* allocate(std::size_t n);
        void deallocate(T* ptr, std::size_t n);

    };

    template<class T, size_t ALLOC_SIZE>
    T* my_allocator<T, ALLOC_SIZE>::allocate(std::size_t n) {
        if (n != 1) {
            throw std::logic_error("can`t allocate arrays");
        }
        if (size_t(pool_end - pool_tail) < sizeof(T)) {
            if (!free_blocks.Empty()) {//ищем свободное место в райне отданном пространстве
                char* ptr = free_blocks.Back();
				free_blocks.PopBack();
                return reinterpret_cast<T*>(ptr);
            }
            std::cout<<"Bad Alloc"<<std::endl;
            throw std::bad_alloc();
        }
        T* result = reinterpret_cast<T*>(pool_tail);//приведение к типу
        pool_tail += sizeof(T);
        return result;
    }

    template<class T, size_t ALLOC_SIZE>
    void my_allocator<T, ALLOC_SIZE>::deallocate(T* ptr, std::size_t n) {
        if (n != 1) {
            throw std::logic_error("can`t allocate arrays, thus can`t deallocate them too");
        }
        if (ptr == nullptr) {
            return;
        }
        free_blocks.PushBack(reinterpret_cast<char*>(ptr));
    }

}

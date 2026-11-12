#pragma once
#include <iostream>

template <typename T>
class Stack {
    static constexpr unsigned int maxValue = UINT_MAX;
    int top_i, size;
    T* pMem;

    void resize() {
        int new_size = (size == 0) ? 1 : size * 2;
        T* new_pMem = new T[new_size];
        for (int i = 0; i <= top_i; i++) {
            new_pMem[i] = pMem[i];
        }
        delete[] pMem;
        pMem = new_pMem;
        size = new_size;
    }
public:
    Stack(int _size = 1) : top_i(-1), size(_size) {
        if (_size <= 0 || _size > UINT_MAX) throw "некорректный размер";
        pMem = new T[size];
    }
    ~Stack() {
        size = 0;
        top_i = -1;
        delete[] pMem;
    }

    Stack(const Stack& st) noexcept {
        size = st.size;
        top_i = st.top_i;
        pMem = new T[size];
        for (int i = 0; i <= top_i; i++) {
            pMem[i] = st.pMem[i];
        }
    }

    Stack(Stack&& st) noexcept{
        size = st.size;
        top_i = st.top_i;
        pMem = st.pMem;
        st.pMem = nullptr;
        st.size = 0;
        st.top_i = -1;
    }


    Stack<T>& operator=(const Stack<T>& st) {
        if (this != &st) { 
            T* newMem = new T[st.size];
            for (int i = 0; i <= st.top_i; i++) newMem[i] = st.pMem[i];
            delete[] pMem;
            pMem = newMem;
            size = st.size;
            top_i = st.top_i;
        }
        return *this;
    }

    Stack& operator=(Stack&& st) noexcept {
        if (this != &st) {
            delete[] pMem;
            pMem = st.pMem;
            size = st.size;
            top_i = st.top_i;
            st.pMem = nullptr;
            st.size = 0;
            st.top_i = -1;
        }
        return *this;
    }

    bool operator==(const Stack <T>& st) const {
        if (size != st.size) return false;
        if (top_i != st.top_i) return false;
        for (int i = 0; i <= top_i; i++) {
            if (pMem[i] != st.pMem[i]) return false;
        }
        return true;
    }

    bool operator!=(const Stack& st) const noexcept {
        return !(*this == st);
    }

    bool IsFull() const {
        return top_i == size - 1;
    }
    bool IsEmpty() const {
        return top_i == -1;
    }

    void Clear() noexcept {
        top_i = -1;
    }


    void push(const T& el) {
        if (IsFull()) {
            resize();
        }
        pMem[++top_i] = el; 
    }

    T pop() {
        if (IsEmpty()) { throw "Стек пуст"; }
        else {
            top_i--;
            return pMem[top_i + 1];
        }
    }

    T top() const {
        if (IsEmpty()) throw "Стек пуст";
        return pMem[top_i];
    }
    void clear() noexcept {
        top_i = -1;
    }
};

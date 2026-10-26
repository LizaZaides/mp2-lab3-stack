#include <iostream>

template <typename T>
class Stack {
    int top_i, size;
    T* pMem;
public:
    Stack(int _size = 1) : top_i(-1), size(_size) {
        pMem = new T[size];
    }
    ~Stack() {
        delete[] pMem;
    }

    Stack(const Stack& s) {
        size = s.size;
        top_i = s.top_i;
        pMem = new T[size];
        for (int i = 0; i < top_i; i++) {
            pMem[i] = s.pMem[i];
        }
    }

    Stack(Stack&& s) noexcept: top_i(s.top_i), size(s.size), pMem(s.pMem) {
        s.pMem = nullptr;
        s.top_i = -1;
        s.size = 0;
    }
    //конструктор перемещения, оператор присваиваня с перемещением самим

    Stack<T>& operator=(const Stack <T>& st) {
        if (&st == this) {
            if (this->size = st.size) {
                size = st.size;
                delete[] pMem;
                pMem = new T[size];
            }
            top_i = st.top_i;
            for (int i = 0; i < top_i; i++) {
                pMem[i] = st.pMem[i];
            }
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

    bool operator==(const Stack <T>& st) {
        if (size != st.size) return false;
        if (top_i != st.top_i) return false;
        for (int i = 0; i < top_i; i++) {
            if (pMem[i] != st.pMem[i]) return false;
        }
        return true;
    }

    bool IsFull() {
        return top_i == size - 1;
    }
    bool IsEmpty() {
        return top_i == -1;
    }

    void Clear() {
        top = -1;
    }


    void push(T el) {
        if (IsFull()) { trow ""; }
        else {
            top_i++;
            pMem[top_i] = el;
        }
    }

    T pop() {
        //исключение
        if (IsEmpty) { throw ""; }
        else {
            top_i--;
            return pMem[top_i + 1];
        }
    }
};

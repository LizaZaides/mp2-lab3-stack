#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Container {
    int size;
    int count;
    T* pMem;

    void resize() {
        int new_size = (size == 0) ? 1 : size * 2;
        T* new_pmem = new T[new_size];
        for (int i = 0; i < count; i++) {
            new_pmem[i] = pMem[i];
        }
        delete[] pMem;
        pMem = new_pmem;
        size = new_size;
    }

public:
    Container(int _size = 10) : size(_size), count(0) {
        if (_size <= 0) throw "размер меньше или равен 0";
        pMem = new T[size];
    }

    ~Container() {
        delete[] pMem;
    }

    Container(const Container& c) : size(c.size), count(c.count) {
        pMem = new T[c.size];
        for (int i = 0; i < count; i++) {
            pMem[i] = c.pMem[i];
        }
    }

    Container(Container&& c) noexcept : size(c.size), count(c.count), pMem(c.pMem) {
        c.size = 0;
        c.count = 0;
        c.pMem = nullptr;
    }

    Container& operator=(const Container& c) {
        if (this != &c) {
            T* newMem = new T[c.size];
            for (int i = 0; i < c.count; i++) {
                newMem[i] = c.pMem[i];
            }
            delete[] pMem;
            pMem = newMem;
            size = c.size;
            count = c.count;
        }
        return *this;
    }

    Container& operator=(Container&& c) noexcept {
        if (this != &c) {
            delete[] pMem;
            size = c.size;
            count = c.count;
            pMem = c.pMem;
            c.size = 0;
            c.count = 0;
            c.pMem = nullptr;
        }
        return *this;
    }

    T& operator[](int ind) {
        if (ind < 0 || ind >= count) throw "Неверный индекс";
        return pMem[ind];
    }

    const T& operator[](int ind) const {
        if (ind < 0 || ind >= count) throw "Неверный индекс";
        return pMem[ind];
    }

    Container& Size(int s) {
        if (s <= 0) throw "размер меньше или равен 0";
        if (size != s) {
            if (count > s) count = s;
            T* pNew = new T[s];
            int min = (size < s) ? size : s;
            for (int i = 0; i < min; i++) {
                pNew[i] = pMem[i];
            }
            delete[] pMem;
            pMem = pNew;
            size = s;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Container& v) {
        for (int i = 0; i < v.count; i++) out << v.pMem[i] << " ";
        return out;
    }

    friend istream& operator>>(istream& in, Container& v) {
        for (int i = 0; i < v.count; i++) in >> v.pMem[i];
        return in;
    }

    void push_back(const T& elem) {
        if (count >= size) {
            resize();
        }
        pMem[count++] = elem;
    }

    T pop_back() {
        if (count == 0) {
            throw "Контейнер пустой";
        }
        return pMem[--count];
    }

    void clear() noexcept {
        count = 0;
    }
    int get_count() const { return count; }
    int get_size() const { return size; }
};
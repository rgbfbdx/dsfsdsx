#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
private:
    T* data;
    int size;
    int count;
    int grow;

    void resize(int newSize) {
        T* newData = new T[newSize];
        for (int i = 0; i < count && i < newSize; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        size = newSize;
        if (count > size) count = size;
    }

public:
    Array() : data(nullptr), size(0), count(0), grow(1) {}

    explicit Array(int sz, int gr = 1) : size(sz), grow(gr), count(0) {
        if (sz < 0 || gr <= 0) throw std::invalid_argument("Invalid parameters");
        data = new T[size];
    }

    Array(const Array<T>& other) : size(other.size), count(other.count), grow(other.grow) {
        data = new T[size];
        for (int i = 0; i < count; ++i)
            data[i] = other.data[i];
    }

    ~Array() {
        delete[] data;
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            count = other.count;
            grow = other.grow;
            data = new T[size];
            for (int i = 0; i < count; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    int GetSize() const { return size; }

    void SetSize(int newSize, int newGrow = 1) {
        if (newSize < 0 || newGrow <= 0) throw std::invalid_argument("Invalid parameters");
        grow = newGrow;
        resize(newSize);
    }

    int GetUpperBound() const { return count - 1; }

    bool IsEmpty() const { return count == 0; }

    void FreeExtra() { resize(count); }

    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = count = 0;
    }

    T& GetAt(int index) {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& GetAt(int index) const {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of range");
        data[index] = value;
    }

    T& operator[](int index) { return GetAt(index); }

    const T& operator[](int index) const { return GetAt(index); }

    void Add(const T& value) {
        if (count >= size)
            resize(size + grow);
        data[count++] = value;
    }

    void Append(const Array<T>& other) {
        int requiredSize = count + other.count;
        if (requiredSize > size)
            resize(((requiredSize - 1) / grow + 1) * grow);
        for (int i = 0; i < other.count; ++i)
            data[count++] = other.data[i];
    }

    T* GetData() { return data; }

    const T* GetData() const { return data; }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > count) throw std::out_of_range("Index out of range");
        if (count >= size)
            resize(size + grow);
        for (int i = count; i > index; --i)
            data[i] = data[i - 1];
        data[index] = value;
        ++count;
    }

    void RemoveAt(int index, int num = 1) {
        if (index < 0 || index + num > count) throw std::out_of_range("Index out of range");
        for (int i = index; i < count - num; ++i)
            data[i] = data[i + num];
        count -= num;
    }
};

#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

class MyVector {
private:
    int _size = 0;
    int _capacity = 0;
    int* _data = nullptr;

    void reallocate(int new_capacity) {
        int* new_data = new int[new_capacity];
        if (_data) {
            copy(_data, _data + _size, new_data);
            delete[] _data;
        }
        _data = new_data;
        _capacity = new_capacity;
    }

public:
    // Базовый конструктор
    MyVector() : _size(0), _capacity(0), _data(nullptr) {}

    // Конструктор с размером и начальным значением
    MyVector(int n, int initialValue = 0) : _size(n), _capacity(n) {
        _data = new int[_capacity];
        fill(_data, _data + _size, initialValue);
    }

    // Конструктор копирования
    MyVector(const MyVector& other) : _size(other._size), _capacity(other._size) {
        _data = new int[_capacity];
        copy(other._data, other._data + _size, _data);
    }

    // Оператор присваивания копированием
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _capacity = other._size;
            _data = new int[_capacity];
            copy(other._data, other._data + _size, _data);
        }
        return *this;
    }

    // Деструктор
    ~MyVector() {
        delete[] _data;
    }

    // Изменение размера
    void resize(int new_size, int value = 0) {
        if (new_size > _capacity) {
            reserve(max(new_size, _capacity * 2));
        }
        if (new_size > _size) {
            fill(_data + _size, _data + new_size, value);
        }
        _size = new_size;
    }

    // Резервирование памяти
    void reserve(int new_capacity) {
        if (new_capacity > _capacity) {
            reallocate(new_capacity);
        }
    }

    // Уменьшение емкости до размера
    void shrink_to_fit() {
        if (_size < _capacity) {
            reallocate(_size);
        }
    }

    // Доступ к первому элементу
    int& front() {
        if (_size == 0) throw out_of_range("Vector is empty");
        return _data[0];
    }

    const int& front() const {
        if (_size == 0) throw out_of_range("Vector is empty");
        return _data[0];
    }

    // Доступ к последнему элементу
    int& back() {
        if (_size == 0) throw out_of_range("Vector is empty");
        return _data[_size - 1];
    }

    const int& back() const {
        if (_size == 0) throw out_of_range("Vector is empty");
        return _data[_size - 1];
    }

    // Размер вектора
    int size() const { return _size; }

    // Проверка на пустоту
    bool empty() const { return _size == 0; }

    // Емкость вектора
    int capacity() const { return _capacity; }

    // Добавление элемента в конец
    void push_back(int value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = value;
    }

    // Вставка элемента
    void insert(int pos, int value) {
        if (pos < 0 || pos > _size) throw out_of_range("Invalid position");

        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }

        for (int i = _size; i > pos; --i) {
            _data[i] = _data[i - 1];
        }

        _data[pos] = value;
        ++_size;
    }

    // Удаление элемента
    void erase(int pos) {
        if (pos < 0 || pos >= _size) throw out_of_range("Invalid position");

        for (int i = pos; i < _size - 1; ++i) {
            _data[i] = _data[i + 1];
        }

        --_size;
    }

    // Оператор доступа по индексу
    int& operator[](int index) {
        return _data[index];
    }

    const int& operator[](int index) const {
        return _data[index];
    }

    // Вывод содержимого
    void print() const {
        for (int i = 0; i < _size; ++i) {
            cout << _data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Тестирование всех функций
    MyVector v1(5, 10);
    v1.print(); // 10 10 10 10 10

    v1.push_back(20);
    v1.print(); // 10 10 10 10 10 20

    v1.insert(2, 30);
    v1.print(); // 10 10 30 10 10 10 20

    v1.erase(3);
    v1.print(); // 10 10 30 10 10 20

    cout << "Front: " << v1.front() << ", Back: " << v1.back() << endl;
    cout << "Size: " << v1.size() << ", Capacity: " << v1.capacity() << endl;

    v1.resize(3);
    v1.print(); // 10 10 30

    v1.shrink_to_fit();
    cout << "After shrink: Size = " << v1.size()
        << ", Capacity = " << v1.capacity() << endl;

    MyVector v2 = v1;
    v2.print(); // 10 10 30

    MyVector v3;
    v3 = v1;
    v3.print(); // 10 10 30

    return 0;
}

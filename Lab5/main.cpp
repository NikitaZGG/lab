
#include <iostream>
#include <algorithm> 

using namespace std;

class MyVector {
private:
    int _size;        
    int _capacity;    
    int* _data;      

public:
    MyVector() : _size(0), _capacity(0), _data(nullptr) {}

    MyVector(int n, int initialValue = 0) : _size(n), _capacity(n) {
        _data = new int[n];
        for (int i = 0; i < n; ++i) {
            _data[i] = initialValue;
        }
    }

    MyVector(const MyVector& other) : _size(other._size), _capacity(other._capacity) {
        _data = new int[_capacity];
        std::copy(other._data, other._data + _size, _data); 
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] _data;

            _size = other._size;
            _capacity = other._capacity;
            _data = new int[_capacity];
            std::copy(other._data, other._data + _size, _data);
        }
        return *this;
    }

    ~MyVector() {
        delete[] _data;
    }

    
    void resize(int newSize) {
        if (newSize > _capacity) {
            reserve(newSize);
        }

        if (newSize > _size) {
            for (int i = _size; i < newSize; ++i) {
                _data[i] = 0;
            }
        }

        _size = newSize;
    }

    void reserve(int newCapacity) {
        if (newCapacity > _capacity) {
            int* newData = new int[newCapacity];
            if (_data) {
                std::copy(_data, _data + _size, newData);
                delete[] _data;
            }
            _data = newData;
            _capacity = newCapacity;
        }
    }

    void shrink_to_fit() {
        if (_size < _capacity) {
            int* newData = new int[_size];
            std::copy(_data, _data + _size, newData);
            delete[] _data;
            _data = newData;
            _capacity = _size;
        }
    }

    int& front() {
        if (_size == 0) {
            throw std::out_of_range("MyVector::front: Vector is empty");
        }
        return _data[0];
    }

    const int& front() const {
        if (_size == 0) {
            throw std::out_of_range("MyVector::front: Vector is empty");
        }
        return _data[0];
    }


    int& back() {
        if (_size == 0) {
            throw std::out_of_range("MyVector::back: Vector is empty");
        }
        return _data[_size - 1];
    }

    const int& back() const {
        if (_size == 0) {
            throw std::out_of_range("MyVector::back: Vector is empty");
        }
        return _data[_size - 1];
    }
    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    int capacity() const {
        return _capacity;
    }

    void push_back(int value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = value;
    }

    void insert(int position, int value) {
        if (position < 0 || position > _size) {
            throw std::out_of_range("MyVector::insert: Invalid position");
        }

        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }

        for (int i = _size; i > position; --i) {
            _data[i] = _data[i - 1];
        }

        _data[position] = value;

        _size++;
    }

    void erase(int position) {
        if (position < 0 || position >= _size) {
            throw std::out_of_range("MyVector::erase: Invalid position");
        }

        for (int i = position; i < _size - 1; ++i) {
            _data[i] = _data[i + 1];
        }

        _size--;
    }

    int& operator[](int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("MyVector::operator[]: Index out of range");
        }
        return _data[index];
    }

    const int& operator[](int index) const {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("MyVector::operator[]: Index out of range");
        }
        return _data[index];
    }
    void print() const {
        for (int i = 0; i < _size; ++i) {
            cout << _data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MyVector v1;
    cout << "v1.size(): " << v1.size() << ", v1.capacity(): " << v1.capacity() << endl;

    MyVector v2(5, 10);
    cout << "v2: ";
    v2.print(); 
    cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << endl;

    MyVector v3 = v2;
    cout << "v3: ";
    v3.print(); 
    cout << "v3.size(): " << v3.size() << ", v3.capacity(): " << v3.capacity() << endl;

    MyVector v4;
    v4 = v2;
    cout << "v4: ";
    v4.print();
    cout << "v4.size(): " << v4.size() << ", v4.capacity(): " << v4.capacity() << endl;

    cout << "v2.front(): " << v2.front() << ", v2.back(): " << v2.back() << endl;
    v2[0] = 5;
    cout << "v2[0]: " << v2[0] << endl;
    cout << "v2: ";
    v2.print();

    v2.push_back(20);
    cout << "v2 after push_back(20): ";
    v2.print();
    cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << endl;

    v2.insert(2, 30);
    cout << "v2 after insert(2, 30): ";
    v2.print();
    cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << endl;

    v2.erase(3);
    cout << "v2 after erase(3): ";
    v2.print();
    cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << endl;

    v2.resize(3);
    cout << "v2 after resize(3): ";
    v2.print();
    cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << endl;

    v2.reserve(10);
    cout << "v2 after reserve(10): ";
    v2.print();
    cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << endl;

    v2.shrink_to_fit();
    cout << "v2 after shrink_to_fit(): ";
    v2.print();
    cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << endl;

    cout << "v2.empty(): " << v2.empty() << endl;

    MyVector v5;
    cout << "v5.empty(): " << v5.empty() << endl;

    return 0;
}

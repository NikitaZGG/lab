
#include <iostream>
#include <vector>  
#include <algorithm> 
#include <iomanip>   
#include <cmath>     
#include <stdexcept>  

using namespace std;


template <typename T, int N, int M>
class Matrix {
private:
    T data[N][M]; 

public:  
    Matrix() {       
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] = 0;
            }
        }
    }    
    Matrix(const Matrix& other) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    
    Matrix& operator=(const Matrix& other) {
        if (this != &other) { 
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    
    friend istream& operator>>(istream& in, Matrix& matrix) {
        cout << "Введите элементы матрицы " << N << "x" << M << ":" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                in >> matrix.data[i][j];
            }
        }
        return in;
    }

    
    friend ostream& operator<<(ostream& out, const Matrix& matrix) {
        out << "Матрица " << N << "x" << M << ":" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                out << setw(5) << matrix.data[i][j]; 
            }
            out << endl;
        }
        return out;
    }

    
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    
    Matrix& operator+=(const Matrix& other) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    
    Matrix operator*(const Matrix& other) const {
        if constexpr (M != N) {
            throw std::invalid_argument("Нельзя умножить матрицы с такими размерами");
        }

        Matrix result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < M; ++k) {  // Или N, т.к. M == N
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;  
        return *this;
    }
    Matrix& operator++() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                ++data[i][j];
            }
        }
        return *this;
    }
    Matrix operator++(int) {
        Matrix temp = *this; 
        ++(*this); 
        return temp; 
    }

    T determinant() const {
        if constexpr (N == 2 && M == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
        else if constexpr (N == 3 && M == 3) {
            return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
                - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
                + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        }
        else {
            throw std::invalid_argument("Определитель можно вычислить только для матриц 2x2 и 3x3");
        }
    }

    T& operator()(int row, int col) {
        if (row < 0 || row >= N || col < 0 || col >= M) {
            throw std::out_of_range("Индекс выходит за границы матрицы");
        }
        return data[row][col];
    }

    const T& operator()(int row, int col) const {
        if (row < 0 || row >= N || col < 0 || col >= M) {
            throw std::out_of_range("Индекс выходит за границы матрицы");
        }
        return data[row][col];
    }
};

template <typename T>
class MyVector {
public:
    
};


template <>
class MyVector<bool> {
private:
    vector<unsigned char> data; 
    int _size;                   

    bool getBit(int index) const {
        int byteIndex = index / 8;       
        int bitIndex = index % 8;        

        return (data[byteIndex] >> bitIndex) & 1; 
    }

    void setBit(int index, bool value) {
        int byteIndex = index / 8;
        int bitIndex = index % 8;

        if (value) {
            data[byteIndex] |= (1 << bitIndex);  
        }
        else {
            data[byteIndex] &= ~(1 << bitIndex); 
        }
    }

public:
    MyVector() : _size(0) {}

    int size() const {
        return _size;
    }

    void push_back(bool value) {
        int byteIndex = _size / 8;
        int bitIndex = _size % 8;

        if (byteIndex >= data.size()) {
            data.push_back(0); 
        }

        setBit(_size, value); 
        _size++;               
    }

    
    class BitReference { 
        MyVector<bool>* vec;
        int index;
    public:
        BitReference(MyVector<bool>* v, int i) : vec(v), index(i) {}

        operator bool() const { return vec->getBit(index); }

        BitReference& operator=(bool value) {
            vec->setBit(index, value);
            return *this;
        }
    };
    BitReference operator[](int index) {
        if (index < 0 || index >= _size) {
            throw out_of_range("Индекс за пределами диапазона");
        }
        return BitReference(this, index);
    }
    bool operator[](int index) const {
        if (index < 0 || index >= _size) {
            throw out_of_range("Индекс за пределами диапазона");
        }
        return getBit(index);
    }

   
    void insert(int position, bool value) {
        if (position < 0 || position > _size) {
            throw out_of_range("Индекс за пределами диапазона");
        }

        
        for (int i = _size; i > position; --i) {
            bool temp = getBit(i - 1);

            int byteIndex = i / 8;
            int bitIndex = i % 8;
            if (byteIndex >= data.size()) {
                data.push_back(0); 
            }

            setBit(i, temp);
        }
        setBit(position, value);
        _size++;
        return;
    }


    void erase(int position) {
        if (position < 0 || position >= _size) {
            throw out_of_range("Индекс за пределами диапазона");
        }

        for (int i = position + 1; i < _size; ++i) {
            setBit(i - 1, getBit(i));
        }

        _size--;
        return;
    }

    void print() const {
        for (int i = 0; i < _size; ++i) {
            cout << getBit(i);
        }
        cout << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    cout << " " << endl;

    Matrix<int, 2, 2> matrix1;
    cin >> matrix1;
    cout << matrix1;

    Matrix<int, 2, 2> matrix2;
    cin >> matrix2;
    cout << matrix2;

    Matrix<int, 2, 2> sumMatrix = matrix1 + matrix2;
    cout << "Сумма матриц:" << endl << sumMatrix;

    Matrix<int, 2, 2> productMatrix = matrix1 * matrix2;
    cout << "Произведение матриц:" << endl << productMatrix;

    cout << "Определитель matrix1: " << matrix1.determinant() << endl;

    matrix1(0, 0) = 100;
    cout << "matrix1 после изменения элемента (0,0):" << endl << matrix1;

    Matrix<int, 2, 2> matrix3 = matrix1++;
    cout << "matrix1++:" << endl << matrix3;
    cout << "matrix1 после инкремента:" << endl << matrix1;

    ++matrix1;
    cout << "++matrix1:" << endl << matrix1;

    cout << endl << "===================== MyVector<bool> Example =====================" << endl;

    MyVector<bool> boolVector;

    boolVector.push_back(true);
    boolVector.push_back(false);
    boolVector.push_back(true);
    boolVector.push_back(true);

    cout << "Vector contents: ";
    boolVector.print();
    cout << "Size: " << boolVector.size() << endl;

    cout << "Element at index 1: " << boolVector[1] << endl;

    boolVector[1] = true;
    cout << "Vector after setting index 1 to true: ";
    boolVector.print();

    boolVector.insert(2, false);
    cout << "Vector after inserting false at index 2: ";
    boolVector.print();
    cout << "Size: " << boolVector.size() << endl;

    boolVector.erase(3);
    cout << "Vector after erasing element at index 3: ";
    boolVector.print();
    cout << "Size: " << boolVector.size() << endl;

    return 0;
}

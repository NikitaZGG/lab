#include <iostream>
#include <iomanip> 
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
                for (int k = 0; k < M; ++k) {  
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
        } else if constexpr (N == 3 && M == 3) {
            return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
                 - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
                 + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        } else {
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

int main() {
    setlocale(LC_ALL, "Russian");
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

    Matrix<double, 3, 3> matrixDouble;
    cin >> matrixDouble;
    cout << matrixDouble;

    cout << "Определитель matrixDouble: " << matrixDouble.determinant() << endl;

    return 0;
}

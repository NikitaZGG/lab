#include <iostream>
#include <iomanip> // Для форматированного вывода (setw)
using namespace std;

// Шаблонный класс Matrix для работы с матрицами размером N x M
template <typename T, int N, int M>
class Matrix {
private:
    T data[N][M]; // Двумерный массив для хранения элементов матрицы

public:
    // Конструктор по умолчанию - инициализирует матрицу нулями
    Matrix() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] = 0;
            }
        }
    }

    // Конструктор копирования
    Matrix(const Matrix& other) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) { // Проверка на самоприсваивание
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    // Оператор ввода матрицы из потока
    friend istream& operator>>(istream& in, Matrix& matrix) {
        cout << "Введите элементы матрицы " << N << "x" << M << ":" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                in >> matrix.data[i][j];
            }
        }
        return in;
    }

    // Оператор вывода матрицы в поток
    friend ostream& operator<<(ostream& out, const Matrix& matrix) {
        out << "Матрица " << N << "x" << M << ":" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                out << setw(5) << matrix.data[i][j]; // Форматированный вывод
            }
            out << endl;
        }
        return out;
    }

    // Оператор сложения матриц
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Оператор += для сложения матриц
    Matrix& operator+=(const Matrix& other) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    // Оператор умножения матриц
    Matrix operator*(const Matrix& other) const {
        // Проверка совместимости размеров для умножения
        if constexpr (M != N) {
            throw std::invalid_argument("Нельзя умножить матрицы с такими размерами");
        }

        Matrix result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.data[i][j] = 0;
                // Вычисление скалярного произведения строки и столбца
                for (int k = 0; k < M; ++k) {  
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Оператор *= для умножения матриц
    Matrix& operator*=(const Matrix& other) {
        *this = *this * other; // Используем уже реализованный оператор *
        return *this;
    }

    // Префиксный оператор инкремента (увеличивает все элементы на 1)
    Matrix& operator++() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                ++data[i][j];
            }
        }
        return *this;
    }

    // Постфиксный оператор инкремента
    Matrix operator++(int) {
        Matrix temp = *this; // Сохраняем текущее состояние
        ++(*this); // Используем префиксный инкремент
        return temp; // Возвращаем старое состояние
    }

    // Вычисление определителя матрицы
    T determinant() const {
        if constexpr (N == 2 && M == 2) {
            // Формула для определителя 2x2: ad - bc
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        } else if constexpr (N == 3 && M == 3) {
            // Формула для определителя 3x3 (правило Саррюса)
            return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
                 - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
                 + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        } else {
            throw std::invalid_argument("Определитель можно вычислить только для матриц 2x2 и 3x3");
        }
    }

    // Оператор доступа к элементам матрицы (неконстантная версия)
    T& operator()(int row, int col) {
        if (row < 0 || row >= N || col < 0 || col >= M) {
            throw std::out_of_range("Индекс выходит за границы матрицы");
        }
        return data[row][col];
    }

    // Оператор доступа к элементам матрицы (константная версия)
    const T& operator()(int row, int col) const {
        if (row < 0 || row >= N || col < 0 || col >= M) {
            throw std::out_of_range("Индекс выходит за границы матрицы");
        }
        return data[row][col];
    }
};

int main() {
    setlocale(LC_ALL, "Russian"); // Для корректного вывода кириллицы

    // Тестирование с матрицами 2x2
    Matrix<int, 2, 2> matrix1;
    cin >> matrix1; // Ввод первой матрицы
    cout << matrix1; // Вывод первой матрицы

    Matrix<int, 2, 2> matrix2;
    cin >> matrix2; // Ввод второй матрицы
    cout << matrix2; // Вывод второй матрицы

    // Сложение матриц
    Matrix<int, 2, 2> sumMatrix = matrix1 + matrix2;
    cout << "Сумма матриц:" << endl << sumMatrix;

    // Умножение матриц
    Matrix<int, 2, 2> productMatrix = matrix1 * matrix2;
    cout << "Произведение матриц:" << endl << productMatrix;

    // Вычисление определителя
    cout << "Определитель matrix1: " << matrix1.determinant() << endl;

    // Изменение элемента матрицы
    matrix1(0, 0) = 100;
    cout << "matrix1 после изменения элемента (0,0):" << endl << matrix1;

    // Тестирование операторов инкремента
    Matrix<int, 2, 2> matrix3 = matrix1++; // Постфиксный инкремент
    cout << "matrix1++:" << endl << matrix3;
    cout << "matrix1 после инкремента:" << endl << matrix1;

    ++matrix1; // Префиксный инкремент
    cout << "++matrix1:" << endl << matrix1;

    // Тестирование с матрицами 3x3 и типом double
    Matrix<double, 3, 3> matrixDouble;
    cin >> matrixDouble;
    cout << matrixDouble;

    // Вычисление определителя для матрицы 3x3
    cout << "Определитель matrixDouble: " << matrixDouble.determinant() << endl;

    return 0;
}

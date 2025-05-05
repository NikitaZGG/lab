#include <iostream>
#include <cmath>  // Для использования математической функции sqrt()

using namespace std;

// Класс, представляющий квадрат
class Square {
private:  
    double side;  // Длина стороны квадрата (приватное поле)

public:   
    // Конструктор класса Square с параметром - длиной стороны
    Square(double sideLength) {
        // Проверка, что длина стороны положительна
        if (sideLength <= 0) {
            cout << "Ошибка: Длина стороны должна быть больше нуля. Устанавливаем значение по умолчанию: 1." << endl;
            side = 1.0;  // Установка значения по умолчанию
        }
        else {
            side = sideLength;  // Установка переданного значения
        }
    }

    // Метод для вычисления площади квадрата
    double calculateArea() {
        return side * side;  // Площадь = сторона^2
    }

    // Метод для вычисления периметра квадрата
    double calculatePerimeter() {
        return 4 * side;  // Периметр = 4 * сторона
    }

    // Метод для вычисления длины диагонали квадрата
    double calculateDiagonalLength() {
        return side * sqrt(2.0);  // Диагональ = сторона * √2
    }

    // Метод для вывода информации о квадрате
    void printInfo() {
        cout << "Квадрат:" << endl;
        cout << "  Сторона: " << side << endl;
        cout << "  Площадь: " << calculateArea() << endl;
        cout << "  Периметр: " << calculatePerimeter() << endl;
        cout << "  Длина диагонали: " << calculateDiagonalLength() << endl;
    }

    // Метод для изменения длины стороны с проверкой
    void setSide(double newSide) {
        if (newSide <= 0) {
            cout << "Ошибка: Длина стороны должна быть больше нуля.  Значение не изменено." << endl;
        }
        else {
            side = newSide;  // Установка нового значения, если оно корректно
        }
    }

    // Метод для получения длины стороны (геттер)
    double getSide() const { 
        return side;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");  // Установка русской локали для вывода сообщений
    
    // Создание объекта mySquare с длиной стороны 7.0
    Square mySquare(7.0);

    // Вывод информации о mySquare
    cout << "Информация о mySquare:" << endl;
    mySquare.printInfo();
    cout << endl;

    // Создание другого объекта anotherSquare с длиной стороны 10.0
    Square anotherSquare(10.0);

    // Вывод только площади anotherSquare
    cout << "Площадь anotherSquare: " << anotherSquare.calculateArea() << endl;
    cout << endl;

    // Попытка создать квадрат с отрицательной длиной стороны
    Square badSquare(-2.0); 

    // Вывод информации о badSquare (сторона будет установлена в 1.0 по умолчанию)
    cout << "Информация о badSquare (сторона будет 1 по умолчанию):" << endl;
    badSquare.printInfo();
    cout << endl;

    // Изменение длины стороны mySquare на 9.0
    mySquare.setSide(9.0);
    cout << "Информация о mySquare после изменения стороны:" << endl;
    mySquare.printInfo();
    cout << endl;

    // Получение и вывод длины стороны mySquare с помощью геттера
    cout << "Длина стороны mySquare: " << mySquare.getSide() << endl;

    return 0;
}

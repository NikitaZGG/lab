#include <iostream>
#include <cmath>

using namespace std;



class Square {
private:  

    double side; 

public:   
    Square(double sideLength) {
        if (sideLength <= 0) {
            cout << "Ошибка: Длина стороны должна быть больше нуля. Устанавливаем значение по умолчанию: 1." << endl;
            side = 1.0; 
        }
        else {
            side = sideLength; 
        }
    }

    double calculateArea() {
        return side * side; 
    }

    double calculatePerimeter() {
        return 4 * side; 
    }

    double calculateDiagonalLength() {
        return side * sqrt(2.0); 
    }

    void printInfo() {
        cout << "Квадрат:" << endl;
        cout << "  Сторона: " << side << endl;
        cout << "  Площадь: " << calculateArea() << endl;
        cout << "  Периметр: " << calculatePerimeter() << endl;
        cout << "  Длина диагонали: " << calculateDiagonalLength() << endl;
    }

    void setSide(double newSide) {
        if (newSide <= 0) {
            cout << "Ошибка: Длина стороны должна быть больше нуля.  Значение не изменено." << endl;
        }
        else {
            side = newSide;
        }
    }

    double getSide() const { 
        return side;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    Square mySquare(7.0);

    
    cout << "Информация о mySquare:" << endl;
    mySquare.printInfo();
    cout << endl;

    
    Square anotherSquare(10.0);

    
    cout << "Площадь anotherSquare: " << anotherSquare.calculateArea() << endl;
    cout << endl;

    Square badSquare(-2.0); 

    cout << "Информация о badSquare (сторона будет 1 по умолчанию):" << endl;
    badSquare.printInfo();
    cout << endl;

    mySquare.setSide(9.0);
    cout << "Информация о mySquare после изменения стороны:" << endl;
    mySquare.printInfo();
    cout << endl;

    cout << "Длина стороны mySquare: " << mySquare.getSide() << endl;

    return 0;
}

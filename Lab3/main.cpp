#include <iostream>
#include <cmath>

using namespace std;



class Square {
private:  

    double side; 

public:   
    Square(double sideLength) {
        if (sideLength <= 0) {
            cout << "������: ����� ������� ������ ���� ������ ����. ������������� �������� �� ���������: 1." << endl;
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
        cout << "�������:" << endl;
        cout << "  �������: " << side << endl;
        cout << "  �������: " << calculateArea() << endl;
        cout << "  ��������: " << calculatePerimeter() << endl;
        cout << "  ����� ���������: " << calculateDiagonalLength() << endl;
    }

    void setSide(double newSide) {
        if (newSide <= 0) {
            cout << "������: ����� ������� ������ ���� ������ ����.  �������� �� ��������." << endl;
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

    
    cout << "���������� � mySquare:" << endl;
    mySquare.printInfo();
    cout << endl;

    
    Square anotherSquare(10.0);

    
    cout << "������� anotherSquare: " << anotherSquare.calculateArea() << endl;
    cout << endl;

    Square badSquare(-2.0); 

    cout << "���������� � badSquare (������� ����� 1 �� ���������):" << endl;
    badSquare.printInfo();
    cout << endl;

    mySquare.setSide(9.0);
    cout << "���������� � mySquare ����� ��������� �������:" << endl;
    mySquare.printInfo();
    cout << endl;

    cout << "����� ������� mySquare: " << mySquare.getSide() << endl;

    return 0;
}

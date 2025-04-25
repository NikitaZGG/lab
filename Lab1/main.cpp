
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head; 

public:
    DoublyLinkedList() {
        head = new Node(0); 
        head->next = head;
        head->prev = head;
    }

    ~DoublyLinkedList() {
        clear();
        delete head;
    }

    void append(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
    }
    void printList() {
        if (isEmpty()) {
            cout << "Список пуст." << endl;
            return;
        }

        Node* current = head->next;
        while (current != head) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    bool isEmpty() {
        return head->next == head;
    }

    vector<int> toVector() {
        vector<int> result;
        Node* current = head->next;
        while (current != head) {
            result.push_back(current->data);
            current = current->next;
        }
        return result;
    }

    void clear() {
        Node* current = head->next;
        while (current != head) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head->next = head;
        head->prev = head;
    }

    void remove(int data) {
        Node* current = head->next;
        while (current != head) {
            if (current->data == data) {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            else {
                current = current->next;
            }
        }
    }

    void insertAfter(Node* node, int data) {
        if (node == nullptr) return;

        Node* newNode = new Node(data);
        newNode->next = node->next;
        newNode->prev = node;
        node->next->prev = newNode;
        node->next = newNode;
    }

    Node* getHead() {
        return head;
    }
};


bool isIncreasing(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

bool isDecreasing(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] > arr[i - 1]) {
            return false;
        }
    }
    return true;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int getFirstDigit(int n) {
    while (n >= 10) {
        n /= 10;
    }
    return n;
}


int main() {
    DoublyLinkedList myList;
    int num;

    cout << "Введите последовательность натуральных чисел (для завершения введите 0):" << endl;
    while (cin >> num && num != 0) {
        myList.append(num);
    }

    vector<int> data = myList.toVector();

    if (isIncreasing(data) || isDecreasing(data)) {
       
        vector<int> primesToDuplicate;
        Node* current = myList.getHead()->next;
        while (current != myList.getHead())
        {
            if (current && current->data % 15 == 0)
            {
                Node* temp = current;
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current = current->next;
                delete temp;
                continue;
            }

            if (isPrime(current->data)) {
                primesToDuplicate.push_back(current->data);
            }

            current = current->next;
        }

        for (int prime : primesToDuplicate) {
            current = myList.getHead()->next;
            while (current != myList.getHead())
            {
                if (current->data == prime)
                {
                    myList.insertAfter(current, prime);
                    current = current->next->next; 
                }
                else {
                    current = current->next;
                }
            }
        }



    }
    else {
        
        sort(data.begin(), data.end(), [](int a, int b) {
            return getFirstDigit(a) > getFirstDigit(b);
            });

        myList.clear(); 
        for (int val : data) {
            myList.append(val);
        }
    }

    cout << "Результат:" << endl;
    myList.printList();

    return 0;
}

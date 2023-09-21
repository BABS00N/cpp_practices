#include <iostream>
#include <queue>
using namespace std;
class QueueStl {
    queue <int>* qu;
protected:
    void goToTheBack() {
        push(front());
        pop();
    }
public:
    QueueStl() {
        qu = new queue<int>();
    }
    void push(int element) {
        qu->push(element);
    }
    int front() {
        return qu->front();
    }
    int back() {
        return qu->back();
    }
    int size() {
        return qu->size();
    }
    void pop() {
        qu->pop();
    }
    void Display() {
        int c_size = size();
        for (int i = 0; i < c_size; i++) {
            cout << ' ' << front();
            goToTheBack();
        }
    }
};

class Adapter4QueueStl : public QueueStl{
    QueueStl* qu;
public:
    Adapter4QueueStl() {
        qu = new QueueStl;
    }
    int getElement(int index) {
        int element;
        for (int i = 0; i < index; i++)
            goToTheBack();
        element = front();
        for (int i = 0; i < size() - index; i++)
            goToTheBack();
        return element;
    }
    void setElement(int index, int element) {
        for (int i = 0; i < index; i++)
            goToTheBack();
        pop(); push(element);
        for (int i = 0; i < size() - (index+1); i++)
            goToTheBack();
    }
};

void bubbleSort(Adapter4QueueStl * tmpA) {
    int size = tmpA->size();
    for (int i = 0; i < size - 1;i++) {
        bool flag = true;
        for (int j = 0; j < size - (i + 1); j++) {
            int current = tmpA->getElement(j);
            int next = tmpA->getElement(j + 1);
            if (current > next) {
                tmpA->setElement(j, next);
                tmpA->setElement(j+1, current);
                flag = false;
            }
        }
        if (flag)
            break;
    }
}


int main()
{
    Adapter4QueueStl* b = new Adapter4QueueStl;
    b->push(5);
    b->push(100);
    b->push(-1);
    b->push(4);
    b->push(-7);
    b->push(0);
    b->setElement(3, 10);
    b->Display();
    cout << endl;
    bubbleSort(b);
    cout << endl;
    b->Display();
}

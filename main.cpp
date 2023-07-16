#include <iostream>
#include "queue.hpp"


int main(int, char**){

    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << q.pop() << std::endl;
    std::cout << q.pop() << std::endl;
    std::cout << q.pop() << std::endl;


    std::cout << "Hello, from threading!\n";
}

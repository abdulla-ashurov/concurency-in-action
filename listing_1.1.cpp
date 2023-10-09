#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello Concurency World!" << std::endl;
}

int main() {
    // main - is initial thread
    // t - is second thread
    std::thread t(hello); // hello - job for a new thread
    t.join(); // wait second thread


    return 0;
}

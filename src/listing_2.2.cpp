#include <iostream>
#include <thread>
#include <chrono>

void do_something(const int i) {
    std::cout << i << std::endl;
}

struct Test {
    int &i;

    Test(int &i) : i(i) {}
    void operator()() {
        for (size_t j = 0; j < 1000000; j++) {
            do_something(i); // Potential access to dangling reference
        }
    }
};

void do_something_in_current_thread() {
    for (size_t i = 0; i < 100; i++) {
        std::cout << "Hello from current thread!" << std::endl;
    }
}

void f() {
    int some_local_state=0;
    Test test(some_local_state);
    std::thread t(test);

    try {
        do_something_in_current_thread();
    }
    catch(...) {
        t.join();
        throw; 
    }
    
    t.join();
}

int main() {
    f();

    return 0;
}

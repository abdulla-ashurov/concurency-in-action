// Listing 2.3 Using RAII to wait for a thread to complete

#include <iostream>
#include <thread>

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
        throw std::runtime_error("Oops");
    }
}

class ThreadGuard {
private:
    std::thread  &t;

public:
    ThreadGuard(std::thread &t) : t(t) {
        std::cout << "ThreadGuard constructor: " << this << std::endl; 
    }

    ThreadGuard(const ThreadGuard &) = delete;
    ThreadGuard& operator=(const ThreadGuard &) = delete;


    ~ThreadGuard() {
        std::cout << "ThreadGuard destructor: " << this << std::endl;
        if(t.joinable()) {
            t.join();
        }
    }   
};

void f() {
    int some_local_state=0;
    Test test(some_local_state);
    std::thread t(test);
    ThreadGuard guard(t);
    do_something_in_current_thread();
}

int main() {
    try {
        f();
    } catch(...) {
        ;
    }

    return 0;
}

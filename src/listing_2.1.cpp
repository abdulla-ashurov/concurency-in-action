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

void oops() {
    int some_local_state = 0;
    Test test(some_local_state);

    std::thread my_thread(test);
    // Don’t wait for thread to finish
    my_thread.detach();
    // New thread might still be running
}

int main() {
    oops();

    return 0;
}

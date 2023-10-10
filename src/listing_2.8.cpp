// Listing 2.8 Spawns some threads and waits for them to finish

#include <iostream>
#include <thread>

int main() {
    std::thread t;

    std::cout << "Id:" << t.get_id() << std::endl;

    std::cout << std::this_thread::get_id() << std::endl;

    return 0;
}


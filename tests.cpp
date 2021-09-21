#include <iostream>
#include <vector>
#include <thread>
#include "synchronized.hpp"

int main() {
    size_t threads = 16;
    uint64_t num = rand();
    uint64_t count = 1'000'000;

    al::Synchronized<uint64_t> sync;

    auto f = [&sync, num, count] {
        for (auto i = 0ull; i < count; ++i) {
            sync.get().ref() += num;
        }
    };

    std::vector<std::thread> ths;
    for (size_t i = 0; i < threads; ++i) {
        ths.emplace_back(f);
    }

    for (auto &i : ths) {
        i.join();
    }

    std::cout << sync.get().ref();

    if (sync.get().ref() == threads * num * count) {
        std::cout << " == ";
    } else {
        std::cout << " != ";
    }

    std::cout << threads * num * count << std::endl;
}

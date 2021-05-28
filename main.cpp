#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

long unsigned int sum (const std::vector<int>& vec, int begin, int end) {
    long unsigned int result{0};
    for (int i = begin; i <= end; i++) {
        result += vec[i];
    }
    return result;
}

std::vector<int> fill (int range) {
    std::vector<int> returnVector;

    for (int i = 0; i <= range; i++)
        returnVector.emplace_back(i);

    return returnVector;
}

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    long unsigned int range = 500'00000 ;
    long unsigned int result = {0};
    std::mutex mut{};
    std::vector<int> myVector = fill(range);

    auto t1 = high_resolution_clock::now();
    std::thread thread1 {
            [&result, &myVector, &mut]
            {
                long unsigned int a = sum(myVector, 0, 124'99999);
                std::lock_guard<std::mutex> lock(mut);
                result += a;
            }
    };
    std::thread thread2 {
            [&result, &myVector, &mut]
            {
                long unsigned int a = sum(myVector, 0, 124'99999);
                std::lock_guard<std::mutex> lock(mut);
                result += a;
            }
    };
    std::thread thread3 {
            [&result, &myVector, &mut]
            {
                long unsigned int a = sum(myVector, 0, 124'99999);
                std::lock_guard<std::mutex> lock(mut);
                result += a;
            }
    };
    std::thread thread4 {
            [&result, &myVector, &mut]
            {
                long unsigned int a = sum(myVector, 0, 124'99999);
                std::lock_guard<std::mutex> lock(mut);
                result += a;
            }
    };
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    auto t2 = high_resolution_clock::now();

    std::cout << result << std::endl;

    duration<double, std::milli> ms_double = t2-t1;
    std::cout << ms_double.count() << "ms" << std::endl;

    auto t3 = high_resolution_clock::now();
    long unsigned int result2 = sum(myVector, 0, 499'99999);
    auto t4 = high_resolution_clock::now();

    std::cout << result2 << std::endl;
    duration<double, std::milli> ms_double2 = t4-t3;
    std::cout << ms_double2.count() << "ms" << std::endl;


    return 0;
}
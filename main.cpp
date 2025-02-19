#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std::chrono;

int N = 50000;
std::random_device dev;
std::mt19937 gen(dev());

int random(int n) {
    if (n <= 0) return 0;  // Prevents out-of-bounds issues
    std::uniform_int_distribution<> dist(0, n - 1);
    return dist(gen);
}

template <class T>
auto insertion(T& cont) {
    auto start_time = steady_clock::now();
    for (int i = 0; i < N; i++) {
        int num = random(N);
        auto it = cont.begin();
        for (; it != cont.end() && *it < num; ++it);
        cont.insert(it, num);
    }
    auto end_time = steady_clock::now();
    return duration_cast<milliseconds>(end_time - start_time);
}

template <class T>
auto deletion(T& cont) {
    auto start_time = steady_clock::now();
    while (!cont.empty()) {
        int pos = random(cont.size());
        auto it = cont.begin();
        for (int j = 0; j < pos; ++j) ++it;
        cont.erase(it);
    }
    auto end_time = steady_clock::now();
    return duration_cast<milliseconds>(end_time - start_time);
}

int main() {
    std::vector<int> vec;
    std::list<int> list;

    auto vec_ins_time = insertion(vec);
    auto list_ins_time = insertion(list);
    auto vec_del_time = deletion(vec);
    auto list_del_time = deletion(list);

    auto total_vec_time = vec_ins_time + vec_del_time;
    auto total_list_time = list_ins_time + list_del_time;

    std::cout << "Vector vs List performance when N= " << N << '\n';
    std::cout << "\n+------------------+------------+\n";
    std::cout << "| Operation        | Time (ms)  |\n";
    std::cout << "+------------------+------------+\n";
    std::cout << "| Vector Insertion | " << std::setw(10) << vec_ins_time.count()  << " |\n";
    std::cout << "| Vector Deletion  | " << std::setw(10) << vec_del_time.count()  << " |\n";
    std::cout << "| Vector Total     | " << std::setw(10) << total_vec_time.count() << " |\n";
    std::cout << "+------------------+------------+\n";
    std::cout << "| List Insertion   | " << std::setw(10) << list_ins_time.count()  << " |\n";
    std::cout << "| List Deletion    | " << std::setw(10) << list_del_time.count()  << " |\n";
    std::cout << "| List Total       | " << std::setw(10) << total_list_time.count() << " |\n";
    std::cout << "+------------------+------------+\n";
    std::cout << "| Vector is Faster | " << std::setw(10) << std::fixed << std::setprecision(2) << (total_list_time / total_vec_time) << "x|\n";
    std::cout << "+------------------+------------+\n";

    return 0;
}

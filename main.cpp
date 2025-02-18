#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

const int N = 20000;
const int MAX_VALUE = 20000;

template <typename Container>
void insert_sorted(Container& cont, int value) {
    auto it = std::find_if(cont.begin(), cont.end(), [value](int x) { return x >= value; });
    cont.insert(it, value);
}

template <typename Container>
void remove_by_index(Container& cont, int index) {
    if (index < 0 || index >= cont.size()) return;

    auto it = cont.begin();
    for (int i = 0; i < index; ++i) {
        ++it;
    }

    cont.erase(it);
}

int main() {
    std::srand(std::time(0));
    std::vector<int> vec;
    std::list<int> lst;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        int value = std::rand() % MAX_VALUE;
        insert_sorted(vec, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> vector_time = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        int value = std::rand() % MAX_VALUE;
        insert_sorted(lst, value);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> list_time = end - start;

    std::cout << "Insertion Time: Vector = " << vector_time.count() << "ms, List = " << list_time.count() << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N && !vec.empty(); ++i) {
        int index = std::rand() % vec.size();
        remove_by_index(vec, index);
    }
    end = std::chrono::high_resolution_clock::now();
    vector_time = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N && !lst.empty(); ++i) {
        int index = std::rand() % lst.size();
        remove_by_index(lst, index);
    }
    end = std::chrono::high_resolution_clock::now();
    list_time = end - start;

    std::cout << "Deletion Time: Vector = " << vector_time.count() << "ms, List = " << list_time.count() << "ms\n";

    std::cout << "Vector is " << (list_time.count() + list_time.count()) / (vector_time.count() + vector_time.count()) << " times faster than List in total operations.\n";

    return 0;
}

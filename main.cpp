#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

const int N = 20000;
const int MAX_VALUE = 20000;

template <typename Container>
void insert_sorted(Container& cont, int value) {
    auto it = std::find_if(cont.begin(), cont.end(), [value](int x) { return x >= value; });
    cont.insert(it, value);
}

template <typename Container>
void remove_by_index(Container& cont, size_t index) {
    if (index < 0 || index >= cont.size()) return;

    auto it = cont.begin();
    for (size_t i = 0; i < index; ++i) {
        ++it;
    }

    cont.erase(it);
}

void print_results(auto vector_insert_time, auto list_insert_time, auto vector_del_time, auto list_del_time)
{
    std::cout << std::setw(20) << std::left << "Operation"
              << std::setw(15) << "List (ms)"
              << std::setw(15) << "Vector (ms)"
              << std::setw(15) << "Speedup (x)" << std::endl;
    std::cout << std::string(65, '-') << std::endl;
          

    std::cout << std::setw(20) << "Insertion Time"
              << std::setw(15) << std::fixed << std::setprecision(2) << list_insert_time.count()
              << std::setw(15) << std::fixed << std::setprecision(2) << vector_insert_time.count()
              << std::setw(15) << std::fixed << std::setprecision(2)
              << (list_insert_time.count() / vector_insert_time.count()) << std::endl;

    std::cout << std::setw(20) << "Deletion Time"
              << std::setw(15) << std::fixed << std::setprecision(2) << list_del_time.count()
              << std::setw(15) << std::fixed << std::setprecision(2) << vector_del_time.count() 
              << std::setw(15) << std::fixed << std::setprecision(2)
              << (list_del_time.count() / vector_del_time.count()) << std::endl;

    std::cout << std::setw(20) << "Total Time"
              << std::setw(15) << std::fixed << std::setprecision(2)
              << list_insert_time.count() + list_del_time.count()
              << std::setw(15) << std::fixed << std::setprecision(2)
              << vector_insert_time.count() + vector_del_time.count() 
              << std::setw(15) << std::fixed << std::setprecision(2)
              << (list_insert_time.count() + list_del_time.count())
              / (vector_insert_time.count() + vector_del_time.count()) << std::endl;
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
    std::chrono::duration<double, std::milli> vector_insert_time = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        int value = std::rand() % MAX_VALUE;
        insert_sorted(lst, value);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> list_insert_time = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N && !vec.empty(); ++i) {
        int index = std::rand() % vec.size();
        remove_by_index(vec, index);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> vector_del_time = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N && !lst.empty(); ++i) {
        int index = std::rand() % lst.size();
        remove_by_index(lst, index);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> list_del_time = end - start;

    print_results(vector_insert_time, list_insert_time, vector_del_time, list_del_time);

    return 0;
}

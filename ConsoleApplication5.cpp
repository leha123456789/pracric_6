#include <iostream>
#include <sstream>
#include <omp.h>
#include <chrono>
using namespace std;
int main() {
    setlocale(LC_ALL, "RUSSIAN");
    int thrs;
    int num;
    int sum = 0;
    cout << "Введите количество потоков: ";
    cin >> thrs;
    cout << "Введите верхнюю границу: ";
    cin >> num;
    chrono::high_resolution_clock::time_point start_seq = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num + 1; i++) 
    {
        sum += i;
    }
    chrono::high_resolution_clock::time_point end_seq = std::chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed_time_seq = end_seq - start_seq;
    cout << "SUM (без многопоточности): " << sum << std::endl;
    cout << "Время выполнения (без многопоточности): " << elapsed_time_seq.count() << " мс" << std::endl;
    sum = 0;
    omp_set_num_threads(thrs);
    auto start_par = std::chrono::steady_clock::now();
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num + 1; i++)
    {
        sum += i;
    }
    auto end_par = std::chrono::steady_clock::now();
    auto elapsed_time_par = std::chrono::duration_cast<std::chrono::milliseconds>(end_par - start_par).count();
    cout << "SUM (с многопоточностью): " << sum << std::endl;
    cout << "Время выполнения (с многопоточностью): " << elapsed_time_par << " мс" << std::endl;
    return 0;
}

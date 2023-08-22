#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }

    int sqrtn = sqrt(n);
    for (int i = 2; i <= sqrtn; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


int main() {
    int N;
    double parallel_time, serial_time = 0.0;;
    cout << "Enter the value of N: ";
    cin >> N;



    vector<bool> marked1(N + 1, false);
    int largest_unmarked = 0;

    for (int j = 1; j <= 4; j++) {

        int num_threads = j;

        // Compute parallel execution time
        double t1 = omp_get_wtime();
#pragma omp parallel num_threads(num_threads) reduction(max:largest_unmarked)
        for (int i = 2; i <= N; i++) {
            if (!marked1[i] && is_prime(i)) {
                for (int j = i + i; j <= N; j += i) {
                    marked1[j] = true;
                }
                largest_unmarked = i;
            }
        }
        double t2 = omp_get_wtime();
        parallel_time = t2 - t1;


        // Compute speedup and efficiency
        double speedup = serial_time / parallel_time;
        double efficiency = speedup / num_threads;


        // Print results
        cout << "Number of threads:" << num_threads << endl;
        cout << "Largest unmarked number: " << largest_unmarked << endl;
        cout << "Serial Execution Time:" << serial_time << " seconds" << endl;
        cout << "Parallel Execution Time: " << parallel_time << " seconds" << endl;
        cout << "Speedup: " << speedup << endl;
        cout << "Efficiency: " << efficiency << endl;
        cout <<"-----------------------------------------------------------" << endl;

        if (num_threads == 1) {
            serial_time = parallel_time;
        }

    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

mutex mut; 
int primes = 0;
ofstream outFS("primes.dat"); //global so it can be written to everywhere

bool isPrime(int n) {
    if (n < 2) {
        return false;
    }
    else if (n == 2) {
        return true;
    }
    else if (n % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= n / 2; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void findPrimes(int start, int end, int thread) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            mut.lock(); //lock em up
            outFS << i << endl; 
            primes++;
            count++;
            mut.unlock(); //freeeeeeeeeeeee
        }
    }
    cout << "Thread " << thread << " found " << count << " prime numbers." << endl;
}

int main() {
    int start = 2;
    int end = 1000000;
    int numThreads = 4;
    int numSize = (end - start + 1) / numThreads;
    int threadStart;
    int threadEnd;
    vector<thread> threads;

    for (int i = 0; i < numThreads; i++) {
        threadStart = start + i * numSize;
        threadEnd = (i == numThreads - 1) ? end : threadStart + numSize - 1;
        threads.push_back(thread(findPrimes, threadStart, threadEnd, i + 1));
    }
    for (auto& t : threads) {
        t.join();
    }
    cout << "Total number of primes found: " << primes << endl;
    outFS.close();
    return 0;
}

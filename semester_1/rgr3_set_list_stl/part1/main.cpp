#include <iostream>
#include <set>

int main() {
    int N;
    std::cout << "Enter int number N: ";
    if (!(std::cin >> N)) {
        std::cout << "Error, needed to be entered int number";
        return 1;
    }

    std::set<int> primes;
    for (int i = 2; i <= N; i++) {
        primes.insert(i);
    }

    for (int i = 2; i * i <= N; i++) {
        if (primes.find(i) != primes.end()) {
            for (int j = i * i; j <= N; j += i) {
                primes.erase(j);
            }
        }
    }

    std::cout << "prime numbers up to " << N << ":\n";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}
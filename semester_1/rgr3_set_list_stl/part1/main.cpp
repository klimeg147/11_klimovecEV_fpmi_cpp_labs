#include <iostream>
#include <set>

int main() {
    int N;
    std::cout << "Введите число N: ";
    std::cin >> N;

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

    std::cout << "Простые числа до " << N << ":\n";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}
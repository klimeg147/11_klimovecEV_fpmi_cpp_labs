#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {

    std::vector<int> vector;
    int nm;

    std::cout << "Enter int vector elements one by one (To stop enter NOT number): " << '\n';
    while (std::cin >> nm) {
        vector.push_back(nm);
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int sum = std::accumulate(vector.begin(), vector.end(), 0);
    std::cout << "Sum of vector elements: " << sum << '\n';
    if (!vector.empty()) {

        std::cout << "Number of vector elements: " << vector.size() << '\n';

        int seek;
        std::cout << "Enter the number is seeked: ";
        std::cin >> seek;
        int num_seek = std::count(vector.begin(), vector.end(), seek);
        std::cout << "Number of the number is seeked: " << num_seek << '\n';

        std::cout << "Enter an int number greater than which numbers will be searched in the vector: ";
        int les_num;
        std::cin >> les_num;
        int num_if_seek = std::count_if(vector.begin(), vector.end(), [les_num](int n) {return n > les_num; });
        std::cout << "Number of numbers greater than choosen number: " << num_if_seek << '\n';

        int mean = sum / vector.size();
        std::replace(vector.begin(), vector.end(), 0, mean);
        std::cout << "redacted vector(zero replaced): ";
        for (int num : vector) {
            std::cout << num << " ";
        }
        std::cout << '\n';

        int start, end;
        std::cout << "Enter \"begin\" and \"end\" (max: " << vector.size() - 1 << ") indexes if choosen interval:" << '\n';
        std::cin >> start >> end;
        try {
            if (start >= vector.size() || end >= vector.size()) {
                throw "YOU ENTERED MORE THAN MAX!";
            }
            if (start < 0) {
                throw "entered start index is under 0";
            }
            if (end < 0) {
                throw "entered end index is under 0";
            }

            if (start > end) {
                std::swap(start, end);
            }
            sum = std::accumulate(vector.begin() + start, vector.begin() + end + 1, 0);
            for (size_t i = 0; i < vector.size(); ++i) {
                vector[i] += sum;
            }
            std::cout << "redacted vector(interval): ";
            for (int num : vector) {
                std::cout << num << " ";
            }
            std::cout << '\n';
        }
        catch (const char* msg) {
            std::cerr << msg;
        }

        int diff = *std::max_element(vector.begin(), vector.end()) - *std::min_element(vector.begin(), vector.end());
        std::cout << "redacted vector (even replaced): ";
        for (size_t i = 0; i < vector.size(); ++i) {
            if (std::abs(vector[i]) % 2 == 0) {
                vector[i] = diff;
            }
            std::cout << vector[i] << " ";
        }
        std::cout << '\n';

        for (size_t i = 0; i < vector.size(); ++i) {
            for (size_t j = i + 1; j < vector.size();) {
                if (std::abs(vector[j]) == std::abs(vector[i])) {
                    vector.erase(vector.begin() + j);
                }
                else { j++; }
            }
        }
        std::cout << "redacetd vector(delete identical ones): ";
        for (int num : vector) {
            std::cout << num << " ";
        }
    }
    else {
        std::cout << "vector is empty" << '\n';
    }

    return 0;
}
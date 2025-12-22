#include "time_utility.h"
#include "train.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {

    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);

    std::cout << "t2: ";
    PrintTime(t2);

    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';

    vector<Train> trains;
    ifstream file("schedule.txt");

    if (!file.is_open()) {
        cout << "error: file schedule.txt is not open" << endl;
        return 1;
    }

    int id, type_num;
    std::string dest;
    int h1, m1, h2, m2;

    while (file >> id >> type_num >> dest >> h1 >> m1 >> h2 >> m2) {
        TrainType type;
        if (type_num == 0)
            type = TrainType::PASSENGER;
        else if (type_num == 1)
            type = TrainType::FREIGHT;
        else if (type_num == 2)
            type = TrainType::HIGH_SPEED;
        else if (type_num == 3)
            type = TrainType::SUBWAY;
        else
            type = TrainType::SPECIALIZED;

        time_t dep = SetTime(h1, m1);
        time_t travel = SetTime(h2, m2);

        trains.push_back(Train(id, type, dest, dep, travel));
    }
    file.close();

    if (trains.empty()) {
        cout << "error: file schedule.txt is empty" << endl;
        return 1;
    }

    sort(trains.begin(), trains.end(),
         [](const Train& a, const Train& b) { return a.GetDispatchTime() < b.GetDispatchTime(); });

    cout << '\n';
    cout << "Trains after sorting by departure time:" << '\n';
    for (const auto& train : trains) {
        train.Print();
    }

    cout << '\n';
    cout << "Trains from 13:00 up to 23:00:" << '\n';
    time_t start = SetTime(13, 0);
    time_t end = SetTime(23, 0);
    bool found_time = false;

    for (const auto& train : trains) {
        time_t t = train.GetDispatchTime();
        if (t >= start && t <= end) {
            train.Print();
            found_time = true;
        }
    }
    if (!found_time)
        cout << "There are no trains in this time range" << '\n';

    cout << '\n';
    cout << "Trains to Minsk:" << '\n';
    bool found_dest = false;
    for (const auto& train : trains) {
        if (train.GetDestination() == "Minsk") {
            train.Print();
            found_dest = true;
        }
    }
    if (!found_dest) {
        cout << "There are no trains to Minsk" << '\n';
    }

    cout << '\n';
    cout << "Passenger trains to Minsk:" << '\n';
    bool found_type = false;
    for (const auto& train : trains) {
        if (train.GetDestination() == "Minsk" && train.GetType() == TrainType::PASSENGER) {
            train.Print();
            found_type = true;
        }
    }

    if (!found_type) {
        cout << "There are no passenger trains to Minsk" << '\n';
    }

    cout << '\n';
    cout << "Fastest train to Minsk:" << '\n';
    const Train* fastest = nullptr;
    bool found_fastest = false;

    for (const auto& train : trains) {
        if (train.GetDestination() == "Minsk") {
            if (!found_fastest) {
                fastest = &train;
                found_fastest = true;
            } else if (train.GetTravellingTime() < fastest->GetTravellingTime()) {
                fastest = &train;
            }
        }
    }

    if (found_fastest) {
        fastest->Print();
    } else {
        cout << "There are no trains to Minsk" << '\n';
    }

    return EXIT_SUCCESS;
}

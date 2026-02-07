#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <locale>

struct Mark {
    std::string subject_;
    std::size_t mark_;
};

struct StudentData {
    std::string name_;
    std::size_t number_;
    std::vector<Mark> marks_;

    double average() const {
        if (marks_.empty()) return 0;
        double sum = 0;
        for (const auto& m : marks_) {
            sum += m.mark_;
        }
        return sum / marks_.size();
    }
};


void readFromFile(std::map<std::size_t, StudentData>& students, std::ifstream& in) {
    std::string line;
    std::string separators = " ~`!?/.><()}{][;:\t";
    std::string digits = "1234567890";

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        StudentData student;
        std::size_t pos = 0, next = 0;

        pos = line.find_first_not_of(separators, 0);
        if (pos == std::string::npos) continue;
        next = line.find_first_of(separators, pos);
        student.name_ = line.substr(pos, next - pos);

        pos = line.find_first_not_of(separators, next);
        if (pos == std::string::npos) continue;
        next = line.find_first_of(separators, pos);
        student.number_ = std::stoul(line.substr(pos, next - pos));

        while (pos < line.size()) {
            pos = line.find_first_not_of(separators, next);
            if (pos == std::string::npos) break;

            std::size_t first_digit = line.find_first_of(digits, pos);
            if (first_digit == std::string::npos) break;

            std::string subject = line.substr(pos, first_digit - pos);

            while (!subject.empty() &&
                separators.find(subject.back()) != std::string::npos) {
                subject.pop_back();
            }

            std::size_t mark_end = first_digit;
            while (mark_end < line.size() &&
                digits.find(line[mark_end]) != std::string::npos) {
                mark_end++;
            }

            std::string mark_str = line.substr(first_digit, mark_end - first_digit);
            std::size_t mark = std::stoul(mark_str);

            next = mark_end;

            if (!subject.empty()) {
                student.marks_.push_back({ subject, mark });
            }
        }

        students[student.number_] = student;
    }
}

void printSortedByNumber(const std::map<std::size_t, StudentData>& students) {
    std::cout << "2. Students sorted by numbers:\n";

    for (const auto& s : students) {
        std::cout << s.second.name_;
        std::cout << "; " << s.first;
        for (const auto& m : s.second.marks_) {
            std::cout << "; " << m.subject_ << ":" << m.mark_;
        }

        std::cout << "\n";
    }
    std::cout << "\n";
}


void printAlphabetical(const std::map<std::size_t, StudentData>& students) {
    std::cout << "4. Students sorted by alphabet:\n";


    std::vector<std::pair<std::size_t, StudentData>> studentList;
    for (const auto& pair : students) {
        studentList.push_back(pair);
    }


    std::sort(studentList.begin(), studentList.end(),
        [](const auto& a, const auto& b) {
            if (a.second.name_ != b.second.name_) {
                return a.second.name_ < b.second.name_;
            }
            return a.second.average() > b.second.average();
        });

    int count = 1;
    for (const auto& pair : studentList) {
        std::cout << count++ << ". " << pair.second.name_
            << ", " << pair.first
            << ", " << std::fixed << std::setprecision(2)
            << pair.second.average() << std::endl;
    }
    std::cout << std::endl;
}


void printStudentsInRange(const std::map<std::size_t, StudentData>& students) {
    double minAvg, maxAvg;
    std::cout << "5. Enter diapazone of marks: ";
    std::cin >> minAvg >> maxAvg;

    std::cout << "Students with marks from" << minAvg << " to " << maxAvg << ":\n";

    std::vector<std::pair<std::size_t, StudentData>> result;
    for (const auto& pair : students) {
        double avg = pair.second.average();
        if (avg >= minAvg && avg <= maxAvg) {
            result.push_back(pair);
        }
    }


    std::sort(result.begin(), result.end(),
        [](const auto& a, const auto& b) {
            return a.second.average() > b.second.average();
        });

    if (result.empty()) {
        std::cout << "There are no students in thisa diapazone.\n";
    }
    else {
        for (const auto& pair : result) {
            std::cout << pair.second.name_ << ", " << pair.first
                << ", " << std::fixed << std::setprecision(2)
                << pair.second.average() << std::endl;
        }
    }
    std::cout << std::endl;
}


void printStudentsBySubject(const std::map<std::size_t, StudentData>& students) {
    std::cout << "6. Available subjects:\n";

    std::map<std::string, bool> unique_subjects;
    for (const auto& pair : students) {
        for (const auto& mark : pair.second.marks_) {
            unique_subjects[mark.subject_] = true;
        }
    }

    int index = 1;
    std::map<int, std::string> subject_map;
    for (const auto& subj : unique_subjects) {
        std::cout << index << ". " << subj.first << std::endl;
        subject_map[index] = subj.first;
        index++;
    }

    std::cout << "Enter subject number: ";
    int choice;
    std::cin >> choice;

    if (subject_map.find(choice) == subject_map.end()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    std::string subject = subject_map[choice];
    std::cout << "Students, took an exam of " << subject << ":\n";

    bool found = false;
    for (const auto& pair : students) {
        for (const auto& mark : pair.second.marks_) {
            if (mark.subject_ == subject) {
                std::cout << pair.second.name_ << ", " << pair.first << std::endl;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        std::cout << "No students found.\n";
    }
    std::cout << std::endl;
}


void countStudentsPerSubject(const std::map<std::size_t, StudentData>& students) {
    std::cout << "7. Number of students for each subject:\n";

    std::map<std::string, std::size_t> subjectCount;

    for (const auto& pair : students) {

        std::map<std::string, bool> alreadyCounted;
        for (const auto& mark : pair.second.marks_) {
            if (!alreadyCounted[mark.subject_]) {
                subjectCount[mark.subject_]++;
                alreadyCounted[mark.subject_] = true;
            }
        }
    }

    for (const auto& pair : subjectCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << std::endl;
}


void calculateSubjectAverages(const std::map<std::size_t, StudentData>& students) {
    std::cout << "8. Average marks of subjects from highest to lowest:\n";


    std::map<std::string, std::pair<std::size_t, std::size_t>> subjectData;

    for (const auto& pair : students) {
        for (const auto& mark : pair.second.marks_) {
            subjectData[mark.subject_].first += mark.mark_;
            subjectData[mark.subject_].second++;
        }
    }

    std::vector<std::pair<std::string, double>> averages;
    for (const auto& pair : subjectData) {
        double avg = static_cast<double>(pair.second.first) / pair.second.second;
        averages.push_back({ pair.first, avg });
    }

    std::sort(averages.begin(), averages.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    for (const auto& pair : averages) {
        std::cout << pair.first << ": " << std::fixed << std::setprecision(2)
            << pair.second << std::endl;
    }
    std::cout << std::endl;
}


void findStudentsWithMaxSum(const std::map<std::size_t, StudentData>& students) {
    std::cout << "9. Students with max sum of marks:\n";


    std::size_t maxSum = 0;
    for (const auto& pair : students) {
        std::size_t sum = 0;
        for (const auto& mark : pair.second.marks_) {
            sum += mark.mark_;
        }
        if (sum > maxSum) {
            maxSum = sum;
        }
    }


    bool found = false;
    for (const auto& pair : students) {
        std::size_t sum = 0;
        for (const auto& mark : pair.second.marks_) {
            sum += mark.mark_;
        }
        if (sum == maxSum) {
            std::cout << pair.second.name_ << ", " << pair.first
                << ", sum of marks: " << maxSum << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "There are no students.\n";
    }
    std::cout << std::endl;
}


void findStudentsWithUnsatisfactory(const std::map<std::size_t, StudentData>& students) {
    std::cout << "10. Students with bad marks (1, 2, 3):\n";

    bool found = false;
    for (const auto& pair : students) {
        bool hasUnsatisfactory = false;
        for (const auto& mark : pair.second.marks_) {
            if (mark.mark_ <= 3) {
                hasUnsatisfactory = true;
                break;
            }
        }

        if (hasUnsatisfactory) {
            std::cout << pair.second.name_ << ", " << pair.first << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "There are no students with bad marks.\n";
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::map<std::size_t, StudentData> students;

    std::ifstream in("input1.txt");   //менять здесь для тестов
    if (!in) {
        std::cerr << "Can't open input file\n";
        return 1;
    }
    std::cout << "File opened successfully.\n";
    readFromFile(students, in);
    in.close();

    if (students.empty()) {
        std::cout << "There are no data\n";
        return 1;
    }

    printSortedByNumber(students);
    printAlphabetical(students);
    printStudentsInRange(students);
    printStudentsBySubject(students);
    countStudentsPerSubject(students);
    calculateSubjectAverages(students);
    findStudentsWithMaxSum(students);
    findStudentsWithUnsatisfactory(students);

    return 0;
}
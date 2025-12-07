#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;

int main() {
    std::ifstream in("input.txt");
    if (!in) {
        cout << "Can't open input file!";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    if (lines.empty()) {
        cout << "input file is empty!";
        return 1;
    }

    bool found = false;
    int minLen = 0, maxLen = 0;
    int minLine, maxLine;
    int minPos, maxPos;

    for (int i = 0; i < lines.size(); i++) {
        std::string cur = lines[i];
        int pos = 0;

        while (pos < cur.size()) {
            while (pos < cur.size() && cur[pos] == ' ') {
                pos++;
                if (pos >= cur.size()) {
                    break;
                }
            }
            int start = pos;

            while (pos < cur.size() && cur[pos] != ' ') {
                pos++;
            }
            int len = pos - start;

            if (!found || len < minLen) {
                minLen = len;
                minLine = i;
                minPos = start;
                found = true;
            }
            if (!found || len > maxLen) {
                maxLen = len;
                maxLine = i;
                maxPos = start;
                found = true;
            }
        }
    }

    if (found && !(minLine == maxLine && minPos == maxPos)) {
        std::string& line1 = lines[minLine];
        std::string& line2 = lines[maxLine];

        int end1 = minPos;
        while (end1 < line1.size() && line1[end1] != ' ') {
            end1++;
        }
        int end2 = maxPos;
        while (end2 < line2.size() && line2[end2] != ' ') {
            end2++;
        }
        std::string word1 = line1.substr(minPos, end1 - minPos);
        std::string word2 = line2.substr(maxPos, end2 - maxPos);

        line1 = line1.substr(0, minPos) + word2 + line1.substr(end1);
        line2 = line2.substr(0, maxPos) + word1 + line2.substr(end2);
    }

    std::ofstream out("output.txt");
    if (!out) {
        cout << "Can't open output file!";
        out.close();
        return 1;
    }
    for (int i = 0; i < lines.size(); i++) {
        out << lines[i] << '\n';
    }
    out.close();

    return 0;
}
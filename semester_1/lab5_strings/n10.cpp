#include <iostream>
#include <string>
using std::cin;
using std::cout;

int main() {
    std::string StartStr;
    std::string NewSTR;
    cout << "Enter a string of words separated by punctuation marks: " << '\n';
    std::getline(cin, StartStr);
    if (StartStr.empty()) {
        cout << "Input string is empty!\n";
        return 0;
    }
    cout << '\n';

    int CurUnique = 0, MaxUnique = 0;
    int len = StartStr.size();
    bool used[256] = { false };

    for (int i = 0; i < len; i++) {
        if (StartStr[i] == '.' || StartStr[i] == ',' || StartStr[i] == ':' ||
            StartStr[i] == ';' || StartStr[i] == '!' || StartStr[i] == '?') {

            if (CurUnique > MaxUnique) {
                MaxUnique = CurUnique;
            }
            CurUnique = 0;
            for (int k = 0; k < 256; k++) {
                used[k] = false;
            }
        }
        else {
            unsigned char c = StartStr[i];
            if (!used[c]) {
                used[c] = true;
                CurUnique++;
            }
        }
    }

    if (CurUnique > MaxUnique) {
        MaxUnique = CurUnique;
    }

    CurUnique = 0;
    for (int k = 0; k < 256; k++) {
        used[k] = false;
    }

    int wordStart = 0;
    for (int i = 0; i <= len; i++) {
        if (i == len || StartStr[i] == '.' || StartStr[i] == ',' || StartStr[i] == ':' ||
            StartStr[i] == ';' || StartStr[i] == '!' || StartStr[i] == '?') {

            if (CurUnique == MaxUnique && CurUnique > 0) {
                if (!NewSTR.empty()) {
                    NewSTR += " ";
                }
                NewSTR += StartStr.substr(wordStart, i - wordStart);
            }

            if (i < len) {
                wordStart = i + 1;
            }
            CurUnique = 0;
            for (int k = 0; k < 256; k++) {
                used[k] = false;
            }
        }
        else if (i < len) {
            unsigned char c = StartStr[i];
            if (!used[c]) {
                used[c] = true;
                CurUnique++;
            }
        }
    }
    cout << "String of words with maximum unique characters: " << NewSTR << '\n';

}
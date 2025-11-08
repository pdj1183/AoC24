#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)");
    int sum = 0;

    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            auto begin = sregex_iterator(line.begin(), line.end(), pattern);
            auto end = sregex_iterator();

            cout << "Found: " << distance(begin, end) << " matches" << endl;
            for (sregex_iterator i = begin; i != end; i++) {
                string match = i->str();
                int first, second;
                cout << "Match: " << match << endl;
                regex digit_pattern("\\d{1,3}");
                smatch digit_match;
                if (regex_search(match, digit_match, digit_pattern)) {
                    cout << "Size: " << digit_match.size() << endl;
                    cout << "First: " << digit_match[0] << endl;
                    first = stoi(digit_match[0]);
                    match = digit_match.suffix();
                }
                if (regex_search(match, digit_match, digit_pattern)) {
                    cout << "Second: " << digit_match[0] << endl;
                    second = stoi(digit_match[0]);
                }
                sum += first * second;
            }
        }
    }
    cout << "Sum of multiplication is: " << sum << endl;
    return 0;
}

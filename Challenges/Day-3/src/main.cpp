#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
using namespace std;

string TrimInstructions(string &input) {
    bool followingInstructions = true;
    string trimmedInput = "";
    string originalInput = input;
    regex doPattern("do\\(\\)");
    regex dontPattern("don\\'t\\(\\)");

    smatch match;
    while (regex_search(originalInput, match, dontPattern)) {
        trimmedInput += match.prefix();
        cout << "Trimming: " << match.prefix() << " --added" << endl;
        string dontSuffix = match.suffix();
        if (regex_search(dontSuffix, match, doPattern)) {
            originalInput = match.suffix();
        } else {
            originalInput = "";
            break;
        }
    }
    trimmedInput += originalInput;
    cout << "Trimmed Input: " << trimmedInput << endl;
    return trimmedInput;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file> [--instruct]" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    string inputString = "";

    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            inputString += line;
        }
        input.close();
    }

    if (argc >= 3 && string(argv[2]) == "--instruct") {
        cout << "Follow instructions mode enabled" << endl;
        inputString = TrimInstructions(inputString);
    }

    regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)");
    int sum = 0;
    auto begin = sregex_iterator(inputString.begin(), inputString.end(), pattern);
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

    cout << "Sum of multiplication is: " << sum << endl;
    return 0;
}

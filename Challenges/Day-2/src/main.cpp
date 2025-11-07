#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int isSafe(vector<int> numbers) {
  int prev = numbers[0];
  int curr = numbers[1];
  bool increasing;

  int diff = curr - prev;

  if (0 == abs(diff) || abs(diff) > 3) {
    cout << "First values were the same or too large. Prev: " << prev
         << " Curr: " << curr << endl;
    return -1; // Unsafe change too big or stayed same
  } else if (0 < diff) {
    increasing = true;
  } else {
    increasing = false;
  }

  prev = curr;

  for (int i = 2; i < numbers.size(); i++) {
    curr = numbers[i];

    if (increasing) {
      diff = curr - prev;
    } else {
      diff = prev - curr;
    }

    cout << "Increasing is " << increasing << " and the diff is: " << diff
         << endl;

    if (0 >= diff || diff > 3) {
      return -1;
    }

    prev = curr;
  }
  return 1;
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <input_file> [--damper]" << endl;
    return 1;
  }

  bool damper = false;
  if (argc >= 3 && string(argv[2]) == "--damper") {
    damper = true;
    cout << "Damper mode enabled" << endl;
  }

  ifstream input(argv[1]);
  int safe = 0;

  if (input.is_open()) {
    string line;
    while (getline(input, line)) {
      vector<int> numbers;
      stringstream ss(line);
      int num;
      while (ss >> num) {
        numbers.push_back(num);
      }

      if (isSafe(numbers) == 1) {
        cout << line << " IS Safe" << endl;
        safe += 1;
      } else {
        cout << line << " is NOT safe" << endl;
        if (damper) {
          cout << "Trying with damper active!" << endl;
          // Try removing each number one at a time
          for (int i = 0; i < numbers.size(); i++) {
            vector<int> dampened = numbers;
            dampened.erase(dampened.begin() + i);
            if (isSafe(dampened) == 1) {
              cout << line << " IS Safe with damper (removed position " << i
                   << ")" << endl;
              safe += 1;
              break;
            }
          }
        }
      }
    }
    input.close();

    cout << safe << " lines were safe!" << endl;
  } else {
    cerr << "Error reading file" << endl;
  }
  return 0;
}

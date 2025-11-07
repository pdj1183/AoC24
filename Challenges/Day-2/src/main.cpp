#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int isSafe(string line) {
  stringstream ss(line);
  int prev, curr;
  bool increasing;
  ss >> prev;
  ss >> curr;

  int diff = curr - prev;

  if (0 == abs(diff) || abs(diff) > 3) {
    cout << "First values of line were the same or too large. Prev: " << prev
         << " Curr: " << curr << endl;
    return -1; // Unsafe change too big or stayed same
  } else if (0 < diff) {
    increasing = true;
  } else {
    increasing = false;
  }

  prev = curr;

  while (ss >> curr) {
    if (increasing) {
      diff = curr - prev;
    } else {
      diff = prev - curr;
    }

    cout << "Increasing is " << increasing << "and the diff is: " << diff
         << endl;

    if (0 >= diff | diff > 3)
      return -1;

    prev = curr;
  }
  return 1;
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <input_file>" << endl;
    return 1;
  }

  ifstream input(argv[1]);
  int safe = 0;

  if (input.is_open()) {
    string line;
    while (getline(input, line)) {
      if (isSafe(line) == 1) {
        cout << line << " IS Safe" << endl;
        safe += 1;
      }
      cout << line << " is NOT safe" << endl;
    }
    input.close();

    cout << safe << " lines were safe!" << endl;
  } else {
    cerr << "Error reading file" << endl;
  }
  return 0;
}

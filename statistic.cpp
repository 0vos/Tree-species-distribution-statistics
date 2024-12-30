#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

class StaForest {
private:
    unordered_map<string, int> forest;
    size_t size;

public:
    StaForest() : size(0) {}
    StaForest(string* trees, int length);
    string statistic();
};

string get_statistic(string* trees, int length) {
    try {
        StaForest forest = StaForest(trees, length);
        return forest.statistic();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return "";
    }
}

StaForest::StaForest(string* trees, int length) {
    size = 0;
    for (size_t i = 0; i < length; ++i) {
        size_t end_pos = trees[i].find(",", 0);
        string name;
        if (end_pos != string::npos) {
            name = trees[i].substr(0, end_pos);
        } else {
            name = trees[i];
        }

        if (!name.empty()) {
            ++size;
            forest[name]++;
        } else {
            throw invalid_argument("Tree name cannot be empty.");
        }
    }
}

string StaForest::statistic() {
    if (size == 0) {
        throw runtime_error("No trees in the forest. Size is zero.");
    }

    string result;
    for (const auto& [name, count] : forest) {
        double percent = 100.0 * count / size;
        result += name + " " + to_string(percent) + "%\n";
    }

    return result;
}

string statistic_string2json(const string& input) {
    istringstream stream(input);
    string line, key, value, result = "{";

    while (getline(stream, line)) {
        istringstream lineStream(line);

        // Separate key and value
        lineStream >> key >> value;

        // Remove '%' symbol
        if (!value.empty() && value.back() == '%') {
            value.pop_back();
        }

        // Append to JSON string
        if (result.size() > 1) { // If not the first element, add a comma
            result += ",";
        }
        result += "\"" + key + "\":\"" + value + "\"";
    }

    result += "}";
    return result;
}

// Test
// int main() {
//     string trees[] = {
//         "Oak,1",
//         "Pine,2",
//         "Birch,3",
//         "Oak,4"
//     };

//     try {
//         string result = get_statistic(trees, 4);
//         cout << "Statistics Result:" << endl;
//         cout << result << endl;

//         string json_result = statistic_string2json(result);
//         cout << "JSON Format:" << endl;
//         cout << json_result << endl;

//     } catch (const exception& e) {
//         cerr << "Unhandled Error: " << e.what() << endl;
//     }

//     return 0;
// }
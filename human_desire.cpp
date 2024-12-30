#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// 辅助递归函数，进行字符串匹配的重复计算
int repeat(int i, int j, int next[], string in_test) {
    if (i == 0) {
        return 0;
    } else {
        i--;
        i = next[i];
        if (in_test[i] == in_test[j]) {
            return i;
        } else {
            i = repeat(i, j, next, in_test);
            return i;
        }
    }
}

// 辅助函数：从内容中提取所有匹配的树名位置
vector<int> find_tree_positions(const string &content, const string &tree_name) {
    if (tree_name.empty()) {
        throw invalid_argument("Tree name cannot be empty.");
    }

    vector<int> positions;
    size_t pos = 0;

    while (pos < content.size()) {
        size_t start = content.find(tree_name + ",", pos);
        if (start == string::npos) break;

        // 确保匹配到的是完整的树名（前后需要是换行符或文件开头）
        if ((start == 0 || content[start - 1] == '\n')) {
            positions.push_back(start);
        }
        pos = start + tree_name.length() + 1; // 跳过当前匹配位置
    }

    return positions;
}

// 统计文件中与给定树名匹配的条目数量
int count_num_of_same(const string &content, const string &tree_name) {
    if (tree_name.empty()) {
        throw invalid_argument("Tree name cannot be empty.");
    }

    vector<int> positions = find_tree_positions(content, tree_name);
    return positions.size(); // 返回匹配到的树名数量
}

// 将匹配树名的位置存储到数组中
void position_of_number(int *p, const string &content, const string &tree_name) {
    if (p == nullptr) {
        throw invalid_argument("Pointer p cannot be null.");
    }
    vector<int> positions = find_tree_positions(content, tree_name);
    for (size_t i = 0; i < positions.size(); ++i) {
        p[i] = positions[i];
    }
}

// 生成包含前后5个字符的信息
string get_total_part(string test, string in_test) {
    if (test.empty() || in_test.empty()) {
        throw invalid_argument("Input strings cannot be empty.");
    }

    int count = count_num_of_same(test, in_test); // 统计匹配数量
    if (count == 0) {
        return ""; // 无匹配则直接返回空字符串
    }

    int *p = new (nothrow) int[count]; // 动态分配数组
    if (!p) {
        throw runtime_error("Memory allocation failed for position array.");
    }

    position_of_number(p, test, in_test); // 将匹配位置存入数组

    string part1, part2, final_all = "";
    for (int j = 0; j < count; j++) {
        // 提取前5个和后5个字符，处理边界情况
        if (p[j] - 5 > 0) {
            part1 = test.substr(p[j] - 5, 5);
        } else {
            part1 = test.substr(0, p[j]);
        }

        if (p[j] + in_test.size() + 5 <= test.size()) {
            part2 = test.substr(p[j] + in_test.size(), 5);
        } else {
            part2 = test.substr(p[j] + in_test.size());
        }

        // 组合结果并追加
        final_all += to_string(j + 1) + "." + part1 + "(" + in_test + ")" + part2 + "\n";
    }

    delete[] p; // 释放动态分配的内存
    return final_all;
}

// // 主函数（仅用于测试功能）
// int main() {
//     try {
//         string test = "oak,apple,oaktree,banana,oaktree,pear,oaktree";
//         string in_test = "oaktree";
//         string result = get_total_part(test, in_test);

//         if (!result.empty()) {
//             cout << "Result:\n" << result;
//         } else {
//             cout << "No matches found.\n";
//         }
//     } catch (const exception &e) {
//         cerr << "Error: " << e.what() << endl;
//     }

//     return 0;
// }
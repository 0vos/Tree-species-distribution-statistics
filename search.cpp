#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 函数用于读取文件并查找包含指定文字的行并输出
void read_and_search(const string& target_text) {
    ifstream file("tree_info.txt");
    if (!file) {
        cerr << "无法打开文件: " << "tree_info.txt" << endl;
        return;
    }
    string line;
    bool found = false;  // 用于标记是否找到包含目标文字的行
    while (getline(file, line)) {
        if (line.find(target_text)!= string::npos) {
            cout << line << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "没有查询到，请检查输入的格式是否正确" << endl;
    }
    file.close();
}

int main() {
    string target_text;
    while (true) {
        cout << "请输入要查找的文字内容（输入'exit'可退出）: ";
        getline(cin, target_text);
        if (target_text == "exit") {
            break;
        }
        read_and_search(target_text);
    }
    return 0;
}
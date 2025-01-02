#include<iostream>
#include<fstream>
#include<string>
#include <locale>
#include"human_desire.cpp"
using namespace std;
int count_useful_lines(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件" << filename << endl;
        return 0;
    }

    int line_count = 0;
    string line;

    // 逐行读取文件内容
    while (getline(file, line)) {
        if(line.find(",")!=string::npos&&line.find(",")!=0){
            line_count++;
        }
    }

    // // 检查最后一行是否被遗漏
    // if (!line.empty() && file.eof()) {
    //     line_count++;
    // }

    file.close();
    // cout << "Number of useful lines in the file: " << line_count << endl;
    return line_count;
}
int count_lines(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件" << filename << endl;
        return 0;
    }

    int line_count = 0;
    string line;

    // 逐行读取文件内容
    while (getline(file, line)) {
        line_count++;
    }

    // 检查最后一行是否被遗漏
    if (!line.empty() && file.eof()) {
        line_count++;
    }

    file.close();
    // cout << "Number of lines in the file: " << line_count << endl;
    return line_count;
}

void add(string filename){
    string addition= "";
    cin>>addition;
    while(addition.find(',')==string::npos||addition.find(',')==0){
        cout<<"无效条目，请重新按格式输入，或者输入exit退出"<<endl;
        cin>>addition;
        if(addition== "exit"){
            return;
        }
    }
    string content= "";
    ifstream ifile(filename);
    char c;
    while(ifile.get(c)){
        content+= c;
    }
    content= content+'\n'+ addition; 
    //cout<<content;
    cout<<"已添加"<<endl;
    ofstream ofile(filename);
    if(ofile.is_open()){
        ofile<<content;
    }else{
        cout<<"无法打开文件！"<<endl;
    }

}

void read(string filename, string* p, int max_lines) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件：" << filename << endl;
        return;
    }

    string line;
    int j = 0;

    // 逐行读取文件内容并存储到数组中
    while (getline(file, line) && j < max_lines) {
        if(line.find(",")!=string::npos&&line.find(",")!=0){
            p[j] = line;
            j++;
        }
    }
    file.close();
}
void remove_info(string filename) {
    cout << "请输入一个树名来删除，或者输入exit退出删除程序" << endl;

    string re_move;
    while (true) {
        // 提示用户输入树名
        cout << "树名：";
        cin >> re_move;

        // 如果输入 "exit"，退出程序
        if (re_move == "exit") {
            cout << "退出删除程序！" << endl;
            break;
        }

        // 读取文件内容
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "无法打开文件：" << filename << endl;
            return;
        }
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        // 找到匹配的条目
        vector<int> positions; // 存储每个匹配条目的起始位置
        vector<string> entries; // 存储每个匹配条目的内容
        size_t pos = 0;

        while ((pos = content.find(re_move + ",", pos)) != string::npos) {
            size_t start_pos = pos;
            // 确保匹配到的是完整的树名（树名前必须是换行符或文件开头）
            if (start_pos == 0 || content[start_pos - 1] == '\n') {
                size_t end_pos = content.find('\n', start_pos);
                if (end_pos == string::npos) end_pos = content.size(); // 如果是最后一行
                string entry = content.substr(start_pos, end_pos - start_pos);
                positions.push_back(start_pos);
                entries.push_back(entry);
            }
            pos += re_move.length() + 1; // 跳过当前匹配位置
        }

        if (positions.empty()) {
            cout << "无效树名，请重新输入！" << endl;
            continue;
        }

        // 显示匹配的树条目
        for (size_t i = 0; i < entries.size(); ++i) {
            cout << i + 1 << ". " << entries[i] << endl;
        }

        cout << "请选择一个序号来删除，或者输入exit取消删除：";
        string choice;
        cin >> choice;

        if (choice == "exit") {
            cout << "取消删除！" << endl;
            continue;
        }

        // 检查输入的编号是否有效
        int selected_index = -1;
        try {
            selected_index = stoi(choice) - 1;
        } catch (invalid_argument&) {
            cout << "无效输入，请输入一个有效的数字！" << endl;
            continue;
        }

        if (selected_index < 0 || selected_index >= static_cast<int>(positions.size())) {
            cout << "无效选择，请重新输入！" << endl;
            continue;
        }

        // 删除选中的条目
        size_t start_pos = positions[selected_index];
        size_t end_pos = content.find('\n', start_pos);
        if (end_pos == string::npos) {
            // 如果是最后一行，删除到文件末尾，包括可能的换行符
            content.erase(start_pos-1);
        } else {
            content.erase(start_pos, end_pos - start_pos + 1); // 删除包含换行符的整条记录
        }

        // 更新文件内容
        ofstream ofile(filename);
        if (!ofile.is_open()) {
            cerr << "无法写到文件中！" << endl;
            break;
        }
        ofile << content;
        ofile.close();

        cout << "删除成功！" << endl;
    }
}
void search_trees(string filename) {
    cout << "请输入树名进行查找，输入exit退出" << endl;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件：" << filename << endl;
        return;
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    string re_move;
    while (true) {
        cout << "树名：";
        cin >> re_move;

        if (re_move == "exit") {
            cout << "退出查找程序！" << endl;
            break;
        }

        // 验证输入的树名是否有效
        bool valid_tree = false;
        size_t pos = 0;
        while ((pos = content.find('\n', pos)) != string::npos) {
            size_t start = content.rfind('\n', pos - 1) + 1;
            size_t comma_pos = content.find(',', start);
            string tree_name = content.substr(start, comma_pos - start);
            if (tree_name == re_move) {
                valid_tree = true;
                break;
            }
            pos++;
        }

        if (!valid_tree) {
            cout << "无效树名，请重新输入：" << endl;
            continue;
        }

        // 搜索并显示匹配的树名
        int number_of_same_tree = count_num_of_same(content, re_move);
        if (number_of_same_tree == 0) {
            cout << "对树名：" << re_move << " 没有匹配的树！" << endl;
        } else {
            int* p = new int[number_of_same_tree];
            position_of_number(p, content, re_move);

            // 显示匹配的树条目
            for (int i = 0; i < number_of_same_tree; i++) {
                int start_pos = p[i];
                int end_pos = content.find('\n', start_pos);
                string entry = content.substr(start_pos, end_pos - start_pos);
                cout << i + 1 << ". " << entry << endl;
            }

            delete[] p; // 释放动态数组内存
        }
    }
}
// int main(){
//     string filename= "tree_info.txt";
//     string *p= new string[count(filename)];
//     search_trees(filename);
//     //remove_info(filename);
//     //read(filename, p);
//     //add(filename);
//     //delete[]p;
    
//     return 0;
// }
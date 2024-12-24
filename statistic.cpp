#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

class StaForest{
    private:
    unordered_map<string, int> forest;
    size_t size;
    public:
    StaForest(): size(0){}
    StaForest(string* trees, int length);
    string statistic();
};

string get_statistc(string* trees, int length){
    StaForest forest = StaForest(trees, length);
    return forest.statistic();
}

StaForest::StaForest(string *trees, int length){
    size = 0;
    for(size_t i=0;i<length;++i){
        size_t end_pos = trees[i].find(",", 1);
        string name;
        if(i==0){
            name = trees[i].substr(0, end_pos);
        }
        else{
            name = trees[i].substr(1, end_pos - 1);
        }
        if(!name.empty()){
            size++;
            if(forest.count(name)){
                forest[name] += 1;
            }
            else{
                forest[name] = 1;
            }
        }
        else{
            printf("树名不能为空！\n");
            exit(0);
        }
    }
}

string StaForest::statistic(){
    string result = "";
    // cout << "size: " << size << endl;
    // for (auto it = forest.begin(); it != forest.end(); ++it) {
    //     cout << "Tree type: " << it->first << ", Count: " << it->second << endl;
    // }
    for(auto it=forest.begin();it!=forest.end();++it){
        result += it->first;
        if(size){
            // cout << "name: " << it->first << "number: " << it->second << endl;
            double percent = 100 * (double(it->second) / double(size));
            result += " " + to_string(percent) + "%\n";
        }
        else{
            printf("树木总数为空！\n");
            exit(0);
        }
    }
    cout << "result\n" << result << endl;
    string hint = "<----------树种统计程序---------->\n1. 查找一棵树\n2. 增加一棵树\n3. 删除一棵树\n4. 退出\n请输入功能对应的序号进行操作: ";
    cout << hint << endl;
    return result;
}

string statistic_string2json(const string& input) {
    istringstream stream(input);
    string line, key, value, result = "{";

    while (std::getline(stream, line)) {
        istringstream lineStream(line);

        // 分离 key 和 value
        lineStream >> key >> value;

        // 去掉 '%' 符号
        if (!value.empty() && value.back() == '%') {
            value.pop_back();
        }

        // 添加到 JSON 格式字符串
        if (result.size() > 1) {  // 如果不是第一个元素，添加逗号分隔
            result += ",";
        }
        result += "\"" + key + "\":\"" + value + "\"";
    }

    result += "}";
    return result;
}

// // test
// int main(){

//     return 0;
// }
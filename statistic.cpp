#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

class StaForest{
    private:
    unordered_map<string, int> forest;
    size_t size;
    public:
    StaForest(): size(0){}
    StaForest(string* trees);
    string statistic();
};

string get_statistc(string* trees){
    StaForest forest = StaForest(trees);
    return forest.statistic();
}

StaForest::StaForest(string *trees){
    size = 0;
    for(size_t i=0;trees[i][0];++i){
        size_t end_pos = trees[i].find(" ", 0);
        string name = trees[i].substr(0, end_pos - 0);
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
    for(auto it=forest.begin();it!=forest.end();++it){
        result += it->first;
        if(size){
            double percent = 100 * (double(it->second) / double(size));
            result += " " + to_string(percent) + "%\n";
        }
        else{
            printf("树木总数为空！\n");
            exit(0);
        }
    }
    return result;
}

// // test
// int main(){

//     return 0;
// }
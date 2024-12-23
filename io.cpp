#include<iostream>
#include<fstream>
#include<string>
using namespace std;
// void add(string p[], int number_of_trees){
//     cout<<"请输入增加的树种和相应的坐标，格式例为：桦树，（30，45）"<<endl;
//     string addition= "";
//     cin>>addition;
//     string *p= new string[number_of_trees+1];
// }
int count(string filename){
    ifstream file(filename);
    char c;
    string content= "";
    int number_of_trees= 0;
    if(file.is_open()){
        while(file.get(c)){
            if(c== ','){
                number_of_trees++;
            }
        }
    }else{
        cout<<"cannot open the file"<<endl;
    }
    return number_of_trees/2;
}
void read(string filename, string *p)
{
    ifstream file(filename);
    char c;
    string content= "";
    while(file.get(c)){
        content+= c;
    }
    int i, j=0;
    for(i=0; i<content.size(); i++){
        if(content[i]!= ')'){
            p[j]+= content[i];
        }else{
            p[j]+= ')';
            j++;
        }
    }
    
}
// 松树 3.1%\n桦树 3.6%\n
string statistic_string2json(const string& input_string){
    string json_string = "{";
    for(size_t i=0;i<input_string.length();){
        //树名
        size_t start_pos = i;
        json_string += "\"";
        size_t end_name = input_string.find(" ", start_pos);
        string name = input_string.substr(start_pos, end_name - start_pos);
        json_string += name + "\":\"";
        start_pos = end_name + 1;
        //百分比
        size_t end_percent = input_string.find("%", start_pos);
        string percent = input_string.substr(start_pos, end_percent - start_pos);
        json_string += percent + "\",";
        i = end_percent + 2;
    }
    json_string.pop_back();
    json_string += "}";
    return json_string;
}
// int main(){
//     string filename= "tree_info.txt";
//     string *p= new string[count(filename)];
//     read(filename, p);
//     for(int i=0; i<count(filename); i++){
//         cout<<p[i];
//     }
//     string s = "松树 3.1%\n桦树 3.6%\n";
//     string json_result = statistic_string2json(s);
//     cout << json_result << endl;
// }
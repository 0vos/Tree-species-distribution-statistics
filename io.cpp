#include<iostream>
#include<fstream>
#include<string>
#include"statistic.cpp"
#include <locale>
#include <windows.h>
#include"human_desire.cpp"
using namespace std;

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
void add(string filename){
    cout<<"上树,(99,99)"<<endl;
    string addition= "";
    cin>>addition;
    string content= "";
    ifstream ifile(filename);
    char c;
    while(ifile.get(c)){
        content+= c;
    }
    content= content+'\n'+ addition;
    //cout<<content;
     
    ofstream ofile(filename);
    if(ofile.is_open()){
        ofile<<content;
    }else{
        cout<<"cannot open the file"<<endl;
    }

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
        if(content[i]!= '\n'){
            p[j]+= content[i];
        }else{
            j++;
        }
    }
    
}
void remove_info(string filename){
    cout<<"请输入你想要删除的树种"<<endl;
    ifstream file(filename);
    char c;
    string content= "";
    while(file.get(c)){
        content+= c;
    }
    //截止到这里是把文件内容录入到content中
    string re_move;
    cin>>re_move;//输入要作为删除的字符串
    //这里判定re_move的输入可以直接退出循环
    string position= search(content, re_move);
    int number_of_same_tree= count_num_of_same(content, re_move);//对于相同的内容进行计数，比如说松树一共有多少坐标

    while(number_of_same_tree== 0){//异常输入处理，进行提示，可以在这里加入比如exit就退出
        cout<<"error input,请重新输入"<<endl;
        cin>>re_move;
        position= search(content, re_move);
        number_of_same_tree= count_num_of_same(content, re_move);
    }
    int *p= new int[number_of_same_tree];//数组p包含了该搜索内容所有位置，准备进行删改
    posion_of_number(p, content, re_move);
    
    int i;
    for(i= 0; i<number_of_same_tree; i++){
        int number= p[i];
        int end= content.find('\n', p[i]);//一直找到这一行的末尾，完整的输出这一行
        string part= content.substr(number, end- number);
        cout<<i+1<<"."<<part<<endl;
    }
    cout<<"请输入你想删除的位置"<<endl;
    string po;
    int judge= 0;
    while(judge== 0){//异常处理
        cin>>po;
        for(int i=0; i<number_of_same_tree; i++){
            if(po!= to_string(i+1)){
                continue;
            }else{
                judge= 1;
                break;
            }
        }
        if(judge== 0){
            cout<<"error input"<<endl;
        }
        
    }
    int number= p[stoi(po)-1];
    string part1= content.substr(0, number);//缝合两个字符串
    int end= content.find('\n', number);
    string part2= content.substr(end+1);
    content= part1+part2;
    //cout<<content;
    ofstream ofile(filename);
    ofile<<content;
    //return position;
}
void search_trees(string filename){
    cout<<"请输入你想要查询的树种"<<endl;
    ifstream file(filename);
    char c;
    string content= "";
    while(file.get(c)){
        content+= c;
    }
    string re_move;
    cin>>re_move;
    //这里判定re_move的输入可以直接退出循环


    string position= search(content, re_move);
    int number_of_same_tree= count_num_of_same(content, re_move);
    while(number_of_same_tree== 0){
        cout<<"不存在,请重新输入"<<endl;
        cin>>re_move;
        position= search(content, re_move);
        number_of_same_tree= count_num_of_same(content, re_move);
    }
    int *p= new int[number_of_same_tree];
    posion_of_number(p, content, re_move);
    
    for(int i= 0; i<number_of_same_tree; i++){
        int number= p[i];
        int end= content.find('\n', p[i]);
        string part= content.substr(number, end- number);
        cout<<i+1<<"."<<part<<endl;
    }
}
int main(){
    string filename= "tree_info.txt";
    string *p= new string[count(filename)];
    // string name;
    // cin>>name;
    //name= "鏉炬爲,(75,92)";
    //search_trees(filename);
    remove_info(filename);
    //read(filename, p);
    //add(filename);
    //delete[]p;
    //string final= get_statistc(p, count(filename));
    //cout<<final<<endl;
    // for(int i=0; i<count(filename); i++){
    //     cout<<p[i]<<endl;
    // }
    return 0;
}
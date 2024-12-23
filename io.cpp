#include<iostream>
#include<fstream>
#include<string>
#include"statistic.cpp"
#include <locale>
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
    //content= content+'\n'+ addition;
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
        if(content[i]!= ')'){
            p[j]+= content[i];
        }else{
            p[j]+= ')';
            j++;
        }
    }
    
}
int repeat(int i, int j, int next[], string in_test){
    //repeat函数主要用来递归计算next数组，就是采用最常规的next数组的计算方法
    if(i== 0){
        return 0;
    }else{
        i--;
        i= next[i];
        if(in_test[i]== in_test[j]){
            return i;
        }else{
            i= repeat(i, j, next, in_test);
            return i;
        }
    }
}
string search(string test, string in_test){
    int next[in_test.size()]= {0};
    int i=0, j=1;
    //计算next数组
    while(j<= in_test.size()){
        if(in_test[j]== in_test[i]){
            next[j]= i+1;
            i++;
            j++;
        }else{
            if(i== 0){
                j++;
            }else{
                i= repeat(i, j, next, in_test);
            }
        }
    }
    i=0, j=0;
    int judge= 0;
    string posion= "";
    while(j<= test.size()){
        if(i== in_test.size()){
            judge++;
            posion+= to_string(j-in_test.size());
            posion+="_";
            i= 0;
        }else{
            if(test[j]== in_test[i]){
                i++;
                j++;
            }else{
                if(i== 0){
                    j++;
                }else{
                    i= next[i-1];
                    if(test[j]== in_test[i]){
                        i++;
                    }
                    j++;
                }
            }
        }
    }
    posion+= to_string(judge);
    return posion;
}
void remove(string filename){
    cout<<"请输入你想要删除的数据"<<endl;
    ifstream file(filename);
    char c;
    string content= "";
    while(file.get(c)){
        content+= c;
    }
    string re_move= "梧桐树,(40,55)";
    re_move= re_move+'\n';
    //cin>>re_move;
    string position= search(content, re_move);
    int i= 0, j= 0, k= 0;
    string position_of_same= "";
    while(position[i]!= '\0'){
        if(position[i]== '_'){
            break;
        }else{
            position_of_same+= position[i];
        }
        i++;
    }
    int number= stoi(position_of_same);
    string part1= content.substr(0, number);
    string part2= content.substr(number+re_move.size());
    content= part1+part2;
    //cout<<content;
    ofstream ofile(filename);
    ofile<<content;
    //return position;
}
int main(){
    string filename= "tree_info.txt";
    //string *p= new string[count(filename)];
    string name;
    //name= "松树,(75,92)";
    remove(filename);
    // scanf("%s", name);
    // cout<<name;
    // read(filename, p);
    // add(filename);
    //delete[]p;
    //string final= get_statistc(p, count(filename));
    //cout<<final<<endl;
    // for(int i=0; i<count(filename); i++){
    //     cout<<p[i];
    // }
    return 0;
}
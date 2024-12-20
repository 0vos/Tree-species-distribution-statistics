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
int main(){
    string filename= "tree_info.txt";
    string *p= new string[count(filename)];
    read(filename, p);
    for(int i=0; i<count(filename); i++){
        cout<<p[i];
    }
}
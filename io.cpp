#include<iostream>
#include<fstream>
#include<string>
#include"statistic.cpp"
#include<codecvt>
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
    content= content+'\n'+ addition;
     
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
int main(){
    string filename= "tree_info.txt";
    string *p= new string[count(filename)];
    read(filename, p);
    add(filename);
    delete[]p;
    //string final= get_statistc(p, count(filename));
    //cout<<final<<endl;
    // for(int i=0; i<count(filename); i++){
    //     cout<<p[i];
    // }
}
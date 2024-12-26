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
    cout<<"����,(99,99)"<<endl;
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
    cout<<"����������Ҫɾ��������"<<endl;
    ifstream file(filename);
    char c;
    string content= "";
    while(file.get(c)){
        content+= c;
    }
    //��ֹ�������ǰ��ļ�����¼�뵽content��
    string re_move;
    cin>>re_move;//����Ҫ��Ϊɾ�����ַ���
    //�����ж�re_move���������ֱ���˳�ѭ��
    string position= search(content, re_move);
    int number_of_same_tree= count_num_of_same(content, re_move);//������ͬ�����ݽ��м���������˵����һ���ж�������

    while(number_of_same_tree== 0){//�쳣���봦��������ʾ������������������exit���˳�
        cout<<"error input,����������"<<endl;
        cin>>re_move;
        position= search(content, re_move);
        number_of_same_tree= count_num_of_same(content, re_move);
    }
    int *p= new int[number_of_same_tree];//����p�����˸�������������λ�ã�׼������ɾ��
    posion_of_number(p, content, re_move);
    
    int i;
    for(i= 0; i<number_of_same_tree; i++){
        int number= p[i];
        int end= content.find('\n', p[i]);//һֱ�ҵ���һ�е�ĩβ�������������һ��
        string part= content.substr(number, end- number);
        cout<<i+1<<"."<<part<<endl;
    }
    cout<<"����������ɾ����λ��"<<endl;
    string po;
    int judge= 0;
    while(judge== 0){//�쳣����
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
    string part1= content.substr(0, number);//��������ַ���
    int end= content.find('\n', number);
    string part2= content.substr(end+1);
    content= part1+part2;
    //cout<<content;
    ofstream ofile(filename);
    ofile<<content;
    //return position;
}
void search_trees(string filename){
    cout<<"����������Ҫ��ѯ������"<<endl;
    ifstream file(filename);
    char c;
    string content= "";
    while(file.get(c)){
        content+= c;
    }
    string re_move;
    cin>>re_move;
    //�����ж�re_move���������ֱ���˳�ѭ��


    string position= search(content, re_move);
    int number_of_same_tree= count_num_of_same(content, re_move);
    while(number_of_same_tree== 0){
        cout<<"������,����������"<<endl;
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
    //name= "松树,(75,92)";
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
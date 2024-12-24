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
<<<<<<< Updated upstream
    cout<<"上树,(99,99)"<<endl;
=======
    cout<<"����,(99,99)"<<endl;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
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
=======
void remove_info(string filename){
    cout<<"����������Ҫɾ��������"<<endl;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
    //delete[]p;
    //string final= get_statistc(p, count(filename));
    //cout<<final<<endl;
    // for(int i=0; i<count(filename); i++){
<<<<<<< Updated upstream
    //     cout<<p[i];
=======
    //     cout<<p[i]<<endl;
>>>>>>> Stashed changes
    // }
    return 0;
}
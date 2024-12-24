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
    cout<<"ä¸Šæ ‘,(99,99)"<<endl;
=======
    cout<<"ÉÏÊ÷,(99,99)"<<endl;
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
    //repeatå‡½æ•°ä¸»è¦ç”¨æ¥é€’å½’è®¡ç®—nextæ•°ç»„ï¼Œå°±æ˜¯é‡‡ç”¨æœ€å¸¸è§„çš„nextæ•°ç»„çš„è®¡ç®—æ–¹æ³•
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
    //è®¡ç®—nextæ•°ç»„
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
    cout<<"è¯·è¾“å…¥ä½ æƒ³è¦åˆ é™¤çš„æ•°æ®"<<endl;
=======
void remove_info(string filename){
    cout<<"ÇëÊäÈëÄãÏëÒªÉ¾³ıµÄÊ÷ÖÖ"<<endl;
>>>>>>> Stashed changes
    ifstream file(filename);
    char c;
    string content= "";
    while(file.get(c)){
        content+= c;
    }
    //½ØÖ¹µ½ÕâÀïÊÇ°ÑÎÄ¼şÄÚÈİÂ¼Èëµ½contentÖĞ
    string re_move;
    cin>>re_move;//ÊäÈëÒª×÷ÎªÉ¾³ıµÄ×Ö·û´®
    //ÕâÀïÅĞ¶¨re_moveµÄÊäÈë¿ÉÒÔÖ±½ÓÍË³öÑ­»·
    string position= search(content, re_move);
    int number_of_same_tree= count_num_of_same(content, re_move);//¶ÔÓÚÏàÍ¬µÄÄÚÈİ½øĞĞ¼ÆÊı£¬±ÈÈçËµËÉÊ÷Ò»¹²ÓĞ¶àÉÙ×ø±ê

    while(number_of_same_tree== 0){//Òì³£ÊäÈë´¦Àí£¬½øĞĞÌáÊ¾£¬¿ÉÒÔÔÚÕâÀï¼ÓÈë±ÈÈçexit¾ÍÍË³ö
        cout<<"error input,ÇëÖØĞÂÊäÈë"<<endl;
        cin>>re_move;
        position= search(content, re_move);
        number_of_same_tree= count_num_of_same(content, re_move);
    }
    int *p= new int[number_of_same_tree];//Êı×ép°üº¬ÁË¸ÃËÑË÷ÄÚÈİËùÓĞÎ»ÖÃ£¬×¼±¸½øĞĞÉ¾¸Ä
    posion_of_number(p, content, re_move);
    
    int i;
    for(i= 0; i<number_of_same_tree; i++){
        int number= p[i];
        int end= content.find('\n', p[i]);//Ò»Ö±ÕÒµ½ÕâÒ»ĞĞµÄÄ©Î²£¬ÍêÕûµÄÊä³öÕâÒ»ĞĞ
        string part= content.substr(number, end- number);
        cout<<i+1<<"."<<part<<endl;
    }
    cout<<"ÇëÊäÈëÄãÏëÉ¾³ıµÄÎ»ÖÃ"<<endl;
    string po;
    int judge= 0;
    while(judge== 0){//Òì³£´¦Àí
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
    string part1= content.substr(0, number);//·ìºÏÁ½¸ö×Ö·û´®
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
    //name= "æ¾æ ‘,(75,92)";
    remove(filename);
    // scanf("%s", name);
    // cout<<name;
    // read(filename, p);
    // add(filename);
=======
void search_trees(string filename){
    cout<<"ÇëÊäÈëÄãÏëÒª²éÑ¯µÄÊ÷ÖÖ"<<endl;
    ifstream file(filename);
    char c;
    string content= "";
    while(file.get(c)){
        content+= c;
    }
    string re_move;
    cin>>re_move;
    //ÕâÀïÅĞ¶¨re_moveµÄÊäÈë¿ÉÒÔÖ±½ÓÍË³öÑ­»·


    string position= search(content, re_move);
    int number_of_same_tree= count_num_of_same(content, re_move);
    while(number_of_same_tree== 0){
        cout<<"²»´æÔÚ,ÇëÖØĞÂÊäÈë"<<endl;
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
    //name= "æ¾æ ‘,(75,92)";
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
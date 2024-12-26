#include<iostream>
#include<string>
using namespace std;
//��ֱ�ӽ�������һ������ϵͳ����������ַ����Ĺ���ϵͳ����Ϊ���������Ǵ洢ͼƬ�����ı�����󶼽���ת��Ϊ�ַ�������
//������ѹ���ˣ��������ϵͳʵ���˶����ַ���������ɾ���ģ��鹦�ܣ�����Ŀ�еĲ�ѯ�͸���ȫ��ʵ��
int repeat(int i, int j, int next[], string in_test){
    //repeat������Ҫ�����ݹ����next���飬���ǲ�������next����ļ��㷽��
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
    int next[in_test.size()];//ͨ��Ҫƥ����ַ����ĳ���������next����Ĵ�С
    for(size_t i=0;i<in_test.size();++i){
        next[i] = 0;//�����ʼ��Ϊ0
    }
    int i=0, j=1;
    //����next����
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
    //����ʹ��kmpƥ���㷨
    while(j<= test.size()){
        if(i== in_test.size()){//jȥ����test���飬iȥ����in_test���飬��i==in_test.size()ʱ��˵����ȫƥ������
            judge++;//judge���������ڵ�ǰtest�ַ������ж��ٸ���in_test��ͬ���ַ���
            posion+= to_string(j-in_test.size());//position��������in_test�ַ���������test�е�������������ַ�������ʽ�洢����  
            posion+="_";//ÿ��λ��֮����_����
            i= 0;//��i��գ���ʼ��һ��ƥ��
        }else{
            if(test[j]== in_test[i]){//���ַ����ʱ��ƥ����һ��
                i++;
                j++;
            }else{//�����ʱ
                if(i== 0){//����kmp�㷨������Ѿ��˻���in_testͷ������ʼƥ��test����һ���ַ�
                    j++;
                }else{
                    i= next[i-1];//����next���飬��ת����Ӧ��in_testλ�ý��бȽ�
                    if(test[j]== in_test[i]){//���ʱƥ����һ��
                        i++;
                    }
                    j++;
                }
            }
        }
    }
    posion+= to_string(judge);//ԭposition�е���ϢΪ������_��������_������������������һ���ж��ٸ�λ�ã������ٸ�����
    return posion;//���������������λ�ú�λ�ø������ַ���������Ϊ�����Ľ��
}
int count_num_of_same(string test, string in_test){//�ú���������ȡposition����λ�ø�����������Ϊ���ַ���(��Ҫ���������������С)
    int j=0, k=0;
    string posion= search(test, in_test);
    while(posion[j]!= '\0'){
        if(posion[j]== '_'){
            k= j;
        }
        j++;
    }
    if(k== 0){
        return 0;
    }else{
        string num_of_posion= posion.substr(k+1);//��ȡ�����ַ���
        return (stoi(num_of_posion));//����ת��Ϊ���ַ���
    }
}
void posion_of_number(int *p, string test, string in_test){//�ú������ڽ�position�е�λ��ת��Ϊ���ִ洢������p��
    string posion= search(test, in_test);
    string temp_posion= "";
    int j=0,k= 0;
    while(posion[j]!= '\0'){
        if(posion[j]!= '_'){//�ԡ�_��Ϊ���޽����и�
            temp_posion+= posion[j];
        }else{
            p[k]= stoi(temp_posion);//���ַ���ת��Ϊ���ֽ��б���
            k++;
            temp_posion= "";//��ԭ�ַ���Ϊ��
        }
        j++;
    }
}
string get_total_part(string test, string in_test){//Ϊ����ʵ����������Լ������û�ʹ�ã��Ὣ��������in_test�ַ�����ԭtest�ַ����е�ǰ��5���ַ���������������û�֪������������޸�
    int count= count_num_of_same(test, in_test);//
    int *p= new int(count);
    posion_of_number(p, test, in_test);//��λ��¼�뵽p�����У���������ʽ�洢����
    if(count== 0){
        return "";
    }else{
        //cout<<"����"<<endl;
    }
    int j= 0;
    string part1, part2;
    string final_all= "";
    //�����Ƕ�test�ַ����еı�Ե���м�⣬���in_test�ַ���������ͷ�����ܻ���ֿ�ͷ��in_testû��5���ַ��Ŀ��ܣ���ô�����ж���������٣�ĩβҲ�����
    for(j=0; j<count; j++){
        if(p[j]-5> 0){
            part1= test.substr(p[j]-5, 5);
            if(p[j]+5< test.size()){
                part2= test.substr(p[j]+in_test.size(), 5);
            }else{
                part2= test.substr(p[j]+in_test.size());
            }
        }else{
            part1= test.substr(0, p[j]);
            if(p[j]+5< test.size()){
                part2= test.substr(p[j]+in_test.size(), 5);
            }else{
                part2= test.substr(p[j]+in_test.size());
            }
        }    
        //cout<<j+1<<"."<<"\033[31m"<<part1<<" "<<"\033[33m"<<part2<<"\033[0m"<<endl;
        final_all+= (to_string(j+1)+ "."+ part1 +"("+in_test+")"+part2+ "\n");//�����ţ�ʹ�������Ŀ
    }
    cout<<final_all;
    return final_all;
}
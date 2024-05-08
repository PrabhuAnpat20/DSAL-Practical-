//  ps 22

#include<iostream>
#include <iomanip>
using namespace std; 
class Student{
    string name;
    int marks;
    Student(){
        name="";
        marks=0;
    }
    Student(string name,int marks){
        this->name=name;
        this->marks=marks;
    }
    friend class Heap;
};

class Heap{
    Student ** heap;
    int size=0;
public:
    Heap(){
       heap=new Student *[100];
    }
    void Insert(string name,int marks){
        Student * newStudent=new Student(name,marks);
        size++;
        int index=size;
        heap[index]=newStudent;
        while (index>1)
        {
            int parent=index/2;
            if (heap[parent]->marks >newStudent->marks)
            {
                swap(heap[parent],heap[index]);
                index=parent;
                
            }
            else
            {
                return;
            }
            
            
        }
        
    }

    void getMin(){
        cout<<"Minimum marks obtained are:"<<heap[1]->marks<<endl;
        cout<<"student name:"<<heap[1]->name;
    }
    void print(){
        for (int i = 1; i <= size; i++)
        {
            
           cout<<heap[i]->name<<"->"<<heap[i]->marks<<endl;
        }
        
    }
};

int main()
{

Heap h;
h.Insert("prabhu",50);
h.Insert("renu",80);
h.Insert("me",30);
h.Insert("hello",60);
h.print();
h.getMin();
return 0;
}
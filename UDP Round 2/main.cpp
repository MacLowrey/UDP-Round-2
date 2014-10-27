/*
 Jon Lowrey
 Programming II
 Bill McDaniel
 "UDP Packet Recombination"
 
 A program to recombine packets into understandable data, 
 using a singly linked list, with the understanding that 
 all data should be printed ASAP.
 
 Due: 10-27-2014
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct node{
    node *link;
    int num;
    string dat;
    //Constructor to create each node with the link set to NULL
    node() { link = NULL; }
};

void insert(node *x, node *&head)
{
    //Case 1: There is no node in the list
    node *p;
        if (head == NULL)
            {head = x;}
    else
    {   //Case 2: The node given is less than the current head
        if (x->num < head->num)
        {
            x->link = head;
            head = x;
        }
        //Case 3: The Node needs to be placed between two existing nodes in the list
        else
        {
            p = head;
            
            while (p->link && x->num > p->link->num) p = p ->link;
            /*while there is a next node in the list and the given node number is greater than
            the node ahead of the current selection go to the next node*/
            
            if (!p->link) p->link = x;
            /*if you reach the end of the list without finding where it goes
            add the current node onto the end of the list */
            
            else
            {   /* put the given node between two nodes*/
                x->link = p->link;
                p->link = x;
            }
            
        }
    }
}
node * createN (int i, string data)
{
    node *x;
    x =  new node;
    x->dat= data;
    x->num= i;
    return x;
}
int numString(string s)
{
    int x;
    stringstream(s)>>x;
    return x;
}

string newLine(string st)
{
    /*This function uses the ASCII Values of characters in a given string and changes the string based on the condition that a =+ should be changed to a newline.*/
    
    for(int i = 0; i < st.length(); i++)
    {   //if the character detected is an = replace it with a newline
        if(st[i]==61)
        {
            st[i] = 10;
        }
        //if the character detected is a + replace it with a null character
        if(st[i]==43)
        {
            st[i]=0;
        }
    }
    return st;
}


int main(int argc, const char * argv[])
{
    node *head=NULL;
    string holder,dat,number;
    int num, counter = 1;
    
    ifstream myfile;
    
    myfile.open("data.txt");
    //if(myfile.is_open()){ cout<<"File is Open"<<endl;}
    //else cout<<"File is Not Open"<<endl;
    
    for (int i =0; i<107; i++)
        {
            getline(myfile,holder);//get the next line in the file, store in holder
            number = holder.substr(0,4);//get the number of the packet
            dat = holder.substr(4,12);//get the data of the packet
            dat = newLine(dat);//turn all =+ into newlines
            num = numString(number);//turn the packet number string to an int
            node *p = createN(num,dat);//create a node pointer with the data
            insert(p, head);//insert it into the list
            while(p)//print if possible
            {   cout<<"I RAN!!"<<counter<<endl;
                if (p->num == counter)
                {
                    counter++;
                    cout  <<p->dat;
                    p = p->link;
                }
                else break;
            }
        }
}
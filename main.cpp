#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <boost\regex.hpp>
#include "cheker.h" //realization of Stemer Porter
using namespace std;

void input(map<string,int> &words)
{
    ifstream in;
    string s;
    string name;
    cin>>name;
    in.open(name);
    while(in>>s)
    {
        s=check(s);
        if(s.length()<1) continue;
        if (words.count(s)>0)
            words[s]++;
        else
            words.insert(pair<string,int>(s,1));
    }
    in.close();
}

void compare(map<string,int> &file1, map<string,int> &file2, int* amount, int* difference) //compare different of 2 texts
{
    map <string,int>::iterator cur;
	for (cur=file1.begin();cur!=file1.end();cur++)
	{
	    if (file2.count((*cur).first)>0)
        {
            *amount+=max(file1[(*cur).first],file2[(*cur).first]);
            *difference+=min(file1[(*cur).first],file2[(*cur).first]);
            file2.erase((*cur).first);
        }
        else
        {
            *amount+=file1[(*cur).first];
        }
	}
	for (cur=file2.begin();cur!=file2.end();cur++)
    {
        *amount+=(*cur).second;
    }
}

void output(int amount, int difference) //output in console about how many per cent sample of two texts
{
    double percent = (double)difference/amount;
    printf("File compare for %f%%", percent* 100.0);
}

int main()
{
    setlocale(LC_ALL, "rus");
    map<string,int> mapFile1;           //two maps to safe words
    cout<<"Please, enter first file name"<<endl;
    input(mapFile1);
    map<string,int> mapFile2;
    cout<<"Please, enter second file name"<<endl;
    input(mapFile2);
    int amount=0, difference=0;
    compare(mapFile1,mapFile2,&amount,&difference);
    cout<<amount<<" "<<difference;
    output(amount,difference);
    return 0;
}

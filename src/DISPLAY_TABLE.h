//Realized by Aleandro 2000

#ifndef DISPLAY_TABLE_FILE
#define DISPLAY_TABLE_FILE

#include <bits/stdc++.h>
#include "CSV.h"

using namespace std;

class DISPLAY_TABLE
{
    vector<vector<string>> array;
    size_t lines;
public:
    void exec(string);
    vector<vector<string>> getArray();
    void CSVread(string);
    size_t getLines();
    ~DISPLAY_TABLE();
};

vector<vector<string>> DISPLAY_TABLE::getArray()
{
    return this->array;
}

size_t DISPLAY_TABLE::getLines()
{
    return this->lines;
}

void DISPLAY_TABLE::CSVread(string file)
{
    ifstream in(file);
    string line, field;

    vector<string> v;
	this->lines=0;

    this->array.clear();

    while (getline(in, line))
    {
        v.clear();
        stringstream ss(line);
		++this->lines;
        while (getline(ss, field, ','))
            v.push_back(field);
        this->array.push_back(v);
    }
	in.close();
}

void DISPLAY_TABLE::exec(string file)
{
    ifstream in("./tables/"+file+".csv"),header("./structure/"+file+".csv");

    if(in.good()&&header.good())
    {
        CSVread("./structure/"+file+".csv");
        vector<vector<string>> array=this->getArray();
        size_t length=this->getLines();
        for(size_t i=0;i<length;++i)
            cout<<array[i][0]<<' ';
        cout<<'\n';

        string line;

        while(getline(in,line))
        {
            for(size_t i=0;i<line.length();++i)
                if(line[i]==',')
                    cout<<' ';
                else
                    cout<<line[i];
            cout<<'\n';
        }
    }
    else
        perror("ERROR");
    
    header.close();
    in.close();
}

DISPLAY_TABLE::~DISPLAY_TABLE()
{}

#endif
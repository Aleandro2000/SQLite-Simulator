//Realized by Aleandro 2000

#ifndef CREATE_TABLE_FILE
#define CREATE_TABLE_FILE

#include <bits/stdc++.h>
#include "CSV.h"

using namespace std;

class CREATE_TABLE
{
    string name;
public:
    ~CREATE_TABLE();
    void exec(string);
    void infoAdd(vector<string>);
    string getName();
    friend bool checker(string);
};

bool checker(string file)
{
    fstream f(file);
    return f.good();
}

void CREATE_TABLE::exec(string file)
{
    if(!checker(file))
    {
        this->name="./structure/"+file+".csv";
        ofstream f("./tables/"+file+".csv");
        f<<"";
        f.close();
    }
    else
     cout<<"ERROR: File exists!\n";
}

void CREATE_TABLE::infoAdd(vector<string> info)
{
    ofstream f(this->name);
    for(size_t i=0;i<info.size();++i)
        if((i+1)%4)
            f<<info[i]<<',';
        else
            f<<info[i]<<'\n';
    f.close();
}

string CREATE_TABLE::getName()
{
    return this->name;
}

CREATE_TABLE::~CREATE_TABLE()
{}


#endif
//Realized by Aleandro 2000

#ifndef DELETE_FROM_FILE
#define DELETE_FROM_FILE

#include <bits/stdc++.h>
#include "CSV.h"

using namespace std;

class DELETE_FROM
{
    string name;
    vector<vector<string>> array;
    size_t lines;
public:
    size_t findParameter(string);
    void CSVreader(string);
    void exec(size_t,string);
    void setName(string);
    vector<vector<string>> getArray();
    size_t getLines();
    friend bool check(string);
    ~DELETE_FROM();
};

void DELETE_FROM::CSVreader(string file)
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

vector<vector<string>> DELETE_FROM::getArray()
{
    return this->array;
}

size_t DELETE_FROM::getLines()
{
    return this->lines;
}

void DELETE_FROM::setName(string name)
{
    this->name=name;
}

size_t DELETE_FROM::findParameter(string param)
{
    CSVreader("./structure/"+this->name+".csv");
    vector<vector<string>> array=this->getArray();
    size_t length=this->getLines();
    for(size_t i=0;i<length;++i)
        if(array[i][0]==param)
            return i;
    return SIZE_MAX;
}

bool check(string file)
{
    fstream f(file);
    return f.good();
}

void DELETE_FROM::exec(size_t index, string value)
{

    CSVreader("./tables/"+this->name+".csv");
    vector<vector<string>> array=this->getArray();
    size_t length=this->getLines();
    if(index<=length&&check("./tables/"+this->name+".csv"))
    {
        ofstream out("./tables/"+this->name+".csv");
        for(size_t i=0;i<length;++i)
            if(array[i][index]!=value)
            {
                for(size_t j=0;j<array[i].size()-1;++j)
                    out<<array[i][j]<<',';
                out<<*(array[i].end()-1)<<'\n';
            }
        out.close();
    }
    else
        perror("ERROR");
}

DELETE_FROM::~DELETE_FROM()
{}

#endif
//Realized by Aleandro 2000

#ifndef UPDATE_FILE
#define UPDATE_FILE

#include <bits/stdc++.h>
#include "CSV.h"

using namespace std;

class UPDATE
{
    string name;
    vector<vector<string>> array;
    size_t lines;
public:
    size_t findParameter(string);
    void CSVreader(string);
    void exec(size_t,size_t,string,string);
    void setName(string);
    vector<vector<string>> getArray();
    size_t getLines();
    friend bool updateCheck(string);
    ~UPDATE();
};

void UPDATE::CSVreader(string file)
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

vector<vector<string>> UPDATE::getArray()
{
    return this->array;
}

size_t UPDATE::getLines()
{
    return this->lines;
}

void UPDATE::setName(string name)
{
    this->name=name;
}

size_t UPDATE::findParameter(string param)
{
    CSVreader("./structure/"+this->name+".csv");
    vector<vector<string>> array=this->getArray();
    size_t length=this->getLines();
    for(size_t i=0;i<length;++i)
        if(array[0][i]==param)
            return i;
    return SIZE_MAX;
}

bool updateCheck(string file)
{
    fstream f(file);
    return f.good();
}

void UPDATE::exec(size_t index1, size_t index2, string value1, string value2)
{
    if(updateCheck("./tables/"+this->name+".csv"))
    {
        ofstream out("./tables/"+this->name+".csv");
        CSVreader("./tables/"+this->name+".csv");
        vector<vector<string>> array=this->getArray();
        size_t length=this->getLines();
        if(array[0].size()>=index1&&array[0].size()>=index2)
        {
            for(size_t i=0;i<length;++i)
            {
                if(array[i][index2]==value2)
                    array[i][index1]=value1;
                for(size_t j=0;j<array[i].size()-1;++j)
                    out<<array[i][j]<<',';
                out<<*(array[i].end()-1)<<'\n';
            }
        }
        else
            cout<<"Syntax error or failed function!\n";
        out.close();
    }
    else
        perror("ERROR");
}

UPDATE::~UPDATE()
{}

#endif
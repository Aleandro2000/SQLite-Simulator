//Realized by Aleandro 2000

#ifndef SELECT_FILE
#define SELECT_FILE

#include <bits/stdc++.h>
#include "CSV.h"

using namespace std;

class SELECT
{
    string name,savename;
    vector<vector<string>> array;
    size_t lines;
public:
    vector<string> where;
    size_t findParameter(string);
    void CSVreader(string);
    void CSVwriter(string);
    void exec(size_t,bool&);
    void exec(size_t,size_t,string,bool&);
    void exec(string);
    void setName(string);
    void setSaveName(string);
    vector<vector<string>> getArray();
    size_t getLines();
    friend bool SELECTCheck(string);
    ~SELECT();
};

void SELECT::CSVreader(string file)
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

void SELECT::CSVwriter(string file)
{
    ifstream in(file);
    string line;

    if(in.good())
        while(getline(in,line))
            cout<<line<<'\n';
    else
        perror("ERROR!");

    in.close();
}

vector<vector<string>> SELECT::getArray()
{
    return this->array;
}

size_t SELECT::getLines()
{
    return this->lines;
}

void SELECT::setName(string name)
{
    this->name=name;
}

void SELECT::setSaveName(string savename)
{
    this->savename=savename;
}

size_t SELECT::findParameter(string param)
{
    this->CSVreader("./structure/"+this->name+".csv");
    vector<vector<string>> array=this->getArray();
    size_t length=this->getLines();
    for(size_t i=0;i<length;++i)
        if(array[i][0]==param)
            return i;
    return SIZE_MAX;
}

bool SELECTCheck(string file)
{
    fstream f(file);
    return f.good();
}

void SELECT::exec(size_t index, bool &good)
{
    if(SELECTCheck("./tables/"+this->name+".csv"))
    {
        ofstream out("./query/"+this->savename,ios_base::app);
        this->CSVreader("./tables/"+this->name+".csv");
        vector<vector<string>> array=this->getArray();
        size_t length=this->getLines();
        if(array[0].size()>=index)
        {
            for(size_t i=0;i<length-1;++i)
                out<<array[i][index]<<',';
            out<<array[length-1][index]<<'\n';
            good=true;
        }
        else
        {
            cout<<"Syntax error or failed function!\n";
            good=false;
        }
        out.close();
    }
    else
        perror("ERROR");
}

void SELECT::exec(size_t index, size_t whereIndex, string value, bool &good)
{
    if(SELECTCheck("./tables/"+this->name+".csv"))
    {
        ofstream out("./query/"+this->savename,ios_base::app);
        CSVreader("./tables/"+this->name+".csv");
        vector<vector<string>> array=this->getArray();
        size_t length=this->getLines();
        if(array[0].size()>=index&&array[0].size()>=whereIndex)
        {
            for(size_t i=0;i<length-1;++i)
                if(array[i][whereIndex]==value)
                    out<<array[i][index]<<',';
            if(array[length-1][whereIndex]==value)
                out<<array[length][index]<<'\n';
            good=true;
        }
        else
        {
            cout<<"Syntax error or failed function!\n";
            good=false;
        }
        out.close();
    }
    else
        perror("ERROR");
}

void exec(string path)
{

}

SELECT::~SELECT()
{}

#endif
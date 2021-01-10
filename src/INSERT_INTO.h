//Realized by Aleandro 2000

#ifndef INSERT_INTO_FILE
#define INSERT_INTO_FILE

#include <bits/stdc++.h>
#include "CSV.h"

using namespace std;

class INSERT_INTO: public CSV
{
    string name;
public:
    void exec(vector<string>);
    void setName(string);
    ~INSERT_INTO();
};

void INSERT_INTO::exec(vector<string> info)
{
    ofstream out("./tables/"+this->name+".csv",ios_base::app);
    CSVreader("./structure/"+this->name+".csv");
    if(info.size()==this->getLines()&&out.good())
    {
        for(size_t i=0;i<info.size()-1;++i)
            out<<info[i]<<',';
        out<<*(info.end()-1)<<'\n';
    }
    else
        cout<<"Syntax error or failed execution!\n";
}

void INSERT_INTO::setName(string name)
{
    this->name=name;
}

INSERT_INTO::~INSERT_INTO()
{}

#endif
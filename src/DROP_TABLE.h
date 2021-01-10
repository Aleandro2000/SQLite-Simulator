//Realized by Aleandro 2000

#ifndef DROP_TABLE_FILE
#define DROP_TABLE_FILE

#include <bits/stdc++.h>
#include "CSV.h"

using namespace std;

class DROP_TABLE
{
public:
    void exec(string,bool);
    ~DROP_TABLE();
};

void DROP_TABLE::exec(string file,bool message)
{
    string table("./tables/"+file+".csv"),structure("./structure/"+file+".csv");
    if((remove(table.c_str())||remove(structure.c_str()))&&message)
        perror("File deletion failed");
    else if(message)
        cout << "File deleted successfully\n";
}

DROP_TABLE::~DROP_TABLE()
{}

#endif
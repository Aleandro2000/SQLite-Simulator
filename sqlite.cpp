//Realized by Aleandro 2000

#include "./src/CREATE_TABLE.h"
#include "./src/DISPLAY_TABLE.h"
#include "./src/DROP_TABLE.h"
#include "./src/INSERT_INTO.h"
#include "./src/DELETE_FROM.h"
#include "./src/UPDATE.h"
#include "./src/SELECT.h"

void tokenize(string const &str, const char delim, vector<string> &out)
{
    out.clear();
    size_t start;
    size_t end=0;
 
    while((start=str.find_first_not_of(delim, end))!=string::npos)
    {
        end=str.find(delim, start);
        out.push_back(str.substr(start,end-start));
    }
}

int main(int argc, char *argv[])
{

    string buffer,temp;
    vector<string> out;
    bool open=true,good;
    size_t index=1;
    CREATE_TABLE create;
    DROP_TABLE drop;
    DISPLAY_TABLE display;
    INSERT_INTO insert;
    DELETE_FROM del;
    UPDATE update;
    SELECT selection;

    time_t now=time(0);
    tm *gmtm = gmtime(&now);
    cout<<"SQLite version ALEANDRO 2000 "<<asctime(gmtm);
    cout<<"Connected to a \033[0;31mtransient in-memory database\033[0m\n";
        
    while(open)
    {
        cout<<"sqlite> ";
        getline(cin,buffer);
        transform(buffer.begin(), buffer.end(), buffer.begin(),
        [](unsigned char c){
            return tolower(c);
        });
        if(buffer=="quit"||buffer=="quit()")
        {
            for(size_t i=0;i<index;++i)
            {
                temp="./query/SELECT_"+to_string(i+1)+".csv";
                remove(temp.c_str());
            }
            open=false;
        }
        else if(buffer=="clear"||buffer=="clear()")
            system("@cls||clear");
        else
        {
            tokenize(buffer,' ',out);
            if((out.size()==4||out.size()==5)&&out[0]=="create"&&out[1]=="table")
            {
                create.exec(*(out.begin()+2));
                temp=*(out.end()-1);
                for(size_t i=0;i<temp.length();++i)
                    if(temp[i]==')'||temp[i]=='('||temp[i]==',')
                        temp[i]=' ';
                tokenize(temp,' ',out);
                good=true;
                if(out.size()%4==0&&out.size())
                    for(size_t i=1;i<out.size()&&good;i+=4)
                    {
                        if(out[i]!="char"&&out[i]!="varchar"&&out[i]!="binary"&&out[i]!="varbinary"&&out[i]!="tinytext"&&out[i]!="text"&&out[i]!="mediumtext"&&out[i]!="largetext")
                            good=false;
                    }
                else
                    good=false;
                if(good)
                    create.infoAdd(out);
                else
                {
                    drop.exec(create.getName(),false);
                    cout<<"Syntax error or failed execution!\n";
                }
            }
            else if(out.size()==3&&out[0]=="drop"&&out[1]=="table")
                drop.exec(out[2],true);
            else if(out.size()==3&&out[0]=="display"&&out[1]=="table")
                display.exec(out[2]);
            else if(out.size()==5&&out[0]=="insert"&&out[1]=="into"&&out[3]=="values")
            {
                insert.setName(out[2]);
                temp=*(out.end()-1);
                for(size_t i=0;i<temp.length();++i)
                    if(temp[i]==')'||temp[i]=='('||temp[i]==',')
                        temp[i]=' ';
                tokenize(temp,' ',out);
                insert.exec(out);
            }
            else if(out.size()==5&&out[0]=="delete"&&out[1]=="from"&&out[3]=="where")
            {
                del.setName(out[2]);
                temp=*(out.end()-1);
                for(size_t i=0;i<temp.length();++i)
                    if(temp[i]=='=')
                        temp[i]=' ';
                tokenize(temp,' ',out);
                if(out.size()==2)
                    del.exec(del.findParameter(*(out.begin())),*(out.end()-1));
                else
                    cout<<"Syntax error or failed execution!\n";
            }
            else if(out.size()==6&&out[0]=="update"&&out[2]=="set"&&out[4]=="where")
            {
                update.setName(out[2]);
                temp=*(out.end()-1);
                for(size_t i=0;i<temp.length();++i)
                    if(temp[i]=='=')
                        temp[i]=' ';
                tokenize(temp,' ',out);
                if(out.size()==4)
                    update.exec(update.findParameter(out[0]),update.findParameter(out[1]),out[2],out[3]);
                else
                    cout<<"Syntax error or failed execution!\n";
            }
            else if(out.size()==3&&out[0]=="select")
            {
                selection.setName(*(out.end()-1));
                selection.setSaveName("SELECT_"+to_string(index)+".csv");
                temp=out[1];
                for(size_t i=0;i<temp.length();++i)
                    if(temp[i]==','||temp[i]=='('||temp[i]==')')
                        temp[i]=' ';
                tokenize(temp,' ',out);
                for(size_t i=0;i<out.size();++i)
                    selection.exec(selection.findParameter(out[i]),good);
                if(good)
                    ++index;
                selection.CSVwriter("./query/SELECT_"+to_string(index)+".csv");
            }
            else if(out.size()==5&&out[0]=="select"&&out[3]=="where")
            {
                selection.setName(out[2]);
                selection.setSaveName("SELECT_"+to_string(index)+".csv");
                tokenize(*(out.end()-1),'=',selection.where);
                temp=out[1];
                for(size_t i=0;i<temp.length();++i)
                    if(temp[i]==','||temp[i]=='('||temp[i]==')')
                        temp[i]=' ';
                tokenize(temp,' ',out);
                for(size_t i=0;i<out.size();++i)
                    selection.exec(selection.findParameter(out[i]),selection.findParameter(*(selection.where.begin())),*(selection.where.end()-1),good);
                if(good)
                    ++index;
                selection.CSVwriter("./query/SELECT_"+to_string(index)+".csv");
            }
            else if(out.size()==4&&out[0]=="select"&&out[1]=="all"&&out[2]=="form")
            {
                temp=out[3];
                ofstream out("./query/SELECT_"+to_string(index)+".csv");
                ifstream in("./tables/"+temp+".csv");
                if(in.good())
                    while(getline(in,temp))
                        out<<temp<<'\n';
                else
                    cout<<"Syntax error or failed execution!\n";
                in.close();
                out.close();
                selection.CSVwriter("./query/SELECT_"+to_string(index)+".csv");
            }
            else if(out.size())
                cout<<"Syntax error or failed execution!\n";
        }
    }
    return 0;
}
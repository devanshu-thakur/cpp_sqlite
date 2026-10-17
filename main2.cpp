#include<iostream>
#include<sqlite3.h>
using namespace std;
int main(){
    sqlite3* db;
    if(sqlite3_open("student.db",&db)!=SQLITE_OK){
        cout<<"Error: "<<sqlite3_errmsg(db)<<endl;
        //sqlite3_free(db);
        sqlite3_close(db);
        return 1;
    }
    cout<<"Data Opened successfully!";
    char* error=nullptr;
    const char* createTable=
        "create table teacher("
        "id int primary key, "
        "name text not null)";
    if(sqlite3_exec(db,createTable,nullptr,nullptr,&error)!=SQLITE_OK){
        cout<<"Error: "<<sqlite3_errmsg(db)<<endl;   //changing error with sqlite3_errmsg(db)
        sqlite3_close(db);
        return 1;
    }

    const char* insertData =
        "INSERT INTO teacher(id, name) VALUES "
        "(101, 'Devanshu'), "
        "(102, 'Himashu')";
    if(sqlite3_exec(db,insertData,nullptr,nullptr,&error)){
        cout<<"Error: "<<sqlite3_errmsg(db)<<endl;
        sqlite3_close(db);
        return 1;
    }
    const char* selectData="select id, name from teacher";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db,selectData,-1,&stmt,nullptr)!=SQLITE_OK){
        cout<<"Error: "<<sqlite3_errmsg(db)<<endl;
        sqlite3_close(db);
        return 1;
    }
    cout << "\nID\tName\n";
    cout << "----------------\n";
    while(sqlite3_step(stmt)==SQLITE_ROW){
        int id=sqlite3_column_int(stmt,0);
        const unsigned char* name=sqlite3_column_text(stmt,1);
        cout<<id<<"\t"<<name<<endl;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

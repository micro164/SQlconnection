#include<iostream>
#include<string>
#include "sqlite3.h"
#include "Database.h"

using std::cout;
using std::string;

int main(){
    string database;
    sqlite3 *db; //Database object
    
    cout << "What database do you want to open?\n";
    std::cin >> database;
    const char * datab = database.c_str();
    
    int rc = sqlite3_open(datab, &db); //opens database
    rc = error(rc, db);
    
    string sql = "";
    getline(std::cin, sql);
    
    while(sql != "exit"){
        cout << "SqlCommand>> ";
        getline(std::cin, sql);
        rc = executeD(sql, db, rc);
    }
    
    sqlite3_close(db);
    
    return 0;
}
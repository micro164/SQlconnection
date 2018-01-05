#include<iostream>
#include<string>
#include "sqlite3.h"
#include "Database.h"

int main(){
    sqlite3 *db; //Database object
    int rc = sqlite3_open("demo.db", &db); //opens database
    rc = error(rc, db); //checks for error in opening database
    
    string sql = "SELECT ename, sal, comm FROM emp WHERE ename = 'KING';"
                 "UPDATE emp SET sal = 6000 WHERE ename = 'KING';"
                 "SELECT ename, sal, comm FROM emp WHERE ename = 'KING';";
                 
    rc = executeD(sql, db, rc); //executes sql statement
    sqlite3_close(db); //Closing sqlite3 object (destructor)

    return 0;
}
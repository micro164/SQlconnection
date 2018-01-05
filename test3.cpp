#include<iostream>
#include<string>
#include "sqlite3.h"

using namespace std;

//Function for displaying SQL statement
static int callback(void *data, int argc, char **argv, char **azColName){
  
  string info;
  
   for(int i = 0; i < argc; i++){
        info = (argv[i] ? argv[i] : "NULL");
        cout << azColName[i] << ": " << info << '\t';
   }
   cout << '\n';
   
   return 0;
}

int error(int rc, sqlite3 *db){
    //checking if database will open
    if(rc != SQLITE_OK){
        cout << "Cannot open database: " << sqlite3_errmsg(db) << '\n';
        sqlite3_close(db);
        return 1;
    }
    return rc;

}

int executeD(string sql, sqlite3 *db, int rc){
    const char * csql = sql.c_str();
    char *err_msg = 0;
    
    rc = sqlite3_exec(db, csql, callback, 0, &err_msg);
    
    //checks for SQL error
    if(rc != SQLITE_OK){
        cout << "SQL error: " << err_msg << '\n';
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    return rc;
}

int main(){
    
    sqlite3 *db; //Database object
    char *err_msg = 0;
    
    int rc = sqlite3_open("demo.db", &db);
    rc = error(rc, db);
    
    string sql = "SELECT ename, sal, comm FROM emp WHERE ename = 'KING';"
                 "UPDATE emp SET sal = 6000 WHERE ename = 'KING';"
                 "SELECT ename, sal, comm FROM emp WHERE ename = 'KING';";
    
    rc = executeD(sql, db, rc);
    
    sqlite3_close(db); //Closing sqlite3 object (destructor)
    
    return 0;
 }
 
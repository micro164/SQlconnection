#include<iostream>
#include<string>
#include "sqlite3.h"

using std::cout;
using std::string;

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

//checking if database will open
int error(int rc, sqlite3 *db){
    if(rc != SQLITE_OK){
        cout << "Cannot open database: " << sqlite3_errmsg(db) << '\n';
        sqlite3_close(db);
        return 1;
    }
    return rc;

}

//Exectues sql statement
int executeD(string sql, sqlite3 *db, int rc){
    const char * csql = sql.c_str();
    char *err_msg = 0;
    
    if(sql != "exit"){
    rc = sqlite3_exec(db, csql, callback, 0, &err_msg);
    
    //checks for SQL error
    if(rc != SQLITE_OK){
        cout << "SQL error: " << err_msg << '\n';
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }else{
        return rc;
    }
    }
}
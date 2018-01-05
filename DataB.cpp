#include<iostream>
#include<string>
#include "sqlite3.h"

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName){
   cout << (const char*)data;
   for(int i=0; i<argc; i++){
      printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   cout << '\n';
   return 0;
}

int main(){
    cout << "Beggining of the program\n";
    cout << "The sum is: " << 2+3 << '\n';
    cout << "The produce is: " << 2*9 << '\n';
    sqlite3 *db;
    char *err_msg = 0;
    const char* data = "callback function called\n";
    
    int rc = sqlite3_open("demo.db", &db);
    
    if(rc != SQLITE_OK){
        cout << "Cannot open database: " << sqlite3_errmsg(db) << '\n';
        sqlite3_close(db);
        return 1;
    }
    
    string sql = "SELECT ename, comm FROM emp;";
    
    const char * csql = sql.c_str();
    
    rc = sqlite3_exec(db, csql, callback, (void*)data, &err_msg);
    
    if(rc != SQLITE_OK){
        cout << "SQL error: " << err_msg << '\n';
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_close(db);
    
    return 0;
 }
/*
Summary:

The library I am using for accessing the database is sqlite3.h. This library
can be found on sqlite.org, it has an interface for accessing the database.
It has eight methods and two objects that make up the interface.

Objects: 1. The first object is sqlite3 which is a database connection object.
         2. The second object is sqlite3_stmt which is the prepared statement 
            object. 
    
Methods: 1. The first method is sqlite3_open() which opens a connection to 
            the database.
         2. The second method is sqlite3_prepare() which compiles any SQL text
            into byte-code. This byte code will do the querying and updating
            of the database.
         3. The third method is sqlite3_bind() which stores application data
            into parameters of the original SQL.
         4. The forth method is sqlite3_step() which advances an sqlite3 stmt
            object to the next result row or to completion.
         5. The fifth method is sqlite3_column() which returns information
            on the current result row about a single column.
         6. The sixth method is sqlite3_finalize() which is the destructor for
            the sqlite3_stmt object.
         7. The seventh method is sqlite3_close() which is the destructor for
            the sqlite3 object.
         8. The eighth method is sqlite3_exec() which is a wrapper function that
            does the job of the sqlite3_prepare(), sqlite3_step(), sqlite3_column(),
            and sqlite3_finalize() methods for a string of one or more SQL statements.
*/

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

int main(){
    
    sqlite3 *db; //Database object
    char *err_msg = 0;
    
    int rc = sqlite3_open("demo.db", &db); //Opening Database
    
    //checking if database will open
    if(rc != SQLITE_OK){
        cout << "Cannot open database: " << sqlite3_errmsg(db) << '\n';
        sqlite3_close(db);
        return 1;
    }
    
    string sql = "SELECT ename, sal, comm FROM emp WHERE ename = 'KING';"
                 "UPDATE emp SET sal = 6000 WHERE ename = 'KING';"
                 "SELECT ename, sal, comm FROM emp WHERE ename = 'KING';";
    
    const char * csql = sql.c_str();
    
    rc = sqlite3_exec(db, csql, callback, 0, &err_msg);
    
    //checks for SQL error
    if(rc != SQLITE_OK){
        cout << "SQL error: " << err_msg << '\n';
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_close(db); //Closing sqlite3 object (destructor)
    
    return 0;
 }
 
 /*
OUTPUT:
ENAME: KING     SAL: 5500       COMM: NULL
ENAME: KING     SAL: 6000       COMM: NULL
*/
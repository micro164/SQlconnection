#include<iostream>
#include<string>
#include<cstdio>
#include<cctype>
#include "sqlite3.h"
#include "Database.h"

using std::cout;
using std::string;

int input();
string Sinput();
string InputCheck();

int main(){
    sqlite3 *db;
    int rc = sqlite3_open("demo.db", &db); //opens database
    rc = error(rc, db);
    
    string choice = "";
    int Scase = 0;
    string name = "";
    string name2 = "";
    string sql = "";
    string empn = "";
    string job = "";
    string mgr = "";
    string sal = "";
    string deptno = "";
    
    while(choice != "exit"){
        
        cout << "1.Update Name\n"
             << "2.Insert Employee\n"
             << "3.Select an Employee\n"
             << "4.Delete an Employee\n"
             << "5.Exit\n";
        
        Scase = input();
        
        switch(Scase){
            case 1:
                cout << "What name do you want to update: ";
                name = InputCheck();
                cout << "What name do you want to change it to: ";
                name2 = InputCheck();
                sql = "UPDATE emp SET ename = upper('" + name2 + "') WHERE ename = upper('" + name + "');";
                rc = executeD(sql, db, rc);
                sql = "SELECT ename FROM emp;";
                rc = executeD(sql, db, rc);
                break;
            case 2:
                cout << "What is the name of employee: ";
                name = InputCheck();
                cout << "What is thier employee number: ";
                empn = Sinput();
                cout << "What is their job: ";
                job = InputCheck();
                cout << "What is their manager number: ";
                mgr = Sinput();
                cout << "What is their salary: ";
                sal = Sinput();
                cout << "What is their department number: ";
                deptno = Sinput();
                sql = "INSERT INTO emp (empno, ename, job, mgr, sal, deptno) values (" + empn + ", upper('" + name + "'), upper('" + job + "'), " + mgr + ", " + sal + ", " + deptno + ");";
                rc = executeD(sql, db, rc);
                sql = "SELECT empno, ename, job, mgr, sal, deptno FROM emp WHERE ename = upper('" + name + "');";
                rc = executeD(sql, db, rc);
                break;
            case 3:
                cout << "What employee do you want to look up: ";
                name = InputCheck();
                sql = "SELECT empno, ename, job, mgr, sal, deptno FROM emp WHERE ename = upper('" + name + "');";
                rc = executeD(sql, db, rc);
                break;
            case 4:
                cout << "What employee do you want to delete: ";
                name = InputCheck();
                sql = "DELETE FROM emp WHERE ename = upper('" + name + "');";
                rc = executeD(sql, db, rc);
                break;
            case 5:
                choice = "exit";
                break;
            default:
                cout << "That is not a correct choice.\n";
                break;
        }
    }
    
    sqlite3_close(db);
    return 0;
}

int input(){
    
    int temp;
    std::cin >> temp;
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(256, '\n');
        return 0;
    }
    
    int c = std::cin.peek();
    if(c != EOF){
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }
    
    return temp;
}

string Sinput(){
    
    int temp;
    string temp2 = "";
    std::cin >> temp;
    while(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(256, '\n');
        cout << "Not a number. Enter a number:" << '\n';
        std::cin >> temp;
    }
    temp2 = std::to_string(temp);
    
    int c = std::cin.peek();
    if(c != EOF){
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }
    
    return temp2;
}

string InputCheck(){
    string temp;
    bool loop = true;
    
    while(loop){
    std::cin >> temp;
    string::const_iterator it = temp.begin();
    while(it != temp.end()){
        if(isdigit(*it) || !isalpha(*it)){
            cout << "Not a valid Input\n";
            break;
        }
        
        if( (it +1) == temp.end()){
            loop = false;
        }
        
        it++;
    }
    }
    
    int c = std::cin.peek();
    if(c != EOF){
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }
    
    return temp;
}
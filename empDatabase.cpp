#include<iostream>
#include<string>
#include "sqlite3.h"
#include "Database.h"

using std::cout;
using std::string;

int input();

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
             << "4.Exit\n";
        
        Scase = input();
        
        switch(Scase){
            case 1:
                cout << "What name do you want to update: ";
                std::cin >> name;
                cout << "What name do you want to change it to: ";
                std::cin >> name2;
                sql = "UPDATE emp SET ename = '" + name2 + "' WHERE ename = '" + name + "';";
                rc = executeD(sql, db, rc);
                sql = "SELECT ename FROM emp;";
                rc = executeD(sql, db, rc);
                break;
            case 2:
                cout << "What is the name of employee: ";
                std::cin >> name;
                cout << "What is thier employee number: ";
                std::cin >> empn;
                cout << "What is their job: ";
                std::cin >> job;
                cout << "What is their manager number: ";
                std::cin >> mgr;
                cout << "What is their salary: ";
                std::cin >> sal;
                cout << "What is their department number: ";
                std::cin >> deptno;
                sql = "INSERT INTO emp (empno, ename, job, mgr, sal, deptno) values (" + empn + ", '" + name + "', '" + job + "', " + mgr + ", " + sal + ", " + deptno + ");";
                rc = executeD(sql, db, rc);
                sql = "SELECT empno, ename, job, mgr, sal, deptno FROM emp WHERE ename = '" + name + "';";
                rc = executeD(sql, db, rc);
                break;
            case 3:
                cout << "What employee do you want to look up: ";
                std::cin >> name;
                sql = "SELECT empno, ename, job, mgr, sal, deptno FROM emp WHERE ename = '" + name + "';";
                rc = executeD(sql, db, rc);
                break;
            case 4:
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
    return temp;
}
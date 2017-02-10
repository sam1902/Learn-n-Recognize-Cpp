//
//  Database.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 22/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

// Forward declaration
#include "Database.hpp"

// Constructor
Database::Database(){
    
}

Database::~Database(){
    this->close();
}

bool Database::create(string path){
    string prefix = "lrn_db_";
    
    if(path.size() > 0){
        // If our path doesn't end with / we need to add one:
        if(path[path.size()-1] != '/')
            prefix = "/" + prefix;
    }
    return this->init(path + prefix + timestamp("%d-%m-%Y_%H-%M-%S_%Z") +".sqlite") ? true : false;
}

bool Database::open(string path){
    if(sqlite3_open_v2(path.c_str(), &this->db, SQLITE_OPEN_READWRITE, NULL) == SQLITE_OK){
        SuccessAccessDBMessage();
        return true;
    }else{
        ErrorAccessDBMessage(sqlite3_errmsg(db));
        return false;
    }
}

bool Database::init(string path){
    string req = "CREATE TABLE `subjects` (`id`  INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `name`	varchar(255) UNIQUE);";
    sqlite3_stmt* stmt;
    if (sqlite3_open_v2(path.c_str(), &this->db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL) == SQLITE_OK){
        sqlite3_prepare(this->db, req.c_str(), -1, &stmt, NULL);
        
        if(sqlite3_step(stmt) != SQLITE_DONE){
            ErrorCreateDBMessage(sqlite3_errmsg(this->db));
            sqlite3_finalize(stmt);
            return false;
        }
    }
    else{
        // No need to sqlite3_finilize here since stmt isn't initialized already
        ErrorCreateDBMessage(sqlite3_errmsg(this->db));
        return false;
    }
    sqlite3_finalize(stmt);
    SuccessCreateDBMessage(path);
    return true;
}

//    int emptyCallback(void *NotUsed, int argc, char **argv, char **azColName){
//        return 0;
//    }

int Database::insertSubject(string subjectName){
    string sql = "INSERT INTO subjects (NAME) VALUES (\"" + subjectName + "\");";
    char *zErrMsg = 0;
    /* Execute SQL statement */
    int rc = sqlite3_exec(this->db, sql.c_str(), NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        ErrorInsertSubjectDBMessage(sqlite3_errmsg(this->db));
        sqlite3_free(zErrMsg);
        return NULL;
    }else{
        return getSubjectID(subjectName);
    }
}

vector<vector<string>> Database::query(string query){
    sqlite3_stmt *statement;
    vector<vector<string>> results;
    
    if(sqlite3_prepare_v2(this->db, query.c_str(), -1, &statement, 0) == SQLITE_OK)
    {
        int cols = sqlite3_column_count(statement);
        int result = 0;
        while(true)
        {
            result = sqlite3_step(statement);
            
            if(result == SQLITE_ROW)
            {
                vector<string> values;
                for(int col = 0; col < cols; col++)
                {
                    string val;
                    char * ptr = (char*)sqlite3_column_text(statement, col);
                    ptr ? val = ptr : val = "";
                    values.push_back(val);
                }
                results.push_back(values);
            }
            else
            {
                break;  
            }

        }
        
        sqlite3_finalize(statement);
    }
    
    // If there is an error, SQLITE_ERROR will be the first value of the first column of the first row
    string error = sqlite3_errmsg(this->db);
    if(error != "not an error"){
        ErrorExecuteQueryDBMessage(query, error);
        vector<string> values;
        values.push_back("-1");
        results.push_back(values);
    }
    
    return results;  
}

int Database::getNumberOfSubjects(){
    
    return (int)this->query("SELECT * FROM subjects;").size();
}

string Database::getSubjectName(int subjectID){
    vector<vector<string>> result;
    if(getNumberOfSubjects() > 0)
        result = this->query("SELECT name FROM subjects WHERE id=" + to_string(subjectID) + ";");
    else
        return "-1";
    return result.size() > 0 ? (result[0])[0] : "-1";
}

int Database::getSubjectID(string subjectName){
    vector<vector<string>> result;
    if(getNumberOfSubjects() > 0)
        result = this->query("SELECT id FROM subjects WHERE name=\"" + subjectName + "\";");
    else
        return -1;
    
    return result.size() > 0 ? stoi((result[0])[0]) : -1;
}

bool Database::isSubjectIDValid(int id){
    if(getNumberOfSubjects() > 0)
        return this->getSubjectName(id) != "-1" ? true : false;
    else
        return true;
}

bool Database::isSubjectNameValid(string name){
    if(getNumberOfSubjects() > 0)
        return this->getSubjectID(name) != -1 ? true : false;
    else
        return false;
}

void Database::close(){
    sqlite3_close(this->db);
}

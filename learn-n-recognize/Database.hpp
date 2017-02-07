//
//  Database.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 22/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sqlite3.h> 
#include "Message.hpp"
#include "Miscellaneous.hpp"

using std::vector;
using std::to_string;
using std::string;

class Database {
private:
    sqlite3* db;
public:
    Database(string pathToDB);
    Database();
    ~Database();
    // Open already existing database
    bool open(string path);
    // Create a new database with table subject
    bool create(string path, sqlite3* db);
    // Return subject's ID
    int insertSubject(string subjectName);
    // Return subject's name from ID
    string getSubjectName(int subjectID);
    // Return subject's ID from name
    int getSubjectID(string subjectName);
    // Execute query and return the result
    // First column of first row contains to_string(SQLITE_ERROR) if error happnd
    vector<vector<string>> query(string query);
    
    bool isSubjectIDValid(int id);
    bool isSubjectNameValid(string name);
    void close();
};

#endif /* Database_hpp */

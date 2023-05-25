#include "sqlite3/SQLlite3.hpp"

// g++ main.cpp sqlite3/sqlite3.o sqlite3/SQLite3.cpp -o main && ./main

int main(int argc, char** argv){
    SQLite3 db("database.sql");

    db.execute("CREATE TABLE test("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL )");

    // db.execute_query("INSERT INTO test(name) VALUES('Bogdan');");
    // db.execute_query("INSERT INTO test(name) VALUES('Marcin');");
    // db.execute_query("INSERT INTO test(name) VALUES('Szymon');");
    // db.execute_query("INSERT INTO test(name) VALUES('Michał');");

    // std::vector<std::string> result = db.select_query("SELECT * FROM test;");

    // for(std::string s : result)
        // printf("%s\n", s.c_str());
    
}
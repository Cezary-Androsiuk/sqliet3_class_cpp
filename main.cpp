

#include "sqlite3/SQLlite3.hpp"

int main(int argc, char** argv){
    SQLite3 db("database.sql");

    // db.execute_query("CREATE TABLE test("
    //     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //     "name TEXT NOT NULL )");

    // db.execute_query("INSERT INTO test(name) VALUES('Bogdan');");
    // db.execute_query("INSERT INTO test(name) VALUES('Marcin');");
    // db.execute_query("INSERT INTO test(name) VALUES('Szymon');");
    // db.execute_query("INSERT INTO test(name) VALUES('Michał');");

    // std::vector<std::string> result = db.select_query("SELECT * FROM test;");

    // for(std::string s : result)
        // printf("%s\n", s.c_str());
    
}
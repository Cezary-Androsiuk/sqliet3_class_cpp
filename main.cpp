#include "sqlite3/SQLlite3.hpp"

// g++ main.cpp sqlite3/sqlite3.o sqlite3/SQLite3.cpp -o main && ./main

int main(int argc, char** argv){

    {
        SQLite3 db("database.sql");

        db.execute("CREATE TABLE test("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT NOT NULL )");
    }

    // db.execute_query("INSERT INTO test(name) VALUES('Bogdan');");
    // db.execute_query("INSERT INTO test(name) VALUES('Marcin');");
    // db.execute_query("INSERT INTO test(name) VALUES('Szymon');");
    // db.execute_query("INSERT INTO test(name) VALUES('Michał');");

    // std::vector<std::string> result = db.select_query("SELECT * FROM test;");

    // for(std::string s : result)
        // printf("%s\n", s.c_str());
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;
    rc = sqlite3_open("database.sql", &db);
    if(rc != SQLITE_OK){
        fprintf(stderr, "cannot connect to database!\n");
        return 1;
    }

    rc = sqlite3_prepare_v2(db, "INSERT INTO test (name) VALUES (?1);", -1, &stmt, nullptr);
    if(rc != SQLITE_OK) return 2;

    for(int i=0; i<10000; i++){
        std::string text("imie_" + std::to_string(i+1));
        
        rc = sqlite3_bind_text(stmt, 1, text.c_str(), -1, nullptr);
        if(rc != SQLITE_OK) return 3;
        
        if(sqlite3_step(stmt) != SQLITE_DONE){
            sqlite3_finalize(stmt);
            return 4;
        }
        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);
    }

    sqlite3_close(db);
}
#include "sqlite3/SQLlite3.hpp"

// g++ main.cpp sqlite3/sqlite3.o sqlite3/SQLite3.cpp -o main && ./main

int main(int argc, char** argv){

    {
        SQLite3 db("database.sql");

        db.execute("CREATE TABLE test3("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT NOT NULL, second_name TEXT NOT NULL )");
    }

    // db.execute_query("INSERT INTO test(name) VALUES('Bogdan');");
    // db.execute_query("INSERT INTO test(name) VALUES('Marcin');");
    // db.execute_query("INSERT INTO test(name) VALUES('Szymon');");
    // db.execute_query("INSERT INTO test(name) VALUES('Michał');");

    // std::vector<std::string> result = db.select_query("SELECT * FROM test;");

    // for(std::string s : result)
        // printf("%s\n", s.c_str());

    // sqlite3* db;
    // sqlite3_stmt* stmt;
    // int rc;
    // rc = sqlite3_open("database.sql", &db);
    // if(rc != SQLITE_OK){
    //     fprintf(stderr, "cannot connect to database!\n");
    //     return 1;
    // }

    // rc = sqlite3_prepare_v2(db, "INSERT INTO test2 (name, second_name) VALUES (?1, ?2);", -1, &stmt, nullptr);
    // if(rc != SQLITE_OK) return 2;
    
    // std::string text1("imie_" + std::to_string(0+1));
    // std::string text2("drugie_imie_" + std::to_string(0+1));
    
    // rc = sqlite3_bind_text(stmt, 1, text1.c_str(), -1, nullptr);
    // if(rc != SQLITE_OK) return 3;
    // rc = sqlite3_bind_text(stmt, 2, text2.c_str(), -1, nullptr);
    // if(rc != SQLITE_OK) return 4;

    // for(int i=0; i<2; i++){
        
    //     if(sqlite3_step(stmt) != SQLITE_DONE){
    //         sqlite3_finalize(stmt);
    //         return 6;
    //     }
    //     sqlite3_reset(stmt);
    //     // sqlite3_clear_bindings(stmt);
    // }

    // sqlite3_close(db);

    {
        SQLite3 db("database.sql");

        // std::vector<std::string> vs = db.execute("SELECT * FROM test3");
        // std::vector<std::string> vs = db.select_prepared_query("INSERT INTO test2 (name, second_name) VALUES ('test', 'test2');");
        // for(const std::string& s : vs)
        //     printf("%s\n", s.c_str());
        // vs = db.select_prepared_query("SELECT * FROM test2");
        // for(const std::string& s : vs)
        //     printf("%s\n", s.c_str());
    }
}
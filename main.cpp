#include "sqlite3/SQLlite3.hpp"

// g++ main.cpp sqlite3/sqlite3.o sqlite3/SQLite3.cpp -o main && ./main

void printPersonsTable(SQLite3& database){
    database.prepare_query("SELECT * FROM persons;");
    for(std::string s : database.execute_prepared_query())
        printf("%s\n", s.c_str());

    printf("\n");
}

int main(int argc, char** argv){
    system("rm database.sql");
    
    SQLite3 database("database.sql");

    database.prepare_query(
        "CREATE TABLE IF NOT EXISTS persons(                        "
            "id         INTEGER         PRIMARY KEY AUTOINCREMENT,  "
            "name       TEXT            NOT NULL,                   "
            "surname    TEXT            NOT NULL,                   "
            "pesel      VARCHAR(11)     NOT NULL,                   "
            "birth_date DATE            NOT NULL,                   "
            "phone      VARCHAR(11)     ,                           "
            "add_date   DATE            NOT NULL DEFAULT TIMESTAMP  "
        ");"
    );
    database.execute_prepared_query();
    
    printPersonsTable(database);

    database.prepare_query(
        "INSERT INTO persons (name, surname, pesel, birth_date, phone, add_date) "
        "VALUES ('Cezary', 'Androsiuk', '123456789AB', '01-01-2002', '48123456789', '27-05-2023');"
    );
    database.execute_prepared_query();
    database.execute_prepared_query();
    
    printPersonsTable(database);

    database.prepare_query(
        "INSERT INTO persons (name, surname, pesel, birth_date) "
        "VALUES (?1, ?2, ?3, '01-01-2002');"
    );
    database.bind_text(1, "Czaruś");
    database.bind_text(2, "ABCDEFXYZ");
    database.bind_text(3, "123456789AB");
    database.execute_prepared_query();
    database.bind_text(1, "Stanisław");
    database.execute_prepared_query();
    database.execute_prepared_query();
    
    printPersonsTable(database);

    database.prepare_query("ALTER TABLE persons ADD height INTEGER ;");
    database.execute_prepared_query();

    printPersonsTable(database);

    database.prepare_query("ALTER TABLE persons ADD additional_info TEXT NOT NULL DEFAULT 'NO INFO';");
    database.execute_prepared_query();
    
    printPersonsTable(database);

    database.prepare_query(
        "UPDATE persons SET additional_info = 'additional text about a single record or person' "\
        "WHERE id = 2 OR name LIKE 'Czaruś'"
    );
    database.execute_prepared_query();
    
    printPersonsTable(database);
}
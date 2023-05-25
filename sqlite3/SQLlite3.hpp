#ifndef SQLITE3_HPP
#define SQLITE3_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <typeinfo>

#include "sqlite3.h"

class SQLite3{
    sqlite3* db;
    bool db_open;

    bool prep_started;
    std::string prep_query;
    sqlite3_stmt* prep_stmt;

public:
    SQLite3(const std::string& path);
    ~SQLite3();

protected:
    std::string read_row(sqlite3_stmt* stmt) const;

    void exec_q(const std::string& query);
    std::vector<std::string> selec_q(const std::string& query);

public:

    std::vector<std::string> execute_query(const std::string& query);

    void prepare_query(const std::string& query);

    void bind_int_param(int pos, int param);
    void bind_double_param(int pos, double param);
    void bind_text_param(int pos, const std::string& param);

    std::vector<std::string> execute_prepared(const std::string& query);
    // std::vector<std::string> select_prepared(const std::string& query);
};

#endif
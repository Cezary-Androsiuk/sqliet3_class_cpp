#ifndef SQLITE3_HPP
#define SQLITE3_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <typeinfo>

#include "sqlite3.h"

#define _EXECUTE_ERROR_ fprintf(stderr, "%s error\n", __func__);
#define _EXECUTE_ERROR_MSG_(msg) fprintf(stderr, "%s error: %s\n", __func__, msg);
#define _SKIPPED_OPEN_ fprintf(stderr, "%s skipped - open database first\n", __func__);
#define _SKIPPED_PREP_ fprintf(stderr, "%s skipped - prepare query first\n", __func__);

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

    void execute_query(const std::string& query);
    std::vector<std::string> select_query(const std::string& query);
public:
    std::vector<std::string> execute(const std::string& query);

    void prepare_query(const std::string& query);

    void bind_int_param(int pos, int param);
    void bind_double_param(int pos, double param);
    void bind_text_param(int pos, const std::string& param);
protected:
    void execute_prepared_query(const std::string& query);
    std::vector<std::string> select_prepared_query(const std::string& query);
public:
    std::vector<std::string> execute_prepared(const std::string& query);
};

#endif
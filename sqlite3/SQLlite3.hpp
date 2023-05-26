#ifndef SQLITE3_HPP
#define SQLITE3_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <typeinfo>

#include "sqlite3.h"

#define PRINT_MESSAGES

#ifdef PRINT_MESSAGES
#define _PF_ERROR_ fprintf(stderr, "%s() error\n", __func__);
#define _PF_STMT_CLOSE_ fprintf(stderr, "cannot close prep_stmt in %s!\n", __func__);
#define _PF_STMT_RESET_ fprintf(stderr, "cannot close prep_stmt in %s!\n", __func__);
#define _PF_SKIPPED_OPEN_ fprintf(stderr, "%s() skipped - open database first\n", __func__);
#define _PF_SKIPPED_PREP_ fprintf(stderr, "%s() skipped - prepare query first\n", __func__);
#else
#define _PF_ERROR_ ;
#define _PF_STMT_CLOSE_ ;
#define _PF_STMT_RESET_ ;
#define _PF_SKIPPED_OPEN_ ;
#define _PF_SKIPPED_PREP_ ;
#endif // PRINT_MESSAGES

class SQLite3{
    sqlite3* db;
    bool db_open;

    sqlite3_stmt* prep_stmt;
    bool prep_started;

public:
    SQLite3(const std::string& path);
    ~SQLite3();

protected:
    std::string read_row(sqlite3_stmt* stmt) const;
public:
    std::vector<std::string> execute(const std::string& query);

    void prepare_query(const std::string& query);

    void bind_int_param(int pos, int param);
    void bind_double_param(int pos, double param);
    void bind_text_param(int pos, const std::string& param);
    void bind_clear();

    std::vector<std::string> execute_prepared(bool keep_open = true);

    void close_prepared();
};

#endif
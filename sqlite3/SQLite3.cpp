#include "SQLlite3.hpp"

SQLite3::SQLite3(const std::string& path){
    this->prep_stmt = nullptr;
    int rc = sqlite3_open(path.c_str(), &this->db);
    if(rc != SQLITE_OK){
        fprintf(stderr, "cannot open database!\n");
        this->db_open = false;
        return;
    }
    this->db_open = true;
}

SQLite3::~SQLite3(){
    if(this->db_open){
        int rc = sqlite3_close(this->db);
        if(rc != SQLITE_OK){
            const char* message = "cannot close database!\n";
            fprintf(stderr, "%s", message);
            return;
        }
    }
    if(this->prep_stmt != nullptr){
        sqlite3_finalize(this->prep_stmt);
    }
}


std::string SQLite3::read_row(sqlite3_stmt* stmt) const{
    std::string result = "| ";

    result += std::to_string(sqlite3_column_int(stmt, 0)) + " | ";
    result += std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,1))) + " |";

    return result;
}


void SQLite3::exec_q(const std::string& query){
    if(this->db_open){
        char* errMSG = nullptr;
        int rc = sqlite3_exec(this->db, query.c_str(), nullptr, nullptr, &errMSG);
        
        if(rc != SQLITE_OK){
            fprintf(stderr, "execute query error: %s\n", errMSG);
            sqlite3_free(errMSG);
            return;
        }
    }
    else{
        fprintf(stderr, "execute query skipped - open database first\n");
    }
}

std::vector<std::string> SQLite3::selec_q(const std::string& query){
    std::vector<std::string> feedback;
    if(this->db_open){
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
        if(rc != SQLITE_OK){
            fprintf(stderr, "select query error!\n");
            return feedback;
        }

        std::string c_name = "|";
        for(int i=0; i<sqlite3_column_count(stmt); i++){
            c_name += std::string(sqlite3_column_name(stmt, i)) + " | ";
        }
        feedback.push_back(c_name);


        while(sqlite3_step(stmt) == SQLITE_ROW)
            feedback.push_back(this->read_row(stmt));

        sqlite3_finalize(stmt);
    }
    else{
        fprintf(stderr, "select query skipped - open database first\n");
    }
    return feedback;
}

std::vector<std::string> SQLite3::execute_query(const std::string& query){
    std::vector<std::string> feedback;
    if(this->db_open){
        char* errMSG = nullptr;
        int rc = sqlite3_exec(this->db, query.c_str(), nullptr, nullptr, &errMSG);
        
        if(rc != SQLITE_OK){
            fprintf(stderr, "execute query error: %s\n", errMSG);
            sqlite3_free(errMSG);
            return;
        }
    }
    else{
        fprintf(stderr, "execute query skipped - open database first\n");
    }
}


void SQLite3::prepare_query(const std::string& query){
    if(this->db_open){
        this->prep_started = true;
        int rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &this->prep_stmt, nullptr);
        if(rc != SQLITE_OK){
            fprintf(stderr, "prepared query error!\n");
            return;
        }
    }
    else{
        fprintf(stderr, "prepare query skipped - open database first\n");
        this->prep_started = false;
    }
}

void SQLite3::bind_int_param(int pos, int param){
    if(this->prep_started){
        int rc = sqlite3_bind_int(this->prep_stmt, pos, param);
        if(rc != SQLITE_OK){
            fprintf(stderr, "binding int error!\n");
            return;
        }
    }
    else{
        fprintf(stderr, "bind param skipped - prepare query first\n");
    }
}

void SQLite3::bind_double_param(int pos, double param){
    if(this->prep_started){
        int rc = sqlite3_bind_double(this->prep_stmt, pos, param);
        if(rc != SQLITE_OK){
            fprintf(stderr, "binding double error!\n");
            return;
        }
    }
    else{
        fprintf(stderr, "bind param skipped - prepare query first\n");
    }
}

void SQLite3::bind_text_param(int pos, const std::string& param){
    if(this->prep_started){
        int rc = sqlite3_bind_text(this->prep_stmt, pos, param.c_str(), -1, nullptr);
        if(rc != SQLITE_OK){
            fprintf(stderr, "binding text error!\n");
            return;
        }
    }
    else{
        fprintf(stderr, "bind param skipped - prepare query first\n");
    }
}


std::vector<std::string> SQLite3::execute_prepared(const std::string& query){
    if(this->prep_started){
        
    }
    else{
        fprintf(stderr, "execute prepared skipped - prepare query first\n");
    }
}

// std::vector<std::string> SQLite3::select_prepared(const std::string& query){
//     std::vector<std::string> feedback;
//     if(this->prep_started){
        
//     }
//     else{
//         fprintf(stderr, "select prepared skipped - prepare query first\n");
//     }
//     return feedback;
// }
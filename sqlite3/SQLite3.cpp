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
            fprintf(stderr, "cannot close database!\n");
            return;
        }
    }
    if(this->prep_stmt != nullptr){
        sqlite3_finalize(this->prep_stmt);
    }
}


std::string SQLite3::read_row(sqlite3_stmt* stmt) const{
    std::string result = "| ";
    int column_count = sqlite3_data_count(stmt);
    for(int i=0; i<column_count; i++){
        switch (sqlite3_column_type(stmt, i)){
        case SQLITE_INTEGER:
            result += std::to_string(sqlite3_column_int(stmt, i));
            break;
        case SQLITE_FLOAT:
            result += std::to_string(sqlite3_column_double(stmt, i));
            break;
        case SQLITE_TEXT:
            result += reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            break;
        case SQLITE_BLOB:
            result += "{BLOB}"; //  binary labge object
            break;
        case SQLITE_NULL:
            result += "NULL";
            break;
        default:
            result += "{unknown}"; // unknown data type
            break;
        }
        result += " | ";
    }
    return result;
}


void SQLite3::execute_query(const std::string& query){
    char* errMSG = nullptr;
    int rc = sqlite3_exec(this->db, query.c_str(), nullptr, nullptr, &errMSG);
    
    if(rc != SQLITE_OK){
        _EXECUTE_ERROR_MSG_(errMSG)
        sqlite3_free(errMSG);
        return;
    }
}

std::vector<std::string> SQLite3::select_query(const std::string& query){
    std::vector<std::string> feedback;
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
    if(rc != SQLITE_OK){
        _EXECUTE_ERROR_
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
    return feedback;
}

std::vector<std::string> SQLite3::execute(const std::string& query){
    if(this->db_open){
        std::string cpq;
        for(const char& c : query)
            cpq.push_back(std::toupper(c));

        if(cpq.find("SELE") != std::string::npos){
            return this->select_query(query);
        }
        else{
            this->execute_query(query);
        }
    }
    else{
        _SKIPPED_OPEN_
    }
    return std::vector<std::string>();
}


void SQLite3::prepare_query(const std::string& query){
    if(this->db_open){
        this->prep_started = true;
        int rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &this->prep_stmt, nullptr);
        if(rc != SQLITE_OK){
            _EXECUTE_ERROR_
            return;
        }
    }
    else{
        _SKIPPED_OPEN_
        this->prep_started = false;
    }
}

void SQLite3::bind_int_param(int pos, int param){
    if(this->prep_started){
        int rc = sqlite3_bind_int(this->prep_stmt, pos, param);
        if(rc != SQLITE_OK){
            _EXECUTE_ERROR_
            return;
        }
    }
    else{
        _SKIPPED_PREP_
    }
}

void SQLite3::bind_double_param(int pos, double param){
    if(this->prep_started){
        int rc = sqlite3_bind_double(this->prep_stmt, pos, param);
        if(rc != SQLITE_OK){
            _EXECUTE_ERROR_
            return;
        }
    }
    else{
        _SKIPPED_PREP_
    }
}

void SQLite3::bind_text_param(int pos, const std::string& param){
    if(this->prep_started){
        int rc = sqlite3_bind_text(this->prep_stmt, pos, param.c_str(), -1, nullptr);
        if(rc != SQLITE_OK){
            _EXECUTE_ERROR_
            return;
        }
    }
    else{
        _SKIPPED_PREP_
    }
}

void SQLite3::bind_clear(){
    sqlite3_clear_bindings(this->prep_stmt);
}


void SQLite3::execute_prepared_query(const std::string& query){
    char* errMSG = nullptr;
    int rc = sqlite3_exec(this->db, query.c_str(), nullptr, nullptr, &errMSG);
    
    if(rc != SQLITE_OK){
        _EXECUTE_ERROR_MSG_(errMSG)
        sqlite3_free(errMSG);
        return;
    }
}

std::vector<std::string> SQLite3::select_prepared_query(const std::string& query){
    std::vector<std::string> feedback;
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
    if(rc != SQLITE_OK){
        _EXECUTE_ERROR_
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
    return feedback;
}

std::vector<std::string> SQLite3::execute_prepared(const std::string& query){
    if(this->prep_started){
        std::string cpq;
        for(const char& c : query)
            cpq.push_back(std::toupper(c));

        if(cpq.find("SELECT") != std::string::npos){
            return this->select_prepared_query(query);
        }
        else{
            this->execute_prepared_query(query);
        }
    }
    else{
        _SKIPPED_PREP_
    }
    return std::vector<std::string>();
}
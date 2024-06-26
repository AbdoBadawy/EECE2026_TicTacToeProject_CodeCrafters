#include <iostream>
#include "sqlite3.h"
#include <vector>
#include <sstream>
#include "md5.h"
using namespace std;
bool signUp(const std::string& username, const std::string& password) {
    sqlite3* db;
    char* errMsg = 0;
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_open("C:/Users/user/OneDrive/Desktop/TicTacToe_Project/TicTacToe_Project/TicTacToe_Project/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/project_database", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Check if email already exists
    std::string checkEmailSQL = "SELECT 1 FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, checkEmailSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    bool emailExists = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);

    if (emailExists) {
        // Email already exists
        sqlite3_close(db);
        return false;
    }

    // Email does not exist, proceed with insertion
    std::string insertSQL = "INSERT INTO users (username, password) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1,username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}
bool login(const std::string& username, const std::string& password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_open("C:/Users/user/OneDrive/Desktop/database_interface_encryption_included&&draws/database_interface/project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    const char* hashedPassword = GetMD5String(password.c_str(), password.length());
    std::string query = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?;";

    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    // Bind values to the query
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword, -1, SQLITE_STATIC);

    int userCount = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userCount = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return userCount > 0;
}

std::vector<std::string> get_history(const std::string& username) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    std::vector<std::string> result;

    rc = sqlite3_open("project_database.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return result;
    }

    std::string query = "SELECT history FROM users_history WHERE username = '" + username + "' ORDER BY date DESC ";

    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* history = sqlite3_column_text(stmt, 0);
        result.push_back(std::string(reinterpret_cast<const char*>(history)));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}
vector<int> get_history_int(string username){
vector<int>the_final_reslut ;
vector<string >s=get_history(username);

for(int i=0;i<s.size();i++){
 for(int j=0;j<s[i].size();j++){
    int  x=s[i][j]-'0';
     the_final_reslut.push_back(x);
  }
}

if(the_final_reslut.size()%12!=0){
    the_final_reslut.pop_back();
}

return the_final_reslut;

}

//don't miss history_x

// each 11 element from this vector reperesent a game

void history_insert(const std::string& username,  std::vector<int>& history_x) {
    sqlite3* db;
    int rc = sqlite3_open("C:/Users/user/OneDrive/Desktop/database_interface_encryption_included&&draws/database_interface/project_database.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::stringstream ss;
    std::string history;
    for (int i = 0; i < history_x.size(); i++) {
        history.push_back('0' + history_x[i]);
    }

    const char* sql = "INSERT INTO users_history (username, history) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind username: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_bind_text(stmt, 2, history.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind history: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
std::string get_age(const std::string& username) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return "";
    }

    const char* sql = "SELECT age FROM users WHERE username = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return "";
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    std::string age;
    if (rc == SQLITE_ROW) {
        age = std::to_string(sqlite3_column_int(stmt, 0));
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return age;
}
void update_draws(const std::string& username, int new_draws) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Query to get the current draws value
    const char* select_sql = "SELECT draws FROM users WHERE username = ?";
    sqlite3_stmt* select_stmt;
    rc = sqlite3_prepare_v2(db, select_sql, -1, &select_stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare select statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(select_stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    int current_draws = 0;
    rc = sqlite3_step(select_stmt);
    if (rc == SQLITE_ROW) {
        current_draws = sqlite3_column_int(select_stmt, 0);
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute select statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(select_stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(select_stmt);

    // Calculate the new draws value
    int updated_draws = current_draws + new_draws;

    // Update the draws value in the database
    const char* update_sql = "UPDATE users SET draws = ? WHERE username = ?";
    sqlite3_stmt* update_stmt;
    rc = sqlite3_prepare_v2(db, update_sql, -1, &update_stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(update_stmt, 1, updated_draws);
    sqlite3_bind_text(update_stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(update_stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(update_stmt);
    sqlite3_close(db);
}


// Function to update the wins of a user
void update_wins(const std::string& username, int new_wins) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Query to get the current wins value
    const char* select_sql = "SELECT wins FROM users WHERE username = ?";
    sqlite3_stmt* select_stmt;
    rc = sqlite3_prepare_v2(db, select_sql, -1, &select_stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare select statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(select_stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    int current_wins = 0;
    rc = sqlite3_step(select_stmt);
    if (rc == SQLITE_ROW) {
        current_wins = sqlite3_column_int(select_stmt, 0);
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute select statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(select_stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(select_stmt);

    // Calculate the new wins value
    int updated_wins = current_wins + new_wins;

    // Update the wins value in the database
    const char* update_sql = "UPDATE users SET wins = ? WHERE username = ?";
    sqlite3_stmt* update_stmt;
    rc = sqlite3_prepare_v2(db, update_sql, -1, &update_stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(update_stmt, 1, updated_wins);
    sqlite3_bind_text(update_stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(update_stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(update_stmt);
    sqlite3_close(db);
}

std::string get_phone(const std::string& username) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return "";
    }

    const char* sql = "SELECT phone FROM users WHERE username = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return "";
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    std::string phone;
    if (rc == SQLITE_ROW) {
        phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return phone;
}
int get_wins(const std::string& username) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    const char* sql = "SELECT wins FROM users WHERE username = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    int wins = -1;
    if (rc == SQLITE_ROW) {
        wins = sqlite3_column_int(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return wins;
}
int get_draws(const std::string& username) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    const char* sql = "SELECT draws FROM users WHERE username = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    int draws = -1;
    if (rc == SQLITE_ROW) {
        draws = sqlite3_column_int(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return draws;
}

int get_loses(const std::string& username) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    const char* sql = "SELECT loses FROM users WHERE username = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    int loses = -1;
    if (rc == SQLITE_ROW) {
        loses = sqlite3_column_int(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return loses;
}
void update_loses(const std::string& username, int new_loses) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Query to get the current loses value
    const char* select_sql = "SELECT loses FROM users WHERE username = ?";
    sqlite3_stmt* select_stmt;
    rc = sqlite3_prepare_v2(db, select_sql, -1, &select_stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare select statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(select_stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    int current_loses = 0;
    rc = sqlite3_step(select_stmt);
    if (rc == SQLITE_ROW) {
        current_loses = sqlite3_column_int(select_stmt, 0);
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute select statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(select_stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(select_stmt);

    // Calculate the new loses value
    int updated_loses = current_loses + new_loses;

    // Update the loses value in the database
    const char* update_sql = "UPDATE users SET loses = ? WHERE username = ?";
    sqlite3_stmt* update_stmt;
    rc = sqlite3_prepare_v2(db, update_sql, -1, &update_stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(update_stmt, 1, updated_loses);
    sqlite3_bind_text(update_stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(update_stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(update_stmt);
    sqlite3_close(db);
}

bool signUp(const std::string& username, const std::string& password, const std::string& phone, bool gender, int age) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    rc = sqlite3_open("C:/Users/user/OneDrive/Desktop/database_interface_encryption_included&&draws/database_interface/project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Check if username already exists
    std::string checkUserSQL = "SELECT 1 FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, checkUserSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    bool userExists = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);

    if (userExists) {
        // Username already exists
        sqlite3_close(db);
        return false;
    }

    // Username does not exist, proceed with insertion
    const char* hashedPassword = GetMD5String(password.c_str(), password.length());
    std::string insertSQL = "INSERT INTO users (username, password, phone, gender, age) VALUES (?, ?, ?, ?, ?);";
    rc = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, phone.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, gender);
    sqlite3_bind_int(stmt, 5, age);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}
bool get_gender(const std::string& username) {
    sqlite3* db;
    int rc = sqlite3_open("project_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false; // Return a default value indicating failure
    }

    const char* sql = "SELECT gender FROM users WHERE username = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false; // Return a default value indicating failure
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    bool gender = false; // Default value
    if (rc == SQLITE_ROW) {
        gender = sqlite3_column_int(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return gender;
}

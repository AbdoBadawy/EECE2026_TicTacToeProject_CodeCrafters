#include <iostream>
#include "sqlite3.h"
#include <vector>
#include <sstream>
using namespace std;
bool login(const std::string& username, const std::string& password) ;
std::vector<int> get_history(const std::string& username) ;
vector<int> get_history_int(string username);
void history_insert(const std::string& username,vector<int> &history_x);
bool signUp(const std::string& username, const std::string& password, const std::string& phone, bool gender, int age);
std::string get_age(const std::string& username);
std::string get_phone(const std::string& username);
int get_wins(const std::string& username);
int get_loses(const std::string& username);
void update_loses(const std::string& username, int new_loses);
bool get_gender(const std::string& username);
void update_draws(const std::string& username, int new_draws);
int get_draws(const std::string& username);

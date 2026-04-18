#include "database.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>

// Helper to read the .env file (internal to this file only)
static std::map<std::string, std::string> loadEnv(const std::string& filename) {
    std::map<std::string, std::string> env;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream is_line(line);
        std::string key, value;
        if (std::getline(is_line, key, '=') && std::getline(is_line, value)) {
            env[key] = value;
        }
    }
    return env;
}

std::string getConnectionString() {
    // Static variable persists for the life of the program
    static std::string connection_string = "";

    // Only load the file if the string is empty
    if (connection_string.empty()) {
        auto env = loadEnv(".env");
        if (env.find("DB_HOST") == env.end()) {
            std::cerr << "[Critical] Could not load database configuration!" << std::endl;
            return "";
        }

        connection_string = "host=" + env["DB_HOST"] + 
                           " dbname=" + env["DB_NAME"] + 
                           " user=" + env["DB_USER"] + 
                           " password='" + env["DB_PASS"] + "' " +
                           "channel_binding=disable";
    }

    return connection_string;
}
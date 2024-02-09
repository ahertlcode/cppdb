#include "env.h"

using namespace std;

map<string, string> Env::envMap_;
bool Env::initialized = false;

string Env::getenv(const string& key) {
    // Load environment variables from a file during the first call
    if (!initialized) {
        envMap_ = Env::loadEnvFromFile();
        initialized = true;
    }

    // Access and return the environment variable value
    if (envMap_.count(key) > 0) {
        return envMap_[key];
    } else {
        // Handle the case when the environment variable is not found
        return "";
    }
}

map<string, string> Env::loadEnvFromFile() {
    map<string, string> env;
    ifstream file("../.env");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find("=");
            if (pos != string::npos) {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);
                env[key] = value;
            }
        }
        file.close();
    }

    return env;
}

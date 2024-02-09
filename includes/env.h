#ifndef ENV_H
#define ENV_H

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Env {
    public:
        static string getenv(const string& key);
    private:
        static map<string, string> loadEnvFromFile();
        static map<string, string> envMap_;
        static bool initialized;
};

#endif /* ENV_H */

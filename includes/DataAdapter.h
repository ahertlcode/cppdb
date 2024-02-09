#ifndef DATA_ADAPTER
#define DATA_ADAPTER
#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;
using json = nlohmann::json;

class DataAdapter {
    public:
        virtual void connect(const string& host, const string& user, const string& password, const string& dbName, bool useSsl)=0;
        virtual bool executeSqlQueryNonReturn(const string& sql) = 0;
        virtual json executeSqlQuery(const string& sql) = 0;
        virtual ~DataAdapter() = default;
};

#endif /* DATABASE_DRIVER */

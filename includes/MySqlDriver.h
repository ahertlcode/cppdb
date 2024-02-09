#ifndef MYSQL_ADAPTER_H
#define MYSQL_ADAPTER_H

#pragma once
#include <memory>
#include "Model.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include "nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;

typedef sql::ResultSet* dataSet;
typedef sql::mysql::MySQL_Driver* mysqlDriver;
typedef sql::Connection* mysqlConnection;
typedef sql::PreparedStatement* mysqlStatement;

class MysqlDriver : public Model{
    public:
        MysqlDriver(const string& host, const string& user, const string& password, const string& dbName, bool useSsl);
        ~MysqlDriver();
        bool executeSqlQueryNonReturn(const string& query);
        json executeSqlQuery(const string& query);

    private:
        mysqlDriver driver;
        mysqlConnection conn;

        string databaseName;
        string DB_HOST;
        string DB_NAME;
        string DB_USER;
        string DB_PASSWD;
        bool USESSL;

        mysqlConnection createConnection();
        void closeConnection();
};

#endif /* MYSQL_ADAPTER_H */

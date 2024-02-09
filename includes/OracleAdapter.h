#ifndef ORACLE_ADAPTER_H
#define ORACLE_ADAPTER_H

#include "DataAdapter.h"

using namespace std;
using json = nlohmann::json;

class OracleAdapter : public DataAdapter {
    public:
        void connect(const string& host, const string& user, const string& password, const string& dbName, bool useSsl) override;
        bool executeSqlQueryNonReturn(const string& query) override;
        json executeSqlQuery(const string& query) override;

    private:
        //mysqlDriver driver;
        //mysqlConnection conn;

        string databaseName;
        string DB_HOST;
        string DB_NAME;
        string DB_USER;
        string DB_PASSWD;
        bool USESSL;

        //mysqlConnection createConnection();
        void closeConnection();
};
#endif /* ORACLE_ADAPTER_H */

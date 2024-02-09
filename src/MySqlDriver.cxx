#include "MySqlDriver.h"

MysqlDriver::MysqlDriver(const string& host, const string& user, const string& password, const string& dbName, bool useSsl) : DB_HOST(host), DB_USER(user), DB_PASSWD(password), DB_NAME(dbName), USESSL(useSsl) {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        conn = driver->connect(host, user, password);

        if (useSsl == true) {
            conn->setClientOption("mysql_ssl_key", "/etc/mysql/certs/client-key.pem");
            conn->setClientOption("mysql_ssl_cert", "/etc/mysql/certs/client-cert.pem");
            conn->setClientOption("mysql_ssl_ca", "/etc/mysql/certs/ca-cert.pem");
        }

        conn->setSchema(dbName);
    } catch (const exception& e) {
        throw runtime_error(string("There is an error! ") + e.what());
    }
}

MysqlDriver::~MysqlDriver() {
    delete conn;
}

mysqlConnection MysqlDriver::createConnection() {
    conn = driver->connect(DB_HOST, DB_USER, DB_PASSWD);

    if(USESSL) {
        conn->setClientOption("mysql_ssl_key", "/etc/mysql/certs/client-key.pem");
        conn->setClientOption("mysql_ssl_cert", "/etc/mysql/certs/client-cert.pem");
        conn->setClientOption("mysql_ssl_ca", "/etc/mysql/certs/ca-cert.pem");
    }

    conn->setSchema(DB_NAME);

    return conn;
}

void MysqlDriver::closeConnection() {
    delete conn;
}

bool MysqlDriver::executeSqlQueryNonReturn(const string& query) {
    try {
        mysqlConnection conn = createConnection();
        mysqlStatement stmt = conn->prepareStatement(query);
        stmt->executeUpdate();
        closeConnection();
        delete stmt;
        return true;
    } catch(exception& e) {
        throw runtime_error(e.what());
        return false;
    }
}

json MysqlDriver::executeSqlQuery(const string& query) {
    dataSet res;
    try {
        mysqlConnection conn = createConnection();
        mysqlStatement stmt = conn->prepareStatement(query);
        res = stmt->executeQuery();
    } catch(exception& e) {
        throw runtime_error(e.what());
    }

    json data = nlohmann::json::array();
    
    while(res->next()) {
        json dJson = {};
        int numCols = res->getMetaData()->getColumnCount();

        for(int i=1; i<=numCols; ++i) {
            string col = res->getMetaData()->getColumnName(i);
            string value = res->getString(i);
            dJson[col] = value;
        }
        data.push_back(dJson);
    }

    return data;
}
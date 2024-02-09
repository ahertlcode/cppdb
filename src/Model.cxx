#include "Model.h"
#include "MySqlDriver.h"

typedef vector<string> stringList;
typedef variant<int, short, long, float, double, char, string, bool> anyType;
unique_ptr<Model> Model::adapter = nullptr;
string Model::dialect;
bool Model::freezeTableName;
Model::Model(){}
Model::~Model(){}

struct anyToString {
    template <typename T>
    string operator()(const T& value) const {
        return to_string(value);
    }

    std::string operator()(const std::string& value) const {
        return value;
    }
};

unique_ptr<Model> Model::createModel() {
    unique_ptr<MysqlDriver> model = nullptr;
    dialect = Env::getenv("DATABASE_DRIVER");
    transform(dialect.begin(), dialect.end(), dialect.begin(), ::toupper);
    string host = Env::getenv("DATABASE_HOST");
    string user = Env::getenv("DATABASE_USER");
    string password = Env::getenv("DATABASE_PASSWORD");
    string dbname = Env::getenv("DATABASE_NAME");
    bool usessl = Env::getenv("USE_SSL") == "true";
    
    if (dialect=="MYSQL") {
        model = make_unique<MysqlDriver>(host, user, password, dbname, usessl);
    } /*else if (dialect=="PGSQL") {
        model = unique_ptr<PgSqlAdapter>();
    } else if(dialect == "ORACLE") {
        model = unique_ptr<OracleAdapter>();
    } else if (dialect == "MSSQL") {
        model = unique_ptr<MsSqlAdapter>();
    }*/ else {
        throw runtime_error("Database type must be specified!");
    }

    return model;
}

stringList Model::getTableColumns() {
    return fillable;
}

stringList Model::getHiddenFields() {
    return hidden;
}

string Model::getCurrentTable() {
    if (!tableName.empty()) {
        return tableName;
    } else {
        if (freezeTableName == true) {
            throw runtime_error("Invalid value set, you can only free table name when the tableName is set.");
            return "-1";
        } else {
            string className = typeid(*this).name();
            int status;
            char* demangled = abi::__cxa_demangle(className.c_str(), nullptr, nullptr, &status);

            if (status == 0) {
                className = demangled;
                free(demangled);
            }
            
            transform(className.begin(), className.end(), className.begin(), ::tolower);
            return Inflect::pluralize(className);
        }
    }
}

json Model::all() {
    if(adapter == nullptr) {
        adapter = createModel();
    }

    string tbl = getCurrentTable();
    stringList hiddenFields = getHiddenFields();
    string sqlQuery = "select * from " + tbl;
    json data = adapter->executeSqlQuery(sqlQuery);

    for(auto& row : data) {
        for(auto& fld : hiddenFields) {
            row.erase(fld);
        }
    }

    return data;
}

bool Model::create(const map<string, anyType>& data) {
    if (adapter==nullptr){
        adapter = createModel();
    }
    string tbl = getCurrentTable();
    stringList cols = getTableColumns();
    if (cols.empty()) {
        throw runtime_error("Specify non nullable fields to be insert in your model.");
        exit(1);
    }
    string sqlQuery = "insert into " + tbl;
    string columns;
    string values;
    int l=0;
    for(const auto& entry : data) {
        auto it = find(cols.begin(), cols.end(), entry.first);
        if(it != cols.end()) {
            if(l < cols.size()-1) {
                columns += entry.first+",";
                values += "\""+ visit(anyToString{}, entry.second) + "\"" + ",";
            } else {
                columns += entry.first;
                values += "\""+ visit(anyToString{}, entry.second) + "\"";
            }
        }
        l+=1;
    }
    sqlQuery += "("+columns+") values ("+values+");";
    return adapter->executeSqlQueryNonReturn(sqlQuery);
}

bool Model::update(const map<string, anyType>& condition, const map<string, anyType>& data) {
    if (adapter==nullptr){
        adapter = createModel();
    }

    string tbl = getCurrentTable();
    string sqlQuery = "update " + tbl + " SET ";
    int l=0;
    for(auto& pt : data) {
        if (l < data.size()-1) {
            sqlQuery += pt.first + "=\""+visit(anyToString{}, pt.second)+"\", ";
        } else {
            sqlQuery += pt.first + "=\""+visit(anyToString{}, pt.second)+"\"";
        }
        l += 1;
    }
    sqlQuery += " WHERE ";
    int p=0;
    for(auto& cond : condition) {
        if(p < condition.size()-1 && condition.size() > 1) {
            sqlQuery += cond.first + "=\""+visit(anyToString{}, cond.second)+"\" AND ";
        } else {
            sqlQuery += cond.first + "=\""+visit(anyToString{}, cond.second)+"\"";
        }
        p += 1;
    }

    sqlQuery += ";";
    cout << sqlQuery << endl;
    return adapter->executeSqlQueryNonReturn(sqlQuery);
}

json Model::executeSqlQuery(const string& sql) {
    return adapter->executeSqlQuery(sql);
}

bool Model::executeSqlQueryNonReturn(const string& sql) {
    return adapter->executeSqlQueryNonReturn(sql);
}
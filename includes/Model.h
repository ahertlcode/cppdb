#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <fstream>
#include <sstream>
#include <cxxabi.h>
#include <iostream>
#include <string>
#include <map>
#include <variant>
#include "env.h"
#include "inflect.h"
#include <typeinfo>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

typedef vector<string> stringList;
typedef variant<int, short, long, float, double, char, string, bool> anyType;

enum class OrderType {
    ASC,
    DESC
};

class Model {
    protected:
        static unique_ptr<Model> adapter;
        static string dialect;
        string tableName;
        stringList columns;
        stringList fillable;
        stringList hidden;
        stringList guarded;
        string primaryKey;
        static bool freezeTableName;

    public:
        Model();
        virtual ~Model();
        virtual json all();
        static json show(Model* model);
        virtual bool create(const map<string, anyType>& data);
        static bool update(Model* model);
        static bool destroy(Model* model);
        Model& where(const map<string, anyType>& conditions);
        Model& groupBy(const string& column);
        Model& orderBy(const string& column, OrderType type);
        // the current model has a relationship with relatedModel
        Model& hasOne(Model* relatedModel, const string& foreignKey="", const string& primaryKey="");
        //the current model belongs to relatedModel
        Model& belongsTo(Model* relatedModel, const string& foreignKey="", const string& primaryKey="");
        Model& hasMany(Model* relatedModel, const string& foreignKey="", const string& primaryKey="");
        static json get(const stringList& fields={});
        static json first();
    
    private:
        map<string, anyType> whereConditions;
        static unique_ptr<Model> database;
        string getCurrentTable();
        stringList getTableColumns();
        stringList getHiddenFields();
        static unique_ptr<Model> createModel();
        virtual json executeSqlQuery(const string& sql);
        virtual bool executeSqlQueryNonReturn(const string& sql);
};

#endif /* MODEL_H */

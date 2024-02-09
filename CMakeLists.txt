cmake_minimum_required(VERSION 3.10)

project(cppdb)

# Add all relevant source files to the DataAdapter target
add_executable(app
    src/models/user.cxx
    src/Controllers/UserController.cxx
    src/main.cxx
    src/env.cxx
    src/inflect.cxx
    src/Model.cxx 
    src/MySqlDriver.cxx
)

# Specify the include directories
target_include_directories(app PRIVATE includes)

# Link against the MySQL Connector/C++ library
target_link_libraries(app PRIVATE mysqlcppconn)
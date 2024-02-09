#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include "Controllers/UserController.cxx"

using namespace std;
using json = nlohmann::json;


int main() {
    UserController user;
    json user1 = user.store({
        {"name", "Peter Apetu"},
        {"email", "peteru@ymail.com"},
        {"password", "0123456789"}
    });
    cout << "Single user: " << user1.dump() << endl;
    json data = user.index();
    cout << data.dump() << endl;
    return 0;
}
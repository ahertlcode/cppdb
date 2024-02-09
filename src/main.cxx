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
        {"email", "peteru6@ymail.com"},
        {"password", "0123456789"}
    });
    cout << "Single user: " << user1.dump() << endl;
    json user2 = user.update({{"id",1},{"email","temidoswag@gmail.com"}}, {{"password","pa5sW0rD"}});
    cout << "Updated user: " << user2.dump() << endl;
    json data = user.index();
    cout << data.dump() << endl;
    return 0;
}
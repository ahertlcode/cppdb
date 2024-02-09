#include "../models/user.cxx"

class UserController {
    public:
        User user;
        json index() {
            return user.all();
        }

        bool store(const map<string, anyType>& data) {
            return user.create(data);
        }
};
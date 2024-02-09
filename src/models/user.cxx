#include "Model.h"

class User : public Model {
    public:
        User() {
            fillable = {
                "name",
                "email",
                "password"
            };

            hidden = {
                "password",
                "remember_token",
                "updated_at",
                "created_at",
                "email_verified_at"
            };
        }
};
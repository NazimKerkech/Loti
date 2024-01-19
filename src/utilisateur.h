#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>
#include <vector>

class Utilisateur {
public:
    Utilisateur();
    ~Utilisateur();

    std::string getUserAccess() const;
    bool login(const std::string& username);
    void loadCSV(const std::string& filename);
    const std::vector<std::vector<std::string>>& getUserData() const;

private:
    std::string userAccess;
    bool userExist;
    std::vector<std::vector<std::string>> userData;
};

#endif // UTILISATEUR_H

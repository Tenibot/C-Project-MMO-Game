#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct User
{
    std::string username;
    std::string password;
    int level;
};

std::vector<User> Users;

void LoadProfiles(std::vector<User> &Users)
{
    std::fstream usersFile;
    usersFile.open("users.txt", std::fstream::in);

    std::string userLine;

    std::string username;
    std::string password;
    std::string level;

    if (usersFile.is_open() == false)
    {
        std::cerr << "Failed to open file";
    }
    else
    {
        while (std::getline(usersFile, userLine))
        {
            int i = 0;
            while (i < userLine.size() && userLine[i] != ':')
            {
                username += userLine[i++];
            }
            i++;
            while (i < userLine.size() && userLine[i] != ':')
            {
                password += userLine[i++];
            }
            i++;
            while (i < userLine.size())
            {
                level += userLine[i++];
            }
            i++;

            int n_level;
            std::istringstream(level) >> n_level;

            User aUser = {username, password, n_level};
            Users.push_back(aUser);

            username = "";
            password = "";
            level = "";
        }
        usersFile.close();
    }
}

int main()
{
    LoadProfiles(Users);

    return 0;
}
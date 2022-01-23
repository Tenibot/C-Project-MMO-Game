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

bool isLetter_UpperCase(const char letter)
{
    if (letter < 'A' || letter > 'Z')
    {
        return false;
    }
    return true;
}

bool isLetter_LowerCase(const char letter)
{
    if (letter < 'a' || letter > 'z')
    {
        return false;
    }
    return true;
}

bool isLetter_Digit(const char letter)
{
    if (letter < '0' || letter > '9')
    {
        return false;
    }
    return true;
}

bool isLetter_Symbol(const char letter)
{
    const std::vector<char> GivenSymbols = {'!', '@', '#', '$', '%', '^', '&', '*'};
    for (int l = 0; l < GivenSymbols.size(); l++)
    {
        if (letter == GivenSymbols[l])
        {
            return true;
        }
    }
    return false;
}

bool is_Username_OK(std::string &username)
{
    for (int i = 0; i < username.size(); i++)
    {
        if (!(isLetter_UpperCase(username[i]) || isLetter_LowerCase(username[i]) || isLetter_Digit(username[i])))
        {
            return false;
        }
    }
    return true;
}

bool is_Password_Characters_OK(std::string &password)
{
    for (int i = 0; i < password.size(); i++)
    {
        if (!(isLetter_UpperCase(password[i]) || isLetter_LowerCase(password[i]) || isLetter_Digit(password[i]) || isLetter_Symbol(password[i])))
        {
            return false;
        }
    }
    return true;
}

bool is_Password_size_OK(std::string &password)
{
    const int min_pass_size = 5;
    if (password.size() < min_pass_size)
    {
        return false;
    }
    return true;
}

bool String_Contains_UpperCase(std::string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (isLetter_UpperCase(str[i]))
        {
            return true;
        }
    }
    return false;
}

bool String_Contains_LowerCase(std::string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (isLetter_LowerCase(str[i]))
        {
            return true;
        }
    }
    return false;
}

bool String_Contains_Symbol(std::string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (isLetter_Symbol(str[i]))
        {
            return true;
        }
    }
    return false;
}

bool String_Contains_Digit(std::string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (isLetter_Digit(str[i]))
        {
            return true;
        }
    }
    return false;
}

bool LoginUsername(int userNumber)
{
    std::cout << "Enter username: ";
    std::string username;
    std::getline(std::cin, username);

    if (!is_Username_OK(username))
    {
        std::cout << "Please enter a valid username!\n";
        return false;
    }

    bool isUsernameSaved = false;
    for (int i = 0; i < Users.size(); i++)
    {
        if (username == Users[i].username)
        {
            userNumber = i;
            isUsernameSaved = true;
        }
    }

    if (!isUsernameSaved)
    {
        std::cout << "Please enter an existing username!\n";
        return false;
    }
    return true;
}

bool LoginPassword(const int userNumber)
{
    std::cout << "Enter password: ";
    std::string password;
    std::getline(std::cin, password);

    if (!is_Password_Characters_OK(password))
    {
        std::cout << "Incorrect Input! Password contains forbidden characters!\n";
        return false;
    }
    if (password != Users[userNumber].password)
    {
        std::cout << "Password is incorrect! Try again!\n";
    }

    return true;
}

void Login()
{
    int userNumber = -1;
    bool Loop_Username = true;
    while (Loop_Username)
    {
        Loop_Username = !LoginUsername(userNumber);
    }
    bool Loop_Password = true;
    while (Loop_Password)
    {
        Loop_Password = !LoginPassword(userNumber);
    }
}

int main()
{
    LoadProfiles(Users);
    Login();

    return 0;
}
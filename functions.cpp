#include <iostream>
#include <vector>
#include <string>

#include <fstream>

#include <utility>
#include <functional>

#define ErrorNumber -1

struct User
{
    std::string username;
    std::size_t password;
    int level = 1;
    std::pair<int, int> range;
};

std::vector<User> Users;

std::pair<int, int> DetermineRange(const int level)
{
    std::pair<int, int> range;
    const int step = 5;
    int level_Copy = level;

    while (level_Copy % step != 0)
    {
        level_Copy--;
    }
    range.first = level_Copy;
    range.second = level_Copy + step;
    return range;
}

template <typename T>

T ConvertTo(std::string &text)
{
    T result = 0;
    for (int i = 0; i < text.size(); i++)
    {
        result *= 10;
        result += text[i] - '0';
    }
    return result;
}

void LoadProfiles()
{
    std::fstream usersFile;
    usersFile.open("users.txt", std::fstream::in);

    std::string userLine;

    std::string username;
    std::string password;
    std::string level;

    if (usersFile.is_open() == false)
    {
        std::cerr << "Failed to open file.";
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
            n_level = ConvertTo<int>(level);

            std::pair<int, int> range = DetermineRange(n_level);

            std::size_t n_password = ConvertTo<size_t>(password);

            User aUser = {username, n_password, n_level, range};
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

bool is_Input_size_OK(std::string &input)
{
    const int min_input_size = 5;
    if (input.size() < min_input_size)
    {
        return false;
    }
    return true;
}

bool is_Username_OK(std::string &username)
{
    if (!is_Input_size_OK(username))
    {
        return false;
    }
    for (int i = 0; i < username.size(); i++)
    {
        if (!(isLetter_UpperCase(username[i]) || isLetter_LowerCase(username[i]) || isLetter_Digit(username[i])))
        {
            return false;
        }
    }
    return true;
}

bool are_Password_Characters_OK(std::string &password)
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

bool Password_Check(std::string &password)
{
    if (!are_Password_Characters_OK(password))
    {
        std::cout << "Password contains forbidden characters!\n";
        return false;
    }
    if (!is_Input_size_OK(password))
    {
        std::cout << "Password must contain at least 5 symbols!\n";
        return false;
    }
    if (!String_Contains_Digit(password))
    {
        std::cout << "Password must contain at least 1 digit!\n";
        return false;
    }
    if (!String_Contains_UpperCase(password))
    {
        std::cout << "Password must contain at least 1 upper case letter!\n";
        return false;
    }
    if (!String_Contains_LowerCase(password))
    {
        std::cout << "Password must contain at least 1 lower case letter!\n";
        return false;
    }
    if (!String_Contains_Symbol(password))
    {
        std::cout << "Password must contain at least 1 special symbol!\n";
        return false;
    }
    return true;
}

int SearchUsernameIndex(std::string &username)
{
    int userNumber = ErrorNumber;
    for (int i = 0; i < Users.size(); i++)
    {
        if (username == Users[i].username)
        {
            userNumber = i;
            break;
        }
    }
    return userNumber;
}

bool LoginUsername(int &userNumber)
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
    userNumber = SearchUsernameIndex(username);
    if (userNumber != ErrorNumber)
    {
        isUsernameSaved = true;
    }

    if (!isUsernameSaved)
    {
        std::cout << "Please enter an existing username!\n";
        return false;
    }
    return true;
}

size_t ReturnHash(std::string &password)
{
    std::hash<std::string> str_hash;
    std::size_t h_password = str_hash(password);
    return h_password;
}

bool LoginPassword(const int userNumber)
{
    std::cout << "Enter password: ";
    std::string password;
    std::getline(std::cin, password);

    if (!are_Password_Characters_OK(password))
    {
        std::cout << "Incorrect Input! Password contains forbidden characters!\n";
        return false;
    }

    std::size_t h_password = ReturnHash(password);

    if (h_password != Users[userNumber].password)
    {
        std::cout << "Password is incorrect! Try again!\n";
        return false;
    }

    return true;
}

User Login()
{
    int userNumber = ErrorNumber;

    bool Loop_Username = true;
    while (Loop_Username)
    {
        Loop_Username = !LoginUsername(userNumber);
    }

    bool Loop_Password = true;
    while (Loop_Password)
    {
        Loop_Password = !LoginPassword(userNumber);
    } //add exist if password is not guessed

    User user = Users[userNumber];
    return user;
}

bool RegisterUsername(std::string &username)
{
    std::cout << "Enter a new username: ";
    std::getline(std::cin, username);

    if (!is_Username_OK(username))
    {
        std::cout << "Please enter a valid username!\n";
        return false;
    }

    for (int i = 0; i < Users.size(); i++)
    {
        if (username == Users[i].username)
        {
            std::cout << "Username is already used!\n";
            return false;
        }
    }

    return true;
}

bool RegisterPassword(std::string &password)
{
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    if (!Password_Check(password))
    {
        return false;
    }

    return true;
}

bool RegisterPassword_Repeat(std::string &password)
{
    std::cout << "Repeat password: ";

    std::string rep_password;
    std::getline(std::cin, rep_password);

    if (rep_password != password)
    {
        std::cout << "Incorrect password confirmation!\n";
        return false;
    }
    return true;
}

bool DeletePassword_Repeat(std::size_t &h_password)
{
    std::cout << "Confirm password: ";

    std::string rep_password;
    std::getline(std::cin, rep_password);

    std::size_t rep_h_password = ReturnHash(rep_password);

    if (rep_h_password != h_password)
    {
        std::cout << "Incorrect password confirmation!\n";
        return false;
    }

    return true;
}

User Register()
{
    std::string username;
    std::string password;

    bool Loop_Username = true;
    while (Loop_Username)
    {
        Loop_Username = !RegisterUsername(username);
        if (Loop_Username)
        {
            username = "";
        }
    }

    bool Loop_Password = true;
    while (Loop_Password)
    {
        Loop_Password = !RegisterPassword(password);
        if (!Loop_Password)
        {
            Loop_Password = !RegisterPassword_Repeat(password);
        }
    }

    std::size_t h_password = ReturnHash(password);

    User user = {username, h_password};
    user.range = DetermineRange(user.level);
    Users.push_back(user);

    return user;
}

bool DeleteAccount(User &aUser)
{
    bool isIn = DeletePassword_Repeat(aUser.password);
    int userNumber = ErrorNumber;
    if (isIn)
    {
        userNumber = SearchUsernameIndex(aUser.username);
        Users.erase(Users.begin() + userNumber);
        return true;
    }
    return false;
}

void ShowAccount(std::string &username)
{
    int userNumber = ErrorNumber;
    userNumber = SearchUsernameIndex(username);

    if (userNumber == ErrorNumber)
    {
        std::cout << "Player not found.\n";
        return;
    }

    std::cout << "Player ";
    std::cout << Users[userNumber].username;

    std::cout << " is range ";
    std::cout << Users[userNumber].range.first;
    std::cout << "-";
    std::cout << Users[userNumber].range.second;

    std::cout << ".\n";
}

std::string InputOtherPlayerUsername()
{
    std::cout << "Enter player username: ";

    std::string pl_username;
    std::getline(std::cin, pl_username);

    return pl_username;
}

void ShowAccountSearchTogether()
{
    std::string pl_username = InputOtherPlayerUsername();
    ShowAccount(pl_username);
}

void ShowAllBySameRangeWithoutYou(User &aUser)
{
    int userNumber = ErrorNumber;
    userNumber = SearchUsernameIndex(aUser.username);

    int countSameRange = 0;
    for (int i = 0; i < Users.size(); i++)
    {
        if (aUser.range == Users[i].range && userNumber != i)
        {
            ShowAccount(Users[i].username);
            countSameRange++;
        }
    }

    if (countSameRange == 0)
    {
        std::cout << "There are currently no players with the same range as you!\n";
    }
}

void UpdatePlayerInfo(User &aUser)
{
    int playerNumber = SearchUsernameIndex(aUser.username);

    Users[playerNumber].range = aUser.range;
    Users[playerNumber].level = aUser.level;
}

void DuelWin(User &Winner, User &Loser)
{
    if (Winner.level - Loser.level < 5)
    {
        Winner.level++;
        Winner.range = DetermineRange(Winner.level);
        UpdatePlayerInfo(Winner);

        if (Loser.level > 1)
        {
            Loser.level--;
            Loser.range = DetermineRange(Loser.level);
            UpdatePlayerInfo(Loser);
        }
    }
    std::cout << Winner.username << " won the Duel!\n";
}

void DuelLogic(User &Attacker, User &Defender)
{
    if (Attacker.level > Defender.level)
    {
        DuelWin(Attacker, Defender);
    }
    else if (Attacker.level == Defender.level)
    {
        DuelWin(Attacker, Defender);
    }
    else
    {
        DuelWin(Defender, Attacker);
    }
}

void Duel(User &aUser)
{
    std::cout << "You have choosen to Duel!\n";
    std::string enemy_username = InputOtherPlayerUsername();

    int enemyNumber = ErrorNumber;
    enemyNumber = SearchUsernameIndex(enemy_username);

    int playerNumber = SearchUsernameIndex(aUser.username);

    if (enemyNumber == playerNumber)
    {
        std::cout << "You can't Duel yourself, sire!\n";
        return;
    }

    if (enemyNumber == ErrorNumber)
    {
        std::cout << "There is no such player, sir!\n";
        return;
    }

    User Enemy = Users[enemyNumber];

    DuelLogic(aUser, Enemy);
}

bool UserMenuLogic(User &aUser)
{
    std::string UserMenuCommand;
    bool endUserMenu = false;
    do
    {
        std::cout << "You are level " << aUser.level;
        std::cout << ".\n";
        std::cout << "Choose one of the following options: ";

        std::getline(std::cin, UserMenuCommand);
        if (UserMenuCommand == "C")
        {
            bool isSuccessful = DeleteAccount(aUser);
            if (isSuccessful)
            {
                endUserMenu = true;
            }
        }
        if (UserMenuCommand == "F")
        {
            ShowAccountSearchTogether();
        }
        if (UserMenuCommand == "S")
        {
            ShowAllBySameRangeWithoutYou(aUser);
        }
        if (UserMenuCommand == "D")
        {
            Duel(aUser);
        }
        if (UserMenuCommand == "L")
        {
            endUserMenu = true;
        }
    } while (!endUserMenu);
    return endUserMenu;
}

bool MainMenuLogic(User &aUser)
{
    std::string HomeMenuCommand;
    bool endProgram = false;
    do
    {
        std::cout << "Choose a command: ";
        std::getline(std::cin, HomeMenuCommand);
        if (HomeMenuCommand == "L")
        {
            aUser = Login();
            UserMenuLogic(aUser);
        }
        if (HomeMenuCommand == "R")
        {
            aUser = Register();
            UserMenuLogic(aUser);
        }
        if (HomeMenuCommand == "Q")
        {
            endProgram = true;
        }
    } while (!endProgram);
    return endProgram;
}

int main()
{
    LoadProfiles();
    User aUser;
    MainMenuLogic(aUser);


    return 0;
}
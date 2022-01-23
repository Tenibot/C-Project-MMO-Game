#include <iostream>
#include <vector>
#include <string>

#include <fstream>

#include <utility>
#include <functional>

#define ErrorNumber -1
#define FileDataChar ':'

#define Main_Command_Quit "Q"
#define Main_Command_Login "L"
#define Main_Command_Register "R"

#define User_Command_Close "C"
#define User_Command_Duel "D"
#define User_Command_Find "F"
#define User_Command_Logout "L"
#define User_Command_Suggest "S"
#define User_Command_Help "H"

struct User
{
    std::string username;
    std::size_t password;
    int level = 1;
    std::pair<int, int> range;
};

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

T ConvertTo(const std::string &text)
{
    T result = 0;
    for (int i = 0; i < text.size(); i++)
    {
        result *= 10;
        result += text[i] - '0';
    }
    return result;
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

bool is_Input_size_OK(const std::string &input)
{
    const int min_input_size = 5;
    if (input.size() < min_input_size)
    {
        return false;
    }
    return true;
}

bool is_Username_OK(const std::string &username)
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

bool are_Password_Characters_OK(const std::string &password)
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

bool String_Contains_UpperCase(const std::string &str)
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

bool String_Contains_LowerCase(const std::string &str)
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

bool String_Contains_Symbol(const std::string &str)
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

bool String_Contains_Digit(const std::string &str)
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

bool Check_Only_Digits(const std::string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (!isLetter_Digit(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool Check_OnlyTwo_Colons(const std::string &str)
{
    int count_colons = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == FileDataChar)
        {
            count_colons++;
        }
    }

    if (count_colons == 2)
    {
        return true;
    }
    return false;
}

bool CheckDublicateProfile(const std::string username, const std::vector<User> &Users)
{
    for (int i = 0; i < Users.size(); i++)
    {
        if (username == Users[i].username)
        {
            return false;
        }
    }
    return true;
}

std::vector<User> LoadProfiles()
{
    std::vector<User> Users;

    std::fstream usersFile;
    usersFile.open("users.txt", std::fstream::in);

    std::string userLine;

    std::string username;
    std::string password;
    std::string level;

    if (usersFile.is_open() == false)
    {
        usersFile.open("users.txt", std::fstream::out);
    }
    else
    {
        while (std::getline(usersFile, userLine))
        {
            if (!Check_OnlyTwo_Colons(userLine))
            {
                continue;
            }

            int i = 0;
            while (i < userLine.size() && userLine[i] != FileDataChar)
            {
                username += userLine[i++];
            }
            i++;
            while (i < userLine.size() && userLine[i] != FileDataChar)
            {
                password += userLine[i++];
            }
            i++;
            while (i < userLine.size())
            {
                level += userLine[i++];
            }
            i++;

            if (Check_Only_Digits(level) && Check_Only_Digits(password) && is_Username_OK(username) && CheckDublicateProfile(username, Users))
            {
                int n_level;
                n_level = ConvertTo<int>(level);

                std::pair<int, int> range = DetermineRange(n_level);

                std::size_t n_password = ConvertTo<std::size_t>(password);

                User aUser = {username, n_password, n_level, range};
                Users.push_back(aUser);
            }

            username = "";
            password = "";
            level = "";
        }
    }
    usersFile.close();

    return Users;
}

void SaveFile(const std::vector<User> &Users)
{
    std::fstream usersFile;
    usersFile.open("users.txt", std::fstream::out);

    std::string userLine;

    if (usersFile.is_open() == false)
    {
        std::cerr << "Failed to open file.\n";
    }
    else
    {
        for (int i = 0; i < Users.size(); i++)
        {
            usersFile << Users[i].username << FileDataChar;
            usersFile << Users[i].password << FileDataChar;
            usersFile << Users[i].level << "\n";
        }
        usersFile.close();
    }
}

bool Password_Check(const std::string &password)
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

int SearchUsernameIndex(const std::string &username, const std::vector<User> &Users)
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

//changes the userNumber
bool LoginUsername(int &userNumber, const std::vector<User> &Users)
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
    userNumber = SearchUsernameIndex(username, Users);
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

std::size_t ReturnHash(const std::string &password)
{
    std::hash<std::string> str_hash;
    std::size_t h_password = str_hash(password);
    return h_password;
}

bool LoginPassword(const int userNumber, const std::vector<User> &Users)
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

int Login(const std::vector<User> &Users)
{
    int userNumber = ErrorNumber;

    bool Loop_Username = true;

    int loops = 0;
    const int loops_Limit = 3;

    while (Loop_Username)
    {
        loops++;
        if (loops > loops_Limit)
        {
            return ErrorNumber;
        }
        Loop_Username = !LoginUsername(userNumber, Users);
    }

    loops = 0;

    bool Loop_Password = true;
    while (Loop_Password)
    {
        loops++;
        if (loops > loops_Limit)
        {
            return ErrorNumber;
        }
        Loop_Password = !LoginPassword(userNumber, Users);
    }

    return userNumber;
}

bool RegisterUsername(std::string &username, const std::vector<User> &Users)
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

bool RegisterPassword_Repeat(const std::string &password)
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

bool DeletePassword_Repeat(const std::size_t &h_password)
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

User Register(std::vector<User> &Users)
{
    std::string username;
    std::string password;

    bool Loop_Username = true;
    while (Loop_Username)
    {
        Loop_Username = !RegisterUsername(username, Users);
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

bool DeleteAccount(const User &aUser, std::vector<User> &Users)
{
    bool isIn = DeletePassword_Repeat(aUser.password);
    int userNumber = ErrorNumber;
    if (isIn)
    {
        userNumber = SearchUsernameIndex(aUser.username, Users);
        Users.erase(Users.begin() + userNumber);
        return true;
    }
    return false;
}

void ShowAccount(const std::string &username, const std::vector<User> &Users)
{
    int userNumber = ErrorNumber;
    userNumber = SearchUsernameIndex(username, Users);

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

void ShowAccountSearchTogether(const std::vector<User> &Users)
{
    std::string pl_username = InputOtherPlayerUsername();
    ShowAccount(pl_username, Users);
}

void ShowAllBySameRangeWithoutYou(const User &aUser, const std::vector<User> &Users)
{
    int userNumber = ErrorNumber;
    userNumber = SearchUsernameIndex(aUser.username, Users);

    int countSameRange = 0;
    for (int i = 0; i < Users.size(); i++)
    {
        if (aUser.range == Users[i].range && userNumber != i)
        {
            ShowAccount(Users[i].username, Users);
            countSameRange++;
        }
    }

    if (countSameRange == 0)
    {
        std::cout << "There are currently no players with the same range as you!\n";
    }
}

void UpdatePlayerInfo(const User &aUser, std::vector<User> &Users)
{
    int playerNumber = SearchUsernameIndex(aUser.username, Users);

    Users[playerNumber].range = aUser.range;
    Users[playerNumber].level = aUser.level;
}

void DuelWin(User &Winner, User &Loser, std::vector<User> &Users)
{
    if (Winner.level - Loser.level < 5)
    {
        Winner.level++;
        Winner.range = DetermineRange(Winner.level);
        UpdatePlayerInfo(Winner, Users);

        if (Loser.level > 1)
        {
            Loser.level--;
            Loser.range = DetermineRange(Loser.level);
            UpdatePlayerInfo(Loser, Users);
        }
    }
    std::cout << Winner.username << " won the Duel!\n";
}

void DuelLogic(User &Attacker, User &Defender, std::vector<User> &Users)
{
    if (Attacker.level > Defender.level)
    {
        DuelWin(Attacker, Defender, Users);
    }
    else if (Attacker.level == Defender.level)
    {
        DuelWin(Attacker, Defender, Users);
    }
    else
    {
        DuelWin(Defender, Attacker, Users);
    }
}

void Duel(User &aUser, std::vector<User> &Users)
{
    std::cout << "You have choosen to Duel!\n";
    std::string enemy_username = InputOtherPlayerUsername();

    int enemyNumber = ErrorNumber;
    enemyNumber = SearchUsernameIndex(enemy_username, Users);

    int playerNumber = SearchUsernameIndex(aUser.username, Users);

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

    DuelLogic(aUser, Enemy, Users);
}

void HelpMainMenu()
{
    std::cout << "\nShowing a list of all possible commands:\n";
    std::cout << "Login - " << Main_Command_Login << "\n";
    std::cout << "Register - " << Main_Command_Register << "\n";
    std::cout << "Quit - " << Main_Command_Quit << "\n";
}

void HelpUserMenu()
{
    std::cout << "\n";
    std::cout << User_Command_Duel << " - Duel\n";
    std::cout << User_Command_Find << " - Find\n";
    std::cout << User_Command_Suggest << " - Suggest\n";
    std::cout << User_Command_Logout << " - Logout\n";
    std::cout << User_Command_Close << " - Close account\n";
}

bool UserMenuLogic(User &aUser, std::vector<User> &Users)
{
    std::string UserMenuCommand;
    bool endUserMenu = false;
    HelpUserMenu();
    do
    {
        std::cout << "\nYou are level " << aUser.level << ".\n";
        std::cout << "Choose one of the following options: ";

        std::getline(std::cin, UserMenuCommand);
        if (UserMenuCommand == User_Command_Close)
        {
            bool isSuccessful = DeleteAccount(aUser, Users);
            if (isSuccessful)
            {
                endUserMenu = true;
            }
        }
        if (UserMenuCommand == User_Command_Find)
        {
            ShowAccountSearchTogether(Users);
        }
        if (UserMenuCommand == User_Command_Suggest)
        {
            ShowAllBySameRangeWithoutYou(aUser, Users);
        }
        if (UserMenuCommand == User_Command_Duel)
        {
            Duel(aUser, Users);
        }
        if (UserMenuCommand == User_Command_Help)
        {
            HelpUserMenu();
        }
        if (UserMenuCommand == User_Command_Logout)
        {
            endUserMenu = true;
        }
    } while (!endUserMenu);
    return endUserMenu;
}

void MainMenuLogic(std::vector<User> Users, User &aUser)
{
    std::string MainMenuCommand;
    bool endProgram = false;

    do
    {
        HelpMainMenu();
        std::cout << "Choose a command: ";
        std::getline(std::cin, MainMenuCommand);
        if (MainMenuCommand == Main_Command_Login)
        {
            int User_Index = Login(Users);
            if (User_Index == ErrorNumber)
            {
                std::cout << "Login was cancelled!\n";
                continue;
            }
            aUser = Users[User_Index];
            UserMenuLogic(aUser, Users);
        }
        if (MainMenuCommand == Main_Command_Register)
        {
            aUser = Register(Users);
            UserMenuLogic(aUser, Users);
        }
        if (MainMenuCommand == Main_Command_Quit)
        {
            endProgram = true;
            SaveFile(Users);
        }
    } while (!endProgram);
    return;
}

int main()
{
    std::vector<User> Users = LoadProfiles();
    User aUser;

    MainMenuLogic(Users, aUser);

    return 0;
}
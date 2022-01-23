/**
*  
* Solution to course project # 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Teodor Kostadinov
* @idnumber 4MI0600097
* @compiler GCC
*
* <header file with helper functions>
*
*/

#include <string>

#include <iostream>

#include <vector>

#include <fstream>

#include <utility>

#include <functional>

#define FileDataChar ':'

#define min_input_size 5

template <typename T>

T ConvertTo(const std::string &text);

bool isLetter_UpperCase(const char letter);

bool isLetter_LowerCase(const char letter);

bool isLetter_Digit(const char letter);

bool isLetter_Symbol(const char letter);

bool String_Contains_UpperCase(const std::string &str);

bool String_Contains_LowerCase(const std::string &str);

bool String_Contains_Symbol(const std::string &str);

bool String_Contains_Digit(const std::string &str);

bool Check_Only_Digits(const std::string &str);

bool Check_OnlyTwo_Colons(const std::string &str);

std::size_t ReturnHash(const std::string &password);

bool is_Input_size_OK(const std::string &input);

bool is_Username_OK(const std::string &username);

bool are_Password_Characters_OK(const std::string &password);

#define ErrorNumber -1
#define Range_step 5

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

std::pair<int, int> DetermineRange(const int level);

bool CheckDublicateProfile(const std::string username, const std::vector<User> &Users);

std::vector<User> LoadProfiles();

void SaveFile(const std::vector<User> &Users);

bool Password_Check(const std::string &password);

int SearchUsernameIndex(const std::string &username, const std::vector<User> &Users);

bool LoginUsername(int &userNumber, const std::vector<User> &Users);

bool LoginPassword(const int userNumber, const std::vector<User> &Users);

int Login(const std::vector<User> &Users);

bool RegisterUsername(std::string &username, const std::vector<User> &Users);

bool RegisterPassword(std::string &password);

bool RegisterPassword_Repeat(const std::string &password);

bool DeletePassword_Repeat(const std::size_t &h_password);

User Register(std::vector<User> &Users);

bool DeleteAccount(const User &aUser, std::vector<User> &Users);

void ShowAccount(const std::string &username, const std::vector<User> &Users);

std::string InputOtherPlayerUsername();

void ShowAccountSearchTogether(const std::vector<User> &Users);

void ShowAllBySameRangeWithoutYou(const User &aUser, const std::vector<User> &Users);

void UpdatePlayerInfo(const User &aUser, std::vector<User> &Users);

void DuelWin(User &Winner, User &Loser, std::vector<User> &Users);

void DuelLogic(User &Attacker, User &Defender, std::vector<User> &Users);

void Duel(User &aUser, std::vector<User> &Users);

void HelpMainMenu();

void HelpUserMenu();

bool UserMenuLogic(User &aUser, std::vector<User> &Users);

void MainMenuLogic(std::vector<User> Users, User &aUser);
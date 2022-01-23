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
* <main file>
*
*/

#include <iostream>
#include "functions.h"

int main()
{
    std::vector<User> Users = LoadProfiles();
    User aUser;

    MainMenuLogic(Users, aUser);

    return 0;
}
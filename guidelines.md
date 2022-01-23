
# How does the program work? #

## Database ##
The program starts by accessing the ***database*** - *users.txt* file.

The data format in *users.txt* is *username:hashed_password:level*.
All the data from *users.txt* file gets put in vector Users.
It serves the purpose of our database now.

All invalid entries do not get loaded and later get deleted from the txt file.
This includes invalid:
 - *username* - has a character different from the Latin letters *a* to *z*, and *A* to *Z* or a number. This includes space, underscore, etc. Also duplicate  username values get skipped.
 - *password* - has a character that is not a number. Password is saved hashed.
 - *level* - has a character that is not a number.
 - *formatting* - each line should consist of only two colons, which separate username, password and level.

If the file does not exist, it gets created (empty).


## Main Menu ##
The program for users starts in ***Main Menu***.
The user has 3 options:\
Pressing:
- **L** - allows the user to Login.
  - The user is asked to enter his username.
  - The username should consist of only *Latin letters* and *digits*.
  - If the user inputs invalid username, or one that does not exist, more than *3 times* the Login gets cancelled. This prevents an infinite loop in a program with no users or forgotten username.
  - Then the user is asked to enter his password.
  - If the password is incorrect or consists of forbidden characters (only *Latin letters*, *digits* and *special symbols !@#$%^&\** are allowed) the user is asked to enter again the correct one.
  - After *3* unsuccessful tries the login gets cancelled. This prevents forgotten password or wrong username.

- **R** - allows the user to create a new account.
  - The user is asked to enter a new username, that does not exist in the database.
  - Then a new password is entered.
  - After that the password must be repeated.
  - If the confirmation is failed, the user is asked to enter his wanted password again. This process prevents mistakes done while entering a new password and the following endless loop.
  - The password must be no less than *5 characters*.
  - It must also contain at least *1 digit*, *1 upper case letter*, *1 lower case letter* and *1 of the special symbols*.
  - If one or more criteria are not fulfilled a message is shown showing the first unfulfilled criterion by the given order.
  - The process of registration ends only by successfully creating a new account - entered username, password and confirmation.

 - **Q** - quits the program.
   - All changes get saved on the txt file. This includes deleted accounts, created new accounts, changes in level.
   - All invalid accounts found during the loading are not saved. As a result, the file consist of only valid entries now.

Choosing any other "command" does not do anything.
Every time any command is entered a list of all three possible commands is shown.


## User Menu ##
After Login or Register the User access the ***User Menu*** with all his account information.

The user has 5 valid commands shown on the screen:
 - **C** - allows the user to close his account after a password confirmation.
   - If the password confirmation is unsuccessful the closing gets cancelled.
   - Successful confirmation leads to deleting all data of the account from the current database (the vector) and then from the file as well. This means that deleted account in the current session will not be accessible during the current session, nor after that.
   - After successful closing the user gets redirected to the *Main Menu* where he has the same options as before.
   - One can also create a new account with the same username as the deleted account, though the level will be reset to *1*, as any new account.

- **F** - allows the user to see the current range of any player (including himself).
  - The range is calculated by taking the two nearest numbers divisible by *5*.
  - A player *level 7* is *range 5-10*, and a player *level 10* is *range 10-15*. Players *level 1 to 4* are *range 0-5*.
  - If the player does not exist, a message is shown. Task is finished.

- **S** - shows all players with the same range as the user (excluding himself).
  - This helps the user choose his target for duel.
  - If no player has the same range, a message is shown. Task is finished.

- **D** - allows the user to start a duel with any other player (excluding himself).
  - User is asked to enter his chosen opponent's username.
  - A nonexistent username ends the task.
  - User is also not allowed to duel himself. In this case a message is shown and task finishes.
  - If another player's username is entered successfully, the duel is started.
  - A duel is decided by the players level.
  - The player with higher level wins the duel, or the one attacking (user), if the levels are identical.
  - If the level difference is *lower than 5*, the winner *level ups*, and the loser gets demoted by *1 level*.
  - A message shows who the winner is. Task ends. Levels and Ranges get updated.

 - **L** - user logs out of his account and is returned to the *Main Menu*.
   - There he has the option to login again, create a new account or end the program.
   - Logging out does not end the program.
   - The program is always ended from the *Main Men*u by pressing *Q*.

 - **H** - a secret command showing the list with all 5 commands.
   - All commands with their representing letters are shown only once when the user is transferred in the *User Menu*.
   - This gives the user the option to see them again.

After each command a message is shown showing the user current level.

# NYCU_Programming_2021_Fall

## HW1 
There are various psychological tests available on the internet, and one of the categories is about mysterious numbers. Each person has their own number, and based on this number, the test can classify people into several categories. The most common source of this number is the birthdate.

Let's try to create a simplified version of a psychological test! The user and their partner will input their birthdate (year, month, and day). The program will sum up each digit, for example, for a couple born on January 1, 2000, and January 2, 2000:
2 + 0 + 0 + 0 + 0 + 1 + 0 + 1 + 2 + 0 + 0 + 0 + 0 + 1 + 0 + 2 = 9
If the obtained number is greater than two digits, repeat the process until only a single digit from 0 to 9 remains. For a couple born on January 1, 2000, and March 2, 2000, the process is as follows:
2 + 0 + 0 + 0 + 0 + 1 + 0 + 1 + 2 + 0 + 0 + 0 + 0 + 3 + 0 + 2 = 11, 1 + 1 = 2

After obtaining the number, group them in pairs and tell the user to which category they belong. For example:
Number Category
0, 1 Elan Yecka & Mikasa Ackerman
2, 3 Subaru Kamui & Emilia
4, 5 Kei Asai & Harukasora Kasuga
6, 7 Batman & Robin
8, 9 Trump & Xi^

You can also specify the category names yourself. The program requires input of two sets of birthdates in the Gregorian calendar and outputs the category name you specified.

Example:
Input:
20000101 20000102
Output:
Trump & Xi

## HW2


## Final Project
Program Purpose

+ Design a drink ordering system for "可不可" (a drink shop).
Integrate this semester's programming topics, such as the XAXB game, Sudoku game, and a chat room, into the system.
This program will serve as an assessment of all the programming syntax, functions, and algorithms taught during the semester.
Consumer Main System Functions

+ Develop the main system and six major functions.
Main system functions include reading user database, user login, displaying the main screen, and a main menu with seven major features.
Implement user interface handling for navigation.
Update user data before exiting the system.
Function 1: Order

+ Display the drink shop menu and allow customers to select drinks, quantities, and customization options.
Validate if the user has enough balance for the order.
Save order details to a file.
Function 2: Check Orders

+ Read and display existing orders from a file.
Function 3: Modify Member Data

+ Allow users to change their passwords.
Password input should be masked.
Ensure password input validation.
Function 4: Chat Room

+ Read messages from a file and allow users to post messages under their usernames.
Function 5: Play Sudoku

+ Play a Sudoku game, and if successfully completed, earn $20 of balance.
Function 6: Play XAXB Game

+ Play a game with the computer and keep a record of wins and ties. Earning balance based on outcomes.
Function 0: Exit System

+ Shop Owner Login Main System Functions

+ Shop owner login with special privileges.
Options to view orders and top up customers' balances.
+ Additional Creative Features
Encourage students to come up with their own creative features.

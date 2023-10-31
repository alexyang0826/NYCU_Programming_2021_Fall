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

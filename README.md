# SCALA_Interview_Test
Test challenge to code solution in C++ to the given problem below: ------------------------------------------------------------------ 
Four people come to a river in the night. There is a narrow bridge, but it can only hold two people at a time. They have one torch and, because it's night, the torch has to be used when crossing the bridge. Person A can cross the bridge in 1 minute, B in 2 minutes, C in 5 minutes, and D in 10 minutes. When two people cross the bridge together, they must move at the slower person's pace.  
Write a program in C++ that determines the fastest time they can cross the bridge. The entry to the program will be a yaml file that describes the speeds of each Person. In this situation there are 4 people but your program should assume any number of people can be passed in. 
You will be judged on the following:    1. Strategy(s) - there are several ways to solve the problem, you can provide more than one. The goal is to show us how you think.  2. Architecture - we want to see how well you architect solutions to complex problems  3. Standards and best practices  4. Explanation - as a C++ thought leader in the organization you will be working with and mentoring other engineers. How well you can describe and explain your solution is very important.
=====================================================================================
My Solution Information 
=====================================================================================
There is only one torch with them and the bridge cannot be crossed without the torch. There cannot
be more than two persons on the bridge at any time, and when two people cross the bridge together,
they must move at the slower person’s pace (time speed in minutes to crossing the bridge).

The Strategy is to Calculate the total time it takes all persons to cross the bridge in a number of minutes.

---------  The Solution: -----------------------------------------
- First, persons A and B cross the bridge to the right side. Person A comes back to the left side
to exchange the torch. The time taken will be 3 minutes. Now person B is on the other (Right) side.

- Second, persons C and D cross the bridge to the right side with the torch. Person B comes back
to the left side with the torch. The time taken for this will be 10 + 2 minutes ( equal to 12 min.).
Now persons C and D are on the other (Right) side.

- Third, persons A and B cross the bridge to the right side with the torch. The time taken is
2 minutes. All the persons involved are on the other (right) side of the bridge.

- Finally, the Total time that was spent is: 3 + 12 + 2 = 17 minutes.

  -----------------------------
I used a CSV file as my input instead of a Yaml file. My program would read the CSV file into my
program through opening the file for reading through Class instantiation , a Vector of Vectors
container, and a CSVReader Class with a defined methods and data variables. Also, I used 2 functions to use
a global variable of an integer array "dp[i][j]".

- People will cross the river and reached the right side then only the
     fastest people ( smallest integer) will come back to the left side
- Person can only be present either left side or right side of the bridge. Thus, if we maintain
     the left mask, then right mask can easily be calculated by setting the bits ‘1’ which is
     not present in the left mask. For instance, Right_mask = ((2n) – 1) XOR (left_mask).
- Any person can easily be represented by bitmask(usually called as ‘mask’). When ith bit
   of ‘mask’ is set, that means that person is present at left side of the bridge otherwise
   it would be present at right side of bridge.
   
- For instance, let the mask of 6 people is 100101, which represents the person 1, 4, 6
      are present at left side of bridge and the person 2, 3 and 5 are present at the right
      side of the bridge.
- NOTE: The Bitwise XOR will take a pair of bits from each position, and if both the bits
  are different, the result on that position will be '1'. If both bits are same, then the
  result on that position is '0'.

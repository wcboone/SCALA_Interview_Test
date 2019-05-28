
/**********************************************
 *  Filename: CalcBridgeProblem.cc
 *
 * Problem to resolve:
- People will cross the river and reached the right side then only the
     fastest people ( smallest integer) will come back to the left side
- A Person can only be present on either left side or right side of the bridge. Thus, if we maintain
     the left mask, then right mask can easily be calculated by setting the bits ‘1’ which is
     not present in the left mask. For instance, Right_mask = ((2n) – 1) XOR (left_mask).
- Any person can easily be represented by bitmask(usually called as ‘mask’). When ith bit
   of ‘mask’ is set, that means that person is present at left side of the bridge otherwise
   it would be present at right side of bridge.
=>>> For instance, let the mask of 6 people is 100101, which represents the person 1, 4, 6
      are present at left side of bridge and the person 2, 3 and 5 are present at the right
      side of the bridge.
NOTE: The Bitwise XOR will take a pair of bits from each position, and if both the bits
  are different, the result on that position will be '1'. If both bits are same, then the
  result on that position is '0'.

   COMPILE it using:
     $ g++ -g -Wall -std=c++11 -I. CalcBridgeProblem.cc CSVReader.cc CSVReader.h -o  calcBP

   INPUT File:  input_file.csv

****************
Purpose: C++ program to find minimum time required to send people from one side
         to the other side of a bridge with a torch.
***************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <bits/stdc++.h>
#include <CSVReader.h>

using namespace std;

/****
 * NOTE: Regarding the Global integer array of "..int dp[2^20][2]; ".
 * The description of this array's indexes of dp[i][j] are:
   - Where 'i' denotes mask in which 'set bits' denotes total people standing at left side
     of bridge and 'j' denotes the turn that represent on which side we have to send people
     either from left to right(set to 0) or from right to left(set to 1).
   - In this particular Array declaration, the 'i' denotes a mask of set bits of @ 20 persons on 
     the left side of the bridge invloved with the 'j' denoting a max. of 2 turn positions 
     which indicates which side we have to send people going from the Left to Right for 0 setting
     and from Right to Left for the setting of 1. 
   - For instance, say we have 6 persons involved in the Bridge crossing,
      let the mask of the 6 people be a bit setting of 100101, which reprsents the
      person 1, 4, 6 are present at left side of bridge and the person 2, 3 and 5
      are present at the right side of the bridge.
*************************/
int dp[1 << 20][2];


/*****************************************
 * Function to Calculate total time required to send people to other side of bridge
*******************************************************/
int findMinTime(int leftmask, bool turn, int arr[], int& n)
{

    // If all people has been transfered
    if (!leftmask)
        return 0;

    int& res = dp[leftmask][turn];

    // If we already have solved this subproblem,
    // return the answer.
    if (~res)
        return res;

    // Calculate mask of right side of people
    int rightmask = ((1 << n) - 1) ^ leftmask;

    /* if turn == 1 means currently people are at
     right side, thus we need to transfer
     people to the left side */
    if (turn == 1) {
        int minRow = INT_MAX, person;
        for (int i = 0; i < n; ++i) {

            // Select one people whose time is less
            // among all others present at right
            // side
            if (rightmask & (1 << i)) {
                if (minRow > arr[i]) {
                    person = i;
                    minRow = arr[i];
                }
            }
        }

        // Add that person to answer and recurse for next turn
        // after initializing that person at left side
        res = arr[person] + findMinTime(leftmask | (1 << person),
                                        turn ^ 1, arr, n);
    }
    else {

        // __builtin_popcount() is inbuilt gcc function
        // which will count total set bits in 'leftmask'
        if (__builtin_popcount(leftmask) == 1) {
            for (int i = 0; i < n; ++i) {

                // Since one person is present at left
                // side, thus return that person only
                if (leftmask & (1 << i)) {
                    res = arr[i];
                    break;
                }
            }
        }
        else {

            // try for every pair of people by
            // sending them to right side

            // Initialize the result with maximum value
            res = INT_MAX;
            for (int i = 0; i < n; ++i) {

                // If ith person is not present then
                // skip the rest loop
                if (!(leftmask & (1 << i)))
                    continue;

                for (int j = i + 1; j < n; ++j) {
                    if (leftmask & (1 << j)) {

                        // Find maximum integer(slowest
                        // person's time)
                        int val = max(arr[i], arr[j]);

                        // Recurse for other people after un-setting
                        // the ith and jth bit of left-mask
                        val += findMinTime(leftmask ^ (1 << i) ^ (1 << j),
                                                       turn ^ 1, arr, n);
                        // Find minimum answer among
                        // all chosen values
                        res = min(res, val);
                    }
                }
            }
        }
    }
    return res;
}


// *****************************************
// Function to find minimum time
//
int findTime(int arr[], int n)
{
    // Find the mask of 'n' peoples
    int mask = (1 << n) - 1;

    // Initialize all entries in dp as -1
    memset(dp, -1, sizeof(dp));

    return findMinTime(mask, 0, arr, n);
}

//*****************
//  MAIN() Driver 
//************************
int main()
{

	// Creating an object of CSVReader Class
        CSVReader reader("input_file.csv");

        // Get the data from CSV File
        std::vector<std::vector<std::string> > dataList = reader.readData();

        // Initialize Total persons involved and declare array for keeping their times`
	//  from the Vector of Vectors in "dataList" object
        int persons = dataList.size();
        int person_time[persons];

        // Loop to Assign & Print the content of vector records of dataList by ;
	//  vector "vec" ...
        int i = 0;
        for(std::vector<std::string> vec : dataList)
        {
                person_time[i] = stoi(vec[1]);
                std::cout << "person : person_time = " << vec[0] << ":"<< vec[1] << std::endl;
                i++;
        }

        int n = sizeof(person_time)/sizeof(person_time[0]);
	cout << "\n Total persons involved = " << n << endl;
        cout << " Total time to cross bridge = " << findTime(person_time, n) << endl << endl;

	return 0;

}

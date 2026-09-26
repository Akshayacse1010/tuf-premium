/*
    Problem: Sort Colors (LC 75)

    Given an array containing only 0, 1, and 2,
    sort it in-place without using a sorting algorithm.

    Approach: Dutch National Flag Algorithm
    ---------------------------------------------------------
    Maintain 3 pointers:

        low  -> boundary for 0s
        mid  -> current element
        high -> boundary for 2s

    Regions:
        [0 ... low-1]     -> 0s (sorted)
        [low ... mid-1]   -> 1s (sorted)
        [mid ... high]    -> unknown
        [high+1 ... n-1]  -> 2s (sorted)

    Algorithm:
    - nums[mid] == 0:
        Swap nums[mid] and nums[low].
        low++, mid++.

    - nums[mid] == 1:
        Already in the correct region.
        mid++.

    - nums[mid] == 2:
        Swap nums[mid] and nums[high].
        high--.
        Do NOT increment mid; the swapped element is unprocessed.

    Time Complexity: O(N)
        - Each pointer moves only in one direction.

    Space Complexity: O(1)
        - In-place sorting using constant extra space.

    Key Mistake:
    - After swapping 2 with nums[high], do not move mid.
    - The incoming element could be 0, 1, or 2.
*/

#include <vector>
using namespace std;

class Solution {
public:
    void swap(int a, int b, vector<int>& nums) {
        int temp = nums[a];
        nums[a] = nums[b];
        nums[b] = temp;
    }

    void sortZeroOneTwo(vector<int>& nums) {
        int low = 0;
        int mid = 0;
        int high = nums.size() - 1;

        while(mid <= high) {
            if(nums[mid] == 0) {
                swap(mid, low, nums);
                low++;
                mid++;
            }
            else if(nums[mid] == 2) {
                swap(mid, high, nums);
                high--;
            }
            else {
                mid++;
            }
        }
    }
};


/*
    VISUALIZATION — POINTER-BASED DRY RUN
    =========================================================

    Input: [2, 0, 2, 1, 1, 0]

    → Step 1: mid = 0, nums[mid] = 2

       L/M                 H
        ↓                  ↓
       [2,  0,  2,  1,  1,  0]

       Swap mid and high; high--
       Array: [0, 0, 2, 1, 1, 2]

       Do NOT increment mid.


    → Step 2: mid = 0, nums[mid] = 0

       L/M             H
        ↓              ↓
       [0,  0,  2,  1,  1,  2]

       Swap mid and low; low++, mid++
       Array unchanged.


    → Step 3: mid = 1, nums[mid] = 0

           L/M         H
            ↓          ↓
       [0,  0,  2,  1,  1,  2]

       Swap mid and low; low++, mid++
       Array unchanged.


    → Step 4: mid = 2, nums[mid] = 2

                   M/H
                    ↓
       [0,  0,  2,  1,  1,  2]

       Swap mid and high; high--
       Array: [0, 0, 1, 1, 2, 2]

       Do NOT increment mid.


    → Step 5: mid = 2, nums[mid] = 1

                   M   H
                   ↓   ↓
       [0,  0,  1,  1,  2,  2]

       nums[mid] == 1 -> mid++


    → Step 6: mid = 3, nums[mid] = 1

                       M/H
                        ↓
       [0,  0,  1,  1,  2,  2]

       nums[mid] == 1 -> mid++

       Now mid > high -> STOP.

    Final Array: [0, 0, 1, 1, 2, 2]

    =========================================================

    CORE TAKEAWAY:
    - 0 -> swap with low; increment low and mid.
    - 1 -> increment mid.
    - 2 -> swap with high; decrement high ONLY.
    - Stop when mid > high.

    Pattern: Three Pointers / In-place Partitioning
*/
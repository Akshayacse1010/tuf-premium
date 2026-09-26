/*
    Problem: Majority Element (LC 169)

    Given an array nums of size n, find the element that appears
    more than floor(n/2) times.

    Approach: Boyer-Moore Voting Algorithm
    ---------------------------------------------------------
    - Maintain a candidate (ele) and a counter (cnt).
    - If current element == candidate -> increment cnt.
    - Otherwise -> decrement cnt.
    - If cnt becomes negative, reset candidate to current element
      and set cnt = 1.

    Key Intuition:
    - Different elements cancel each other out.
    - The majority element occurs more than all other elements
      combined, so it survives the cancellation process.

    Time Complexity: O(N)
        - Single traversal of the array.

    Space Complexity: O(1)
        - Only candidate and counter are maintained.

    Important:
    - The problem guarantees that a majority element exists.
    - If no majority is guaranteed, verify the candidate in a
      second pass.

    Note:
    - This implementation resets when cnt < 0.
    - The standard implementation resets when cnt == 0,
      before processing the current element.
    - Both approaches are valid.
*/

#include <vector>
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ele = nums[0], cnt = 1;

        for(int i = 1; i < nums.size(); i++) {
            if(ele != nums[i]) {
                cnt--;
            }
            else {
                cnt++;
            }

            if(cnt < 0) {
                cnt = 1;
                ele = nums[i];
            }
        }

        return ele;
    }
};


/*
    VISUALIZATION
    =========================================================

    Input: [2, 2, 1, 1, 1, 2, 2]

    Initial:
        ele = 2, cnt = 1

    i = 1 -> nums[i] = 2
        Same as candidate -> cnt = 2

    i = 2 -> nums[i] = 1
        Different -> cnt = 1

    i = 3 -> nums[i] = 1
        Different -> cnt = 0

    i = 4 -> nums[i] = 1
        Different -> cnt = -1
        Reset: ele = 1, cnt = 1

    i = 5 -> nums[i] = 2
        Different -> cnt = 0

    i = 6 -> nums[i] = 2
        Different -> cnt = -1
        Reset: ele = 2, cnt = 1

    Final Answer: 2

    =========================================================

    PATTERN: Greedy / Array / Voting Algorithm

    WHEN TO USE:
    - Find the element occurring more than N/2 times.
    - Solve in O(N) time and O(1) auxiliary space.

    CORE TAKEAWAY:
    Pairwise cancellation eliminates non-majority elements.
    The majority element survives because it occurs more
    frequently than all other elements combined.
*/
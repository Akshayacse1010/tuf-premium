/*
    Problem: Maximum Product Subarray (LC 152)

    Given an integer array nums, find the contiguous subarray
    with the largest product and return that product.

    Approach: Prefix + Suffix Product
    ---------------------------------------------------------
    - Traverse the array from both directions simultaneously.
    - Maintain prefixProduct (left to right).
    - Maintain suffixProduct (right to left).
    - Update maxproduct using both products at every index.
    - When a zero is encountered, reset that direction's
      product to 1.

    Key Intuition:
    - A negative number can turn a small product into a large
      positive product when multiplied by another negative.
    - The maximum product may lie on either side of a negative.
    - Traversing from both ends captures these possibilities.
    - Zero breaks a subarray, so restart after it.

    Time Complexity: O(N)
        - One traversal, processing both directions.

    Space Complexity: O(1)
        - Only a few variables.

    Important:
    - Initialize maxproduct to INT_MIN to handle all-negative
      arrays and arrays containing a single negative number.
    - Reset prefix/suffix AFTER updating maxproduct.
    - Subarray must be contiguous.
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxproduct = INT_MIN;
        int prefixProduct = 1;
        int suffixProduct = 1;

        for(int i = 0; i < nums.size(); i++) {
            prefixProduct *= nums[i];
            suffixProduct *= nums[nums.size() - i - 1];

            maxproduct = max(prefixProduct, maxproduct);
            maxproduct = max(suffixProduct, maxproduct);

            if(nums[i] == 0) {
                prefixProduct = 1;
            }

            if(nums[nums.size() - i - 1] == 0) {
                suffixProduct = 1;
            }
        }

        return maxproduct;
    }
};


/*
    VISUALIZATION — PREFIX + SUFFIX POINTERS
    =========================================================

    Input: [-2, 3, -4]

    i = 0

          ↑
    nums = [-2,  3, -4]
    Prefix: -2
    Suffix: -4
    maxproduct = -2

    ---------------------------------------------------------

    i = 1

               ↑
    nums = [-2,  3, -4]
    Prefix: -2 * 3 = -6
    Suffix: -4 * 3 = -12
    maxproduct = -2

    ---------------------------------------------------------

    i = 2

                   ↑
    nums = [-2,  3, -4]
    Prefix: -6 * -4 = 24
    Suffix: -12 * -2 = 24
    maxproduct = 24

    Answer: 24
    Maximum Product Subarray: [-2, 3, -4]

    =========================================================

    ZERO RESET EXAMPLE
    ---------------------------------------------------------

    Input: [-2, 0, -1]

    i = 0
          ↑
    nums = [-2,  0, -1]
    Prefix = -2, Suffix = -1
    maxproduct = -1

    i = 1
               ↑
    nums = [-2,  0, -1]
    Prefix = 0, Suffix = 0
    maxproduct = 0
    → Both products reset to 1.

    i = 2
                   ↑
    nums = [-2,  0, -1]
    Prefix = -1, Suffix = -1
    maxproduct = 0

    Answer: 0

    =========================================================

    CORE TAKEAWAY:
    - Track products from BOTH directions.
    - Negative × negative can produce the maximum.
    - Zero breaks the product sequence → reset to 1.
    - Update the answer BEFORE resetting.
*/
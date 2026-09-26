/*
    Problem: Majority Element II (LC 229)

    Find all elements appearing MORE THAN floor(N/3) times.

    Key Observation:
    - At most 2 elements can appear more than N/3 times.
    - Use Extended Boyer-Moore Voting Algorithm.

    Algorithm:
    ---------------------------------------------------------
    1. Maintain 2 candidates (ele1, ele2) and their counts.
    2. If current element matches a candidate -> increment count.
    3. If a count is 0 -> assign current element as candidate.
    4. Otherwise -> decrement BOTH counts (cancellation).
    5. Second pass: count actual occurrences of both candidates.
    6. Return only candidates occurring more than N/3 times.

    Why 2 Candidates?
    - 3 elements appearing > N/3 times would occur > N times,
      which is impossible.

    Time Complexity: O(N)
        - First pass: O(N)
        - Verification pass: O(N)

    Space Complexity: O(1)
        - Only 2 candidates and 2 counters.

    Important:
    - Candidates from the first pass are NOT guaranteed answers.
    - Always verify their actual frequencies.
    - Strict condition: count > N/3, not count >= N/3.
*/

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> majorityElementTwo(vector<int>& nums) {
        int ele1 = INT_MIN, ele2 = INT_MIN;
        int count1 = 0, count2 = 0;
        int size = nums.size();

        // First pass: find potential candidates
        for(int i = 0; i < size; i++) {
            if(ele1 == nums[i]) {
                count1++;
            }
            else if(ele2 == nums[i]) {
                count2++;
            }
            else if(count1 == 0) {
                ele1 = nums[i];
                count1 = 1;
            }
            else if(count2 == 0) {
                ele2 = nums[i];
                count2 = 1;
            }
            else {
                count1--;
                count2--;
            }
        }

        // Second pass: verify candidates
        int countOfEle1 = 0, countOfEle2 = 0;

        for(int x : nums) {
            if(x == ele1) countOfEle1++;
            if(x == ele2) countOfEle2++;
        }

        vector<int> ans;

        if(countOfEle1 > size / 3)
            ans.push_back(ele1);

        if(countOfEle2 > size / 3 && ele2 != ele1)
            ans.push_back(ele2);

        return ans;
    }
};


/*
    VISUALIZATION — POINTER-BASED ARRAY DRY RUN
    =========================================================

    nums = [1, 1, 1, 3, 3, 2, 2, 2]

    Initial:
        ele1 = -, count1 = 0
        ele2 = -, count2 = 0

    → i = 0
          ↑
    nums = [1, 1, 1, 3, 3, 2, 2, 2]
    count1 == 0 -> ele1 = 1, count1 = 1

    → i = 1
             ↑
    nums = [1, 1, 1, 3, 3, 2, 2, 2]
    nums[i] == ele1 -> count1 = 2

    → i = 2
                ↑
    nums = [1, 1, 1, 3, 3, 2, 2, 2]
    nums[i] == ele1 -> count1 = 3

    → i = 3
                   ↑
    nums = [1, 1, 1, 3, 3, 2, 2, 2]
    count2 == 0 -> ele2 = 3, count2 = 1

    → i = 4
                      ↑
    nums = [1, 1, 1, 3, 3, 2, 2, 2]
    nums[i] == ele2 -> count2 = 2

    → i = 5
                         ↑
    nums = [1, 1, 1, 3, 3, 2, 2, 2]
    Matches neither candidate
    -> count1 = 2, count2 = 1

    → i = 6
                            ↑
    nums = [1, 1, 1, 3, 3, 2, 2, 2]
    Matches neither candidate
    -> count1 = 1, count2 = 0

    → i = 7
                               ↑
    nums = [1, 1, 1, 3, 3, 2, 2, 2]
    count2 == 0 -> ele2 = 2, count2 = 1

    Candidates: ele1 = 1, ele2 = 2

    =========================================================

    SECOND PASS — VERIFY CANDIDATES
    ---------------------------------------------------------

    nums = [1, 1, 1, 3, 3, 2, 2, 2]
             ↑
    Count occurrences of ele1 = 1 -> 3

    nums = [1, 1, 1, 3, 3, 2, 2, 2]
                               ↑
    Count occurrences of ele2 = 2 -> 3

    N = 8
    N / 3 = 2

    3 > 2 -> 1 is valid
    3 > 2 -> 2 is valid

    Answer: [1, 2]

    =========================================================

    CORE TAKEAWAY:
    - Two candidates represent the possible answers.
    - A different element cancels one vote from BOTH candidates.
    - The first pass finds candidates, not guaranteed answers.
    - The second pass confirms their actual frequencies.
*/
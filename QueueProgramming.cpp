#include <iostream>
#include <queue>
#include <vector>
#include <deque>
using namespace std;
int sumOfMaxSubarray(vector<int>& nums, int k) {
   // STUDENT ANSWER
   queue<int> res;
   for (int i = 0; i < k; i++) {
      if (!res.empty() && nums[i] > res.front()) {
         res.pop();
         res.push(nums[i]);
      }
      else if (res.empty()) {
         res.push(nums[i]);
      }
   }
   int sum = 0;
   sum += res.front();
   int n = nums.size();
   for (int i = k; i < n; i++) {
      if (nums[i] > res.front()) {
         res.pop();
         res.push(nums[i]);
      }
      sum += res.front();
   }
   return sum;
}
int main() {
   vector<int> nums {1, 2, 4, 3, 6};
   int k = 3;
   cout << sumOfMaxSubarray(nums, k);
   return 0;
}
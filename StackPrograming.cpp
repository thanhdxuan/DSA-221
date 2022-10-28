#include <stack>
#include <iostream>
#include <vector>
using namespace std;

int baseballScore(string ops){
/*TODO*/
   stack<long int> score;
   for (int i = 0; i < (int)ops.length(); i++) {
      if (isdigit((char)ops[i])) score.push(ops[i] - '0');
      switch (ops[i]) {
         case 'C':
            score.pop();
            break;
         case 'D':
            score.push(2 * score.top());
            break;
         case '+':
            int temp = score.top();
            score.pop();
            int sum = temp + score.top();
            score.push(temp);
            score.push(sum);
            break;
      }
   }
   int sum = 0;
   while (!score.empty()) {
      sum += score.top();
      score.pop();
   }
   return sum;
}
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n=nums.size();
        vector<int>ans(n,0);
        stack<int>s;
        for(int i=n-1;i>=0;i--) {
            s.push(nums[i]);
        }
        
        for(int i=n-1;i>=0;i--) {
            while(!s.empty() && nums[i]>=s.top()) s.pop();
            if(s.empty()) ans[i]=-1;
            else ans[i]=s.top();
            s.push(nums[i]);
        }
        return ans;
    }
vector<int> nextGreater(vector<int>& arr){
   vector<int> res;
   stack<int> rG;
   for (int i = 0; i < arr.size(); i++) {
      rG.push(arr[i]);
   }
   bool cond = false;
   int i = 0;
   while (true) {
      int rightVal = rG.top();
      if (i != 0) {
         rG.pop();
         if (rG.empty()) break;
         cond = rightVal > rG.top();
      }
      if (cond == false) res.push_back(-1);
      else res.push_back(rightVal);
      i++;
   }
   res = vector<int>(res.crbegin(), res.crend());
   return res;
}
int sumOfMaxSubarray(vector<int>& nums, int k) {
    // STUDENT ANSWER
    deque<int> temp(k);
    int i, n = nums.size();
    for (i = 0; i < k; ++i) {
        while ((!temp.empty()) && nums[i] >= nums[temp.back()]) {
            temp.pop_back();
        }
        temp.push_back(i);
    }
    int sum = 0;
    for (; i < n; ++i){
        sum += nums[temp.front()];
        while ((!temp.empty()) && temp.front() <= i - k) {
            temp.pop_front();
        }
        while ((!temp.empty()) && nums[i] >= nums[temp.back()]) {
            temp.pop_back();
        }
        temp.push_back(i);
    }
    sum += nums[temp.front()];
    return sum;
}
int main() {
   vector<int> nums {1, 2, 4, 3, 6};
   int k = 3;
   cout << sumOfMaxSubarray(nums, k);
   return 0;
}
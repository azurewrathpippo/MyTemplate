#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<string>

using namespace std;

class Solution
{
public:
    bool judgePoint24(vector<int>& nums)
    {
        sort(nums.begin(), nums.end());
        bool res = false;
        while (next_permutation(nums.begin(), nums.end()))
        {
            char op[3];
            for (int i = 0; i <= 3; ++i)
            {
                for (int j = 0; j <= 3; ++j)
                {
                    for (int k = 0; k <= 3; ++k)
                    {
                        op[0] = ops[i];
                        op[1] = ops[j];
                        op[2] = ops[k];
                        if (judge(nums[0], nums[1], nums[2], nums[3], op))
                        {
                            cout << nums[0] << nums[1] << nums[2] << nums[3] << endl;
                            cout << op[0] << op[1] << op[2] << endl;
                            cout << endl;
                            res = true;
                        }
                    }
                }
            }
        }
        return res;
    }

private:
    char ops[4] = {'+', '-', '*', '/'};
    bool judge(double n1, double n2, double n3, double n4, char op[3])
    {
        double t1, t2, t3;
        char op1 = op[0], op2 = op[1], op3 = op[2];

        //123
        t1 = cal(n1, n2, op1);
        t2 = cal(t1, n3, op2);
        t3 = cal(t2, n4, op3);
        if (eq(t3, 24.0))
        {
            return true;
        }

        //132
        t1 = cal(n1, n2, op1);
        t2 = cal(n3, n4, op3);
        t3 = cal(t1, t2, op2);
        if (eq(t3, 24.0))
        {
            return true;
        }

        //213
        t1 = cal(n2, n3, op2);
        t2 = cal(n1, t1, op1);
        t3 = cal(t2, n4, op3);
        if (eq(t3, 24.0))
        {
            return true;
        }

        //231
        t1 = cal(n2, n3, op2);
        t2 = cal(t1, n4, op3);
        t3 = cal(n1, t2, op1);
        if (eq(t3, 24.0))
        {
            return true;
        }

        //312
        t1 = cal(n3, n4, op3);
        t2 = cal(n1, n2, op1);
        t3 = cal(t2, t1, op2);
        if (eq(t3, 24.0))
        {
            return true;
        }

        //321
        t1 = cal(n3, n4, op3);
        t2 = cal(n2, t1, op2);
        t3 = cal(n1, t2, op1);
        if (eq(t3, 24.0))
        {
            return true;
        }

        return false;
    }

    double cal(double n1, double n2, char op)
    {
        switch (op)
        {
        case '+':
            return n1 + n2;
            break;
        case '-':
            return n1 - n2;
            break;
        case '*':
            return n1 * n2;
            break;
        case '/':
            if (n2 == 0)
            {
                return 123456789.0;
            }
            return n1 / n2;
            break;
        }
        return 0.0;
    }

    bool eq(double d1, double d2)
    {
        if (fabs(d1 - d2) < 0.0001)
        {
            return true;
        }
        return false;
    }
};

int main()
{
    vector<int> nums = {1,1,1,1};
    cout << boolalpha << Solution().judgePoint24(nums) << noboolalpha << endl;
    return 0;
}

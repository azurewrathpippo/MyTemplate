#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<stack>
#include<cmath>

using namespace std;

//顶点 
class Point
{
public:
	int x;
	int y;
	Point *base;
	
	Point():
		x(0), y(0), base(NULL)
	{
	}
};

//点距离函数 
double dist(const Point &p1, const Point &p2)
{
	double dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrt(dx * dx + dy * dy);
}

//比较函数 
bool cmp(const Point &p1, const Point &p2)
{
	double dx1 = p1.x - p1.base->x, dy1 = p1.y - p1.base->y;
	double dx2 = p2.x - p2.base->x, dy2 = p2.y - p2.base->y;
	double c1, c2;
	if (dx1 == 0)
	{
		c1 = 0.0;
	}
	else
	{
		c1 = dx1 * dx1 / (dx1 * dx1 + dy1 * dy1) * dx1 / abs(dx1);
	}
	if (dx2 == 0)
	{
		c2 = 0.0;
	}
	else
	{
		c2 = dx2 * dx2 / (dx2 * dx2 + dy2 * dy2) * dx2 / abs(dx2);
	}
	if (c1 > c2)
	{
		return true;
	}
	if (c1 == c2)
	{
		dist(p1, *(p1.base)) < dist(p2, *(p2.base));
	}
	return false;
}

//三个点是否是一个左转,利用了叉积 
bool isLeftTurn(const Point &p1, const Point &p2, const Point &p3)
{
	int ax = p2.x - p1.x, ay = p2.y - p1.y;
	int bx = p3.x - p2.x, by = p3.y - p2.y;
	return ax * by - ay * bx >= 0;
}

Point points[105];

//将空的stack填进来，返回的所有空包顶点存在栈里,n代表顶点个数。调用时，points数组应有序，points[0]为最下面的点，其他的点按逆时针排序 
void getConvexHull(int n, stack<Point> &st)
{
	st.push(points[0]);
	st.push(points[1]);
	st.push(points[2]);
	for (int i = 3; i < n; ++i)
	{
		const Point &cur = points[i];
		Point tp, ntp = st.top();
		st.pop();
		do
		{
			tp = ntp;
			ntp = st.top();
			st.pop();
		}while(!isLeftTurn(ntp, tp, cur));
		st.push(ntp);
		st.push(tp);
		st.push(cur);
	}
}

/////////////////////////////////
//分隔符，以上为凸包的模板，以下为杭电oj的第1392题 
/////////////////////////////////

int main()
{
	int n;
	while(true)
	{
		scanf("%d", &n);
		if (n == 0)
		{
			break;
		}
		int baseIndex = 0;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d%d", &points[i].x, &points[i].y);
			if (i > 0)
			{
				if (points[i].y < points[baseIndex].y || (points[i].y == points[baseIndex].y && points[i].x < points[baseIndex].x))
				{
					baseIndex = i;
				}
			}
		}
		if (n == 1)
		{
			cout << "0.00" << endl;
			continue;
		}
		if (n == 2)
		{
			printf("%.2f\n", dist(points[0], points[1]));
			continue;
		}
		Point tmp = points[0];
		points[0] = points[baseIndex];
		points[baseIndex] = tmp;
		
		for (int i = 1; i < n; ++i)
		{
			points[i].base = points;
		}
		sort(points + 1, points + n, cmp);
		
		stack<Point> st;
		getConvexHull(n, st);
		vector<Point> rounds;
		while(!st.empty())
		{
			rounds.push_back(st.top());
			st.pop();
		}
		double len = dist(rounds[0], rounds[rounds.size() - 1]);
		for (int i = 1; i < rounds.size(); ++i)
		{
			len += dist(rounds[i], rounds[i - 1]);
		}
		printf("%.2f\n", len);
	}
	return 0;
}

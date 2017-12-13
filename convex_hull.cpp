/*************************************************************************
	> File Name: convex_hull.c
	> Author: fly
	> Mail:fly@163.com 
	> Created Time: 2017年12月04日 星期一 22时29分29秒
 ************************************************************************/
/*
 * 凸包问题
 *
 * 找一个闭合曲线C，使C能包住所有的点，并且给定的点到C的距离最小为L，
 * 问C的周长是这些点所构成的凸包的周长加上以稍微画一画就知道这个C的周
 * 长是这些点所构成的凸包的周长加上以L为半径的圆的周长。于是求一个凸
 * 包再加上2πL就可以了
 */

#include <cstdio>  
#include <cstring>  
#include <cstdlib>  
#include <algorithm>  
#include <cmath>  

/*
 * d[]是一个Point的数组，Point有两个两个属性x和y，同时支持减法操作和det(叉积)。
 * convex数组保存被选中的凸包的点的编号，cTotal是凸包中点的个数
 * */

using std::sort;
#define MAXN 1002
int N, L;

double sqr(double a)
{
    return a*a;
}

struct Point
{
    double x, y;
    inline Point operator-(const Point &t)
    {
        Point ret;
        ret.x = x - t.x;
        ret.y = y - t.y;
        return ret;
    }
    inline Point operator+(const Point &t)
    {
        Point ret;
        ret.x = x + t.x;
        ret.y = y + t.y;
        return ret;
    }
    inline int det(const Point &t)
    {
        return x*t.y - t.x*y;
    }
    inline double dist(Point &t)
    {
        return sqrt(sqr(x-t.x) + sqr(y-t.y));
    }
}d[MAXN];

bool cmpPoint(const Point &a, const Point &b)  //比较坐标序所用的比较函数
{
    if (a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

int convex[MAXN], cTotal;

void get_convex_hull()
{
    sort(d,d+N,cmpPoint);
    int Total=0,tmp;
    for (int i=0;i<N;++i)  //扫描下凸壳
    {
        while ((Total>1) && 
               ((d[convex[Total-1]]-d[convex[Total-2]]).det(    //获得凸包中最后两个点的向量
               d[i]-d[convex[Total-1]])<=0) ) 
            Total--;                //获得准备插入的点和凸包中最后一点的向量，计算叉积
        convex[Total++]=i;
    }
    
    tmp=Total;
    for (int i=N-2;i>=0;--i)   //扫描上凸壳
    {
        while ( (Total>tmp) &&
                ((d[convex[Total-1]]-d[convex[Total-2]]).det(
                    d[i]-d[convex[Total-1]])<=0) ) Total--;
        convex[Total++]=i;
    }
    cTotal=Total;
}

int main()
{
    int i;
    scanf("%d %d \n", &n, &L);

    for (i = 0;i < N; i++)
    {
        scanf("%lf %lf \n", &d[i].x, &d[i].y);
    }

    get_convex_hull();
    double Ans = 0;

    for (i = 0;i < cTotal - 1; ++i)
    {
        Ans += d[convex[i].dist(convex[i + 1])];
    }

    Ans += d[convex[0].dist(d[convex[cTotal-1]])];
    Ans += 3.1415926*2*L;
    printf("%0.1f\n", Ans);

    return 0;
}

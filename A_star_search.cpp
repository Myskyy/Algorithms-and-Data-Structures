    /* 
        A*寻路.cpp 四方向版 
             --sxysxy 2016-2-15  
              
        常数挺大的。。。可能小图跑不过dij 或者 spfa...... 
        代码写得灰常乱，因为本就不熟。。。然后还不想麻烦... 
    */  
    #include <stdio.h>  
    #include <stdlib.h>  
    #include <math.h>  
    #include <ctype.h>  
    #include <time.h>  
    #include <queue>  
    using namespace std;  
    #define INF (0x23333333)  
    #define MAXN (302)  
      
    //寻四方向用  
    const int dl[] = {1,-1,0,0};  
    const int dc[] = {0,0,-1,1};  
      
    int map[MAXN][MAXN]; //地图  
    int n,m;   //地图的行数列数  
    int g[MAXN][MAXN]; //已用代价，参数为行列坐标  
    int h[MAXN][MAXN]; //估计还需代价，参数为行列坐标  
    bool in_close[MAXN][MAXN]; //在关闭列表中，参数为行列坐标  
    bool in_open[MAXN][MAXN]; //在开启列表中，参数为行列坐标  
    bool ok = false;  //立一个找到解的flag  
    struct point  
    {  
        int l,c;  
        point(){}  
        point(int _l, int _c){l=_l;c=_c;}  
        bool operator<(const point &o) const  
        {  
            return g[l][c]+h[l][c]>g[o.l][o.c]+h[o.l][o.c];  
            //启发数值在优先队列里面从小到大...  
        }  
    };  
    point path[MAXN][MAXN];  //记录路径用  
    int sl,sc,tl,tc; //出发/目标点的位置  
    #define mkpt(a,b) (point{a,b})    
    void find_path()  
    {  
        int i,j;  
        int cl,cc,nl,nc;  
        //cl,cc当前处理的点的位置，  
        //nl,nc当前处理的点的邻居的位置  
        priority_queue<point> open_list;  
        //用优先队列维护开启列表  
        if(map[sl][sc] || map[tl][tc])return; //出发点或者目标点不可通行，返回  
        for(i = 1; i <= n; i++)  
        {  
            for(j = 1; j <= m; j++)  
            {  
                h[i][j] = (int)sqrt((double)(i-tl)*(i-tl)+(double)(j-tc)*(j-tc))+1;  //估计代价 = 这个点到目标点的几何距离向上取整  
                g[i][j] = INF; //已用代价初始化为INF  
            }  
        }  
          
        //出发点扔到open_list  
        g[sl][sc] = 0;  
        in_open[sl][sc] = true;  
        open_list.push(mkpt(sl,sc));  
          
        while(open_list.size())  
        {  
            cl = open_list.top().l;  
            cc = open_list.top().c;  
            open_list.pop();  
            if(cl == tl && cc == tc)  
            {  //找到目标，跳出循环  
                ok = true;  
                break;  
            }  
            //当前点算入关闭列表中  
            in_close[cl][cc] = true;  
            for(i = 0; i < 4; i++)  
            {  
                nl = cl+dl[i];  
                nc = cc+dc[i];  
                if(map[nl][nc] == 1)continue; //不可通行  
                if(in_close[nl][nc])continue; //在关闭列表  
                if(! in_open[nl][nc])  
                {  //发现新节点  
                    open_list.push(mkpt(nl,nc));  
                }else if(g[cl][cc]+1 >= g[nl][nc])  
                    continue; //不是更好的解，continue  
                      
                //找到一个更优的解，记录路径，更新g值  
                path[nl][nc] = mkpt(cl,cc);  
                g[nl][nc] = g[cl][cc] + 1;  
            }  
        }  
    }  
      
    void print_res()  
    {  
        int l,c;  
        int i,j;  
        if(!ok)  
        {  
            printf("无法到达!\n");  
            return;  
        }  
        printf("从出发点到目标点所需步数为:%d\n", g[tl][tc]);  
        //回溯路径  
        l = tl;  
            c = tc;  
        while(true)  
        {  
            map[l][c] = '*'-'0';  
            if(l == sl && c == sc)break;  
            i = path[l][c].l;  
            j = path[l][c].c;  
            l = i;  
            c = j;  
        }  
        map[sl][sc] = '%'-'0';  
        //打印解法  
        printf("走法如下 %%是出发点，*是路径:\n");  
        for(i = 1; i <= n; i++)  
        {  
            for(j = 1; j <= m; j++)  
            {  
                printf("%c ", map[i][j]+'0');  
            }  
            putchar('\n');  
        }  
          
    }  
      
    int main()  
    {  
        int i, j;  
        printf("=======A*搜索 四方向寻路系统=======\n");  
        printf("先输入两个整数，n,m，表示下面将要输入一个n行m列的迷宫\n");  
        scanf("%d %d", &n, &m);  
        for(i = 0; i <= n+1; i++)  
            for(j = 0; j <= m+1; j++)  
                map[i][j] = 1;  //先初始化为全部为不可通行路块，便于处理  
        printf("接下来输入这n行m列的迷宫，用0表示可通行的路块，1表示不可通行的路块\n");  
        for(i = 1; i <= n; i++)  
            for(j = 1; j <= m; j++)  
                scanf("%d", &map[i][j]);  
        printf("接下来输入起点和终点的位置，位置用行列来表示，行列从1开始计算\n");  
        printf("起点位置:");  
        scanf("%d %d", &sl, &sc);  
        printf("终点位置:");  
        scanf("%d %d", &tl, &tc);  
        find_path();  
        print_res();  
        return 0;  
    }  

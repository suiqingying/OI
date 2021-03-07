/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 14:39:20
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-02 14:48:37
 */
#include <set>
#include <map>
#include <cmath>
#include <stack>
#include <ctime>
#include <queue>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = x * 10 + c - '0', c = getchar();
    }
    return x * f;
}
const int maxn = (1 << 12) + 10;
struct BIT
{
    int n, m;
    long long c[maxn][maxn];
    inline void add(int x, int y, long long d)
    {
        if (x > n || y > m)
        {
            return;
        }
        int t = y;
        for (; x <= n; x += x & -x)
        {
            y = t;
            for (; y <= m; y += y & -y)
            {
                c[x][y] += d;
            }
        }
    }
    inline long long ask(int x, int y)
    {
        long long sum = 0;
        int t = y;
        for (; x; x -= x & -x)
        {
            y = t;
            for (; y; y -= y & -y)
            {
                sum += c[x][y];
            }
        }
        return sum;
    }
} c;
long long ask(int lx, int ly, int rx, int ry)
{
    return c.ask(rx, ry) - c.ask(lx - 1, ry) - c.ask(rx, ly - 1) + c.ask(lx - 1, ly - 1);
}
int main()
{
//     freopen("1.in", " r", stdin);
    c.n = read(), c.m = read();
    int opt;
    while (scanf("%d", &opt) != EOF)
    {
        if(opt == 1)
        {
            int x = read(), y = read(), k = read();
            c.add(x, y, k);
        }
        else
        {
            int lx = read(), ly = read(), rx = read(), ry = read();
            printf("%lld\n", ask(lx, ly, rx, ry));
        }
    }
    return 0;
}

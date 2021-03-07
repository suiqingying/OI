/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 16:02:32
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-02 16:51:45
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
	int x = 0, f = 1;char c = getchar();
	while (!isdigit(c)){if(c == '-')f = -1;c = getchar();}
	while (isdigit(c))x = x * 10 + c -48, c = getchar();
	return x * f;
}
const int maxn = (1 << 11) + 7;
int n, m, opt;
struct BIT
{
    long long c[maxn][maxn][4];
    inline void add(int x, int y, long long d)
    {
        long long d2 = d * x, d3 = d * y, d4 = d * x * y;
        int t = y;
        for (; x <= n; x += x & -x)for (y = t; y <= m; y += y & -y)c[x][y][0] += d, c[x][y][1] += d2, c[x][y][2] += d3, c[x][y][3] += d4;
    }
    inline long long ask(int x, int y)
    {
        long long sum = 0, sum2 = 0, sum3 = 0, sum4 = 0;
        int t = y, t2 = x;
        for (; x; x -= x & -x)for (y = t; y; y -= y & -y)sum += c[x][y][0], sum2 += c[x][y][1], sum3 += c[x][y][2], sum4 += c[x][y][3];
        return sum * (t + 1) * (t2 + 1) - sum2 * (t + 1) - sum3 * (t2 + 1) + sum4;
    }
} c;
inline void add(int lx, int ly, int rx, int ry, long long d) { c.add(lx, ly, d), c.add(rx + 1, ly, -d), c.add(lx, ry + 1, -d), c.add(rx + 1, ry + 1, d); }
inline long long ask(int lx, int ly, int rx, int ry) { return c.ask(rx, ry) - c.ask(lx - 1, ry) - c.ask(rx, ly - 1) + c.ask(lx - 1, ly - 1); }
int main()
{
    n = read(), m = read();
    while (scanf("%d", &opt) != EOF)
    {
        int lx = read(), ly = read(), rx = read(), ry = read();
        if (opt == 1)add(lx, ly, rx, ry, read());
        else printf("%lld\n", ask(lx, ly, rx, ry));
    }
    return 0;
}

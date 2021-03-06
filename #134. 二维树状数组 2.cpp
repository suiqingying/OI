/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 15:14:14
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-02 16:05:43
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
const int maxn = (1 << 12) + 5;
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
inline void add(int lx, int ly, int rx, int ry, long long d)
{
    c.add(lx, ly, d), c.add(rx + 1, ly, -d), c.add(lx, ry + 1, -d), c.add(rx + 1, ry + 1, d);
}
int main()
{
    c.n = read(), c.m = read();
    int opt;
    while (scanf("%d", &opt) != EOF)
    {
        if (opt == 1)
        {
            int lx = read(), ly = read(), rx = read(), ry = read();
            add(lx, ly, rx, ry, read());
        }
        else
        {
            int x = read(), y = read();
            printf("%lld\n", c.ask(x, y));
        }
    }
    return 0;
}

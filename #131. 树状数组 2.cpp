/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 13:49:05
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-02 14:14:03
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
const int maxn = 1e6 + 7;
struct BIT
{
    int n;
    long long c[maxn];
    void add(int x, long long d)
    {
        if(x > n)return;
        for (; x <= n; x += x & -x)
        {
            c[x] += d;
        }
    }
    long long ask(int x)
    {
        long long sum = 0;
        for (; x; x -= x & -x)
        {
            sum += c[x];
        }
        return sum;
    }
}c;
int a[maxn];
int main()
{
    int n = read(), q = read();c.n = n;
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
    }
    for (int i = 1; i <= q; ++i)
    {
        int opt = read();
        if(opt == 1)
        {
            int l = read(), r = read(), x = read();
            c.add(l, x), c.add(r + 1, -x);
        }
        else
        {
            int x = read();
            printf("%lld\n", a[x] + c.ask(x));
        }
    }
    return 0;
}

/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 21:00:38
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-02 21:03:54
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
const int maxn = 1e6 + 10;
int v[maxn], dfn[maxn], Siz[maxn];
struct Tree
{
    int tot, head[maxn], nxt[maxn << 1], ver[maxn << 1];
    void add(int u, int v)
    {
        ver[++tot] = v;
        nxt[tot] = head[u];
        head[u] = tot;
    }
    void dfs(int x, int fa)
    {
        dfn[x] = ++dfn[0], Siz[x] = 1;
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = ver[i];
            if (y == fa)
            {
                continue;
            }
            dfs(y, x);
            Siz[x] += Siz[y];
        }
    }
} T;
struct BIT
{
    int n;
    long long c[maxn];
    inline void add(int x, long long d)
    {
        if (x > n)
            return;
        for (; x <= n; x += x & -x)
        {
            c[x] += d;
        }
    }
    inline long long ask(int x)
    {
        long long sum = 0;
        for (; x; x -= x & -x)
        {
            sum += c[x];
        }
        return sum;
    }
} c1, c2;
void add(int x, long long d)
{
    c1.add(x, d), c2.add(x, x * d);
}
long long ask(int x)
{
    return (x + 1) * c1.ask(x) - c2.ask(x);
}
int a[maxn];
int main()
{
//    freopen("1.in", " r", stdin);
    int n = read(), m = read(), root = read();
    c1.n = c2.n = n;
    for (int i = 1; i <= n; ++i)
    {
        v[i] = read();
    }
    for (int i = 1; i < n; ++i)
    {
        int x = read(), y = read();
        T.add(x, y), T.add(y, x);
    }
    T.dfs(root, 0);
    for (int i = 1; i <= n; ++i)
    {
        a[dfn[i]] = v[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        add(i, a[i] - a[i - 1]);
    }
    for (int i = 1; i <= m; ++i)
    {
        int opt = read(), a = read(), x;
        if (opt == 1)
        {
            int x = read();
            add(dfn[a], x), add(dfn[a] + Siz[a], -x);
        }
        else
        {
            printf("%lld\n", ask(dfn[a] + Siz[a] - 1) - ask(dfn[a] - 1));
        }
    }
    return 0;
}

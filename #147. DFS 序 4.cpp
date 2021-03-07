/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 21:10:55
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-03 11:42:00
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
namespace io
{
    const int SIZE = (1 << 18) + 1;
    char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
    int f, qr;
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
    inline void flush()
    {
        fwrite(obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }
    inline void putc(char x)
    {
        *oS++ = x;
        if (oS == oT)
            flush();
    }
    inline int read()
    {
        int x = 0;
        for (f = 1, c = gc(); c < '0' || c > '9'; c = gc())
            if (c == '-')
                f = -1;
        for (x = 0; c <= '9' && c >= '0'; c = gc())
            x = x * 10 + (c & 15);
        return x * f;
    }
    template <class I>
    inline void write(I x)
    {
        if (!x)
            putc('0');
        if (x < 0)
            putc('-'), x = -x;
        while (x)
            qu[++qr] = x % 10 + '0', x /= 10;
        while (qr)
            putc(qu[qr--]);
    }
    struct Flusher_
    {
        ~Flusher_() { flush(); }
    } io_flusher_;
} // namespace io
#define read io::read
#define write io::write
#define putc io::putc
const int maxn = 1e6 + 10;
int n, m, r;
struct BIT
{
    long long c[maxn];
    inline void add(int x, long long d)
    {
        if (x > n || x <= 0)
        {
            return;
        }
        for (; x <= n; x += x & -x)
        {
            c[x] += d;
        }
    }
    inline long long ask(int x)
    {
        if (x <= 0)
        {
            return 0;
        }
        long long sum = 0;
        for (; x; x -= x & -x)
        {
            sum += c[x];
        }
        return sum;
    }
} c1, c2;
int fa[maxn], Siz[maxn], dfn[maxn], depth[maxn];
long long v[maxn];
int tot, head[maxn], nxt[maxn << 1], ver[maxn << 1];
inline void add(int u, int v)
{
    ver[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}
int cnt, pos[maxn];
int f[21][maxn << 1], lg[maxn << 1];
inline void dfs(int x)
{
    Siz[x] = 1, depth[x] = depth[fa[x]] + 1, dfn[x] = ++dfn[0];
    f[0][++cnt] = x;
    pos[x] = cnt;
    for (int i = head[x]; i; i = nxt[i])
    {
        int y = ver[i];
        if (y == fa[x])
        {
            continue;
        }
        fa[y] = x;
        v[y] += v[x];
        dfs(y);
        f[0][++cnt] = x;
        Siz[x] += Siz[y];
    }
}

inline void pre_work()
{
    lg[0] = -1;
    for (int i = 1; i <= cnt; ++i)
    {
        lg[i] = lg[i >> 1] + 1;
    }
    int t = lg[cnt] + 1;
    for (int j = 1; j < t; ++j)
    {
        for (int i = 1; i + (1 << j) - 1 <= cnt; ++i)
        {
            if (depth[f[j - 1][i]] < depth[f[j - 1][i + (1 << (j - 1))]])
            {
                f[j][i] = f[j - 1][i];
            }
            else
            {
                f[j][i] = f[j - 1][i + (1 << (j - 1))];
            }
        }
    }
}
inline int lca(int l, int r)
{
    l = pos[l], r = pos[r];
    if (l > r)
    {
        std::swap(l, r);
    }
    int t = lg[r - l + 1];
    if (depth[f[t][l]] < depth[f[t][r - (1 << t) + 1]])
    {
        return f[t][l];
    }
    else
    {
        return f[t][r - (1 << t) + 1];
    }
}
inline long long ask(int x)
{
    return c1.ask(dfn[x]) + depth[x] * c2.ask(dfn[x]) + v[x];
}
int main()
{
    n = read(), m = read(), r = read();
    for (int i = 1; i <= n; ++i)
    {
        v[i] = read();
    }
    for (int i = 1; i < n; ++i)
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs(r), pre_work(), dfn[0] = 0;
    int opt, x, y;
    for (int i = 1; i <= m; ++i)
    {
        opt = read(), x = read(), y = read();
        if (opt == 1)
        {
            c1.add(dfn[x], y), c1.add(dfn[x] + Siz[x], -y);
        }
        else if (opt == 2)
        {
            long long V = 1ll * (1 - depth[x]) * y;
            c1.add(dfn[x], V), c1.add(dfn[x] + Siz[x], -V);
            c2.add(dfn[x], y), c2.add(dfn[x] + Siz[x], -y);
        }
        else
        {
            int z = lca(x, y);
            write(ask(x) + ask(y) - ask(z) - ask(fa[z])), putc('\n');
        }
    }
    return 0;
}

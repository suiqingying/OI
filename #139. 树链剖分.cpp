/*
 * @Autor: suiqingying
 * @Date: 2020-12-03 14:17:58
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-03 16:04:21
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
namespace io{
const int SIZE=(1<<18)+1;char ibuf[SIZE],*iS,*iT,obuf[SIZE],*oS=obuf,*oT=oS+SIZE-1,c,qu[55];int f,qr;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),(iS==iT?EOF:*iS++)):*iS++)
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++=x;if(oS==oT)flush();}
inline int read(){int x = 0;for(f=1,c=gc();c<'0'||c>'9';c=gc())if(c=='-')f=-1;for(x=0;c<='9'&&c>='0';c=gc())x=x*10+(c&15);return x*f;}
template<class I>inline void write(I x){if(!x)putc('0');if(x<0)putc('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)putc(qu[qr--]);}
struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
#define read io::read
#define write io::write
#define putc io::putc
const int maxn = 1e5 + 10;
int n, v[maxn];
int fa[maxn], son[maxn], top[maxn], depth[maxn], Siz[maxn], dfn[maxn], id[maxn];
struct Tree
{
    int tot, head[maxn], ver[maxn], nxt[maxn];
    void add(int u, int v)
    {
        ver[++tot] = v;
        nxt[tot] = head[u];
        head[u] = tot;
    }
    void dfs1(int x)
    {
        depth[x] = depth[fa[x]] + 1, Siz[x] = 1;
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = ver[i];
            if (y == fa[x])
            {
                continue;
            }
            dfs1(y);
            Siz[x] += Siz[y];
            if (Siz[y] > Siz[son[x]])
            {
                son[x] = y;
            }
        }
    }
    void dfs2(int x, int topf)
    {
        top[x] = topf, dfn[x] = ++dfn[0], id[dfn[0]] = x;
        if (son[x])
        {
            dfs2(son[x], topf);
        }
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = ver[i];
            if (y == fa[x] || y == son[x])
            {
                continue;
            }
            dfs2(y, y);
        }
    }
} G;
struct SegmentTree
{
    int root, tot, lc[maxn << 1], rc[maxn << 1];
    long long sum[maxn << 1], tag[maxn << 1];
    void pushup(int p)
    {
        sum[p] = sum[lc[p]] + sum[rc[p]];
    }
    void pushdown(int p, int l, int r)
    {
        if (!tag[p])
            return;
        int mid = (l + r) >> 1;
        sum[lc[p]] += tag[p] * (mid - l + 1), sum[rc[p]] += tag[p] * (r - mid);
        tag[lc[p]] += tag[p], tag[rc[p]] += tag[p];
        tag[p] = 0;
    }
    void build(int &p, int l, int r)
    {
        p = ++tot;
        if (l == r)
        {
            sum[p] = v[id[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc[p], l, mid), build(rc[p], mid + 1, r);
        pushup(p);
    }
    void change(int p, int l, int r, int L, int R, int d)
    {
        if (L <= l && R >= r)
        {
            sum[p] += d * (r - l + 1);
            tag[p] += d;
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid)
        {
            change(lc[p], l, mid, L, R, d);
        }
        if (R > mid)
        {
            change(rc[p], mid + 1, r, L, R, d);
        }
        pushup(p);
    }
    long long query(int p, int l, int r, int L, int R)
    {
        if (L <= l && R >= r)
        {
            return sum[p];
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        long long sum = 0;
        if (L <= mid)
        {
            sum += query(lc[p], l, mid, L, R);
        }
        if (R > mid)
        {
            sum += query(rc[p], mid + 1, r, L, R);
        }
        return sum;
    }
} T;
int root = 1;
inline void add_chain(int x, int y, int d)
{
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]])
        {
            std::swap(x, y);
        }
        T.change(T.root, 1, n, dfn[top[x]], dfn[x], d);
        x = fa[top[x]];
    }
    if (depth[x] > depth[y])
    {
        std::swap(x, y);
    }
    T.change(T.root, 1, n, dfn[x], dfn[y], d);
}
inline long long query_chain(int x, int y)
{
    long long sum = 0;
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]])
        {
            std::swap(x, y);
        }
        sum += T.query(T.root, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (depth[x] > depth[y])
    {
        std::swap(x, y);
    }
    return sum + T.query(T.root, 1, n, dfn[x], dfn[y]);
}
inline int find(int x, int y)
{
    int k = depth[x] - depth[y] - 1;
    while (depth[x] - depth[fa[top[x]]] <= k)
    {
        k -= depth[x] - depth[fa[top[x]]];
        x = fa[top[x]];
    }
    return id[dfn[x] - k];
}
inline void add_subtree(int u, int d)
{
    if(u == root)
    {
        T.change(T.root, 1, n, 1, n, d);
    }
    else if(dfn[root] >= dfn[u] && dfn[root] <= dfn[u] + Siz[u] - 1)
    {
        int v = find(root, u);
        T.change(T.root, 1, n, 1, n, d), T.change(T.root, 1, n, dfn[v], dfn[v] + Siz[v] - 1, -d);
    }
    else
    {
        T.change(T.root, 1, n, dfn[u], dfn[u] + Siz[u] - 1, d);
    } 
}
inline long long query_subtree(int u)
{
    if(u == root)
    {
        return T.query(T.root, 1, n, 1, n);
    }
    else if(dfn[root] >= dfn[u] && dfn[root] <= dfn[u] + Siz[u] - 1)
    {
        int v = find(root, u);
        T.query(T.root, 1, n, 1, n);
        return T.query(T.root, 1, n, 1, n) - T.query(T.root, 1, n, dfn[v], dfn[v] + Siz[v] - 1);
    }
    else
    {
        return T.query(T.root, 1, n, dfn[u], dfn[u] + Siz[u] - 1);
    } 
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        v[i] = read();
    }
    for (int i = 2; i <= n; ++i)
    {
        fa[i] = read();
        G.add(fa[i], i);
    }
    G.dfs1(root),G.dfs2(root, root),dfn[0] = 0;
    T.build(T.root, 1, n);
    int m = read();
    for (int i = 1; i <= m; ++i)
    {
        int opt = read(), u = read(), v;
        if(opt == 1)
        {
            root = u;
        }
        else if(opt == 2)
        {
            v = read();
            add_chain(u, v, read());
        }
        else if(opt == 3)
        {
            add_subtree(u, read());
        }
        else if(opt == 4)
        {
            printf("%lld\n", query_chain(u, read()));
        }
        else
        {
            printf("%lld\n", query_subtree(u));
        }
    }
    return 0;
}

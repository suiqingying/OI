/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 21:10:55
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-03 09:30:35
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
const int maxn = 1e6 + 10;
int n, m, r;
struct BIT
{
    long long c[maxn];
    inline void add(int x, long long d)
    {
        if(x > n || x <= 0)
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
        long long sum = 0 ;
        for (; x; x -= x & -x)
        {
            sum += c[x];
        }
        return sum;
    }
}c1, c2;
int fa[maxn], son[maxn], Siz[maxn], top[maxn], dfn[maxn], depth[maxn];
int v[maxn];
long long sum[maxn];
struct Tree
{
    int tot, head[maxn], nxt[maxn << 1], ver[maxn << 1];
    inline void add(int u, int v)
    {
        ver[++tot] = v;
        nxt[tot] = head[u];
        head[u] = tot;
    }
    inline void dfs1(int x)
    {
        Siz[x] = 1, depth[x] = depth[fa[x]] + 1, dfn[x] = ++dfn[0], sum[x] = v[x];
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = ver[i];
            if(y == fa[x])
            {
                continue;
            }
            fa[y] = x;
            dfs1(y);
            Siz[x] += Siz[y];
            sum[x] += sum[y];
            if(Siz[y] > Siz[son[x]])
            {
                son[x] = y;
            }
        }
    }
    inline void dfs2(int x, int topf)
    {
        top[x] = topf;
        if(son[x])
        {
            dfs2(son[x], topf);
        }
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = ver[i];
            if(y == fa[x] || y == son[x])
            {
                continue;
            }
            dfs2(y, y);
        }
    }
    inline int lca(int x, int y)
    {
    	if(!x || !y)
    	{
    		return 0;
		}
        while (top[x] != top[y])
        {
            if(depth[top[x]] < depth[top[y]])
            {
                std::swap(x, y);
            }
            x = fa[top[x]];
        }
        if(depth[x] > depth[y])
        {
            std::swap(x, y);
        }
        return x;
    }
}T;
inline void add(int x, long long d)
{
	c1.add(dfn[x], d), c2.add(dfn[x], depth[x] * d);
}
inline void add_chain(int x, int y, long long d)
{
    int z = T.lca(x, y);
    add(x, d), add(y, d), add(z, -d), add(fa[z], -d);
}
inline long long ask(int x)
{
	return (c2.ask(dfn[x] + Siz[x] - 1) - c2.ask(dfn[x] - 1)) - (depth[x] - 1) * (c1.ask(dfn[x] + Siz[x] - 1) - c1.ask(dfn[x] - 1));
}
int main(){
    n = read(), m = read(), r = read();
    for (int i = 1; i <= n; ++i)
    {
    	v[i] = read();
	}
    for (int i = 1; i < n; ++i)
    {
        int u = read(), v = read();
        T.add(u, v), T.add(v, u);
    }
    T.dfs1(r), T.dfs2(r, r), dfn[0] = 0;
    int opt, x, y, d;
    for (int i = 1; i <= m; ++i)
    {
        opt = read(), x = read();
        if(opt == 1)
        {
            y = read(), d = read();
            add_chain(x, y, d);
        }
        else if(opt == 2)
        {
            write(v[x] + c1.ask(dfn[x] + Siz[x] - 1) - c1.ask(dfn[x] - 1)), putc('\n');
        }
        else
        {
            write(ask(x) + sum[x]), putc('\n');
		}
    }
    return 0;
}

/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 12:12:26
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-02 12:15:32
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
const int maxn = 1e6 + 10;
struct BIt
{
    int n;
    long long c[maxn];
    void add(int x, int d)
    {
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
inline int read()
{
    int x = 0,f = 1;char c = getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x = x * 10+ c - '0',c=getchar();}
    return x*f;
}
int main(){
    // freopen("1.in"," r" , stdin);
    int n = read(), q = read();c.n = n;
    for (int i = 1; i <= n; ++i)
    {
        c.add(i, read());
    }
    for (int i = 1; i <= q; ++i)
    {
        int opt = read(), x = read(), y = read();
        if(opt == 1)
        {
            c.add(x, y);
        }
        else
        {
            printf("%lld\n", c.ask(y) - c.ask(x - 1));
        }
    }
    return 0;
}

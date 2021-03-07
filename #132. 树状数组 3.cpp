/*
 * @Autor: suiqingying
 * @Date: 2020-12-02 14:17:00
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-12-02 14:29:45
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
    int x = 0,f = 1;char c = getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x = x * 10+ c - '0',c=getchar();}
    return x*f;
}
const int maxn = 1e6 + 10;
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
}c1, c2;
int a[maxn];
void add(int x, long long d)
{
    c1.add(x, d), c2.add(x, x * d);
}
long long ask(int x)
{
    return (x + 1) * c1.ask(x) - c2.ask(x);
}
int main(){
//    freopen("1.in"," r" , stdin);
    int n = read(), q = read();c1.n = c2.n = n;
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        add(i, a[i] - a[i - 1]);
    }
    for (int i = 1; i <= q; ++i)
    {
        int opt = read(), l = read(), r = read();
        if(opt == 1)
        {
            int x = read();
            add(l, x), add(r + 1, -x);
        }
        else
        {
            printf("%lld\n", ask(r) - ask(l - 1));
        }   
    }
    return 0;
}

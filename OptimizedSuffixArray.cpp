/* Reduced the extra array a from last and making array p already sorted by second element so that we need to only call 1 count sort. Time : O(nlogn)


#include<bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define mod 1000000007
void count_sort(vector<int> &p , vector<int> &c)
{
    int n = p.size();
    vector<int> cnt(n);
    for(int i=0;i<n;i++)
    {
        cnt[c[i]] += 1;
    }
    vector<int> p_new(n);
    vector<int>pos(n);
    pos[0]=0;
    for(int i=1;i<n;i++)
    {
        pos[i] = pos[i-1]+cnt[i-1];
    }
    for(int i=0;i<n;i++)
    {
        int k = c[p[i]];
        p_new[pos[k]] = p[i];
        pos[k] += 1;
    }
    p = p_new;


}


int main()
{
    string s;
    cin>>s;
    s+='$';
    int n=s.size();
    vector<int> p(n),c(n);

    vector<pair<char,int> > a(n);
    for(int i=0;i<n;i++)
    a[i] = {s[i],i};
    sort(a.begin(),a.end());

    for(int i=0;i<n;i++)
        p[i] = a[i].second;

    c[p[0]] = 0;
    for(int i=1;i<n;i++)
    {
        if(a[i].first != a[i-1].first)
        {
            c[p[i]] = c[p[i-1]] + 1;
        }
        else
        {
            c[p[i]] = c[p[i-1]];
        }
    }
    int k=0;

    while((1 << k)<n)
    {
        
        for(int i=0;i<n;i++)
        {
            p[i] = (p[i] - (1<<k) + n)%n;
        }
        count_sort(p,c);

        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for(int i=1;i<n;i++)
        {
            pair<int,int> prev = {c[p[i-1]],c[(p[i-1]+ (1<<k))%n]};
            pair<int,int> now = {c[p[i]],c[(p[i]+ (1<<k))%n]};
            if(now == prev)
            {
                c_new[p[i]] = c_new[p[i-1]];
            }
            else
            {
                c_new[p[i]] = c_new[p[i-1]] + 1;
            }
        }
        c = c_new;
        k+=1;
    }
    for(int i=0;i<n;i++)
        cout<<p[i]<<" ";
    cout<<endl;


    return 0;
}

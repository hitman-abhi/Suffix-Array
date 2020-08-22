/* Given a string , find its suffix array
   This works in O(nlogn) as we use radix sort to sort the pairs*/
#include<bits/stdc++.h>

using namespace std;
void radix_sort(vector<pair<pair<int,int>,int> > &a)
{
    int n = a.size();
    {
    vector<int> cnt(n);
    for(int i=0;i<n;i++)
    {
        cnt[a[i].first.second] += 1;
    }
    vector<pair<pair<int,int>,int> > a_new(n);
    vector<int>pos(n);
    pos[0]=0;
    for(int i=1;i<n;i++)
    {
        pos[i] = pos[i-1]+cnt[i-1];
    }
    for(int i=0;i<n;i++)
    {
        int k = a[i].first.second;
        a_new[pos[k]] = a[i];
        pos[k] += 1;
    }
    a = a_new;
    }
    {
    vector<int> cnt(n);
    for(int i=0;i<n;i++)
    {
        cnt[a[i].first.first] += 1;
    }
    vector<pair<pair<int,int>,int> > a_new(n);
    vector<int>pos(n);
    pos[0]=0;
    for(int i=1;i<n;i++)
    {
        pos[i] = pos[i-1]+cnt[i-1];
    }
    for(int i=0;i<n;i++)
    {
        int k = a[i].first.first;
        a_new[pos[k]] = a[i];
        pos[k] += 1;
    }
    a = a_new;
    }
}
typedef long long int ll;
#define mod 1000000007
int main()
{
    string s;
    cin>>s;
    s+='$';
    int n=s.size();
    vector<int> p(n),c(n);
    {
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
    }
    int k=0;
    while((1 << k)<n)
    {
        vector<pair<pair<int,int>,int> > a(n);
        for(int i=0;i<n;i++)
        a[i] = {{c[i],c[(i+(1<<k))%n]},i};
        radix_sort(a);
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
        k+=1;
    }
    for(int i=0;i<n;i++)
        cout<<p[i] <<" ";
    cout<<endl;

    return 0;
}

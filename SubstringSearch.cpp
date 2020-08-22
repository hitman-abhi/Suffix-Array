/*Given a string t and n queries, each query is a string si. For each request you need to determine whether the string si occurs as a substring in t.
  For each query Time : O(|si|logn)   logn for binary search and |si| for string compare.
  Idea : Every sustring is the prefix of some suffix. */

#include<bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define mod 1000000007
string s;
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

bool get_string(string &z , vector<int> &p)
{
    int n = z.size();
    int left=0,right = p.size()-1;
    while(left<=right)
    {
        int mid = (left+right)/2;
        string z1 = s.substr(p[mid],min(n,int(p.size())-p[mid]-1));
        if(z == z1)
            return true;
        if(z1>z)
            right = mid-1;
        else
            left = mid+1;
    }
    return false;
}

int main()
{
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

    int q;
    cin>>q;
    while(q--)
    {
        string z;
        cin>>z;
        if(get_string(z,p))
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }

    return 0;
}

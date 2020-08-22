//Given a String , output the suffix array in lexographical manner. O(N log^2)

#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define mod 1000000007
int main()
{
    string s;
    cin>>s;
    s+='$';
    int n=s.size();
    vector<int> p(n),c(n); // p contains the answer , c contains the equivalence order.
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
        k+=1;
    }
    for(int i=0;i<n;i++)
        cout<<p[i] <<" ";
    cout<<endl;

    return 0;
}

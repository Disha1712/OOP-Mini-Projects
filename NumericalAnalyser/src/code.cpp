#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;
#define MOD 1000000007
#define ll long long 
vector<bool> sieve(1e6+1, 1);
vector<ll> primes;

void sieveinit(vector<bool>& sieve,vector<long long>& primes){
    sieve[0]=sieve[1] =0;
    for(ll i=2;i*i<=1e6;i++){
        if(sieve[i]){
            for(ll j = i*i; j <= 1e6; j += i){
                sieve[j] = 0;
            }
        }
    }
    for(ll i=2;i<=1e6;i++){
        if(sieve[i]){
            primes.push_back(i);
        }
    }
}
ll power(ll x,ll n){
    ll ans=1;
    while(n>0){
        if (n%2){
            ans=(ans * x);
        }
        x=(x*x);
        n/=2;
    }
    return ans;
}
class CurrencySorter{
    public:
    void quicksort(ll arr[],int s,int e){
        if (s>=e) return;
        ll pivot=arr[e];
        int i=s-1;
        for (ll j=s;j<e;j++){
            if (arr[j]<=pivot){
                i++;
                swap(arr[i],arr[j]);
            }
        }
        swap(arr[i+1],arr[e]);
        quicksort(arr,s,i);
        quicksort(arr,i+2,e);
    }
    void operator()(ll arr[],ll n){
        quicksort(arr,0,n-1);
    }
};
struct FibonnaciGenerator{
    public:
    ll fastfibo(ll n) {
        if (n==0) return 0;
        if (n==1) return 1;
        ll a=0,b=1,c,d;
        for (ll i =1LL << (63 - __builtin_clzll(n)); i; i >>= 1) {
            c = (a*((b << 1) - a + MOD) % MOD)%MOD; 
            d = (a*a% MOD+b * b%MOD) % MOD;   
            if (n & i){
                a=d;
                b=(c+d)%MOD;
            } 
            else{
                a=c;
                b=d;
            }
        }
        return a;
    } 
    void operator()(ll x){
        cout<<fastfibo(x)<<endl;
    }
};
class PrimeCalculator{
public:
    vector<ll> rangeprim;
    ll sum;
    PrimeCalculator(ll l, ll r){
        vector<bool> temp(r-l+1,1);
        if(l==1){
            temp[0]=0;
        }
        for(ll i=0;i<primes.size();i++){
            ll prime=primes[i];
            if(prime>r/prime) break;
            ll start=max(prime*prime,(l+prime-1)/prime*prime);
            for(ll j=start;j<=r;j+=prime){
                temp[j-l]=0;
            }
        }
        sum=0;
        for (ll i=l;i<=r;i++){
            if (temp[i-l]){
                rangeprim.push_back(i);
                sum += i;
            }
        }
    }
    void printPrimes(ll l, ll r){
        for(auto x:rangeprim){
            cout<<x<< " ";
        }
        cout<<endl;
    }
    void printPrimeSum(ll l, ll r){
        cout<<sum<<endl;
    }
};
class NumberAnalyzer {
    public:
        map<ll,ll> factors;
        NumberAnalyzer(ll x) {
            for (ll i:primes) {
                if (i*i>x){
                    break;
                }
                ll ct = 0;
                while (x%i==0) {
                    ct++;
                    x/= i;
                }
                if (ct>0){
                    factors[i] = ct;
                }
            }
            if (x>1){
                factors[x] = 1; 
            }
        }
        void isSquareFree(ll x) {
            for (auto &p:factors) {
                if (p.second>= 2) {
                    cout<<"no"<< endl;
                    return;
                }
            }
            cout <<"yes"<< endl;
        }
    
        void countDivisors(ll x) {
            ll ct=1;
            for (auto &p:factors) {
                ct*=(p.second+1);
            }
            cout<<ct<<endl;
        }   
        void sumOfDivisors(ll x) {
            ll ans=1;
            for (auto &p:factors) {
                ll prime=p.first;
                ll exp=p.second;
                ans*=(ll)(power(prime,exp+1)-1)/(prime-1);
            }
            cout<<ans<< endl;
        }
    };
int main(){
    sieveinit(sieve,primes);
    int type;
    cin>>type;
    int t;
    cin>>t;
    if (type==1){
        while (t--){
            ll n;
            cin>>n;
            ll arr[n];
            CurrencySorter S;
            for (ll i=0;i<n;i++){
                cin>>arr[i];
            }
            S(arr,n);
            for (ll i=0;i<n;i++){
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
    }
    else if (type==2){
        FibonnaciGenerator F;
        while (t--){
            ll n;
            cin>>n;
            F(n);            
        }
    }
    else if (type==3){
        while (t--){
            string comm;
            ll left,right;
            cin>>comm>>left>>right;
            PrimeCalculator calc(left,right);
            if (comm=="printPrimes"){
                calc.printPrimes(left,right);                
            }
            else{
                calc.printPrimeSum(left,right);
            }
        }
    }
    else{
        while (t--){
            string s;
            ll x;
            cin>>s>>x;
            if (s=="isSquareFree"){
                NumberAnalyzer NumberAnalyzer(x);
                NumberAnalyzer.isSquareFree(x);
            }
            else if (s=="countDivisors"){
                NumberAnalyzer NumberAnalyzer(x);
                NumberAnalyzer.countDivisors(x);
            }
            else{
                NumberAnalyzer NumberAnalyzer(x);
                NumberAnalyzer.sumOfDivisors(x);
            }
        }
    }
}
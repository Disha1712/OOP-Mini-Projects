#include <bits/stdc++.h>
using namespace std;
#define ll long long
long double PI=acos(-1);


class Complex{
    public:
        ll real,imaginary;
        Complex(): real(0),imaginary(0) {}
        Complex(ll real,ll img): real(real),imaginary(img){}
        Complex(ll real): real(real),imaginary(0){}
        Complex operator +(Complex b){
            Complex C(this->real+b.real,this->imaginary+b.imaginary);
            return C;
        }
        Complex operator *(Complex b){
            Complex C((this->real*b.real-this->imaginary*b.imaginary),(this->real*b.imaginary+this->imaginary*b.real));
            return C;
        }
        Complex operator -(Complex b){
            Complex C(this->real-b.real,this->imaginary-b.imaginary);
            return C;
        }
        Complex operator *(ll a){
            Complex C(this->real*a,this->imaginary*a);
            return C;
        }
        friend ostream& operator<<(ostream& os, const Complex& c){
            os<<c.real<<" "<<c.imaginary;
            return os;
        }
        friend istream& operator>>(istream& is, Complex& c){
            is>>c.real>>c.imaginary;
            return is;
        }
};


template <typename T>
class Multiplication{
    public:
        vector<T> multi(vector<T>& A,vector<T>& B){
            ll n=A.size();
            if (n==1){
                vector<T> ans(1);
                ans[0]=A[0]*B[0];
                return ans;
            }
            vector<T> a(n/2),b(n/2),c(n/2),d(n/2);
            for (ll i=0;i<n/2;i++){
                a[i]=A[i];
                b[i]=A[i+n/2];
                c[i]=B[i];
                d[i]=B[i+n/2];
            }
            vector<T> r1=multi(a,c);
            vector<T> r4=multi(b,d);
            
            vector<T> absum(n/2),cdsum(n/2);
            for (ll i=0;i<n/2;i++){
                absum[i]=a[i]+b[i];
                cdsum[i]=c[i]+d[i];
            }

            vector<T> sumpoly=multi(absum,cdsum);
            vector<T> xcoeff(sumpoly.size());
            for (ll i=0;i<r1.size();i++){
                xcoeff[i]=sumpoly[i]-r1[i]-r4[i];
            }

            vector<T> ans(2*n-1,0);
            for (ll i=0;i<r1.size();i++){
                ans[i]=ans[i]+r1[i];
                ans[i+n/2]=ans[i+n/2]+xcoeff[i];
                ans[i+n]=ans[i+n]+r4[i];
            }
            return ans;
        }
};

template <typename T>
class Evaluation{
    public:
        vector<ll> Horner(ll n, ll x){
            vector<ll> powers(n,1);
            for(ll i=1;i<n;i++){
                powers[i]=powers[i-1]*x;
            }
            return powers;
        }
        string Eval(vector<string> poly,ll a) {
            string ans="";
            vector<ll> powers=Horner(poly.size(),a);
            for (ll i=poly.size()-1;i>=0;i--) {
                for (ll j=0;j<powers[i];j++) {
                    ans+=poly[i];
                }
            }
            return ans;
        }
        ll Eval(vector<ll> poly,ll a){
            ll ans=0;
            for (ll i=(ll)poly.size()-1;i>=0;i--){
                ans=poly[i]+ans*a;
            }
            return ans;
        }
        long double Eval(vector<long double> poly,ll a){
            long double ans=0;
            for (ll i=(ll)poly.size()-1;i>=0;i--){
                ans=poly[i]+ans*a;
            }
            return ans;
        }
};


template <typename T>
class Differentiation{
    public:
        vector<T> Diff(vector<T> poly){
            vector<T> ans;
            for (ll i=1;i<poly.size();i++){
                ans.push_back(i*poly[i]);
            }
            return ans;
        }
};

template <typename T>
class Polynomial{
    private:
        ll deg;
        vector<T> coeff;
    public:
        Polynomial<T>(ll deg,vector<T> v): deg(deg),coeff(v){}
        vector<T> operator *(Polynomial<T> b){
            vector<T> poly_a16(16,0),poly_b16(16,0);
            for (ll i=0;i<deg;i++){
                poly_a16[i]=coeff[i];
            }
            for (ll i=0;i<b.deg;i++){
                poly_b16[i]=b.coeff[i];
            }
            Multiplication<T> m;
            return m.multi(poly_a16,poly_b16);
        }
        T Eval(ll a){
            Evaluation<T> E;
            T ans=E.Eval(coeff,a);
            return ans;
        }
        vector<T> diff(){
            Differentiation<T> D;
            vector<T> ans=D.Diff(coeff);
            return ans;
        }
};

int main(){
    ll q;
    cin>>q;
    while (q--){
        ll type;
        cin>>type;
        if (type==1){
            string data;
            cin>>data;
            ll deg1;
            cin>>deg1;
            if (data=="integer"){
                vector<ll> v(deg1);
                for (ll i=0;i<deg1;i++){
                    cin>>v[i];
                }
                Polynomial<ll> P(deg1,v);
                ll deg2;
                cin>>deg2;
                vector<ll> u(deg2);
                for (ll i=0;i<deg2;i++){
                    cin>>u[i];
                }
                Polynomial<ll> Q(deg2,u);
                vector<ll> ans=P*Q;
                for (ll i=0;i<deg1+deg2-1;i++){
                    cout<<ans[i]<<" ";
                }
                cout<<endl;
            }
            else if (data=="complex"){
                vector<Complex> c(deg1);
                for (ll i=0;i<deg1;i++){
                    cin>>c[i].real>>c[i].imaginary;
                }
                Polynomial<Complex> C(deg1,c);
                ll deg2;
                cin>>deg2;
                vector<Complex> d(deg2);
                for (ll i=0;i<deg2;i++){
                    cin>>d[i];
                }
                Polynomial<Complex> D(deg2,d);
                vector<Complex> ans=C*D;  
                for (ll i=0;i<deg1+deg2-1;i++){
                    cout<<ans[i].real<<" "<<ans[i].imaginary<<" ";
                }
                cout<<endl;          

            }
            else{
                vector<long double> v(deg1);
                for (ll i=0;i<deg1;i++){
                    cin>>v[i];
                }
                Polynomial<long double> P(deg1,v);
                ll deg2;
                cin>>deg2;
                vector<long double> u(deg2);
                for (ll i=0;i<deg2;i++){
                    cin>>u[i];
                }
                Polynomial<long double> Q(deg2,u);
                vector<long double> ans= P*Q;
                for (ll i=0;i<deg1+deg2-1;i++){
                    cout<<fixed<<setprecision(6)<<ans[i]<<" ";
                }
                cout<<endl;

            }

        }
        else if (type==2){
            string data;
            cin>>data;
            ll deg;
            cin>>deg;
            if (data=="integer"){
                vector<ll> v(deg);
                for (ll i=0;i<deg;i++){
                    cin>>v[i];
                }
                Polynomial<ll> P(deg,v);  
                ll x;
                cin>>x;
                cout<<P.Eval(x)<<endl;              
            }
            else if (data=="float"){
                vector<long double> v(deg);
                for (ll i=0;i<deg;i++){
                    cin>>v[i];
                }
                Polynomial<long double> P(deg,v);
                ll x;
                cin>>x;
                cout<<fixed<<setprecision(6)<<P.Eval(x)<<endl;
            }
            else{
                vector<string> v(deg);
                cin.ignore();
                for (ll i=0;i<deg;i++){
                    cin>>v[i];
                }
                Polynomial<string> P(deg,v);
                ll x;
                cin>>x;
                cout<<P.Eval(x)<<endl;
            }
        }
        else{
            string data;
            cin>>data;
            ll deg;
            cin>>deg;
            if (data=="integer"){
                vector<ll> v(deg);
                for (ll i=0;i<deg;i++){
                    cin>>v[i];
                }
                Polynomial<ll> P(deg,v);
                vector<ll> diff_poly=P.diff();
                for (auto i:diff_poly){
                    cout<<i<<" ";
                }
                cout<<endl;
            }   
            else{
                vector<long double> v(deg);
                for (ll i=0;i<deg;i++){
                    cin>>v[i];
                }
                Polynomial<long double> P(deg,v);
                vector<long double> diff_poly=P.diff();
                for (auto i:diff_poly){
                    cout<<fixed<<setprecision(6)<<i<<" ";
                }
                cout<<endl;

            }         

        }
    }
}

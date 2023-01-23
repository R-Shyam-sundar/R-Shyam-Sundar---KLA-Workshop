#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef tree<int,null_type,less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<ll> vl;
typedef vector<vl> vll;
 
#define llmax LLONG_MAX;
#define llmin LLONG_MIN;
#define imax INT_MAX;
#define imin INT_MIN;
#define F first
#define S second
#define PB push_back
#define MP make_pair
 
#define REP(i,a,b) for (int i = a; i < b; i++)
 
void __print(int x){cerr << x;}
void __print(long x){cerr << x;}
void __print(long long  x){cerr << x;}
void __print(unsigned x){cerr << x;}
void __print(unsigned long x){cerr << x;}
void __print(unsigned long long x){cerr << x;}
void __print(float x){cerr << x;}
void __print(double x){cerr << x;}
void __print(long double x){cerr << x;}
void __print(char x){cerr << x;}
void __print(const char *x){cerr << '\"' << x << '\"';}
void __print(const string &x){cerr << '\"' << x << '\"';}
void __print(bool x){cerr << (x ? "true" : "false");}
 
template<typename T,typename U>
void __print(const pair<T,U> &x){cerr << "{"; __print(x.first); cerr << ","; __print(x.second);cerr << "}";}
template<typename T>
void __print(const T &x){int f = 0; cerr << '{';for(auto &i: x) cerr << (f++ ? "," : ""), __print(i);cerr << "}";}
void _print() {cerr << "]\n";}
template<typename T,typename... V>
void _print(T t,V... v){__print(t); if(sizeof...(v)) cerr << ", "; _print(v...);}
#define debug(x...) cerr << "[" << #x << "] = [";_print(x);

struct polygon{
    int layer,datatype,n;
    vector<pair<int,int>> vertices;
};

vector<polygon> vp;
vector<string> s;
vector<string> headr;
vector<int> rang = {2, 5, 2, 3, 5, 2};
vector<int> rang1 = {2,7,9,12,17,19};



bool strcompare(string s1,string s2){
    if(s1.size() != s2.size())return false;
    for(int i=0;i<s1.size();i++){
        if(s1[i] != s2[i])return false;
    }
    return true;
}

void extract_header()
{
    int ind = 0;
    for(int i=0;i<rang.size();i++){
        for(int j=0;j<rang[i];j++,ind++){
            headr.push_back(s[ind]);
        }
    }
    // debug(headr);
}

void extract_polygons()
{
    string t;
    int index = 0;
    while(!strcompare(t,"boundary")){
        t = s[index];
        index++;
    }
    // printf("\nindex : %d",index);
    index--;
    while(true){
        string bound,lay,dt,xy;
        int lay_int,dt_int,cnt;
        bound = s[index];
        if(strcompare(bound,"endstr")){
            return;
        }
        // debug(bound);

        lay = s[index+1];
        // debug(lay,s[index+1]);
        
        lay_int = stoi(s[index+2]);
        // debug(lay_int,s[index+2]);
        
        dt = s[index+3];
        // debug(dt,s[index+3]);
        
        dt_int = stoi(s[index+4]);
        // debug(dt_int,s[index+4]);
        
        xy = s[index+5];
        // debug(xy);
        
        cnt = stoi(s[index+6]);
        // debug(cnt);
        
        // debug(bound,lay,dt,xy,lay_int,dt_int,cnt);
        
        vector<long long> temp;
        for(int i=index+7;i<(index+7 + (cnt*2));i++){
            long long t = stoi(s[i]);
            temp.push_back(t);
        }
        
        index += (8 + (2*cnt));

        struct polygon poly;
        poly.layer = lay_int;
        poly.datatype = dt_int;
        poly.n = cnt;
        // debug(temp);
        for(int i=0;i<temp.size();i+=2){
            poly.vertices.push_back({temp[i],temp[i+1]});
        }
        vp.push_back(poly);
        // debug(vp.size());
    }
}

void milestone1()
{
    // debug(rang);
    // debug(headr);
    freopen("output.txt","w",stdout);
    int rang_ind = 0;
    for(int i=0;i<headr.size();i++){
        // debug(i,headr[i]);
        if(i == 12){
            // cout << "{12}";
            cout << "\n\n" << headr[i] << " ";
            rang_ind++;
        }
        else if(rang1[rang_ind] == i){
            cout << "\n" << headr[i] << " ";
            rang_ind++;
        }
        else{
            cout << headr[i] << " ";
        }
    }
    
    cout << "\n";
    for(int i=0;i<2;i++){
        cout << "\nboundary\n";
        cout << "layer " << vp[i].layer << "\n";
        cout << "datatype " << vp[i].datatype << "\n";
        cout << "xy " << vp[i].n << " ";
        for(int j=0;j<vp[i].vertices.size();j++){
            cout << vp[i].vertices[j].first << " " << vp[i].vertices[j].second << "  ";
        }
        cout << "\nendel\n";
    }
    cout << "endstr\nendlib\n"; 
}



int main()
{   
    freopen("Format_Source.txt","r",stdin);
    char x;
    int index = 0;
    string t;   
    while(!strcompare(t,"endlib")){
        cin >> t;
        s.push_back(t);
    }
    // debug(s);
    extract_header();
    extract_polygons();
    milestone1();
    return 0;
}

/*
Compilation flag:
-Wall -Wextra -pedantic -std=c++11 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
 
*/
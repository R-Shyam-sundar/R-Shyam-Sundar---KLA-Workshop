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

vector<string> POI_s;
vector<polygon> POI_vp;

vector<double> POI_peri;
vector<double> peri;

vector<int> rang = {2, 5, 2, 3, 5, 2};
vector<int> rang1 = {2,7,9,12,17,19};

set<int> ans1;

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((long long)x2 - x1, 2) + pow((long long)y2 - y1, 2) * 1.0);
}

double poly_perimeter(int x)
{
    // find perimeter of vp[i]
    int num = vp[x].n;
    double val = 0;
    debug(vp[x].vertices);
    double temp = val;
    for(int i=1;i<num;i++){
        val += (distance(vp[x].vertices[i].first, vp[x].vertices[i].second, vp[x].vertices[i-1].first, vp[x].vertices[i-1].second));
        debug(val-temp);
        temp = val; 
    }
    debug(val);
    return val;
}

double POI_poly_perimeter(int x)
{
    // find perimeter of vp[i]
    int num = POI_vp[x].n;
    double val = 0;
    // debug(POI_vp[x].vertices);
    double temp = val;
    for(int i=1;i<num;i++){
        val += (distance(POI_vp[x].vertices[i].first, POI_vp[x].vertices[i].second, POI_vp[x].vertices[i-1].first, POI_vp[x].vertices[i-1].second));
        // debug(val-temp);
        temp = val; 
    }
    return val;
}

void calc_peri(){
    for(int i=0;i<vp.size();i++){
        double val = poly_perimeter(i);
        peri.push_back(val);
    }
    for(int i=0;i<POI_vp.size();i++){
        double val = POI_poly_perimeter(i);
        POI_peri.push_back(val);
    }
}

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

// Extract polygons in POI
void POI_extract_polygons()
{
    string t;
    int index = 0;
    while(!strcompare(t,"boundary")){
        t = POI_s[index];
        index++;
    }
    // printf("\nindex : %d",index);
    index--;
    while(true){
        string bound,lay,dt,xy;
        int lay_int,dt_int,cnt;
        bound = POI_s[index];
        if(strcompare(bound,"endstr")){
            return;
        }
        // debug(bound);

        lay = POI_s[index+1];
        // debug(lay,s[index+1]);
        
        lay_int = stoi(POI_s[index+2]);
        // debug(lay_int,s[index+2]);
        
        dt = POI_s[index+3];
        // debug(dt,s[index+3]);
        
        dt_int = stoi(POI_s[index+4]);
        // debug(dt_int,s[index+4]);
        
        xy = POI_s[index+5];
        // debug(xy);
        
        cnt = stoi(POI_s[index+6]);
        // debug(cnt);
        
        debug(bound,lay,dt,xy,lay_int,dt_int,cnt);
        
        vector<long long> temp;
        for(int i=index+7;i<(index+7 + (cnt*2));i++){
            long long t = stoi(POI_s[i]);
            temp.push_back(t);
        }

        debug(temp);
        
        index += (8 + (2*cnt));

        struct polygon poly;
        poly.layer = lay_int;
        poly.datatype = dt_int;
        poly.n = cnt;
        // debug(temp);
        for(int i=0;i<temp.size();i+=2){
            poly.vertices.push_back({temp[i],temp[i+1]});
        }
        POI_vp.push_back(poly);
        // debug(vp.size());
    }
}

void milestone1()
{
    freopen("output.txt","w",stdout);
    // Print headers
    vector<int> ans(ans1.begin(),ans1.end());
    int rang_ind = 0;
    for(int i=0;i<headr.size();i++){
        if(i == 12){
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
    for(int i=0;i<ans.size();i++){
        cout << "boundary\n";
        cout << "layer " << vp[ans[i]].layer << "\n";
        cout << "datatype " << vp[ans[i]].datatype << "\n";
        cout << "xy " << vp[ans[i]].n << " ";
        for(int j=0;j<vp[ans[i]].vertices.size();j++){
            cout << vp[ans[i]].vertices[j].first << " " << vp[ans[i]].vertices[j].second << "  ";
        }
        cout << "\nendel\n";
    }
    cout << "endstr\nendlib\n"; 
}

void Print_POI_VP()
{
    // freopen("output.txt","w",stdout);
    int rang_ind = 0;
    for(int i=0;i<headr.size();i++){
        if(i == 12){
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
    for(int i=0;i<POI_vp.size();i++){
        cout << "\nboundary\n";
        cout << "layer " << POI_vp[i].layer << "\n";
        cout << "datatype " << POI_vp[i].datatype << "\n";
        cout << "xy " << POI_vp[i].n << " ";
        for(int j=0;j<POI_vp[i].vertices.size();j++){
            cout << POI_vp[i].vertices[j].first << " " << POI_vp[i].vertices[j].second << "  ";
        }
        cout << "\nendel\n";
    }
    cout << "endstr\nendlib\n"; 
}

void PolyofInterest()
{
    freopen("POI.txt","r",stdin);
    string t;   
    while(!strcompare(t,"endlib")){
        cin >> t;
        POI_s.push_back(t);
    }
}

void milestone2()
{
    // Print_POI_VP();
    calc_peri();
    // debug(peri);
    // debug(POI_peri);
    for(int i=0;i<POI_peri.size();i++){
        for(int j=0;j<peri.size();j++){
            if(POI_peri[i] == peri[j]){
                ans1.insert(j);
            }
        }
    }
    // debug(ans);
    milestone1();
}

// bool cmp_polygon()


int main()
{   
    freopen("Source.txt","r",stdin);
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
    PolyofInterest();
    // milestone1();
    POI_extract_polygons();
    milestone2();
    return 0;
}

/*
Compilation flag:
-Wall -Wextra -pedantic -std=c++11 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
 
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll ts = 100005;
#define IOS  ios::sync_with_stdio(0); cin.tie(0);
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define pair <int,int> ii
struct matran{
	int c[2][2];	
} ans[10000],matrix[10000];
vector <int> countt(10000,0);
/* 
   countt[id] = 1 -> nút id được chuyển đổi
   ans[id] : tích các ma trận thuộc đoạn nút id quản lí
   matrix[i] : nếu s[i] = 'A' -> matrix[i] = [1 0]
                                             [1 1]
   tương tự với s[i] = 'B'                                      
 
*/
/* 
 
 Thuật toán :
 
 Nếu đoạn (l , r) bị đảo ngược - > 
 ans[id] = (a , b)
           (c , d) 
 sẽ chuyển thành  ( d, c)
                 ( b, a)
Chứng  minh : quy nạp
 
*/
matran operator *(matran a , matran b) {
	matran res;
	for(int i = 0; i <=1; i++) {
		for(int j = 0; j < 2; j++) {
			res.c[i][j] = 0;
			for(int k = 0; k < 2 ; k++) {
				res.c[i][j] += a.c[i][k] * b.c[k][j];
			}
		}
	}
	return res;
}
void sw(matran x) {     // ma trận x bị đảo ngược
	int &a = x.c[0][0];
	int &b = x.c[0][1];
	int &c1 = x.c[1][0];
	int &d = x.c[1][1];
	swap(a , d);
	swap(b , c1);
}
matran calc (int id , int l , int r) {    // tính giá trị các ma trận ban đầu
	if(l == r) {
		ans[id] = matrix[l];
		return ans[id];
	}
	else {
		matran &x = ans[id] ;
		int mid = (l + r)/2;
		x = calc(id*2 , l , mid )*calc(id*2 + 1 , mid + 1 , r);
		return x;
	}
 
}
void down (int id) {  // truyền lazy xuống
	if(countt[id] == 1) {  // nếu đoạn id được thay đổi
		countt[id*2] = 1;
		countt[id*2 + 1] = 1;
		countt[id] = 0;
		sw(ans[id*2]);
		sw(ans[id*2 + 1]);
	}
	else return ;
}
void update(int id , int l , int r , int u , int v) {
	if(l > v || u > r || l > r) {
		return ;
	}
	if(l >= u && r <=v ) {  
	    matran x = ans[id];    // ma trận của đoạn (l, r)
	    sw(x);                 // đoạn (l,r) được thay đổi
	    countt[id] = 1;
	    return ;
	}
	int mid = (l + r)/2;
	down(id);                                  // đẩy hết các lazy xuống
	update(id* 2 , l , mid , u, v);
	update(id*2 + 1 , mid + 1 , r , u , v);
	ans[id] = ans[id*2] * ans[id*2 + 1];       // re-calculate đoạn (l , r) 
}
matran get(int id , int l , int r , int u , int v) {
	if(l > v || r < u || l > r) {
		matran non;
		non.c[0][0] = 1;
		non.c[0][0] = 0;                // không đi sâu thêm nữa
		non.c[1][0] = 0;
		non.c[1][1] = 1;
		return non;
	}
	if(l >=u && r <= v) {
		return ans[id];         
	}
	int mid = (l + r)/2;
	down(id);
	return get(id*2 , l , mid , u , v)  *  get(id*2 + 1, mid + 1, r , u , v); 
}
signed main() {
    IOS; 
	int n,q;
    string s;
    cin >> n ; cin >>  q;
    cin >> s; 
    for(int i = 0; i < s.length() ; i++) {
    	if(s[i] == 'A') {
    		matrix[i].c[0][0] = 1;
    		matrix[i].c[0][1] = 0;
    		matrix[i].c[1][0] = 1;
    		matrix[i].c[1][1] = 1;
		}
		else {
			matrix[i].c[0][0] = 1;
			matrix[i].c[0][1] = 1;
			matrix[i].c[1][0] = 0;
			matrix[i].c[1][1] = 1;
		}
	}
	calc(1 , 1, s.length() );   
	for(int i = 1; i <= q; i++) {
		int type , l , r, a , b;
		cin >> type >> l >> r;
		if(type == 1) {
			update(1, 1 , s.length() , l , r );
		}
		else {
			cin >> a >> b;
			matran res;
			res.c[0][0] = a;
			res.c[0][1] = b;
			res.c[1][0] = 0;
			res.c[1][1] = 0;
			res = res * get(1 , 1, s.length() , l , r);
			cout << res.c[0][0] << " " << res.c[0][1] << endl;
		}
	}
 }

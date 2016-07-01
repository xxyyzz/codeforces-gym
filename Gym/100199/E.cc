#include <iostream>
#include <algorithm>
#include <vector>
#define LL long long

using namespace std;

LL n, m, mod;

/* Matrix Expo Code */
#define SIZE 33
LL T[SIZE][SIZE], orig_T[SIZE][SIZE], dummy[SIZE][SIZE];
LL C[SIZE];
vector<LL> fnot;	// Should have size == SIZE

// copy to orig_T
void init() {
    // compute T
    for(int b = 0; b < 1<<m; b++) {
        for(int x = 0; x < 1<<m; x++) {
            T[b][x] = 1;
            for(int i = 1; i < m; i++) {
                if((b & (1<<i)) == (x & (1<<i)) &&
                   (b & (1<<(i-1))) == (x & (1<<(i-1))) &&
                   ((b & (1<<i)) > 0) == ((b & (1<<(i-1))) > 0)) {
                    T[b][x] = 0;
                    break;
                }
            }
        }
    }
	std::copy(&T[0][0], &T[0][0] + SIZE*SIZE, &orig_T[0][0]);
}
template<typename T>
void mul(T a[], T b[], T c[]) {
	std::fill(&dummy[0][0], &dummy[0][0] + SIZE*SIZE, 0);
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				dummy[i][j] = (dummy[i][j] + (a[i][k] * b[k][j])) % mod;
	std::copy(&dummy[0][0], &dummy[0][0] + SIZE*SIZE, &c[0][0]);
}
LL temp[SIZE][SIZE];
template<typename T>
void matrix_expo(T a[], int e, T b[]) {
	std::copy(&a[0][0], &a[0][0] + SIZE*SIZE, &temp[0][0]);
	std::fill(&b[0][0], &b[0][0] + SIZE*SIZE, 0);
	for(int i = 0; i < SIZE; i++)	b[i][i] = 1;
	while(e) {
		if(e&1)	mul(b, temp, b);
		e /= 2;
		mul(temp, temp, temp);
	}
}
template<typename T>
void string_expo(T a[], string e, T b[]) {
	std::copy(&a[0][0], &a[0][0] + SIZE*SIZE, &temp[0][0]);
	std::fill(&b[0][0], &b[0][0] + SIZE*SIZE, 0);
	for(int i = 0; i < SIZE; i++)	b[i][i] = 1;
	while(e.size()) {
		if(e.back() == '1')	mul(b, temp, b);
        e.pop_back();
		mul(temp, temp, temp);
	}
}
inline string convert(string s)
{
    if(s == "0") return "";
    string w;
    while(1)
    {
        string temp;
        if(s=="1")
        {
            w.insert(w.begin(),'1');
            return w;
        }
        int quo=0,rem=0;
        for(int i=0;i<s.size();i++)
        {
            int q=((rem*10)+(s[i]-'0'))/2;
            int r=((rem*10)+(s[i]-'0'))%2;
            rem=r;
            temp.insert(temp.end(),q+'0');
        }
        while(1)
        {
            if(temp[0]=='0')
            {
                temp.erase(temp.begin());
            }
            else
            {
                break;
            }
        }
        s=temp;
        w.insert(w.begin(),rem+'0');
    }
    return w;
}
template<typename S>
LL solve(S n) {	// return f(n)
	std::copy(&orig_T[0][0], &orig_T[0][0] + SIZE*SIZE, &T[0][0]);
	string_expo(T, n, T);
    //matrix_expo(T, n-1, T);
	LL answer = 0;
    for(int i = 0; i < 1<<m; i++) {
        for(int j = 0; j < 1<<m; j++) {
            answer += (T[i][j] * 1) % mod;
            answer %= mod;
        }
    }
	// Compute answer
	return answer;
}
/* End Matrix Expo */
template<typename S>
LL debug(S n) {	// return f(n)
	std::copy(&orig_T[0][0], &orig_T[0][0] + SIZE*SIZE, &T[0][0]);
	matrix_expo(T, n, T);
	LL answer = 0;
    for(int i = 0; i < 1<<m; i++) {
        for(int j = 0; j < 1<<m; j++) {
            answer += (T[i][j] * 1) % mod;
            answer %= mod;
        }
    }
	// Compute answer
	return answer;
}

string decrement(string temp) {
    string res = temp;
    if(temp.back() > '0') {
        res[res.size()-1]--;
        return res;
    }
    bool all_zeros = (temp.front() == '1');
    for(int i = 1; i < temp.size(); i++)
        if(temp[i] != '0')
            all_zeros = false;
    if(all_zeros) {
        res.pop_back();
        for(auto &c: res) {
            c = '9';
        }
    } else {
        for(int i = res.size() - 1; ; i--) {
            if(res[i] > '0') {
                res[i]--;
                break;
            }
            res[i] = '9';
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef __APPLE__
    freopen("nice.in", "rb", stdin);
    freopen("nice.out", "wb", stdout);
#endif
    string n;
    cin >> n >> m >> mod;
    n = decrement(n);
    init();
    n = convert(n);
    cout << solve(n) << '\n';
    return 0;
}

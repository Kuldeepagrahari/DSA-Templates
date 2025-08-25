#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, sum;
    cin >> n >> sum;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // yaha hame 2-d dp hi banana padega kyuki koi best ans nhi lena sum - v[i] row se, hame har index ka result pta hona chahiye ki sum is index tak ke elements ko use krne ke baad ban paya tha ki nhi (aisa nhi h ki agar last tak ke elements explore krne ke baad sum ban gya tha to hum maan lenge ki ha sum ban gya h using [0...j] subarray of v se) -> to index pe to depend kar raha h
}
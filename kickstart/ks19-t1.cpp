#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie();

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int a, b, n;
        cin >> a >> b >> n;
        a++;

        while (true) {
            int m = (a + b) / 2;
            cout << m << endl;

            string s;
            cin >> s;
            
            if (s == "CORRECT") {
                break;
            }
            
            if (s == "TOO_SMALL") {
                a = m + 1;
            } else {
                b = m - 1;
            }
        }
    }
}
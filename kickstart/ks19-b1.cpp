#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie();
 
    int tc;
    cin >> tc;
 
    for (int t = 1; t <= tc; t++) {
        int n, q;
        string s;

        cin >> n >> q >> s;

        int occs[26][s.size() + 1];
        memset(occs, 0, sizeof(int) * 26 * (s.size() + 1));

        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < s.size(); j++) {
                int ascii = int(s[j]) - 65;

                occs[i][j+1] = occs[i][j];  // Copy previous value.
                if (ascii == i) occs[i][j+1]++;
            }
        }

        int res = 0;
 
        for (int i = 0; i < q; i++) {
            int l, r, odds = 0;
            cin >> l >> r;

            for (int j = 0; j < 26; j++) {
                int o = occs[j][r] - occs[j][l-1];
                if (o % 2 != 0) odds++;
            }

            if (odds < 2) res++;
        }
 
        cout << "Case #" << t << ": " << res << endl;
    }
 
}
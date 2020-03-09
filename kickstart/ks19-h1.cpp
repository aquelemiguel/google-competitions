#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie();

    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        int n;
        cin >> n;

        int score = 1;
        priority_queue<int, vector<int>, greater<int> > pq;

        cout << "Case #" << t << ": ";

        for (int i = 0; i < n; i++) {
            int c;
            cin >> c;

            if (pq.size() >= score && c > score) {
                score++;
                
                while (!pq.empty() && pq.top() <= score) {
                    pq.pop();
                }
            }

            if (c > score) {
                pq.push(c);
            }

            cout << score << " ";
        }
        cout << endl;
    }
}
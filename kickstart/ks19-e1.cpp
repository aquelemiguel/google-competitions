#include <bits/stdc++.h>
using namespace std;

void add_edge(vector<vector<int>> &adj, int u, int v, int wt) {
    adj[u][v] = wt;
    adj[v][u] = wt;
}

int min_key(int key[], bool mst_set[], int n) {
    int min = INT_MAX, min_index;

    for (int i = 0; i < n; i++) {
        if (!mst_set[i] && key[i] < min) {
            min = key[i], min_index = i;
        }
    }

    return min_index;
}

int prims_mst(vector<vector<int>> &adj, int n) {
    int parent[n], key[n], min = 0;
    bool mst_set[n];

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX, mst_set[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n-1; i++) {
        int u = min_key(key, mst_set, n);
        mst_set[u] = true;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] && !mst_set[v] && adj[u][v] < key[v]) {
                parent[v] = u, key[v] = adj[u][v];
            }
        }
    }

    for (int i = 1; i < n; i++) {
        min += adj[i][parent[i]];
    }

    return min;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie();

    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> adj(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                add_edge(adj, i, j, 2); // Add red sugar strands.
            }
        }

        for (int i = 0; i < m; i++) {
            int c, d;
            cin >> c >> d;
            add_edge(adj, c-1, d-1, 1); // Add black sugar strands.
        }

        cout << "Case #" << t << ": " << prims_mst(adj, n) << endl;
    }
}
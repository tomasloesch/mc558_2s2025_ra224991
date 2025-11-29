#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weightInt;
};

int N, M, S, D;
vector<vector<Edge>> adj;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> M >> S >> D)) return 0;

    adj.resize(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        int wInt = round(w); 
        adj[u].push_back({v, wInt});
        adj[v].push_back({u, wInt});
    }

    int maxW = 500;
    int bucketSize = maxW + 1;
    vector<int> dist(N, INF);
    vector<list<int>> buckets(bucketSize);

    dist[S] = 0;
    buckets[0].push_back(S);

    int cursor = 0;
    int processed = 0;

    while (processed < N) {
        while (buckets[cursor].empty()) {
            cursor = (cursor + 1) % bucketSize;
        }

        while (!buckets[cursor].empty()) {
            int u = buckets[cursor].front();
            buckets[cursor].pop_front();
            processed++;

            if (u == D) {
                cout << dist[D] << endl;
                return 0;
            }

            for (auto& e : adj[u]) {
                int newDist = dist[u] + e.weightInt;
                if (newDist < dist[e.to]) {
                    dist[e.to] = newDist;
                    buckets[newDist % bucketSize].push_back(e.to);
                }
            }
        }
        cursor = (cursor + 1) % bucketSize;
    }

    return 0;
}
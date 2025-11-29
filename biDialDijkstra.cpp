#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <limits>
#include <algorithm>

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

    int bucketSize = 501;
    vector<int> distF(N, INF), distB(N, INF);
    vector<list<int>> bucketsF(bucketSize), bucketsB(bucketSize);
    vector<bool> visF(N, false), visB(N, false);

    distF[S] = 0; bucketsF[0].push_back(S);
    distB[D] = 0; bucketsB[0].push_back(D);

    int curF = 0, curB = 0;
    int mu = INF;
    int processed = 0;

    while (true) {
        while (bucketsF[curF].empty() && bucketsF[curF].size() < (size_t)N * 2) curF = (curF + 1) % bucketSize;
        while (bucketsB[curB].empty() && bucketsB[curB].size() < (size_t)N * 2) curB = (curB + 1) % bucketSize;
        
        if (bucketsF[curF].empty() || bucketsB[curB].empty()) break;

        int dF = distF[bucketsF[curF].front()];
        int dB = distB[bucketsB[curB].front()];

        if (dF + dB >= mu) break;

        if (dF <= dB) {
            while (!bucketsF[curF].empty()) {
                int u = bucketsF[curF].front(); bucketsF[curF].pop_front();
                if (distF[u] < dF) continue; 
                visF[u] = true;

                for (auto& e : adj[u]) {
                    if (distF[u] + e.weightInt < distF[e.to]) {
                        distF[e.to] = distF[u] + e.weightInt;
                        bucketsF[distF[e.to] % bucketSize].push_back(e.to);
                        if (visB[e.to]) mu = min(mu, distF[e.to] + distB[e.to]);
                    }
                }
            }
        } else {
            while (!bucketsB[curB].empty()) {
                int u = bucketsB[curB].front(); bucketsB[curB].pop_front();
                if (distB[u] < dB) continue;
                visB[u] = true;

                for (auto& e : adj[u]) {
                    if (distB[u] + e.weightInt < distB[e.to]) {
                        distB[e.to] = distB[u] + e.weightInt;
                        bucketsB[distB[e.to] % bucketSize].push_back(e.to);
                        if (visF[e.to]) mu = min(mu, distB[e.to] + distF[e.to]);
                    }
                }
            }
        }
    }

    cout << mu << endl;
    return 0;
}
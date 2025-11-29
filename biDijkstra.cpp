#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>

using namespace std;

const double INF = numeric_limits<double>::infinity();

struct Edge {
    int to;
    double weight;
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
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pqF, pqB;
    vector<double> distF(N, INF), distB(N, INF);
    vector<bool> visF(N, false), visB(N, false);

    distF[S] = 0; pqF.push({0, S});
    distB[D] = 0; pqB.push({0, D});

    double mu = INF;

    while (!pqF.empty() && !pqB.empty()) {
        if (pqF.top().first + pqB.top().first >= mu) break;

        if (pqF.top().first < pqB.top().first) {
            int u = pqF.top().second; pqF.pop();
            if (visF[u]) continue;
            visF[u] = true;

            for (auto& e : adj[u]) {
                if (distF[u] + e.weight < distF[e.to]) {
                    distF[e.to] = distF[u] + e.weight;
                    pqF.push({distF[e.to], e.to});
                }
                if (visB[e.to]) mu = min(mu, distF[u] + e.weight + distB[e.to]);
            }
        } else {
            int u = pqB.top().second; pqB.pop();
            if (visB[u]) continue;
            visB[u] = true;

            for (auto& e : adj[u]) {
                if (distB[u] + e.weight < distB[e.to]) {
                    distB[e.to] = distB[u] + e.weight;
                    pqB.push({distB[e.to], e.to});
                }
                if (visF[e.to]) mu = min(mu, distB[u] + e.weight + distF[e.to]);
            }
        }
    }

    cout << fixed << setprecision(3) << mu << endl;
    return 0;
}
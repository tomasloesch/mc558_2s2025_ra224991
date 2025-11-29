#include "gurobi_c++.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Edge {
    int to;
    double weight;
};

int main() {
    int N, M, S, D;
    if (!(cin >> N >> M >> S >> D)) return 0;

    vector<vector<Edge>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    try {
        GRBEnv env = GRBEnv(true);
        env.set("LogToConsole", "0");
        env.start();

        GRBModel model = GRBModel(env);
        
        vector<GRBLinExpr> flow(N, 0.0);
        GRBLinExpr obj = 0.0;

        for (int u = 0; u < N; ++u) {
            for (auto& e : adj[u]) {
                
                string vname = "x_" + to_string(u) + "_" + to_string(e.to);
                GRBVar x = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, vname);
                
                obj += x * e.weight;
                flow[u] += x;      
                flow[e.to] -= x;  
            }
        }

        model.setObjective(obj, GRB_MINIMIZE);

        for (int i = 0; i < N; ++i) {
            if (i == S) model.addConstr(flow[i] == 1.0);
            else if (i == D) model.addConstr(flow[i] == -1.0);
            else model.addConstr(flow[i] == 0.0);
        }

        model.optimize();

        if (model.get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
            cout << fixed << setprecision(3) << model.get(GRB_DoubleAttr_ObjVal) << endl;
        }

    } catch (GRBException e) {
        cerr << "Error code = " << e.getErrorCode() << endl;
        cerr << e.getMessage() << endl;
    } catch (...) {
        cerr << "Exception during optimization" << endl;
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>

#include "solution.hpp"

using namespace std;

typedef long long ll;

int n;
double alpha;
bool best_improvement;
bool use_elite;
vector<vector<ll> > L;
vector<vector<ll> > D;

double worst_on_pool_cost = -99999999;
double best_on_pool_cost = 99999999;
vector<Solution> pool;

void doElite(Solution sol) {
    for (int i = 0; i < pool.size(); i++) {
        Solution p = sol;
        for (int j = 0; j < n; j++) {
            if (p.getMapping(j) == pool[i].getMapping(j)) continue;
            for (int k = j + 1; k < n; k++) {
                if (p.getMapping(k) == pool[i].getMapping(j)) {
                    p.permute(j, k);
                    break;
                }
            }
            Solution pp = p;
            pp.localSearch(best_improvement);
            best_on_pool_cost = min(best_on_pool_cost, pp.getScore());
        }
    }
    if (pool.size() < 10) {
        worst_on_pool_cost = max(worst_on_pool_cost, sol.getScore());
        pool.push_back(sol);
    } else {
        for (int i = 0; i < pool.size(); i++) {
            if (pool[i].getScore() == worst_on_pool_cost) {
                pool[i] = sol;
                break;
            }
        }
        worst_on_pool_cost = -999999999;
        for (int i = 0; i < pool.size(); i++) {
            worst_on_pool_cost = max(worst_on_pool_cost, pool[i].getScore());
        }
    }
}

void showUsage(string name) {
    cout << "Usage: " << name << " --instance <INSTANCE> --alpha <ALPHA> --best_improvement <bool> --elite <bool>" << endl;
}

int main(int argc, char** argv) {
    if (argc < 9) {
        showUsage(argv[0]);
        return -1;
    }
    ifstream fin;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--instance") == 0) {
            fin.open(argv[++i]);
        }
        if (strcmp(argv[i], "--alpha") == 0) {
            alpha = atof(argv[++i]);
        }
        if (strcmp(argv[i], "--best_improvement") == 0) {
            best_improvement = atoi(argv[++i]) == 1;
        }
        if (strcmp(argv[i], "--elite") == 0) {
            use_elite = atoi(argv[++i]) == 1;
        }
    }
    fin >> n;
    L = vector<vector<ll> >(n, vector<ll>(n));
    D = vector<vector<ll> >(n, vector<ll>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fin >> L[i][j];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fin >> D[i][j];
    double best_score = 99999999;
    double best_score_constr = 99999999;
    Solution best_on_pool(n, alpha);

    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    for (int j = 0; j < 100; j++) {
        cout << "Iteration: " << j << endl;
        Solution sol(n, alpha);
        sol.constructionPhase();    
        best_score_constr = min(best_score_constr, sol.getScore());
        sol.localSearch(best_improvement);
        best_score = min(best_score, sol.getScore());

        if (use_elite) {
            doElite(sol);
        }
        double validation = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                validation += L[i][j] * D[sol.getMapping(i)][sol.getMapping(j)];
            }
        }
        double val_cur_w = 0;
        for (int i = 0; i < n; i++) {
            val_cur_w += sol.getCurWeight(i, sol.getMapping(i));
        }
        //cout << "Score = " << (ll)sol.getScore() << endl;
        //cout << "Validation = " << (ll)validation << endl;
        //cout << "Val cur wei = " << (ll) (val_cur_w / 2) << endl;
        if (((ll)sol.getScore() != (ll)validation) || ((ll)sol.getScore() != val_cur_w / 2)) {
            cout << "Error!" << endl;
        }

        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

        if (time_span.count() > 1800) break;
    }
    cout  << fixed << best_score_constr << "\t";
    cout  << fixed <<  best_score << "\t";
    cout  << fixed << best_on_pool_cost << endl;
    /*int opt[12] = {8 , 1, 6, 2, 11, 10, 3, 5, 9, 7, 12, 4};
    double partial = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            partial += L[i][j] * D[opt[i]-1][opt[j]-1];
        }
    }
    cout << "OPT = " << partial << endl;*/
    return 0;
}
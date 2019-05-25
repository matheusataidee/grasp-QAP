#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

#include "solution.hpp"

using namespace std;

typedef long long ll;

int n;
double alpha;
vector<vector<ll> > L;
vector<vector<ll> > D;

void showUsage(string name) {
    cout << "Usage: " << name << " --instance INSTANCE --alpha ALPHA" << endl;
}

int main(int argc, char** argv) {
    if (argc < 5) {
        showUsage(argv[0]);
        return -1;
    }
    ifstream fin;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--instance") == 0) {
            fin.open(argv[++i]);
        }
        if (strcmp(argv[i], "--alpha") ==0) {
            alpha = atof(argv[++i]);
        }
    }
    cout << "Alpha = " << alpha << endl;
    fin >> n;
    L = vector<vector<ll> >(n, vector<ll>(n));
    D = vector<vector<ll> >(n, vector<ll>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fin >> L[i][j];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fin >> D[i][j];
    Solution sol(n, alpha);
    sol.constructionPhase();
    for (int i = 0; i < n; i++) {
        cout << sol.getMapping(i) << " ";
    }
    cout << endl;
    double partial = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            partial += L[i][j] * D[sol.getMapping(i)][sol.getMapping(j)];
        }
    }
    cout << "Partial = " << partial << endl;
    cout << "Score = " << sol.getScore() << endl;

    int opt[12] = {8 , 1, 6, 2, 11, 10, 3, 5, 9, 7, 12, 4};
    partial = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            partial += L[i][j] * D[opt[i]-1][opt[j]-1];
        }
    }
    cout << "OPT = " << partial << endl;
    return 0;
}
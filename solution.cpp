#include "solution.hpp"

Solution::Solution(int _n, double _alpha) {
    n = _n;
    alpha = _alpha;
    score = 0;
    cur_weights = vector<vector<double> > (n, vector<double>(n, 0));
    mapping = vector<int>(n, -1);
    reverse_mapping = vector<int>(n, -1);
    for (int i = 0; i < n; i++) {;
        for (int j = 0; j < n; j++) {
            v.push_back(make_pair(0.0,  make_pair(i, j)));
        }
    }
}

void Solution::constructionPhase() {
    for (int z = 0; z < n; z++) {
        double smaller = v[0].first;
        double bigger = v.back().first;
        double threshold = smaller + (bigger - smaller) * (alpha / 100.0);
        int left = 0, right = v.size();
        while (left < right) {
            int mid = (left + right) / 2;
            if (v[mid].first > threshold) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        int choosen = rand() % left;
        score += v[choosen].first;
        int a = v[choosen].second.first; // Belongs to L
        int b = v[choosen].second.second; // Belongs to D
        mapping[a] = b;
        reverse_mapping[b] = a;
        v.clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cur_weights[i][j] += (L[i][a] * D[j][b]) + (L[a][i] * D[b][j]);
                if (mapping[i] == -1 && reverse_mapping[j] == -1) {
                    v.push_back(make_pair(cur_weights[i][j], make_pair(i, j)));
                }
            }
        }
        sort(v.begin(), v.end());
    }
}

void Solution::localSearch() {
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                int il = mapping[i];
                int jl = mapping[j];
                ll edge = L[i][j] * D[il][jl] + L[j][i] * D[jl][il];
                ll remove_gain = cur_weights[i][il] + cur_weights[j][jl] - edge;
                ll add_cost = cur_weights[i][jl] + cur_weights[j][il] + edge;
                if (remove_gain > add_cost) {
                    change = true;
                    score += add_cost - remove_gain;
                    mapping[i] = jl;
                    mapping[j] = il;
                    reverse_mapping[il] = j;
                    reverse_mapping[jl] = i;
                    for (int k = 0; k < n; k++) {
                        for (int l = 0; l < n; l++) {
                            cur_weights[k][l] -= L[k][i] * D[l][il] + L[i][k] * D[il][l];
                            cur_weights[k][l] += L[k][i] * D[l][jl] + L[i][k] * D[jl][l];

                            cur_weights[k][l] -= L[k][j] * D[l][jl] + L[j][k] * D[jl][l];
                            cur_weights[k][l] += L[k][j] * D[l][il] + L[j][k] * D[il][l];
                        }
                    }
                }
            }
        }
    }
}

double Solution::getCurWeight(int a, int b) {
    return cur_weights[a][b];
}

int Solution::getMapping(int p) {
    return mapping[p];
}

double Solution::getScore() {
    return score;
}
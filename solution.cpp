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

int Solution::getMapping(int p) {
    return mapping[p];
}

double Solution::getScore() {
    return score;
}
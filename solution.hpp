#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

extern vector<vector<ll> > L;
extern vector<vector<ll> > D;

class Solution {
    private:
        int n;
        double alpha;
        ll score;
        vector<vector<double> > cur_weights;
        vector<int> mapping; // L to D
        vector<int> reverse_mapping; // D to L
        vector<pair<double, pair<int, int> > > v;
    public:
        Solution(int _n, double _alpha);

        void constructionPhase();

        void localSearch();

        int getMapping(int p);

        double getCurWeight(int a, int b);

        double getScore();
};

#endif // _SOLUTION_H_
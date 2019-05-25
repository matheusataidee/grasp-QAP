#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int n;
double alpha;
vector<vector<long long> > L;
vector<vector<long long> > D;

void showUsage(string name) {
    cout << "Usage: " << name << " --instance INSTANCE" << endl;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        showUsage(argv[0]);
        return -1;
    }
    ifstream fin;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--instance") == 0) {
            fin.open(argv[++i]);
        }
    }
    fin >> n;
    L = vector<vector<long long> >(n, vector<long long>(n));
    D = vector<vector<long long> >(n, vector<long long>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fin >> L[i][j];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fin >> D[i][j];
    return 0;
}
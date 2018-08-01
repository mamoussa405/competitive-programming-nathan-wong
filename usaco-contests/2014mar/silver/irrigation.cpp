#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1100000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class UnionFind {
private:
    vi p, rank, setSize;
    int numSets;
public:
    UnionFind(int N) {
        setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
        p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) { numSets--;
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
            else                   { p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++; } } }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

int main() {
    freopen("irrigation.in", "r", stdin);
    freopen("irrigation.out", "w", stdout);

    int n, c; cin >> n >> c;
    ii fields[n]; F0R(i, n) cin >> fields[i].A >> fields[i].B;
    vector<pair<long long, ii>> edgeList;
    F0R(i, n) FOR(j, i+1, n) {
        long long cost = (fields[j].A-fields[i].A)*(fields[j].A-fields[i].A)+(fields[j].B-fields[i].B)*(fields[j].B-fields[i].B);
        if (cost < c) continue;
        edgeList.push_back(mp(cost, mp(i, j)));
    }
    sort(edgeList.begin(), edgeList.end());

    long long minCost = 0;
    UnionFind UF(n);
    for (pair<long long, ii> edge : edgeList) {
        if (!UF.isSameSet(edge.B.A, edge.B.B)) {
            UF.unionSet(edge.B.A, edge.B.B);
            minCost += edge.A;
        }
    }
    if (UF.numDisjointSets() > 1) cout << "-1" << endl;
    else cout << minCost << endl;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int n, m, c, q;
const int N = 1000001;

int parent[N];
int depth[N];
unordered_set<int> source;
unordered_set<int> spoiled;
vector<int> adjList[N];
int s[N];
int numOfMagic = 0;
int find(int x) {
    while (parent[x] != -1) x = parent[x];
    return x;
}
bool counted[N];
bool isSource(int x) {
    return source.find(x) != source.end();
}

bool isSpoiled(int x) {
    return spoiled.find(x) != spoiled.end();
}
void Union(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;

    if (isSource(y) && !isSource(x)) {
        swap(x, y);
    } 

    if ((isSource(x) && isSource(y)) || (!isSource(x) && !isSource(y))) {
        if (depth[x] < depth[y]) swap(x, y);
    }

    parent[y] = x;
    if (depth[x] == depth[y]) depth[x]++;
    s[x] += s[y];

    if (isSource(x) && !isSource(y)) {
        numOfMagic += s[y];
    }
    
}

void solve(void){
    cin >> n >> m >> c;
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        s[i] = 1;
    }
    for (int i = 0; i < c; i++) {
        int a;
        cin >> a;
        a--;
        source.insert(a);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    int q;
    cin >> q;
    vector<int> queries;
    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        a--;
        spoiled.insert(a);
        queries.push_back(a);
    }

    for (int u = 0; u < n; u++) {
        if (isSpoiled(u)) continue;
        for (int v : adjList[u]) {
            if (isSpoiled(v)) continue;
            Union(v, u);
        }
    }
    numOfMagic = 0;
    for (int i = 0; i < n; i++) {
        if (isSpoiled(i) || !isSource(i)) continue;
        int p = find(i);
        if (!counted[p]) {
            counted[p] = true;
            numOfMagic += s[p];
        }
    }
    int finalMagic = numOfMagic;
  //  cout << numOfMagic << "\n";
    vector<int> magic(q);
    for (int i = q - 1; i >= 0; i--) {
        int u = queries[i];
        // add to the forest
        
        spoiled.erase(u);
        for (auto v : adjList[u]) {
            
            if (!isSpoiled(v)) {
                Union(v, u);
              //  cout << "union: " << v << " " << u << " " << numOfMagic << "\n";
            }
        }
        if (isSource(u)) {
            numOfMagic++;
        }
        magic[i] = numOfMagic;
    }

    vector<int> ans(q);
    ans[q - 1] = - finalMagic + magic[q - 1];
   
    for (int i = q - 2; i >= 0; i--) {
        ans[i] = magic[i] - magic[i + 1];
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    
    return 0;
}
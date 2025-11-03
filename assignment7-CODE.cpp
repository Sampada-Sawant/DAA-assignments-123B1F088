#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
// ---------------- Greedy Coloring ----------------
void greedyColoring(const vector<set<int>>& graph, vector<int>& result) {
int n = graph.size();
result.assign(n, -1);
result[0] = 0;
vector<bool> available(n, true);
for (int u = 1; u < n; ++u) {
fill(available.begin(), available.end(), true);
for (int adj : graph[u])
if (result[adj] != -1)
available[result[adj]] = false;
int cr;
for (cr = 0; cr < n; ++cr)
if (available[cr])
break;
result[u] = cr;
}
}
// ---------------- Welsh-Powell Coloring ----------------
void welshPowellColoring(const vector<set<int>>& graph, vector<int>& result) {
int n = graph.size();
vector<int> order(n);
for (int i = 0; i < n; ++i)
order[i] = i;
// Sort vertices by degree (descending)
sort(order.begin(), order.end(), [&graph](int a, int b) {
return graph[a].size() > graph[b].size();
});
result.assign(n, -1);
int color = 0;
for (int i = 0; i < n; ++i) {
int u = order[i];
if (result[u] == -1) {
result[u] = color;

for (int j = i + 1; j < n; ++j) {
int v = order[j];
if (result[v] == -1) {
bool conflict = false;
for (int adj : graph[v]) {
if (result[adj] == color) {
conflict = true;
break;
}
}
if (!conflict)
result[v] = color;
}
}
color++;
}
}
}
// ---------------- Main Function ----------------
int main() {
int numCourses, numConflicts;
cout << "Enter number of courses and number of conflicts: ";
cin >> numCourses >> numConflicts;
vector<set<int>> graph(numCourses);
cout << "Enter conflict pairs (u v):\n";
for (int i = 0; i < numConflicts; ++i) {
int u, v;
cin >> u >> v;
if (u >= 0 && v >= 0 && u < numCourses && v < numCourses) {
graph[u].insert(v);
graph[v].insert(u);
}
}
// ---- Greedy Coloring ----
vector<int> colorsGreedy;
greedyColoring(graph, colorsGreedy);
set<int> usedG(colorsGreedy.begin(), colorsGreedy.end());
cout << "\n--- Greedy Coloring ---\n";
cout << "Colors used: " << usedG.size() << endl;

for (int i = 0; i < numCourses; ++i)
cout << "Course " << i << " -> Slot " << colorsGreedy[i] << endl;
// ---- Welsh-Powell Coloring ----
vector<int> colorsWP;
welshPowellColoring(graph, colorsWP);
set<int> usedW(colorsWP.begin(), colorsWP.end());
cout << "\n--- Welsh-Powell Coloring ---\n";
cout << "Colors used: " << usedW.size() << endl;
for (int i = 0; i < numCourses; ++i)
cout << "Course " << i << " -> Slot " << colorsWP[i] << endl;
return 0;
}

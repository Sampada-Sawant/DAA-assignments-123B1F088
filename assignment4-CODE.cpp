#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;
struct Edge {
int to;
int weight;
};
class TrafficNetwork {
int V;
vector<vector<Edge>> adj;
set<int> hospitals;
public:
TrafficNetwork(int vertices) {
V = vertices;
adj.resize(V);
}
void addEdge(int u, int v, int w) {
adj[u].push_back({v, w});
adj[v].push_back({u, w}); // undirected
}
void addHospital(int node) {
hospitals.insert(node);
}
void updateEdgeWeight(int u, int v, int newWeight) {
for (auto &edge : adj[u]) {
if (edge.to == v) edge.weight = newWeight;
}
for (auto &edge : adj[v]) {
if (edge.to == u) edge.weight = newWeight;
}
}
pair<int, vector<int>> shortestPathToNearestHospital(int source) {
vector<int> dist(V, numeric_limits<int>::max());
vector<int> parent(V, -1);
dist[source] = 0;
// Min-heap: (distance, node)
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
pq.push({0, source});
while (!pq.empty()) {
auto [curDist, u] = pq.top(); pq.pop();
if (curDist > dist[u]) continue;
if (hospitals.count(u)) {
// Construct path
vector<int> path;
int v = u;
while (v != -1) {
path.push_back(v);
v = parent[v];
}
reverse(path.begin(), path.end());
return {dist[u], path};
}
for (auto &edge : adj[u]) {
int v = edge.to, w = edge.weight;
if (dist[u] + w < dist[v]) {
dist[v] = dist[u] + w;
parent[v] = u;
pq.push({dist[v], v});
}
}
}
return {-1, {}}; // No hospital reachable
}
};
int main() {
int V, E;
cout << "Enter number of intersections (vertices): ";
cin >> V;
TrafficNetwork city(V);
cout << "Enter number of roads (edges): ";
cin >> E;
cout << "Enter edges (source destination weight):\n";
for (int i = 0; i < E; ++i) {
int u, v, w;
cin >> u >> v >> w;
city.addEdge(u, v, w);
}
int numHospitals;
cout << "Enter number of hospitals: ";
cin >> numHospitals;
cout << "Enter hospital locations:\n";
for (int i = 0; i < numHospitals; ++i) {
int h; cin >> h;
city.addHospital(h);
}
int ambulanceLocation;
cout << "Enter ambulance start location: ";
cin >> ambulanceLocation;
auto [distance, path] = city.shortestPathToNearestHospital(ambulanceLocation);
if (distance != -1) {
cout << "Initial shortest travel time: " << distance << "\nPath: ";
for (int node : path) cout << node << " ";
cout << "\n";
} else {
cout << "No hospital reachable\n";
}
// Real-time update
cout << "Enter edge to update (u v newWeight): ";
int u, v, newWeight;
cin >> u >> v >> newWeight;
city.updateEdgeWeight(u, v, newWeight);
auto [newDistance, newPath] = city.shortestPathToNearestHospital(ambulanceLocation);
if (newDistance != -1) {
cout << "After update shortest travel time: " << newDistance << "\nPath: ";
for (int node : newPath) cout << node << " ";
cout << "\n";
} else {
cout << "No hospital reachable after update\n";
}
return 0;
}

#include <bits/stdc++.h>
using namespace std;
struct Edge {
int toStage;
int toNode;
int weight;
};
// DP function for multistage graph
pair<int, vector<pair<int,int>>> MultiStageDP(int stages, int sourceStage, int sourceNode, int destStage,
int destNode, vector<vector<vector<Edge>>>& graph) {
// cost[stage][node] = min cost from this node to destination
vector<vector<int>> cost(stages);
vector<vector<pair<int,int>>> nextNode(stages); // stores next stage/node
for(int i=0;i<stages;i++) {
int n = graph[i].size();
cost[i].assign(n, INT_MAX);
nextNode[i].assign(n, {-1,-1});
}
cost[destStage][destNode] = 0; // cost to reach destination from destination = 0
// Iterate stages backward
for(int stage = stages-2; stage >= 0; stage--) {
for(int u = 0; u < graph[stage].size(); u++) {
for(auto &e : graph[stage][u]) {
if(cost[e.toStage][e.toNode] != INT_MAX && cost[stage][u] > e.weight +
cost[e.toStage][e.toNode]) {
cost[stage][u] = e.weight + cost[e.toStage][e.toNode];
nextNode[stage][u] = {e.toStage, e.toNode};
}
}
}
}
// Reconstruct path
vector<pair<int,int>> path;
int currStage = sourceStage;
int currNode = sourceNode;
while(currStage != -1 && currNode != -1) {
path.push_back({currStage, currNode});
auto nxt = nextNode[currStage][currNode];
currStage = nxt.first;
currNode = nxt.second;
}
return {cost[sourceStage][sourceNode], path};
}
int main() {
int stages;
cout << "Enter number of stages: ";
cin >> stages;
vector<vector<vector<Edge>>> graph(stages);
vector<int> nodesInStage(stages);
for(int i=0;i<stages;i++) {
cout << "Enter number of nodes in stage " << i << ": ";
cin >> nodesInStage[i];
graph[i].resize(nodesInStage[i]);
}
cout << "Enter edges in format: stage_from node_from stage_to node_to weight\n";
cout << "Enter -1 to stop input.\n";
while(true) {
int sFrom, nFrom, sTo, nTo, w;
cin >> sFrom;
if(sFrom == -1) break;
cin >> nFrom >> sTo >> nTo >> w;
graph[sFrom][nFrom].push_back({sTo, nTo, w});
}
int sourceStage, sourceNode, destStage, destNode;
cout << "Enter source stage and node: ";
cin >> sourceStage >> sourceNode;

cout << "Enter destination stage and node: ";
cin >> destStage >> destNode;
auto result = MultiStageDP(stages, sourceStage, sourceNode, destStage, destNode, graph);
cout << "Minimum cost: " << result.first << endl;
cout << "Optimal Path (stage,node): ";
for(auto p : result.second) {
cout << "(" << p.first << "," << p.second << ") ";
}
cout << endl;
return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct Item {
string name;
int weight;
int utility;
};

pair<int, vector<int>> Knapsack(int N, int W, vector<Item>& items) {
// dp[i][w] = max utility using first i items with weight limit w
vector<vector<int>> dp(N+1, vector<int>(W+1, 0));

// Build DP table
for(int i=1;i<=N;i++) {
for(int w=0;w<=W;w++) {
if(items[i-1].weight <= w) {
dp[i][w] = max(dp[i-1][w], items[i-1].utility + dp[i-1][w - items[i-1].weight]);
} else {
dp[i][w] = dp[i-1][w];
}
}
}

// Reconstruct selected items
vector<int> selectedItems;
int w = W;
for(int i=N; i>0 && w>0; i--) {
if(dp[i][w] != dp[i-1][w]) {
selectedItems.push_back(i-1); // store index of included item
w -= items[i-1].weight;
}
}
reverse(selectedItems.begin(), selectedItems.end());

return {dp[N][W], selectedItems};
}

int main() {
int N, W;
cout << "Enter number of items: ";
cin >> N;
cout << "Enter truck capacity (W): ";
cin >> W;

vector<Item> items(N);
cout << "Enter item name, weight and utility value for each item:\n";
for(int i=0;i<N;i++) {
cin >> items[i].name >> items[i].weight >> items[i].utility;
}

auto result = Knapsack(N, W, items);
cout << "\nMaximum total utility: " << result.first << endl;
cout << "Items to include in the truck: ";
for(int idx : result.second) {
cout << items[idx].name << " ";
}
cout << endl;

return 0;
}

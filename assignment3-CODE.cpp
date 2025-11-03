#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
// Structure for relief items
struct Item {
string name;
double weight; // in kg
double value; // utility value
bool divisible; // true if item can be fractioned
// Value-to-weight ratio
double ratio() const {
return value / weight;
}
};
// Comparator for sorting items by descending ratio
bool cmp(const Item &a, const Item &b) {
return a.ratio() > b.ratio();
}
// Fractional Knapsack function
double MaxUtilFractional(vector<Item> &items, double W) {
sort(items.begin(), items.end(), cmp); // sort by descending value/weight
double totalValue = 0.0;
double remainingCapacity = W;
cout << fixed << setprecision(2);
for (auto &item : items) {
if (remainingCapacity == 0) break;
if (item.weight <= remainingCapacity) {
// Take whole item
totalValue += item.value;
remainingCapacity -= item.weight;
cout << "Taking full: " << item.name
<< " (weight: " << item.weight
<< ", value: " << item.value << ")\n";
} else if (item.divisible) {
// Take fraction of item
double fraction = remainingCapacity / item.weight;
double takenWeight = remainingCapacity; // actual weight taken
double takenValue = fraction * item.value;
totalValue += takenValue;
remainingCapacity = 0;
cout << "Taking fraction: " << item.name
<< " (weight: " << takenWeight
<< ", value: " << takenValue << ")\n";
} else {
// Cannot take indivisible item
cout << "Skipping indivisible: " << item.name
<< " (weight: " << item.weight << ")\n";
}
}
return totalValue;
}
int main() {
int n;
double W;
cout << "Enter number of relief items: ";
cin >> n;
cout << "Enter boat weight limit (kg): ";
cin >> W;
vector<Item> items(n);
for (int i = 0; i < n; ++i) {
cout << "\nEnter details for item " << i+1 << ":\n";
cout << "Name: ";
cin >> items[i].name;
cout << "Weight (kg): ";
cin >> items[i].weight;
cout << "Utility value: ";
cin >> items[i].value;
cout << "Is divisible (1 for yes, 0 for no): ";
int d; cin >> d;
items[i].divisible = (d == 1);
}
double maxValue = MaxUtilFractional(items, W);
cout << "\nMaximum utility value achievable: " << maxValue << "\n";
// Complexity Report
cout << "\n--- Complexity Report ---\n";
cout << "Time Complexity: O(n log n) due to sorting + O(n) traversal = O(n log n)\n";
cout << "Space Complexity: O(1) auxiliary (in-place sorting), O(n) for storing items\n";

return 0;
}

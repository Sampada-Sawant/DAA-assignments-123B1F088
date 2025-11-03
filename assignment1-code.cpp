#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib> // for rand(), srand()
#include <ctime> // for time()
#include <cstdint> // for int64_t, uint64_t
using namespace std;
// Structure to represent a customer order
struct Order {
uint64_t id;
int64_t timestamp;
string details;
bool operator<(const Order& other) const {
return timestamp < other.timestamp;
}

};
// Function to merge two sorted halves
void merge(vector<Order>& src, vector<Order>& dest, size_t left, size_t mid, size_t right) {
size_t i = left;
size_t j = mid;
size_t k = left;
while (i < mid && j < right) {
if (src[i].timestamp <= src[j].timestamp) {
dest[k] = src[i];
i++;
} else {
dest[k] = src[j];
j++;
}
k++;
}
while (i < mid) {
dest[k] = src[i];
i++;
k++;
}
while (j < right) {
dest[k] = src[j];
j++;
k++;
}
}
// Iterative Merge Sort (bottom-up)
void mergeSort(vector<Order>& arr) {
size_t n = arr.size();
if (n <= 1) return;
vector<Order> temp(n);
vector<Order>* src = &arr;
vector<Order>* dest = &temp;
for (size_t width = 1; width < n; width = 2 * width) {
for (size_t i = 0; i < n; i += 2 * width) {
size_t left = i;
size_t mid = (i + width < n) ? (i + width) : n;

size_t right = (i + 2 * width < n) ? (i + 2 * width) : n;
merge(*src, *dest, left, mid, right);
}
// Manual pointer swap (no std::swap)
vector<Order>* tempPtr = src;
src = dest;
dest = tempPtr;
}
// If sorted data is in temp, copy back manually
if (src != &arr) {
for (size_t i = 0; i < n; ++i) {
arr[i] = (*src)[i];
}
}
}
// Generate random customer orders using rand()
vector<Order> generateOrders(size_t count) {
vector<Order> orders;
orders.reserve(count);
srand((unsigned int)time(0));
for (size_t i = 0; i < count; ++i) {
Order o;
o.id = i + 1;
o.timestamp = 1700000000000LL + rand() % 1000000; // random timestamp variation
o.details = "Order_" + to_string(o.id);
orders.push_back(o);
}
return orders;
}
int main() {
ios::sync_with_stdio(false);
cin.tie(nullptr);
size_t N;
cout << "Enter the number of customer orders to sort: ";
cin >> N;

// Generate random dataset
vector<Order> orders = generateOrders(N);
// Measure sorting time
auto start = chrono::high_resolution_clock::now();
mergeSort(orders);
auto end = chrono::high_resolution_clock::now();
chrono::duration<double> duration = end - start;
// Verify sorting correctness
bool sorted = true;
for (size_t i = 1; i < orders.size(); ++i) {
if (orders[i - 1].timestamp > orders[i].timestamp) {
sorted = false;
break;
}
}

cout << "\n--- Merge Sort Report ---\n";
cout << "Total Orders Sorted : " << N << "\n";
cout << "Execution Time : " << duration.count() << " seconds\n";
cout << "Sorting Correctness : " << (sorted ? "SUCCESS " : "FAILED ") << "\n";

// Calculate approximate space usage (arr + temp)
size_t orderSize = sizeof(Order);
double spaceUsed = 2.0 * orderSize * N / (1024.0 * 1024.0); // MB
cout << "Approx. Space Used : " << spaceUsed << " MB\n";

// Print first few sorted results
cout << "\nFirst 5 Sorted Orders:\n";
for (size_t i = 0; i < 5 && i < orders.size(); ++i) {
cout << "Order ID: " << orders[i].id
<< " Timestamp: " << orders[i].timestamp
<< " Details: " << orders[i].details << "\n";
}

// Print complexity report
cout << "\n--- Complexity Analysis ---\n";
cout << "Time Complexity:\n";
cout << " Best Case : O(n log n)\n";
cout << " Average Case : O(n log n)\n";
cout << " Worst Case : O(n log n)\n";

cout << "\nSpace Complexity:\n";
cout << " Auxiliary Space : O(n)\n";
cout << " Stable Sorting : Yes\n";
return 0;
}

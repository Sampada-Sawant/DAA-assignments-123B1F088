#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
// Movie structure
struct Movie {
string title;
double imdbRating;
int releaseYear;
int watchPopularity;
void display() const {
cout << title << " | IMDB: " << imdbRating
<< " | Year: " << releaseYear
<< " | Popularity: " << watchPopularity << "\n";
}
};
// Compare function pointer type
typedef bool (*CompareFunc)(const Movie&, const Movie&);
// Comparison functions
bool compareByRating(const Movie &a, const Movie &b) { return a.imdbRating < b.imdbRating; }
bool compareByYear(const Movie &a, const Movie &b) { return a.releaseYear < b.releaseYear; }
bool compareByPopularity(const Movie &a, const Movie &b) { return a.watchPopularity < b.watchPopularity; }
// Partition function
int partition(vector<Movie>& arr, int low, int high, CompareFunc cmp) {
Movie pivot = arr[high];
int i = low - 1;
for (int j = low; j < high; ++j) {
if (cmp(arr[j], pivot)) {

swap(arr[i + 1], arr[j]);
i++;
}
}
swap(arr[i + 1], arr[high]);
return i + 1;
}
// QuickSort function
void quickSort(vector<Movie>& arr, int low, int high, CompareFunc cmp) {
if (low < high) {
int pi = partition(arr, low, high, cmp);
quickSort(arr, low, pi - 1, cmp);
quickSort(arr, pi + 1, high, cmp);
}
}
// Generate random movies using rand()
vector<Movie> generateMovies(int n) {
vector<Movie> movies;
movies.reserve(n);
srand((unsigned int)time(0));
for (int i = 0; i < n; ++i) {
Movie m;
m.title = "Movie_" + to_string(i + 1);
m.imdbRating = (rand() % 51) / 10.0 + 5.0; // 5.0 to 10.0
m.releaseYear = 2000 + rand() % 24; // 2000-2023
m.watchPopularity = rand() % 100000;
movies.push_back(m);
}
return movies;
}
int main() {
ios::sync_with_stdio(false);
cin.tie(nullptr);
int N = 100000; // number of movies
cout << "Generating " << N << " random movies...\n";
vector<Movie> movies = generateMovies(N);
cout << "Select sorting parameter:\n";
cout << "1. IMDB Rating\n2. Release Year\n3. Watch Popularity\nChoice: ";
int choice;

cin >> choice;
CompareFunc cmp;
if (choice == 1) cmp = compareByRating;
else if (choice == 2) cmp = compareByYear;
else if (choice == 3) cmp = compareByPopularity;
else {
cout << "Invalid choice. Defaulting to IMDB Rating.\n";
cmp = compareByRating;
}
// Measure sorting time
auto start = chrono::high_resolution_clock::now();
quickSort(movies, 0, N - 1, cmp);
auto end = chrono::high_resolution_clock::now();
chrono::duration<double> duration = end - start;
// Space complexity calculation
size_t orderSize = sizeof(Movie);
double spaceUsedMB = orderSize * N / (1024.0 * 1024.0); // vector memory only
cout << "\n--- QuickSort Report ---\n";
cout << "Total Movies Sorted : " << N << "\n";
cout << "Execution Time : " << duration.count() << " seconds\n";
cout << "Approx. Space Used : " << spaceUsedMB << " MB (excluding stack)\n";
// Display first 10 movies
cout << "\nFirst 10 Sorted Movies:\n";
for (int i = 0; i < 10; ++i) {
movies[i].display();
}
// Complexity report
cout << "\n--- Complexity Analysis ---\n";
cout << "Time Complexity:\n";
cout << " Best Case : O(n log n)\n";
cout << " Average Case : O(n log n)\n";
cout << " Worst Case : O(n^2) (rare with random pivot)\n";
cout << "Space Complexity:\n";
cout << " Auxiliary Space : O(log n) (recursive stack)\n";
cout << " Stable Sorting : No\n";
return 0;
}

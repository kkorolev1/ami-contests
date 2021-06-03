#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> m >> n;

    vector<bool> primes(n+1, true);

    for (int i = 2; i * i <= n; ++i) {
        if (primes[i]) {
            for (int j = i * i; j <= n; j += i)
                primes[j] = false;
        }
    }

    bool found_prime = false;
    for (int i = m; i <= n; ++i) {
        if (primes[i]) {
            cout << i << "\n";
            found_prime = true;
        }
    }
    if (!found_prime)
        cout << "Absent\n";
}
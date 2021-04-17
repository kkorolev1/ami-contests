#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int max_a, max_b, max_c, volume;

int main() {
    freopen("input.txt", "r", stdin);
    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> max_a >> max_b >> max_c >> volume;

    struct Vertex {
        int a, b, c;

        Vertex operator+(const Vertex& other) {
            return Vertex{a + other.a, b + other.b, c + other.c};
        }

        bool operator==(const Vertex& other) const {
            return a == other.a && b == other.b && c == other.c;
        }

        bool operator!=(const Vertex& other) const {
            return !(*this == other);
        }

        size_t operator()(const Vertex& v) const {
            return hash<int>()(1e6 * v.a + 1e3 * v.b + v.c);
        }
    };

    using ll = long long;
    queue<Vertex> q;
    unordered_set<Vertex, Vertex> visited;
    unordered_map<Vertex, ll, Vertex> dist;
    Vertex start{0, 0, 0};

    q.push(start);
    visited.insert(start);
    dist.emplace(start, 0);
    const ll MAX_VALUE = numeric_limits<ll>::max();
    ll min_dist = MAX_VALUE;

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        vector<Vertex> dx = {
                {-v.a, 0, 0}, {0, -v.b, 0}, {0, 0, -v.c},
                {max_a - v.a, 0, 0}, {0, max_b - v.b, 0}, {0, 0, max_c - v.c},
                {-min(max_b - v.b, v.a), min(max_b - v.b, v.a), 0}, {-min(max_c - v.c, v.a), 0, min(max_c - v.c, v.a)},
                {min(max_a - v.a, v.b), -min(max_a - v.a, v.b), 0}, {0, -min(max_c - v.c, v.b), min(max_c - v.c, v.b)},
                {min(max_a - v.a, v.c), 0, -min(max_a - v.a, v.c)}, {0, min(max_b - v.b, v.c), -min(max_b - v.b, v.c)}};

        for (auto& d : dx) {
            auto u = v + d;

            if (v != u && u.a >= 0 && u.a <= max_a && u.b >= 0 && u.b <= max_b && u.c >= 0 && u.c <= max_c) {
                if (visited.find(u) == visited.end()) {
                    if (u.a == volume || u.b == volume || u.c == volume) {
                        min_dist = min(min_dist, dist[v] + 1);
                    } else {
                        dist[u] = dist[v] + 1;
                        visited.insert(u);
                        q.push(u);
                    }
                }
            }
        }
    }

    cout << ((min_dist != MAX_VALUE) ? min_dist : -1) << "\n";

    return 0;
}

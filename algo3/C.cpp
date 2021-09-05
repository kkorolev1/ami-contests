#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);

    ios::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int numTeams;
    cin >> numTeams;

    using Queue = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>;
    Queue q;

    for (int i = 0; i < numTeams; ++i) {
        int points;
        cin >> points;
        q.push({points, i});
    }

    vector<vector<int>> table(numTeams, vector<int>(numTeams));

    for (int i = 0; i < numTeams; ++i) {
        auto [lastTeamPts, lastTeamIndex] = q.top();
        q.pop();

        Queue tmpQ;

        while (!q.empty() && lastTeamPts > 0) {
            auto [teamPts, teamIndex] = q.top();
            q.pop();
            --lastTeamPts;
            tmpQ.push({teamPts-1, teamIndex});
            table[teamIndex][lastTeamIndex] = table[lastTeamIndex][teamIndex] = 1;
        }

        while (!q.empty()) {
            auto [teamPts, teamIndex] = q.top();
            q.pop();
            tmpQ.push({teamPts-2, teamIndex});
            table[teamIndex][lastTeamIndex] = 2;
            table[lastTeamIndex][teamIndex] = 0;
        }

        q = move(tmpQ);
    }

    for (int i = 0; i < numTeams; ++i) {
        for (int j = 0; j < numTeams; ++j) {
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}

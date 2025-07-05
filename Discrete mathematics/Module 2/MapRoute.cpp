#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    auto generateRandomPath = [&]() {
        int x = 0, y = 0;
        int sum = grid[x][y];
        while (x != N-1 || y != N-1) {
            if (x == N-1) y++;
            else if (y == N-1) x++;
            else {
                if (rand() % 2 == 0) x++;
                else y++;
            }
            sum += grid[x][y];
        }
        return sum;
    };

    int initialGuess = INF;
    for (int i = 0; i < 10; ++i) {
        initialGuess = min(initialGuess, generateRandomPath());
    }

    vector<vector<int>> dist(N, vector<int>(N, INF));
    dist[0][0] = grid[0][0];
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    pq.push({dist[0][0], {0, 0}});

    while (!pq.empty()) {
        auto [current_dist, pos] = pq.top();
        auto [x, y] = pos;
        pq.pop();

        if (current_dist > dist[x][y]) continue;
        if (x == N-1 && y == N-1) break;  // Дошли до конца

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                int new_dist = dist[x][y] + grid[nx][ny];
                if (new_dist < dist[nx][ny]) {
                    dist[nx][ny] = new_dist;
                    pq.push({new_dist, {nx, ny}});
                }
            }
        }
    }

    cout << dist[N-1][N-1] << endl;
    return 0;
}
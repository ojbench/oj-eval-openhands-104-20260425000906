
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_N = 1005;
int grid[MAX_N][MAX_N];
int dist_from_start[MAX_N][MAX_N];
int dist_from_home[MAX_N][MAX_N];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

void bfs(int start_x, int start_y, int n, int m, int dist[MAX_N][MAX_N]) {
    queue<Point> q;
    
    memset(dist, -1, sizeof(int) * MAX_N * MAX_N);
    
    q.push(Point(start_x, start_y));
    dist[start_x][start_y] = 0;
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                dist[nx][ny] == -1 && grid[nx][ny] != 1) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    int start_x = -1, start_y = -1;
    int home_x = -1, home_y = -1;
    vector<Point> umbrella_shops;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start_x = i;
                start_y = j;
            } else if (grid[i][j] == 3) {
                home_x = i;
                home_y = j;
            } else if (grid[i][j] == 4) {
                umbrella_shops.push_back(Point(i, j));
            }
        }
    }
    
    if (start_x == -1 || home_x == -1 || umbrella_shops.empty()) {
        cout << -1 << endl;
        return 0;
    }
    
    // BFS from start and home once
    bfs(start_x, start_y, n, m, dist_from_start);
    bfs(home_x, home_y, n, m, dist_from_home);
    
    int min_distance = -1;
    
    // Check each umbrella shop
    for (Point shop : umbrella_shops) {
        if (dist_from_start[shop.x][shop.y] != -1 && 
            dist_from_home[shop.x][shop.y] != -1) {
            int total_dist = dist_from_start[shop.x][shop.y] + dist_from_home[shop.x][shop.y];
            if (min_distance == -1 || total_dist < min_distance) {
                min_distance = total_dist;
            }
        }
    }
    
    cout << min_distance << endl;
    
    return 0;
}

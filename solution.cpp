
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_N = 1005;
int grid[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

vector<Point> bfs(int start_x, int start_y, int n, int m) {
    queue<Point> q;
    vector<Point> targets;
    
    memset(dist, -1, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    
    q.push(Point(start_x, start_y));
    dist[start_x][start_y] = 0;
    visited[start_x][start_y] = 1;
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        if (grid[curr.x][curr.y] == 3 || grid[curr.x][curr.y] == 4) {
            targets.push_back(curr);
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                !visited[nx][ny] && grid[nx][ny] != 1) {
                visited[nx][ny] = 1;
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
    
    return targets;
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
    
    // BFS from start to find distances to all umbrella shops and home
    vector<Point> reachable_from_start = bfs(start_x, start_y, n, m);
    
    int min_distance = -1;
    
    // Check each umbrella shop
    for (Point shop : umbrella_shops) {
        if (dist[shop.x][shop.y] == -1) continue; // unreachable
        
        // BFS from umbrella shop to find distance to home
        queue<Point> q;
        int shop_dist[MAX_N][MAX_N];
        memset(shop_dist, -1, sizeof(shop_dist));
        
        q.push(shop);
        shop_dist[shop.x][shop.y] = 0;
        
        while (!q.empty()) {
            Point curr = q.front();
            q.pop();
            
            if (curr.x == home_x && curr.y == home_y) {
                int total_dist = dist[shop.x][shop.y] + shop_dist[home_x][home_y];
                if (min_distance == -1 || total_dist < min_distance) {
                    min_distance = total_dist;
                }
                break;
            }
            
            for (int i = 0; i < 4; i++) {
                int nx = curr.x + dx[i];
                int ny = curr.y + dy[i];
                
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                    shop_dist[nx][ny] == -1 && grid[nx][ny] != 1) {
                    shop_dist[nx][ny] = shop_dist[curr.x][curr.y] + 1;
                    q.push(Point(nx, ny));
                }
            }
        }
    }
    
    cout << min_distance << endl;
    
    return 0;
}

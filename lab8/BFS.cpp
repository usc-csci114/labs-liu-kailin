#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <vector>

using namespace std;

// helper functions
void readGraph(const string &filename, map<char, set<char>> &graph);
void bfs(const map<char, set<char>> &graph, char start_vertex);

// main

int main(int argc, char *argv[]) {

    string filename = argv[1];
    map<char, set<char>> graph;

    // read graph
    readGraph(filename, graph);

    //BFS on the graph
    char start_vertex;
    while (true) {
        cout << "Enter a starting value for BFS (or 'q' to quit): ";
        cin >> start_vertex;
        if (start_vertex == 'q') {
            break;
        }
        bfs(graph, start_vertex);
    }

    return 0;
}

// function implementation

// reading graph
void readGraph(const string &filename, map<char, set<char>> &graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    int vertex_count = 0;
    set<char> vertices;

    while (getline(file, line)) {
        istringstream iss(line);
        char vertex;
        iss >> vertex;
        vertices.insert(vertex);

        string neighbor;
        set<char> neighbors;
        while (iss >> neighbor) {
            if (neighbor != "0") {
                neighbors.insert(neighbor[0]);
            }
        }
        graph[vertex] = neighbors;
        vertex_count++;
    }

    file.close();

    // Output the processed result
    cout << "In file" << filename << ". Found " << vertex_count << " vertices: ";
    for (char v : vertices) {
        cout << v << " ";
    }
    cout << endl;
}

// bfs search
void bfs(const map<char, set<char>> &graph, char start_vertex) {
    if (graph.find(start_vertex) == graph.end()) {
        cout << "Error: Starting vertex " << start_vertex << " not found in the graph." << endl;
        return;
    }

    map<char, int> depth;
    map<char, bool> visited;
    queue<char> q;

    q.push(start_vertex);
    depth[start_vertex] = 0;
    visited[start_vertex] = true;

    vector<pair<char, int>> bfs_order;

    while (!q.empty()) {
        char v = q.front();
        q.pop();
        bfs_order.emplace_back(v, depth[v]);

        for (char neighbor : graph.at(v)) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
                depth[neighbor] = depth[v] + 1;
            }
        }
    }

    // Output the BFS result
    cout << "BFS starting at " << start_vertex << ": ";
    for (size_t i = 0; i < bfs_order.size(); ++i) {
        cout << bfs_order[i].first << ":" << bfs_order[i].second;
        if (i < bfs_order.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

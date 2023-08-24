#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 0x3f3f3f3f // Define infinity as a very large number

// Structure to store information about a node in the network
struct Node {
    int id; // Node ID
    bool isSink; // Whether this node is the sink node or not
    vector<pair<int, int>> neighbors; // Vector of pairs of neighboring node IDs and link weights
};

// Function to detect congestion in the network
bool detectCongestion(vector<Node>& nodes, int T) {
    queue<int> q;
    vector<int> dist(nodes.size(), INF);
    vector<bool> visited(nodes.size(), false);
    int startNode = 0; // Start BFS from the sink node
    q.push(startNode);
    visited[startNode] = true;
    dist[startNode] = 0;

    // Run BFS to find the shortest path to each node from the sink node
    while (!q.empty()) {
        int currNode = q.front();
        q.pop();
        visited[currNode] = false;

        for (auto neighbor : nodes[currNode].neighbors) {
            int neighborNode = neighbor.first;
            int neighborWeight = neighbor.second;

            if (dist[currNode] + neighborWeight < dist[neighborNode]) {
                dist[neighborNode] = dist[currNode] + neighborWeight;

                // If the new shortest path to this node is longer than some threshold T,
                // then there is congestion in the network
                if (dist[neighborNode] > T) {
                    return true;
                }

                if (!visited[neighborNode]) {
                    q.push(neighborNode);
                    visited[neighborNode] = true;
                }
            }
        }
    }

    return false;
}

//we have to add a q-length varibale and check the condition 

int main() {
    // Example usage of the congestion detection function
    vector<Node> nodes; // Vector of all nodes in the network
    nodes.push_back({0, true, {{1, 5}, {2, 10}, {3, 15}}}); // Sink node with 3 neighbors
    nodes.push_back({1, false, {{0, 5}, {2, 5}}}); // Node 1 with 2 neighbors
    nodes.push_back({2, false, {{0, 10}, {1, 5}, {3, 5}}}); // Node 2 with 3 neighbors
    nodes.push_back({3, false, {{0, 15}, {2, 5}}});// Node 3 with 2 neighbors
    nodes.push_back({4, false, {{0, 20}, {1, 5}, {3, 5},{4,5}}});
    nodes.push_back({5, false, {{0, 25}, {2, 5}}});
    nodes.push_back({6, false, {{0, 30}, {1, 5}, {3, 5},{4,5},{5,5}}});
    nodes.push_back({7, false, {{0, 35}, {2, 5}}});
    nodes.push_back({8, false, {{0, 30}, {1, 5}, {3, 5},{4,5},{5,5},{6,5}}});
    nodes.push_back({9, false, {{0, 35}, {2, 5}}});
    nodes.push_back({10, false, {{0, 40}, {1, 5}, {3, 5},{4,5},{5,5},{6,5},{7,5}}});
    
    
    
    int T = 25; // Set the threshold for congestion detection to 25
    bool congestionDetected = detectCongestion(nodes, T);

    if (congestionDetected) {
        cout << "Congestion detected in the network!" << endl;
    } else {
        cout << "No congestion detected in the network." << endl;
    }

    return 0;
}
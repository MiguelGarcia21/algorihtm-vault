#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

class Node {
public:
    std::string name;
    std::vector<Node*> neighbors;

    Node(const std::string& n) : name(n) {}
};

std::vector<Node*> topologicalSortBFS(const std::vector<Node*>& nodes) {
    std::unordered_map<Node*, int> inDegree;

    for (Node* node : nodes) {
        if (!inDegree.count(node)) inDegree[node] = 0;
        for (Node* neighbor : node->neighbors) {
            inDegree[neighbor]++;
        }
    }

    std::queue<Node*> q;
    for (Node* node : nodes) {
        if (inDegree[node] == 0) {
            q.push(node);
        }
    }

    std::vector<Node*> sorted;
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        sorted.push_back(current);

        for (Node* neighbor : current->neighbors) {
            if (--inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (sorted.size() != nodes.size()) {
        throw std::runtime_error("Graph has a cycle!");
    }

    return sorted;
}

int main() {
    Node* A = new Node("A");
    Node* B = new Node("B");
    Node* C = new Node("C");
    Node* D = new Node("D");

    A->neighbors.push_back(B);
    B->neighbors.push_back(C);
    A->neighbors.push_back(C);
    C->neighbors.push_back(D);

    std::vector<Node*> graph = {A, B, C, D};

    try {
        std::vector<Node*> sorted = topologicalSortBFS(graph);
        std::cout << "Topological Sort (BFS): ";
        for (Node* node : sorted) {
            std::cout << node->name << " ";
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    delete A; delete B; delete C; delete D;
    return 0;
}

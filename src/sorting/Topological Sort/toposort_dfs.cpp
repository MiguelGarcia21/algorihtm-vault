#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <string>

class Node {
public:
    std::string name;
    std::vector<Node*> neighbors;

    Node(const std::string& n) : name(n) {}
};

void dfs(Node* node, std::unordered_set<Node*>& visited, std::stack<Node*>& result) {
    visited.insert(node);
    for (Node* neighbor : node->neighbors) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, visited, result);
        }
    }
    result.push(node);
}

std::vector<Node*> topologicalSortDFS(const std::vector<Node*>& nodes) {
    std::unordered_set<Node*> visited;
    std::stack<Node*> result;

    for (Node* node : nodes) {
        if (visited.find(node) == visited.end()) {
            dfs(node, visited, result);
        }
    }

    std::vector<Node*> sorted;
    while (!result.empty()) {
        sorted.push_back(result.top());
        result.pop();
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

    std::vector<Node*> sorted = topologicalSortDFS(graph);
    std::cout << "Topological Sort (DFS): ";
    for (Node* node : sorted) {
        std::cout << node->name << " ";
    }

    delete A; delete B; delete C; delete D;
    return 0;
}
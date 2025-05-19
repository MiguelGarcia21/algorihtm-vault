#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

struct Node {
    char ch;
    int freq;
    std::shared_ptr<Node> left, right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r) 
        : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

struct Compare {
    bool operator()(std::shared_ptr<Node> const& a, std::shared_ptr<Node> const& b) {
        return a->freq > b->freq;
    }
};

void generateCodes(std::shared_ptr<Node> root, const std::string& code,
                   std::unordered_map<char, std::string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

std::string encode(const std::string& text, std::unordered_map<char, std::string>& huffmanCode) {
    std::string encoded = "";
    for (char ch : text) {
        encoded += huffmanCode[ch];
    }
    return encoded;
}

std::string decode(std::string encoded, std::shared_ptr<Node> root) {
    std::string result = "";
    std::shared_ptr<Node> current = root;

    for (char bit : encoded) {
        if (bit == '0') current = current->left;
        else current = current->right;

        if (!current->left && !current->right) {
            result += current->ch;
            current = root;
        }
    }

    return result;
}

int main() {
    std::string text;
    std::cout << "Enter text to encode: ";
    std::getline(std::cin, text);

    std::unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Compare> pq;
    for (auto pair : freq) {
        pq.push(std::make_shared<Node>(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        pq.push(std::make_shared<Node>(left, right));
    }

    std::shared_ptr<Node> root = pq.top();

    std::unordered_map<char, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    std::cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCode) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    std::string encoded = encode(text, huffmanCode);
    std::cout << "\nEncoded string: " << encoded << "\n";

    std::string decoded = decode(encoded, root);
    std::cout << "Decoded string: " << decoded << "\n";

    return 0;
}

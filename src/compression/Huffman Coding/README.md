# Huffman Coding in C++

## 📌 Description
This project implements the **Huffman Coding algorithm** in C++ for **lossless data compression**. Huffman coding reduces the average length of the representation of characters in a string by assigning **shorter codes to more frequent characters** and longer codes to less frequent ones.

This is commonly used in file compression tools such as `ZIP`, and formats like `PNG` and `MP3` (as part of the compression pipeline).

---

## 🧠 How Huffman Coding Works

1. **Frequency Counting**: Count how many times each character appears in the input.
2. **Priority Queue**: Build a min-heap (priority queue) with all characters based on frequency.
3. **Huffman Tree Construction**: Merge the two least frequent nodes until one node (the root) remains.
4. **Code Generation**: Traverse the tree to assign binary codes to each character.
5. **Encoding**: Replace characters in the input with their binary Huffman codes.
6. **Decoding**: Reconstruct the original input using the Huffman tree and encoded binary string.

---

## 🛠️ Compilation

You can compile with `g++`:

```bash
g++ -std=c++17 main.cpp -o huffman
./huffman
````

---

## 📥 Example Input

When running the program, input any string when prompted, for example:

```
Enter a string to encode:
hello world
```

---

## 📤 Example Output

```text
Character Huffman Codes:
'd': 000
'h': 001
'e': 010
' ': 011
'l': 10
'o': 110
'r': 1110
'w': 1111

Encoded string: 001010101010110011110111011111000

Decoded string: hello world
```

---

## 📚 Key concepts

* Greedy algorithms
* Binary trees
* Priority queues (min-heap)
* Encoding & decoding logic
* Data compression theory

---


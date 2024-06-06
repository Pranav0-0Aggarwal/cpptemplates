const int ALPHABET_SIZE = 26;
class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;
    int alphabetSize;

public:
    Trie(int size) {
        alphabetSize = size;
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return current->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return true;
    }

    bool remove(const string& word) {
        TrieNode* current = root;
        TrieNode* parent = nullptr;
        int index;
        for (char ch : word) {
            index = ch - 'a';
            if (!current->children[index]) {
                return false;
            }
            parent = current;
            current = current->children[index];
        }
        if (!current->isEndOfWord) {
            return false;
        }
        current->isEndOfWord = false;

        for (int i = 0; i < alphabetSize; ++i) {
            if (current->children[i]) {
                return true;
            }
        }
        delete current;
        parent->children[index] = nullptr;
        return true;
    }

    bool check(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return current != nullptr && current->isEndOfWord;
    }
};

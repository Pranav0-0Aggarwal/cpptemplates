class Node{   
    Node *links[2];

public:
    int freq[2];
    Node(){
        links[0] = links[1] = nullptr;
        freq[0] = freq[1] = 0;
    }
    void createLink(int b){
        links[b] = new Node();
    }
    Node *goToLink(int b){
        return links[b];
    }
};

class Trie{
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }
    void insert(int x){
        Node *t = root;
        for (int i = 31; i >= 0; i--){
            int b = (x >> i) & 1;
            if (!t->freq[b])
                t->createLink(b);
            t->freq[b]++;
            t = t->goToLink(b);
        }
    }
    void remove(int x){
        Node *t = root;
        for (int i = 31; i >= 0; i--){
            int b = (x >> i) & 1;
            t->freq[b]--;
            t = t->goToLink(b);
        }
    }
    int get(int y){
        Node *t = root;
        int res = 0;
        for (int i = 31; i >= 0; i--){
            int by = (y >> i) & 1, w = 1 - by;
            if (t->freq[w]){
                res = res | (1 << i);
                t = t->goToLink(w);
            }
            else{
                t = t->goToLink(by);
            }
        }
        return res;
    }
};

/*
How to use
  1
  1. Add edges with addEge(u,v)
  2. initialize the HLD construction with init() method
  3. update values for all the nodes
*/


template <typename T>
class HLD {
public:
    int n, current_pos;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos;
    vector<T> segtree;
    T ide;

    HLD(int n, T x) : n(n), ide(x), current_pos(0) {
        adj.resize(n + 1);
        parent.resize(n + 1);
        depth.resize(n + 1);
        heavy.resize(n + 1, -1);
        head.resize(n + 1);
        pos.resize(n + 1);
        segtree.resize(2 * n, ide);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init() {
        parent[1] = -1;
        depth[1] = 0;
        dfs(1);
        decompose(1, 1);
        build();
    }

    void update(int u, T value) {
        updatePos(pos[u], value);
    }

    T queryPath(int u, int v) {
        T res = ide;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]])
                swap(u, v);
            res = combine(res, querySegmentTree(pos[head[v]], pos[v] + 1));
            v = parent[head[v]];
        }
        if (depth[u] > depth[v])
            swap(u, v);
        res = combine(res, querySegmentTree(pos[u], pos[v] + 1));
        return res;
    }

private:
    int dfs(int v) {
        int size = 1, max_c_size = 0;
        for (int c : adj[v]) {
            if (c == parent[v]) continue;
            parent[c] = v;
            depth[c] = depth[v] + 1;
            int c_size = dfs(c);
            size += c_size;
            if (c_size > max_c_size) {
                max_c_size = c_size;
                heavy[v] = c;
            }
        }
        return size;
    }

    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = current_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h);
        for (int c : adj[v]) {
            if (c == parent[v] || c == heavy[v]) continue;
            decompose(c, c);
        }
    }

    void build() {
        for (int i = n - 1; i > 0; --i)
            segtree[i] = combine(segtree[i << 1], segtree[i << 1 | 1]);
    }

    void updatePos(int p, T value) {
        for (segtree[p += n] = value; p > 1; p >>= 1)
            segtree[p >> 1] = combine(segtree[p], segtree[p ^ 1]);
    }

    T querySegmentTree(int l, int r) {
        T res = ide;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = combine(res, segtree[l++]);
            if (r & 1) res = combine(res, segtree[--r]);
        }
        return res;
    }

    T combine(const T& a, const T& b) {
        return a + b;
    }
};

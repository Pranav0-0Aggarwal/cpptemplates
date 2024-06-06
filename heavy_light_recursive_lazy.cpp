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
    vector<T> segtree, lazy;
    T ide;
    
    HLD(int n, T x) : n(n), ide(x) {
        adj.resize(n + 1);
        parent.resize(n + 1);
        depth.resize(n + 1);
        heavy.resize(n + 1, -1);
        head.resize(n + 1);
        pos.resize(n + 1);
        segtree.resize(4 * n, ide);
        lazy.resize(4 * n, ide);
        current_pos = 0;
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
        build(0, n - 1, 1);
    }

    void update(int u,int v, T value) {
        updatePath(u,v, value);
    }

    T queryPath(int u, int v) {
        T res = ide;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]])
                swap(u, v);
            res = combine(res, querySegmentTree(0, n - 1, pos[head[v]], pos[v], 1));
            v = parent[head[v]];
        }
        if (depth[u] > depth[v])
            swap(u, v);
        res = combine(res, querySegmentTree(0, n - 1, pos[u], pos[v], 1));
        return res;
    }

private:
    int dfs(int v) {
        int size = 1, max_c_size = 0;
        for (int c : adj[v]) {
            if (c == parent[v]) continue;
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
        return size;
    }

    void decompose(int v, int h) {
        head[v] = h, pos[v] = current_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h);
        for (int c : adj[v]) {
            if (c == parent[v] || c == heavy[v]) continue;
            decompose(c, c);
        }
    }

    void build(int start, int end, int node) {
        if (start == end) {
            segtree[node] = ide;
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, 2 * node);
        build(mid + 1, end, 2 * node + 1);
        segtree[node] = combine(segtree[2 * node], segtree[2 * node + 1]);
    }

    void applyLazy(int node, int start, int end) {
        if (lazy[node] != ide) {
            apply(segtree[node], lazy[node], end - start + 1);
            if (start != end) {
                apply(lazy[node * 2], lazy[node], 1);
                apply(lazy[node * 2 + 1], lazy[node], 1);
            }
            lazy[node] = ide;
        }
    }

    void updateSegmentTree(int start, int end, int l, int r, T value, int node) {
        applyLazy(node, start, end);
        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            apply(lazy[node], value, 1);
            applyLazy(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        updateSegmentTree(start, mid, l, r, value, 2 * node);
        updateSegmentTree(mid + 1, end, l, r, value, 2 * node + 1);
        segtree[node] = combine(segtree[2 * node], segtree[2 * node + 1]);
    }

    T querySegmentTree(int start, int end, int l, int r, int node) {
        applyLazy(node, start, end);
        if (start > r || end < l) return ide;
        if (start >= l && end <= r) return segtree[node];
        int mid = (start + end) / 2;
        T left_result = querySegmentTree(start, mid, l, r, 2 * node);
        T right_result = querySegmentTree(mid + 1, end, l, r, 2 * node + 1);
        return combine(left_result, right_result);
    }

    void updatePath(int u, int v, T value) {
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]])
                swap(u, v);
            updateSegmentTree(0, n - 1, pos[head[v]], pos[v], value, 1);
            v = parent[head[v]];
        }
        if (depth[u] > depth[v])
            swap(u, v);
        updateSegmentTree(0, n - 1, pos[u], pos[v], value, 1);
    }

    T combine(T a, T b) {
        return a + b;
    }

    void apply(T &a, T b, int length) {
        a += b * length;
    }
};

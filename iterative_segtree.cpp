template<typename T>
class segtree {
    vector<T> tree;
    int n;
    T ide;

    T combine(const T& a, const T& b) {
        T ans=l+r;
        return ans;
    }
public:
    segtree(vector<T>& arr, T x) {
        n = arr.size();
        ide = x;
        tree.assign(2 * n, ide);
        build(arr);
    }

    void build(vector<T>& arr) {
        for (int i = 0; i < n; ++i) {
            tree[n + i] = arr[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void update(int idx, T val) {
        idx += n;
        tree[idx] = val;
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
        }
    }

    T query(int l, int r) {
        l += n;
        r += n;
        T ansl = ide;
        T ansr = ide;
        bool left=true;
        bool right=true;
        while (l < r) {
            if (l & 1){
                if(left){
                    ansl=tree[l++];
                    left=false;
                }else{
                    ansl=combine(ansl,tree[l++]);
                }
            }
            if (r & 1){
                if(right){
                    ansr=tree[--r];
                    right=false;
                }else{
                    ansr=combine(tree[--r],ansr);
                }
            }
            l >>= 1;
            r >>= 1;
        }
        return combine(ansl, ansr);
    }
};

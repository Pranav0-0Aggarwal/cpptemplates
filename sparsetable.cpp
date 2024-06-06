class sparsetable {
public:
    int combine(int l,int r){
        return l&r;
    }
    sparsetable(const vector<int>& arr) {
        n = arr.size();
        k = log2(n) + 1;
        st = vector<vector<int>>(n, vector<int>(k));
        build(arr);
    }
    int query(int L, int R) {
        int j = log2(R - L + 1);
        return combine(st[L][j], st[R - (1 << j) + 1][j]);
    }
private:
    int n, k;
    vector<vector<int>> st;
    void build(const vector<int>& arr) {
        for (int i = 0; i < n; i++) {
            st[i][0] = arr[i];
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; (i + (1 << j) - 1) < n; i++) {
                st[i][j] = combine(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }
};

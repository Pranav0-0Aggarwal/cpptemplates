/*
  How To use
  1. eg. SqrtDecomp<int> s(a,sz,0)
*/

template<typename T>
class SqrtDecomp{
private:
    const int SIZE;
    vector<T> blocks;
    vector<T> arr;
    int n;
    T ide;

public:
    T combine(const T& a, const T& b) {
        return a + b;
    }

    SqrtDecomp(const vector<T>& a, const int blockSize, T x) : SIZE(blockSize), ide(x) {
        n = a.size();
        arr = a;
        blocks.resize((n + SIZE - 1) / SIZE, ide);
        for (int i = 0; i < n; ++i) {
            blocks[i / SIZE] = combine(blocks[i / SIZE], a[i]);
        }
    }

    T query(int l, int r) {
        T sum = ide;
        int startBlock = l / SIZE;
        int endBlock = r / SIZE;

        if (startBlock == endBlock) {
            for (int i = l; i <= r; ++i) {
                sum = combine(sum, arr[i]);
            }
        } else {
            for (int i = l; i < (startBlock + 1) * SIZE; ++i) {
                sum = combine(sum, arr[i]);
            }
            for (int i = startBlock + 1; i < endBlock; ++i) {
                sum = combine(sum, blocks[i]);
            }
            for (int i = endBlock * SIZE; i <= r; ++i) {
                sum = combine(sum, arr[i]);
            }
        }
        return sum;
    }

    void update(int idx, T val) {
        int blockIndex = idx / SIZE;
        blocks[blockIndex] = combine(blocks[blockIndex], val - arr[idx]);
        arr[idx] = val;
    }
};

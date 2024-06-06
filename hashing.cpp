/*
  How to Use
    1. b.size() should be equal to m.size()
    2. use setRandomBases to set base, and hardcode m
*/

class fhstring {
private:
    vector<vector<long long>> dp;
    vector<vector<long long>> inv;
    long long n;
    vector<long long> bases;
    vector<long long> mods;

public:
    fhstring(string& s, vector<long long> bases, vector<long long> mods)
        : bases(bases), mods(mods) {
        n = s.size();
        int num_bases = bases.size();
        dp.resize(num_bases, vector<long long>(n));
        inv.resize(num_bases, vector<long long>(n));

        vector<vector<long long>> p_pow(num_bases, vector<long long>(n, 1));

        for (int k = 0; k < num_bases; ++k) {
            inv[k][0] = 1;
            dp[k][0] = (s[0] - 'a' + 1);
        }

        for (long long j = 1; j < n; ++j) {
            char c = s[j];
            for (int k = 0; k < num_bases; ++k) {
                p_pow[k][j] = (p_pow[k][j - 1] * bases[k]) % mods[k];
                inv[k][j] = binPow(p_pow[k][j], mods[k] - 2, mods[k]);
                dp[k][j] = (dp[k][j - 1] + (c - 'a' + 1) * p_pow[k][j]) % mods[k];
            }
        }
    }

    static long long binPow(long long a, long long b, long long mod) {
        long long res = 1;
        while (b > 0) {
            if (b & 1)
                res = (res * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }
        return res;
    }

    vector<long long> substrhash(long long L, long long R) {
        if (R < L) return vector<long long>(bases.size(), 0);
        int num_bases = bases.size();
        vector<long long> res(num_bases);
        for (int k = 0; k < num_bases; ++k) {
            res[k] = dp[k][R];
            if (L > 0) {
                res[k] = (res[k] - dp[k][L - 1] + mods[k]) % mods[k];
                res[k] = (res[k] * inv[k][L]) % mods[k];
            }
        }
        return res;
    }
};

vector<long long> b;
vector<long long> m;

void setRandomBases(int n) {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 rng(seed);
    uniform_int_distribution<int> base_distribution(31, 100000);

    b.resize(n);
    for (int i = 0; i < n; ++i) {
        b[i] = base_distribution(rng);
    }
}

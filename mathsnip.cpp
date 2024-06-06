
/*
  How to use
  1. Declare a global variable MOD
  2. Invoke factorial, for precomputation
*/

vector<long long> fact;
long long power(long long a, long long b, int m = MOD) {
    if (a == 0) return 0LL;
    if (b == 0) return 1LL;
    long long result;
    if (b % 2) {
        result = a * power(a, b - 1, m) % m;
    } else {
        long long half = power(a, b / 2, m);
        result = half * half % m;
    }
    return result % m;
}

void factorial(int n, int m = MOD) {
    fact.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        fact[i] = (i * fact[i - 1]) % m;
    }
}

long long inverse(long long x, int m = MOD) {
    return power(x, m - 2, m);
}

long long nCr(long long n, long long r, int m = MOD) {
    if (r > n) return 0;
    long long x = (fact[r] * fact[n - r]) % m;
    long long y = fact[n];
    return (y * inverse(x, m)) % m;
}

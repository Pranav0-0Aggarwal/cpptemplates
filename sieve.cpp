/*
  How to use
  1. sieve(1e5)
*/

vector<bool> Prime;
vector<int> spf;
void sieve(int s) {
    Prime.resize(s + 1, 1);
    spf.resize(s + 1, s + 1);
    for(int i = 2 ; i <= s ; i++)   if(Prime[i]) {
        spf[i] = min(spf[i], i);
        for(int j = i ; j * i <= s ; j++)
            Prime[j * i] = 0, spf[j * i] = min(i, spf[j * i]);
    }
}

#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353, root = 31, root_pw = (1 << 23);

int pwr[32];
int getRev(int x) {
    pwr[0] = x;
    for (int i = 1; i <= 30; ++i) {
        pwr[i] = (pwr[i-1] * 1ll * pwr[i-1]) % mod;
    }
    int res = 1, v = mod - 2;
    for (int i = 30; i >= 0; --i) {
        int bit = (v >> i) & 1;
        if (bit) {
            res = (res * 1ll * pwr[i]) % mod;
        }
    }
    return res;
}

const int root_1 = getRev(root);

void print(const vector<int>& p) {
    for (size_t i = 0; i < p.size(); ++i) {
        cout << p[i] << " ";
    }
    cout << endl;
}

struct fft {
    int reorder(vector<int>& v) {
        int n = int(v.size());
        int sz = 1;
        while ((1 << sz) < n) {
            sz += 1;
        }
        assert((1 << sz) == n);
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            int cur = 1, idx = 0;
            for (int j = sz - 1; j >= 0; --j) {
                if (((i >> j) & 1) == 1) {
                    idx += cur;
                }
                cur <<= 1;
            }
            res[i] = v[idx];
        }
        v = res;
        return sz;
    }

    void calc(vector<int>& v, bool invert) {
        int sz = reorder(v);
        int n = v.size();
        for (int t = 1; t <= sz; ++t) {
            int len = (1 << t);
            int proot = root;
            if (invert) {
                proot = root_1;
            }
            for (int i = 23; i > t; --i) {
                proot = (proot * 1ll * proot) % mod;
            }
            for (int i = 0; i < n; i += len) {
                int w = 1, lidx = i, ridx = i + (len >> 1);
                for (int j = 0; j < (len >> 1); ++j) {
                    int x = v[lidx];
                    int y = (v[ridx] * 1ll * w) % mod;
                    v[lidx] = x + y;
                    if (v[lidx] >= mod) {
                        v[lidx] -= mod;
                    }
                    v[ridx] = x - y;
                    if (v[ridx] < 0) {
                        v[ridx] += mod;
                    }
                    w = (w * 1ll * proot) % mod;
                    lidx += 1;
                    ridx += 1;
                }
            }
        }

        if (invert) {
            int rev = getRev(n);
            for (int i = 0; i < n; ++i) {
                v[i] = (v[i] * 1ll * rev) % mod;
            }
        }
    }



    vector<int> multiply(const vector<int>& a, const vector<int>& b) {
        vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        size_t n = 1;
        while (n < max (a.size(), b.size()))  n <<= 1;
        n <<= 1;
        fa.resize(n),  fb.resize(n);
        calc(fa, false);
        calc(fb, false);
        for (size_t i=0; i<n; ++i) {
            fa[i] = (fa[i] * 1ll * fb[i]) % mod;
        }
        calc(fa, true);
        return fa;
    }

};


int main() {
    //freopen("input.txt", "r", stdin);
    fft f;
    vector<int> a({1, 1, 1}), b({1, 1, 1});
    print(f.multiply(a, b));
    return 0;
}

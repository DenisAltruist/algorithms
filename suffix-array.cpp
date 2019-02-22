#include <bits/stdc++.h>

using namespace std;

vector<int> buildSuffixArray(const vector<int>& s, int alphabetSize) {
    int n = s.size();
    vector<int> c(n), cnt(n), p(n), pn(n), cn(n);

    vector<int> chIsUsed(alphabetSize), compressedIdxByCh(alphabetSize);
    for (int i = 0; i < n; ++i) {
        chIsUsed[s[i]] = 1;
    }
    int curIdx = 0;
    for (int i = 0; i < alphabetSize; ++i) {
        if (chIsUsed[i]) {
            compressedIdxByCh[i] = curIdx++;
        }
    }
    for (int i = 0; i < n; ++i) {
        c[i] = compressedIdxByCh[s[i]];
        cnt[c[i]] += 1;
    }
    for (int i = 1; i < n; ++i) {
        cnt[i] += cnt[i-1];
    }
    for (int i = n - 1; i >= 0; --i) {
        p[--cnt[c[i]]] = i;
    }
    for (int h = 0; (1 << h) < n; ++h) {
        cnt.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) {
                pn[i] += n;
            }
        }
        for (int i = 0; i < n; ++i) {
            cnt[c[pn[i]]] += 1;
        }
        for (int i = 1; i < n; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i) {
            int x = p[i] + (1 << h);
            int y = p[i-1] + (1 << h);
            if (x >= n) x -= n;
            if (y >= n) y -= n;
            if (c[p[i]] != c[p[i-1]] || c[x] != c[y]) {
                classes += 1;
            }
            cn[p[i]] = classes - 1;
        }
        c = cn;
    }
    return p;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    vector<int> v;
    for (size_t i = 0; i < s.size(); ++i) {
        v.push_back(s[i]);
    }
    vector<int> p = buildSuffixArray(v, 256);
    string ans = s.substr(p[0], s.size()) + s.substr(0, p[0]);
    cout << ans << endl; // minimal lexicographical shift
}

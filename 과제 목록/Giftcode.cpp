#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

using namespace std;

#define HM 100000000

unsigned long PNUhash(unsigned long long x, int salt) {
    x = x + salt;
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x % HM;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, salt;
    if (!(cin >> N >> salt)) return 0;

    unordered_set<unsigned long long> used_keys;
    used_keys.reserve(N);

    int cnt_valid = 0;
    int cnt_invalid = 0;
    int cnt_used = 0;

    string code;
    for (int i = 0; i < N; i++) {
        cin >> code;

        if (code.length() != 20) {
            cnt_invalid++;
            continue;
        }

        unsigned long long K = 0;
        unsigned long long H_extracted = 0;

        for (int j = 2; j <= 5; j++) K = K * 10 + (code[j] - '0');
        for (int j = 8; j <= 11; j++) K = K * 10 + (code[j] - '0');
        for (int j = 14; j <= 17; j++) K = K * 10 + (code[j] - '0');

        H_extracted = H_extracted * 10 + (code[0] - '0');
        H_extracted = H_extracted * 10 + (code[1] - '0');
        H_extracted = H_extracted * 10 + (code[6] - '0');
        H_extracted = H_extracted * 10 + (code[7] - '0');
        H_extracted = H_extracted * 10 + (code[12] - '0');
        H_extracted = H_extracted * 10 + (code[13] - '0');
        H_extracted = H_extracted * 10 + (code[18] - '0');
        H_extracted = H_extracted * 10 + (code[19] - '0');

        unsigned long long H_calculated = PNUhash(K, salt);

        if (H_calculated != H_extracted) {
            cnt_invalid++;
        } else {
            if (used_keys.find(K) != used_keys.end()) {
                cnt_used++;
            } else {
                cnt_valid++;
                used_keys.insert(K);
            }
        }
    }

    cout << cnt_valid << "\n";
    cout << cnt_invalid << "\n";
    cout << cnt_used << "\n";

    return 0;
}
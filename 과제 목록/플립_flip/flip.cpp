#include <iostream>
#include <list>
using namespace std;
struct Node {
    long long start, end;
};

int main() {
    long long N, a, b, count = 0, s, e;
    int k;
    list<Node> P;
    cin >> N >> k;
    while (k--) {
        cin >> a >> b;
        auto it = P.begin();
        while (it != P.end()) {
            s = it->start, e = it->end;
            if (b < s) {
                if (a<=b) P.insert(it, { a, b });
                a = b + 1;
                break;
            }
            if (a > e) { ++it; continue; }
            if (a < s) P.insert(it, { a, s - 1 });
			if (s < a) P.insert(it, { s, a - 1 });
            it = P.erase(it);
            if (e > b) P.insert(it, { b + 1, e });
            a = max(a, e+1);
        }
        if (a <= b) P.insert(P.end(), { a, b });

		it = P.begin();
		while (it != P.end()){
            auto next_it = next(it);
            if (next_it == P.end()) break;
            if (next_it->start <= it->end + 1) {
                it->end = max(it->end, next_it->end);
                P.erase(next_it);
            }
            else ++it;
        }
    }
    for (auto& node : P) count += node.end - node.start + 1;
    cout << P.size() << " " << count;
}
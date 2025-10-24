#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

struct Applicant {
    int id;
    int score;

    bool operator<(const Applicant& other) const {
        if (score != other.score) {
            return score > other.score;
        }
        return id > other.id;
    }
};

struct University {
    string grad_code;
    vector<Applicant> applicants;
    long long total_score = 0;

    void add_applicant(int new_id, int new_score) {
        Applicant new_app = { new_id, new_score };
        auto it = lower_bound(applicants.begin(), applicants.end(), new_app);
        applicants.insert(it, new_app);
        total_score += new_score;
    }
};

map<string, University> database;
int k;

void handle_pop(int p, int q) {
    vector<University*> canu_list;
    for (auto& pair : database) {
        if (pair.second.applicants.size() >= k) {
            canu_list.push_back(&pair.second);
        }
    }

    if (canu_list.empty()) {
        return;
    }

    sort(canu_list.begin(), canu_list.end(), [&](const University* a, const University* b) {
        if (a->applicants.size() != b->applicants.size()) {
            return a->applicants.size() > b->applicants.size();
        }
        return a->total_score > b->total_score;
        });

    vector<Applicant> global_rank_list;
    bool more_applicants_exist = true;
    for (size_t rank_idx = 0; more_applicants_exist; ++rank_idx) {
        more_applicants_exist = false;
        for (University* uni : canu_list) {
            if (rank_idx < uni->applicants.size()) {
                global_rank_list.push_back(uni->applicants[rank_idx]);
                more_applicants_exist = true;
            }
        }
    }

    set<int> ids_to_delete;
    bool first_print = true;
    for (int i = p - 1; i < q && i < global_rank_list.size(); ++i) {
        if (!first_print) {
            cout << " ";
        }
        cout << global_rank_list[i].id;
        ids_to_delete.insert(global_rank_list[i].id);
        first_print = false;
    }

    if (!ids_to_delete.empty()) {
        cout << "\n";
    }

    for (auto& pair : database) {
        University& uni = pair.second;
        uni.applicants.erase(
            remove_if(uni.applicants.begin(), uni.applicants.end(),
                [&](const Applicant& app) {
                    if (ids_to_delete.count(app.id)) {
                        uni.total_score -= app.score;
                        return true;
                    }
                    return false;
                }),
            uni.applicants.end()
        );
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N >> k;

    for (int i = 0; i < N; ++i) {
        string command;
        cin >> command;

        if (command == "POP") {
            int p, q;
            cin >> p >> q;
            handle_pop(p, q);
        }
        else {
            int id, score;
            cin >> id >> score;
            database[command].grad_code = command;
            database[command].add_applicant(id, score);
        }
    }

    return 0;
}
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

struct file {
    string name;
    int size, address;
};

using pos = list<file>::iterator;

list<file> files;
map<string, vector<pos>> file_map;
int capacity, free_size;

int main() {
    int V, size;
    string cmd, name;
    cin >> V;
    free_size = capacity = V;
    files.push_back({ "free", capacity, 0 });

    while (cin >> cmd && cmd != "end") {
        if (cmd == "compact") {
            int addr = 0;
            for (auto it = files.begin(); it != files.end(); ) {
                if (it->name == "free")
                    it = files.erase(it);
                else {
                    it->address = addr;
                    addr += it->size;
                    ++it;
                }
            }
            for (auto& data : file_map) {
                vector<pos>& vec = data.second;
                if (vec.size() < 2) continue;
                for (auto it = vec.begin(); it + 1 != vec.end();) {
                    pos p = *it, next_p = *(it+1);
                    if (p->address + p->size == next_p->address && p->name == next_p->name) {
                        p->size += next_p->size;
                        vec.erase(it + 1);
                        files.erase(next_p);
                    }
                    else ++it;
                }
            }

            if (free_size > 0)
                files.push_back({ "free", free_size, addr });
            continue;
        }

        cin >> name;
        if (cmd == "write") {
            cin >> size;
            if (file_map.count(name))
                cout << "error\n";
            else if (size > free_size)
                cout << "diskfull\n";
            else {
                free_size -= size;
                pos enough_pos = files.end();
                for (auto it = files.begin(); it != files.end(); ++it) {
                    if (it->name == "free" && it->size >= size) {
                        enough_pos = it;
                        break;
                    }
                }

                if (enough_pos != files.end()) {
                    pos new_it = files.insert(enough_pos, { name, size, enough_pos->address });
                    file_map[name].push_back(new_it);

                    enough_pos->address += size;
                    enough_pos->size -= size;
                    if (enough_pos->size == 0) files.erase(enough_pos);
                }
                else {
                    for (auto it = files.begin(); it != files.end() && size > 0; ++it) {
                        if (it->name == "free") {
                            if (it->size <= size) {
                                it->name = name;
                                file_map[name].push_back(it);
                                size -= it->size;
                            }
                            else {
                                pos new_it = files.insert(it, { name, size, it->address });
                                file_map[name].push_back(new_it);

                                it->address += size;
                                it->size -= size;
                                size = 0;
                            }
                        }
                    }
                }
            }
        }
        else if (!file_map.count(name))
            cout << "error\n";
        else if (cmd == "delete") {
            for (auto p : file_map[name]) {
                p->name = "free";
                free_size += p->size;

                auto next_it = next(p);
                if (next_it != files.end() && next_it->name == "free") {
                    p->size += next_it->size;
                    files.erase(next_it);
                }

                if (p != files.begin()) {
                    auto prev_it = prev(p);
                    if (prev_it->name == "free") {
                        prev_it->size += p->size;
                        files.erase(p);
                    }
                }
            }
            file_map.erase(name);
        }
        else if (cmd == "show") {
            for (auto p : file_map[name])
                cout << p->address << " ";
            cout << "\n";
        }
    }
}

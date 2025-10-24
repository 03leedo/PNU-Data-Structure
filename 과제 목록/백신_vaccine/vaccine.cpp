#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct person {
	int order, id, age;
	char sex;
};

template<char primary_sex>
struct cmp {
	bool operator()(person a, person b) {
		if (a.sex != b.sex) {
			if (a.sex == primary_sex) return false;
			else return true;
		}
		else return a.order > b.order;
	}
};
template<char T>
void print_queue(priority_queue<person, vector<person>, cmp<T>>& pq) {
	while (!pq.empty()){
		person p = pq.top();
		cout << p.id << "\n";
		pq.pop();
	}
}
void print_queue(queue<person>& pq) {
	while (!pq.empty()) {
		person p = pq.front();
		cout << p.id << "\n";
		pq.pop();
	}
}
priority_queue<person, vector<person>, cmp<'M'>> Old;
priority_queue<person, vector<person>, cmp<'F'>> Adult;
queue<person> Child;

int main() {
	int N, count = 1;
	person p;
	cin >> N;
	while (N--) {
		cin >> p.id >> p.age >> p.sex;
		p.order = count++;
		if(p.age >= 61) Old.push(p);
		else if (p.age >= 16) Adult.push(p);
		else Child.push(p);
	}
	print_queue(Old);
	print_queue(Child);
	print_queue(Adult);
}
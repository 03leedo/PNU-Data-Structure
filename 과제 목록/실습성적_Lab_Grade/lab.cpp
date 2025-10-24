#include <iostream>
#include <vector>
#include <algorithm>   
#include <numeric>

using namespace std;
vector<int> priority(5);
class Student {
public:
	string name;
	vector<int> scores;
	vector<int> report;
	Student(string name, vector<int>& points) : name(name), scores(points) {
		report.resize(5);
		for(int i = 0; i < 5; i++)
			report[i] = get_metric(priority[i]);
	}
	int getMin() {
		int min_n = 101;
		for (int num : scores) {
			if (num == 0) continue;
			min_n = min(min_n, num);
		}
		return min_n;
	}
	int get_metric(int id) {
		switch (id) {
			case 1: return scores.size() - count(scores.begin(), scores.end(), 0);
			case 2: return accumulate(scores.begin(), scores.end(),0);
			case 3: return getMin();
			case 4: return *max_element(scores.begin(), scores.end());
			case 5: return count(scores.begin(), scores.end(), 100);
		}
	}
};
int main() {
    int N, k;
	cin >> N >> k;
	for (int i = 0; i < 5; i++)
		cin >> priority[i];
	vector<Student> students;
	while (N--){
		vector<int> scores(k);
		string name;
		cin >> name;
		for(int i = 0 ; i < k; i++)
			cin >> scores[i];
		students.push_back(Student(name,scores));
	}
	sort(students.begin(), students.end(), 
		[&](Student& a, Student& b) {
			for (int i = 0; i < 5; i++) {
				if (a.report[i] != b.report[i])
					return a.report[i] > b.report[i];
			}
			return a.name < b.name;
		});
	for(Student &student : students)
		cout << student.name << '\n';
}
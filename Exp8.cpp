#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef struct student {
    string name;
    double score;
} student;

typedef vector<student> vec_stu;

int main() {
    vec_stu students;
    string name;
    double score;
    while(cin >> name >> score && !(name.compare("0") == 0 && score == 0)) {
        
    }
}
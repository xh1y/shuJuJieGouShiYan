#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

typedef struct student {
    string name;
    double score;
    friend ostream &operator<<(ostream &os, student s);
} student;
ostream &operator<<(ostream &os, student s) {
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << s.name << " " << setprecision(2) << s.score;
    return os;
}

typedef vector<student> vec_stu;

void insertSort(vec_stu &students); // important
void binaryInsertSort(vec_stu &students); // important
void shellInsert(vec_stu &students, int dk);
void shellSort(vec_stu &students, int t); // important
void bubbleSort(vec_stu &students); // important
int partition(vec_stu &students, int low, int high);
void quickSortPart(vec_stu &students, int low, int high);
void quickSort(vec_stu &students); // important
void selectSort(vec_stu &students);
void getLevel(vec_stu students);
int main() {
    vec_stu students;
    string name;
    double score;
    students.push_back({ "", 0 });  // 插入一个空的
    while (cin >> name >> score && !(name.compare("0") == 0 && score == 0)) {
        student a;
        a.name = name;
        a.score = score;
        students.push_back(a);
    }
    cout << "Please choose the way to sort:" << endl;
    cout << "1. Straight insertion sort" << endl;
    cout << "2. Binary insertion sort" << endl;
    cout << "3. Shell's sort" << endl
        << "4. Bubble sort" << endl
        << "5. Quick sort" << endl
        << "6. Selection sort" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        insertSort(students);
        break;
    case 2:
        binaryInsertSort(students);
        break;
    case 3:
        shellSort(students, students.size());
        break;
    case 4:
        bubbleSort(students);
        break;
    case 5:
        quickSort(students);
        break;
    case 6:
        selectSort(students);
        break;
    default:
        cout << "No valid input.";
        return 0;

    }
    for (int i = 1; i < students.size(); i++) {
        cout << i << " " << students[i] << endl;
    }
    getLevel(students);
    return 0;
}

void insertSort(vec_stu &students) {
    int j;
    for (int i = 2; i < students.size(); i++) {
        if (students[i].score > students[i - 1].score) {
            students[0] = students[i];
            students[i] = students[i - 1];
            for (j = i - 1; students[0].score > students[j].score; j--) {
                students[j + 1] = students[j];
            }
            students[j + 1] = students[0];
        }
    }
}

void binaryInsertSort(vec_stu &students) {
    int j;
    for (int i = 2; i < students.size(); i++) {
        students[0] = students[i];
        int low = 1, high = i - 1;
        while (low <= high) {
            int m = (low + high) / 2;
            if (students[0].score > students[m].score) {
                high = m - 1;
            } else {
                low = m + 1;
            }
        }
        for (int j = i - 1; j >= high + 1; j--) {
            students[j + 1] = students[j];
        }
        students[high + 1] = students[0];
    }
}

void shellInsert(vec_stu &students, int dk) {
    int j;
    for (int i = dk + 1; i < students.size(); i++) {
        if (students[i].score > students[i - dk].score) {
            students[0] = students[i];
            for (j = i - dk; j > 0 && students[0].score > students[j].score; j -= dk) {
                students[j + dk] = students[j];
            }
            students[j + dk] = students[0];
        }
    }
}

void shellSort(vec_stu &students, int t) {
    for (int k = 0; k <= t; k++) {
        // dt[k] = ;
        shellInsert(students, static_cast<int>(pow(2, t - k + 1) - 1));
    }
}

void bubbleSort(vec_stu &students) {
    int m = students.size() - 1;
    bool swapped = true;
    while (m > 0 and swapped) {
        swapped = false;
        for (int j = 1; j <= m; j++) {
            if (students[j].score < students[j + 1].score) {
                swapped = true;
                auto temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
        --m;
    }
}

int partition(vec_stu &students, int low, int high) {
    students[0] = students[low];
    int key = students[low].score;
    while (low < high) {
        while (low < high and students[high].score <= key) {
            --high;
        }
        students[low] = students[high];
        while (low < high and students[low].score >= key) {
            ++low;
        }
        students[high] = students[low];
    }
    students[low] = students[0];

    return low;
}

void quickSortPart(vec_stu &students, int low, int high) {
    if (low < high) {
        int middlePlace = partition(students, low, high);
        quickSortPart(students, low, middlePlace - 1);
        quickSortPart(students, middlePlace + 1, high);
    }
}

void quickSort(vec_stu &students) {
    quickSortPart(students, 1, students.size() - 1);
}

void selectSort(vec_stu &students) {
    for (int i = 1; i < students.size() - 1; i++) {
        for (int j = i + 1; j < students.size(); j++) {
            if (students[i].score < students[j].score) {
                auto temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void getLevel(vec_stu students) {
    int *rank = new int[students.size()];
    int nowRank = 1;
    for (int i = 1; i < students.size(); i++) {
        int now = students[i].score;
        rank[i] = nowRank;
        while (students[i + 1].score == now) {
            cout << rank[i] << ": " << students[i] << endl;
            i++;
            rank[i] = nowRank;
        }
        nowRank++;
        cout << rank[i] << ": " << students[i] << endl;
    }
}
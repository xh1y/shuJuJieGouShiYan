#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stack>

using namespace std;

const int maxInt = 2000000000;
const int inf = maxInt;

typedef struct citiesAndRoads {
    string startCity;
    string endCity;
    int distance;
} citiesAndRoads;

typedef struct oneAnswer {
    int cityNum, roadNum;
    vector<string> citiesName;
    vector<citiesAndRoads> roads;
    string startCity, endCity;
} oneAnswer;

typedef vector<int> vec_int;
typedef vector<vec_int> vec_vec_int;
typedef vector<oneAnswer> vec_oa;

vec_vec_int createGraph(oneAnswer oa);
void Dijkstra(vec_vec_int graph, oneAnswer oa, int start, int end);
int findCityNum(oneAnswer oa, string city);
int main() {
    vec_oa answers;
    int cityNum, roadNum;
    while (cin >> cityNum >> roadNum and not (cityNum == 0 and roadNum == 0)) {
        auto answer = new oneAnswer;
        answer->cityNum = cityNum;
        answer->roadNum = roadNum;
        for (int i = 0; i < cityNum; i++) {
            string city;
            cin >> city;
            answer->citiesName.push_back(city);
        }
        for (int i = 0; i < roadNum; i++) {
            string city1, city2;
            int distance;
            cin >> city1 >> city2 >> distance;
            citiesAndRoads car = { city1, city2, distance };
            answer->roads.push_back(car);
        }
        cin >> answer->startCity >> answer->endCity;
        answers.push_back(*answer);
        delete answer;
    }
    for (int questionNumber = 0; questionNumber < answers.size(); questionNumber++) {
        vec_vec_int graph = createGraph(answers[questionNumber]);
        // cout << questionNumber << ": " << endl;
        // for (int i = 0; i < graph.size(); i++) {
        //     for (int j = 0; j < graph[i].size(); j++) {
        //         cout << setw(4) << ((graph[i][j] == inf) ? -1 : graph[i][j]) << " ";
        //     }
        //     cout << endl;
        // }
        Dijkstra(graph, answers[questionNumber], findCityNum(answers[questionNumber], answers[questionNumber].startCity), findCityNum(answers[questionNumber], answers[questionNumber].endCity));
    }

    return 0;
}

vec_vec_int createGraph(oneAnswer oa) {
    vec_vec_int graph(oa.cityNum, vector<int>(oa.cityNum, inf));
    for (int i = 0; i < oa.roads.size(); i++) {
        bool s_f = false, e_f = false;
        int start, end;
        for (int j = 0; j < oa.cityNum; j++) {
            if (oa.citiesName[j].compare(oa.roads[i].startCity) == 0 && !s_f) {
                start = j;
                s_f = true;
            }
            if (oa.citiesName[j].compare(oa.roads[i].endCity) == 0 && !e_f) {
                end = j;
                e_f = true;
            }
            if (s_f && e_f) {
                break;
            }
        }
        if (s_f && e_f)
            graph[start][end] = oa.roads[i].distance;
    }
    return graph;
}

void Dijkstra(vec_vec_int graph, oneAnswer oa, int start, int end) {
    int size = oa.cityNum;
    bool *s = new bool[size];
    int *d = new int[size];
    int *path = new int[size];
    int vex = 0;
    for (vex = 0; vex < size; vex++) {
        s[vex] = false;
        d[vex] = graph[start][vex];
        if (d[vex] < inf) {
            path[vex] = start;
        } else {
            path[vex] = -1;
        }
    }
    s[start] = true;
    d[start] = 0;
    for (int i = 1; i < size; i++) {
        int min = maxInt;
        for (int w = 0; w < size; w++) {
            if (!s[w] and d[w] < min) {
                vex = w;
                min = d[w];
            }
        }
        s[vex] = true;
        for (int w = 0; w < size; w++) {
            if (!s[w] and (d[vex] + graph[vex][w] < d[w])) {
                d[w] = d[vex] + graph[vex][w];
                path[w] = vex;
            }
        }
    }
    cout << "最短距离：" << d[end] << endl;
    // for (int i = 0; i < size; i++) {
    //     cout << path[i] << " ";
    // }
    int now = end;
    stack<int> pathStack;
    cout << "最短路线：" << oa.citiesName[start] << "->";
    while (now != start) {
        pathStack.push(now);
        now = path[now];
    }
    while (!pathStack.empty()) {
        int place;
        cout << oa.citiesName[pathStack.top()] ;
        if(pathStack.size() > 1)
            cout << "->";
        pathStack.pop();
    }
    cout << endl;
}

int findCityNum(oneAnswer oa, string city) {
    bool find = false;
    for (int i = 0; i < oa.cityNum; i++) {
        if (city.compare(oa.citiesName[i]) == 0) {
            find = true;
            return i;
        }
    }
    if (!find) {
        throw "Not found!";
    }
    return -1;
}
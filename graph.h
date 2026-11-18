#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Status {sehat = 1, suspek = 2, positif = 3};

struct orang {
    string id;
    string nama;
    Status status;
    vector<int> kontak; //adjacency list
};

struct Graph {
    vector<orang> daftar;
};

int cariIndex(const Graph &g, const string &id) {
    for (int i = 0; i < (int)g.daftar.size(); i++) {
        if (g.daftar[i].id == id) return i;
    }
    return -1;
}
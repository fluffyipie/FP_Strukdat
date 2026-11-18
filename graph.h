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

int tambahOrang (Graph &g, const string &id, const string &nama, Status status) {
    if (id.empty() || nama.empty()) return -1;
    if (cariIndex(g, id) != -1) return -1;  //ID sudah dipakai

    orang o;
    o.id = id;
    o.nama = nama;
    o.status = status;
    g.daftar.push_back(o);
    return (int)g.daftar.size() - 1;    //index orang baru
}

bool sudahTerhubung(const Graph &g, int a, int b) {
    for (int k : g.daftar[a].kontak) {
        if (k == b) return true;
    }
    return false;
}

bool tambahKontak(Graph &g, int a, int b) {
    int n = (int)g.daftar.size();
    if (a < 0 || b < 0 || a >= n || b >= n) return false;   //index tidak valid
    if (a == b) return false;   //diri sendiri
    if (sudahTerhubung(g, a, b)) return false;  //sudah ada

    g.daftar[a].kontak.push_back(b);
    g.daftar[b].kontak.push_back(a);
    return true;
}

void inputOrangBaru(Graph &g) {
    string id, nama, pilihStatus;

    cout << "ID : ";
    getline(cin, id);
    if (id.empty()) {
        cout << "ID tidak boleh kosong.\n";
        return;
    }
    if (cariIndex(g, id) != -1) {
        cout << "ID " << id << " sudah terdaftar.\n";
        return;
    }
    
    cout << "Nama   : ";
    getline(cin, nama);
    if (nama.empty()) {
        cout << "Nama tidak boleh kosong.\n";
        return;
    }

    cout << "Status (1=sehat, 2=suspek, 3=positif): ";
    getline(cin, pilihStatus);
    if (pilihStatus != "1" && pilihStatus != "2" && pilihStatus != "3") {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    Status status = (Status)(pilihStatus[0] - '0');

    int idx = tambahOrang(g, id, nama, status);
    if (idx == -1) {
        cout << "Gagal menambah orang.\n";
        return;
    }

    cout << "Berhasil menambah " << nama << " [" << pilihStatus << "]\n";
}

void inputKontakBaru(Graph &g) {
    if (g.daftar.size() < 2) {
        cout << "Minimal harus ada 2 orang terdaftar.\n";
        return;
    }

    string idA, idB;
    cout << "ID orang pertama   : ";
    getline(cin, idA);
    int a = cariIndex(g, idA);
    if (a == -1) {
        cout << "ID " << idA << " belum terdaftar.\n";
        return;
    }

    cout << "ID orang kedua : ";
    getline(cin, idB);
    int b = cariIndex(g, idB);
    if (b == -1) {
        cout << "ID " << idB << " belum terdaftar.\n";
        return;
    }

    if (a == b) {
        cout << "tidak bisa kontak dengan diri sendiri";
        return;
    }
    if (sudahTerhubung(g, a, b)) {
        cout << g.daftar[a].nama << " dan " << g.daftar[b].nama << " sudah tercatat saling kontak.\n";
        return;
    }

    tambahKontak(g, a, b);
    cout << "Berhasil: " << g.daftar[a].nama << " <-> " << g.daftar[b].nama << "\n";
}
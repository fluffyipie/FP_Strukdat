#include <iostream>
#include "graph.h"
using namespace std;

int main() {
    Graph g;
    inputOrangBaru(g);    // ketik: A001, Budi, 3
    inputOrangBaru(g);    // ketik: A002, Ani, 1

    inputKontakBaru(g);   // ketik: A001, A002   -> harus berhasil
    inputKontakBaru(g);   // ketik: A001, A002   -> harus ditolak (sudah tercatat)
    inputKontakBaru(g);   // ketik: A001, A001   -> harus ditolak (diri sendiri)
    inputKontakBaru(g);   // ketik: A001, ZZZ    -> harus ditolak (ID tidak ada)
    cout << "Kontak Budi: " << g.daftar[0].kontak.size() << endl;   // harusnya 1
    return 0;
}
#include "data_buku.h"

// Iinisialisasi list
void createListBuku(ListBuku &LB) {
    LB.first = nullptr;
}

void createListPenulis(ListPenulis &LP) {
    LP.first = nullptr;
    LP.last = nullptr;
}

// Alokasi Node

adrBuku alokasiBuku(const Buku &b) {
    adrBuku p = new elmBuku;
    if (p == nullptr) return nullptr;

    p->info = b;
    p->next = nullptr;
    return p;
}

adrPenulis alokasiPenulis(const Penulis &pen) {
    adrPenulis p = new elmPenulis;
    if (p == nullptr) return nullptr;

    p->info = pen;
    p->next = nullptr;
    p->prev = nullptr;
    p->firstRelasi = nullptr;
    return p;
}

adrRelasi alokasiRelasi(adrBuku b) {
    adrRelasi r = new elmRelasi;
    if (r == nullptr) return nullptr;
    
    r->buku = b;
    r->next = nullptr;
    return r;
}

// OPERASI BUKU (SINGLE LIST)

void insertLastBuku(ListBuku &LB, adrBuku p) {
    if (LB.first == nullptr) {
        LB.first = p;
    } else {
        adrBuku q = LB.first;
        while (q->next != nullptr) {
            q = q->next;
        }
        q->next = p;
    }
}

adrBuku findBukuByID(ListBuku LB, const string &id) {
    adrBuku p = LB.first;
    while (p != nullptr) {
        if (p->info.idBuku == id) return p;
        p = p->next;
    }
    return nullptr;
}

adrBuku deleteBukuByID(ListBuku &LB, const string &id) {
    adrBuku p = LB.first;
    adrBuku prev = nullptr;

    while (p != nullptr && p->info.idBuku != id) {
        prev = p;
        p = p->next;
    }

    if (p == nullptr) return nullptr; 

    if (prev == nullptr) {
        LB.first = p->next;
    } else {
        prev->next = p->next;
    }

    p->next = nullptr;
    return p;
}

// OPERASI PENULIS (DOUBLE LIST)

void insertLastPenulis(ListPenulis &LP, adrPenulis p) {
    if (LP.first == nullptr) {
        LP.first = p;
        LP.last = p;
    } else {
        LP.last->next = p;
        p->prev = LP.last;
        LP.last = p;
    }
}

adrPenulis findPenulisByID(ListPenulis LP, const string &id) {
    adrPenulis p = LP.first;
    while (p != nullptr) {
        if (p->info.idPenulis == id) return p;
        p = p->next;
    }
    return nullptr;
}

adrPenulis deletePenulisByID(ListPenulis &LP, const string &id) {
    adrPenulis p = LP.first;

    while (p != nullptr && p->info.idPenulis != id) {
        p = p->next;
    }
    if (p == nullptr) return nullptr;

    if (p == LP.first && p == LP.last) {
        LP.first = LP.last = nullptr;
    } else if (p == LP.first) {
        LP.first = p->next;
        LP.first->prev = nullptr;
    } else if (p == LP.last) {
        LP.last = p->prev;
        LP.last->next = nullptr;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

//  RELASI PENULIS <-> BUKU

bool sudahTerhubung(adrPenulis pen, adrBuku b) {
    adrRelasi r = pen->firstRelasi;
    while (r != nullptr) {
        if (r->buku == b) return true;
        r = r->next;
    }
    return false;
}

bool tambahRelasiPenulisBuku(ListPenulis &LP, ListBuku &LB,
                             const string &idPenulis, const string &idBuku) {
    adrPenulis pen = findPenulisByID(LP, idPenulis);
    adrBuku b = findBukuByID(LB, idBuku);

    if (pen == nullptr || b == nullptr) {
        cout << "Penulis atau Buku tidak ditemukan.\n";
        return false;
    }

    if (sudahTerhubung(pen, b)) {
        cout << "Relasi sudah ada (penulis sudah terhubung ke buku itu).\n";
        return false;
    }

    adrRelasi r = alokasiRelasi(b);
    r->next = pen->firstRelasi;
    pen->firstRelasi = r;

    pen->info.jumlahBuku++;
    b->info.totalPenulis++;

    cout << "Berhasil: \"" << b->info.judul << "\" ditambahkan ke penulis " << pen->info.nama << ".\n";
    return true;
}

void hapusRelasiPenulis(adrPenulis pen) {
    adrRelasi r = pen->firstRelasi;
    while (r != nullptr) {
        r->buku->info.totalPenulis--;
        pen->info.jumlahBuku--;
        adrRelasi del = r;
        r = r->next;
        delete del;
    }
    pen->firstRelasi = nullptr;
}


void hapusRelasiBuku(ListPenulis &LP, adrBuku b) {
    adrPenulis p = LP.first;
    while (p != nullptr) {
        adrRelasi r = p->firstRelasi;
        adrRelasi prev = nullptr;

        while (r != nullptr) {
            if (r->buku == b) {
                if (prev == nullptr) {
                    p->firstRelasi = r->next;
                } else {
                    prev->next = r->next;
                }
                p->info.jumlahBuku--;

                adrRelasi del = r;
                r = r->next;
                delete del;
            } else {
                prev = r;
                r = r->next;
            }
        }
        p = p->next;
    }
}

// DISPLAY FUNCTIONS

void tampilkanSemuaPenulis(ListPenulis LP) {
    cout << "\n=== DATA PENULIS ===\n";
    if (LP.first == nullptr) {
        cout << "Tidak ada data penulis.\n";
        return;
    }

    adrPenulis p = LP.first;
    while (p != nullptr) {
        cout << "ID   : " << p->info.idPenulis << "\n";
        cout << "Nama : " << p->info.nama << "\n";
        cout << "Jumlah Buku: " << p->info.jumlahBuku << "\n";
        cout << "-----------------------------\n";
        p = p->next;
    }
}

void tampilkanSemuaBukuBesertaPenulis(ListBuku LB, ListPenulis LP) {
    cout << "\n=== DATA BUKU BESERTA PENULISNYA ===\n";
    if (LB.first == nullptr) {
        cout << "Tidak ada data buku.\n";
        return;
    }

    adrBuku b = LB.first;
    while (b != nullptr) {
        cout << "ID Buku : " << b->info.idBuku << "\n";
        cout << "Judul   : " << b->info.judul << "\n";
        cout << "Tahun   : " << b->info.tahun << "\n";
        cout << "Total Penulis: " << b->info.totalPenulis << "\n";
        cout << "Penulis:\n";

        bool ada = false;
        adrPenulis p = LP.first;
        while (p != nullptr) {
            adrRelasi r = p->firstRelasi;
            while (r != nullptr) {
                if (r->buku == b) {
                    cout << "- " << p->info.nama << " (ID: " << p->info.idPenulis << ")\n";
                    ada = true;
                    break;
                }
                r = r->next;
            }
            p = p->next;
        }

        if (!ada) cout << "- (Belum ada penulis terhubung)\n";
        cout << "-----------------------------\n";
        b = b->next;
    }
}

void tampilkanBukuDariPenulis(ListPenulis LP) {
    string idP;
    cout << "Masukkan ID Penulis: ";
    getline(cin, idP);

    adrPenulis pen = findPenulisByID(LP, idP);
    if (pen == nullptr) {
        cout << "Penulis tidak ditemukan.\n";
        return;
    }

    cout << "\nPenulis: " << pen->info.nama << " (ID: " << pen->info.idPenulis << ")\n";
    if (pen->firstRelasi == nullptr) {
        cout << "Belum menulis buku apapun.\n";
        return;
    }

    adrRelasi r = pen->firstRelasi;
    int i = 1;
    while (r != nullptr) {
        cout << i << ". " << r->buku->info.judul
             << " (ID: " << r->buku->info.idBuku << ", Tahun: " << r->buku->info.tahun << ")\n";
        r = r->next;
        i++;
    }
}

void tampilkanPenulisDariBuku(ListPenulis LP, ListBuku LB) {
    string idB;
    cout << "Masukkan ID Buku: ";
    getline(cin, idB);

    adrBuku b = findBukuByID(LB, idB);
    if (b == nullptr) {
        cout << "Buku tidak ditemukan.\n";
        return;
    }

    cout << "\nBuku: " << b->info.judul << " (ID: " << b->info.idBuku << ")\n";
    cout << "Daftar Penulis:\n";

    bool ada = false;
    adrPenulis p = LP.first;
    while (p != nullptr) {
        adrRelasi r = p->firstRelasi;
        while (r != nullptr) {
            if (r->buku == b) {
                cout << "- " << p->info.nama << " (ID: " << p->info.idPenulis << ")\n";
                ada = true;
                break;
            }
            r = r->next;
        }
        p = p->next;
    }

    if (!ada) cout << "Belum ada penulis untuk buku ini.\n";
}

void tampilkanPenulisPalingAktifDanTidak(ListPenulis LP) {
    if (LP.first == nullptr) {
        cout << "Tidak ada data penulis.\n";
        return;
    }

    adrPenulis p = LP.first;
    adrPenulis aktif = p;
    adrPenulis tidakAktif = p;

    while (p != nullptr) {
        if (p->info.jumlahBuku > aktif->info.jumlahBuku) aktif = p;
        if (p->info.jumlahBuku < tidakAktif->info.jumlahBuku) tidakAktif = p;
        p = p->next;
    }

    cout << "\n=== PENULIS PALING AKTIF ===\n";
    cout << "Nama : " << aktif->info.nama << "\n";
    cout << "ID   : " << aktif->info.idPenulis << "\n";
    cout << "Jumlah Buku: " << aktif->info.jumlahBuku << "\n";

    cout << "\n=== PENULIS PALING TIDAK AKTIF ===\n";
    cout << "Nama : " << tidakAktif->info.nama << "\n";
    cout << "ID   : " << tidakAktif->info.idPenulis << "\n";
    cout << "Jumlah Buku: " << tidakAktif->info.jumlahBuku << "\n";
}

// MENU INPUT / INTERAKSI USER

void menuTambahPenulis(ListPenulis &LP) {
    Penulis p;
    cout << "ID Penulis : ";
    getline(cin, p.idPenulis);
    cout << "Nama       : ";
    getline(cin, p.nama);
    p.jumlahBuku = 0;

    if (findPenulisByID(LP, p.idPenulis) != nullptr) {
        cout << "ID Penulis sudah ada, gagal menambah.\n";
        return;
    }

    adrPenulis node = alokasiPenulis(p);
    insertLastPenulis(LP, node);
    cout << "Penulis berhasil ditambahkan.\n";
}

void menuTambahBuku(ListBuku &LB) {
    Buku b;
    cout << "ID Buku  : ";
    getline(cin, b.idBuku);
    cout << "Judul    : ";
    getline(cin, b.judul);
    cout << "Tahun    : ";
while (!(cin >> b.tahun)) {
    cout << "Input tahun harus angka: ";
    cin.clear();      
    cin.ignore(1000, '\n');
}
cin.ignore();

    b.totalPenulis = 0;

    if (findBukuByID(LB, b.idBuku) != nullptr) {
        cout << "ID Buku sudah ada, gagal menambah.\n";
        return;
    }

    adrBuku node = alokasiBuku(b);
    insertLastBuku(LB, node);
    cout << "Buku berhasil ditambahkan.\n";
}

void menuRelasiPenulisBuku(ListPenulis &LP, ListBuku &LB) {
    string idP, idB;
    cout << "Masukkan ID Penulis : ";
    getline(cin, idP);
    cout << "Masukkan ID Buku    : ";
    getline(cin, idB);

    tambahRelasiPenulisBuku(LP, LB, idP, idB);
}

void menuHapusPenulis(ListPenulis &LP) {
    string idP;
    cout << "Masukkan ID Penulis yang akan dihapus: ";
    getline(cin, idP);

    adrPenulis pen = findPenulisByID(LP, idP);
    if (pen == nullptr) {
        cout << "Penulis tidak ditemukan.\n";
        return;
    }

    hapusRelasiPenulis(pen);

    adrPenulis del = deletePenulisByID(LP, idP);
    if (del != nullptr) {
        cout << "Penulis \"" << del->info.nama << "\" berhasil dihapus.\n";
        delete del;
    } else {
        cout << "Gagal menghapus penulis.\n";
    }
}

void menuHapusBuku(ListPenulis &LP, ListBuku &LB) {
    string idB;
    cout << "Masukkan ID Buku yang akan dihapus: ";
    getline(cin, idB);

    adrBuku b = findBukuByID(LB, idB);
    if (b == nullptr) {
        cout << "Buku tidak ditemukan.\n";
        return;
    }

    hapusRelasiBuku(LP, b);

    adrBuku del = deleteBukuByID(LB, idB);
    if (del != nullptr) {
        cout << "Buku \"" << del->info.judul << "\" berhasil dihapus.\n";
        delete del;
    } else {
        cout << "Gagal menghapus buku.\n";
    }
}
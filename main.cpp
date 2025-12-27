#include "data_buku.h" //ngerjain bareng

void tampilkanMenu() {
    cout << "\n=====================================\n";
    cout << "            SISTEM DATA BUKU         \n";
    cout << "=====================================\n";
    cout << "1. Tambah Penulis\n";
    cout << "2. Tambah Buku\n";
    cout << "3. Tentukan Relasi Penulis - Buku\n";
    cout << "4. Hapus Penulis\n";
    cout << "5. Hapus Buku\n";
    cout << "6. Tampilkan Semua Buku beserta Penulisnya\n";
    cout << "7. Tampilkan Semua Penulis\n";
    cout << "8. Tampilkan Buku dari Penulis tertentu\n";
    cout << "9. Tampilkan Penulis dari Buku tertentu\n";
    cout << "10. Tampilkan Penulis paling aktif & tidak aktif\n";
    cout << "0. Keluar\n";
    cout << "Pilihan: ";
}

int main() {
    ListBuku LB;
    ListPenulis LP;

    createListBuku(LB);
    createListPenulis(LP);

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: menuTambahPenulis(LP); break;
            case 2: menuTambahBuku(LB); break;
            case 3: menuRelasiPenulisBuku(LP, LB); break;
            case 4: menuHapusPenulis(LP); break;
            case 5: menuHapusBuku(LP, LB); break;
            case 6: tampilkanSemuaBukuBesertaPenulis(LB, LP); break;
            case 7: tampilkanSemuaPenulis(LP); break;
            case 8: tampilkanBukuDariPenulis(LP); break;
            case 9: tampilkanPenulisDariBuku(LP, LB); break;
            case 10: tampilkanPenulisPalingAktifDanTidak(LP); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}
# TMD_STRUKDAT

Tugas Masa Depan (TMD) mata kuliah **Algoritma dan Struktur Data**.
Implementasi **pohon jamak (n-tree)** dengan pointer `sibling` untuk merepresentasikan
pohon bercabang banyak (setiap simpul dapat memiliki lebih dari dua anak),
disertai **mesin kata (kata automata)** untuk mem-parsing baris input yang
dipisahkan oleh pagar `#`.

Program menerima kumpulan simpul yang membentuk pohon, lalu **memangkas seluruh
pohon** sehingga hanya menyisakan jalur dari akar menuju satu simpul tujuan
(*pruning path*), menjumlahkan nilai (`value`) dari simpul yang tersisa, dan
menampilkan seluruh `peluang` pada jalur tersebut.

---

## Janji

> Saya **Jaka Permana Herawan** mengerjakan evaluasi Tugas Masa Depan dalam mata
> kuliah **Algoritma dan Struktur Data**. Untuk keberkahan-Nya, maka saya tidak
> melakukan kecurangan seperti yang telah dispesifikasikan. **Aamiin.**

---

## Struktur Folder

```
TMD_STRUKDAT/
├── README.md        # Dokumentasi proyek (file ini)
├── header.h         # Header utama: struct data, struct simpul, struct tree,
│                    #                prototype fungsi, dan variabel global mesin kata
├── main.c           # Entry point: membaca input, membangun pohon,
│                    #              menandai jalur, memangkas, dan mencetak hasil
├── mesin.c          # Implementasi seluruh fungsi (n-tree) + mesin kata
├── testcase.txt     # Contoh data masukan (16 simpul)
└── tp.exe           # Hasil kompilasi (binary)
```

Penjelasan singkat tiap berkas:

| Berkas         | Peran                                                                       |
| -------------- | --------------------------------------------------------------------------- |
| `header.h`     | Satu-satunya header yang di-`include` oleh `main.c` dan `mesin.c`. Berisi deklarasi tipe data, prototype, dan variabel global. |
| `main.c`       | Prosedur `main()`. Menangani seluruh interaksi dengan pengguna (input/output) dan orkestrasi alur program. |
| `mesin.c`      | Seluruh implementasi logika: operasi n-tree, fungsi bantu pencetakan, dan mesin kata. |
| `testcase.txt` | Data masukan contoh yang bisa langsung di-redirect ke executable.          |
| `tp.exe`       | Binary hasil kompilasi.                                                    |

---

## Cara Kompilasi & Menjalankan

**Kebutuhan:** compiler C (GCC / MinGW / Clang). Standar C99 atau lebih baru
(kode memakai komentar `//` dan deklarasi variabel di tengah blok).

```bash
# Kompilasi
gcc main.c mesin.c -o tp.exe

# Jalankan dengan data dari berkas
tp.exe < testcase.txt

# Jalankan interaktif
tp.exe
```

Kompilasi dengan peringatan tambahan (proyek ini lolos bersih, tanpa warning):

```bash
gcc -std=c11 -Wall -Wextra main.c mesin.c -o tp.exe
```

---

## Format Input

### 1. Baris pertama — jumlah simpul

```
16
```

### 2. Untuk setiap simpul (sebanyak `n` kali)

Satu baris **header** dengan 4 token yang dipisahkan pagar `#`:

```
<nama>#<nama_ortu>#<value>#<jumlah_peluang>
```

Dilanjutkan `jumlah_peluang` baris, masing-masing berisi satu nama peluang.

Contoh untuk satu simpul:

```
kuliah#setelahSMA#110#3
peluang_belajar
peluang_network
peluang_mendapat_skill
```

Aturan penting:

| Aturan                 | Keterangan                                                                                 |
| ---------------------- | ----------------------------------------------------------------------------------------- |
| Pemisah token          | Karakter `#` (pagar). Nama simpul **tidak boleh** mengandung `#`.             |
| Simpul akar            | Bernama induk `null` (huruf kecil, bukan pointer NULL).                                   |
| Nama peluang           | Dibaca dengan `scanf("%s", ...)`, sehingga **tidak boleh mengandung spasi**.               |
| Batas nama simpul      | Maksimal 200 karakter (`huruf[201]`).                                                      |
| Batas nama peluang     | Maksimal 50 buah per simpul, masing-masing 100 karakter (`peluang[50][101]`).              |
| Nilai (`value`)        | Bilangan bulat non-negatif, ditulis sebagai teks lalu dikonversi oleh `strtoint()`.        |
| Sibling                | Diurutkan sesuai urutan masukan dan membentuk **circular linked list** (kembali ke anak pertama). |

### 3. Baris terakhir — nama simpul tujuan

```
buka_cabang
```

Nama ini harus **sudah ada** di dalam pohon (hasil dari `n` baris sebelumnya).

### Ringkasan struktur masukan

```
<n>
<nama_1>#<ortu_1>#<value_1>#<m_1>
<peluang_1_1>
...
<peluang_1_m1>
<nama_2>#<ortu_2>#<value_2>#<m_2>
...
<nama_tujuan>
```

---

## Penjelasan Atribut

### 1. Struktur `data` — kontainer isi simpul

Dideklarasikan di `header.h`. Menyimpan seluruh data yang dimiliki sebuah simpul.

| Atribut     | Tipe              | Keterangan                                                                                   |
| ----------- | ----------------- | ------------------------------------------------------------------------------------------- |
| `huruf`     | `char[201]`       | Nama simpul. Maksimal 200 karakter + terminator `'\0'`.                                     |
| `value`     | `int`             | Nilai numerik dari simpul. Dijumlahkan seluruhnya untuk menghasilkan *total value*.         |
| `jmlpeluang`| `int`             | Jumlah nama peluang yang dimiliki simpul. Dipakai sebagai batas loop saat cetak & hapus.     |
| `peluang`   | `char[50][101]`   | Array 2 dimensi berisi daftar nama peluang simpul. Maksimal 50 item × 100 karakter.          |

### 2. Struktur `simpul` — node pohon

| Atribut   | Tipe            | Keterangan                                                                                                      |
| --------- | --------------- | -------------------------------------------------------------------------------------------------------------- |
| `kontainer` | `data`        | Isi simpul (nama, value, jumlah & daftar peluang).                                                             |
| `child`   | `alamatsimpul`   | Pointer ke **anak pertama** simpul. `NULL` bila daun.                                                           |
| `sibling` | `alamatsimpul`   | Pointer ke **saudara berikutnya** pada tingkat yang sama. Berbentuk *circular* (anak terakhir menunjuk anak pertama). |
| `parent`  | `alamatsimpul`   | Pointer ke **induk** simpul. `NULL` hanya untuk akar. Dipakai untuk menelusuri jalur ke atas.                    |
| `tanda`   | `int`            | Penanda hasil *pruning*. `1` = terpilih/akan dipertahankan, `0` = tidak terpilih/akan dihapus.                 |

Tiga pointer membentuk navigasi dua arah: dari akar menuju daun memakai
`child` → `sibling`, sedangkan dari daun menuju akar memakai `parent`.

### 3. Struktur `tree` — pembungkus simpul tunggal

| Atribut | Tipe     | Keterangan                                     |
| ------- | -------- | ----------------------------------------------- |
| `root`  | `simpul*`| Pointer ke simpul akar pohon.                 |

### 4. Variabel global mesin kata

Dideklarasikan di `mesin.c` (dan dideklarasikan ulang sebagai `extern` di
`header.h`) agar ketiga fungsi mesin kata berbagi state posisi pembacaan.

| Variabel       | Tipe        | Keterangan                                              |
| -------------- | ----------- | -------------------------------------------------------- |
| `indeks`       | `int`       | Posisi karakter terkini pada pita.                      |
| `panjangkata`  | `int`       | Panjang kata yang sedang dibaca.                        |
| `ckata`        | `char[201]` | Kata yang sedang dibaca, sudah diakhiri `'\0'`.           |

### 5. Tipe alias pointer

```c
typedef struct node *alamatsimpul;
```

Alias agar deklarasi pointer-pointer pohon tetap ringkas dan konsisten
digunakan di seluruh fungsi.

---

## Dokumentasi Fungsi

### Fungsi n-tree

| Prototipe                                                    | Jenis      | Fungsi                                                                                          |
| ------------------------------------------------------------ | ---------- | ------------------------------------------------------------------------------------------------ |
| `void makeTree(data temp, tree *T)`                           | prosedur   | Membuat simpul akar dari `temp`, mengarahkan `T->root` ke simpul baru, dan menginisialisasi seluruh pointer sibling/child/parent menjadi `NULL`. |
| `void addChild(data temp, simpul *root)`                      | prosedur   | Menambahkan simpul baru sebagai anak dari `root`. Bila anak sudah ada, simpul baru disisipkan di ujung daftar sibling lalu siklusnya ditutup kembali. |
| `void delAll(simpul *root)`                                   | prosedur   | Membebaskan seluruh sub-pohon yang berakar pada `root` secara rekursif (free semua memori).     |
| `void delChild(char nama[], simpul *root)`                    | prosedur   | Menghapus satu anak bernama `nama` dari `root` beserta seluruh sub-pohonnya, sekaligus memutas ulang rantai sibling agar tetap konsisten. |
| `simpul *findSimpul(char nama[], simpul *root)`              | fungsi     | Pencarian rekursif simpul berdasarkan nama di seluruh pohon. Mengembalikan `NULL` bila tidak ditemukan. |

### Fungsi bantu

| Prototipe                                       | Jenis    | Fungsi                                                                                                     |
| ----------------------------------------------- | -------- | ----------------------------------------------------------------------------------------------------------- |
| `int strtoint(char str[])`                       | fungsi   | Mengubah string bilangan menjadi `int` dengan iterasi karakter (`hasil = hasil*10 + digit`).                 |
| `int digit(simpul *root)`                        | fungsi   | Menghitung banyaknya digit dari `value` sebuah simpul.                                                      |
| `int lebarsimpul(simpul *root)`                  | fungsi   | Menghitung lebar kolom terpanjang pada tingkat sibling tersebut (gabungan panjang nama + `" - "` + digit value, dan panjang peluang + `"[]"`), dipakai untuk indentasi pohon. |
| `void printTree(simpul *root, int spasi, int *jumlah)` | prosedur | Menampilkan pohon dengan format pohon bertingkat, menggeser tiap anak ke kanan sebesar lebar kolom induk, sekaligus menjumlahkan `value` ke `*jumlah`. |
| `void hapusnol(simpul *root)`                    | prosedur   | Merekursif seluruh subtree; anak bertanda `0` dikumpulkan namanya lalu dihapus dengan `delChild`, sedangkan anak bertanda `1` justru ditelusuri lebih dalam. |
| `void semuapeluang(simpul *root)`                | prosedur | Menampilkan seluruh daftar peluang dari seluruh simpul yang tersisa, dari akar ke daun.                      |

### Mesin kata

| Prototipe                 | Jenis    | Fungsi                                                                                                             |
| ------------------------- | -------- | ------------------------------------------------------------------------------------------------------------------- |
| `void START(char pita[])` | prosedur | Memulai pembacaan: menggeser `indeks` melewati pagar pembuka lalu menyalin kata pertama ke `ckata`.                    |
| `void INC(char pita[])`   | prosedur | Meneruskan ke token berikutnya pada pita dengan logika yang sama seperti `START`.                                    |
| `char* GETKATA(void)`     | fungsi   | Mengembalikan pointer ke kata yang sedang dibaca (`ckata`).                                                          |
| `int EOP(char pita[])`    | fungsi   | Mengembalikan `1` bila karakter pada `indeks` adalah `'\0'` (akhir pita), selain itu `0`.                          |

---

## Alur Program

### A. Tahap pembangunan pohon

```
main()
 ├─ (1) baca n
 └─ loop i = 0 .. n-1
      ├─ (2) baca satu baris header ke pita.huruf  (scanf " %200[^\n]")
      ├─ (3) START(pita)  → GETKATA() → nama
      ├─ (4) INC(pita)    → GETKATA() → ortu
      ├─ (5) INC(pita)    → strtoint(GETKATA()) → value
      ├─ (6) INC(pita)    → strtoint(GETKATA()) → m  (jumlah peluang)
      ├─ (7) baca m nama peluang ke baru.peluang[0..m-1]
      └─ (8) pasang simpul
            ├─ jika ortu == "null"  → makeTree(baru, &T)
            └─ selain itu          → findSimpul(ortu, T.root) → addChild(baru, target)
```

Konsekuensi penting: **simpul harus diinput setelah induknya**. Bila `findSimpul`
tidak menemukan induk, simpul tersebut diam-diam diabaikan (tidak ada pesan galat).

### B. Tahap penandaan jalur (pruning)

```
 ├─ (9)  baca nama simpul tujuan  (scanf "%s" → pita.huruf)
 ├─ (10) printTree(T.root, 0, &jumlah)        → cetak pohon SEBELUM dipangkas
 ├─ (11) tujuan = findSimpul(nama_tujuan, T.root)
 └─ (12) while tujuan != NULL                  → berjalan ke atas lewat parent
       |  tujuan->tanda = 1
       +-- tujuan = tujuan->parent
```

Inti algoritma: karena setiap simpul menyimpan pointer `parent`, jalur dari akar
ke tujuan dapat ditandai dengan menelusuri satu jalur ke atas saja, tanpa perlu
mencari ulang seluruh pohon.

### C. Tahap pemangkasan

```
 └─ (13) hapusnol(T.root)
        └─ untuk setiap anak bertanda 0 → kumpulkan namanya → delChild(nama, root)
```

Simpul bertanda `0` beserta seluruh keturunannya otomatis ikut terhapus karena
`delChild` memanggil `delAll` pada sub-pohon tersebut. Simpul bertanda `1`
ditelusuri lebih dalam untuk memeriksa apakah keturunannya juga perlu dihapus.

### D. Tahap pencetakan hasil

```
 ├─ (14) jumlah = 0
 ├─ (15) printTree(T.root, 0, &jumlah)        → cetak pohon SESUDAH dipangkas
 │                                             (jumlah = total value jalur)
 ├─ (16) print "peluang akhir yang diambil: <nama tujuan>"
 ├─ (17) print "total value: <jumlah>"
 └─ (18) print "semua peluang:" lalu semuapeluang(T.root)
```

### Ringkasan visual

```
   [INPUT]                    : baca n, n baris simpul, nama tujuan
       |
       v
   [BUILD TREE]               : makeTree() untuk akar, addChild() untuk anak
       |
       v
   [PRINT POHON AWAL]          : printTree() sebelum pemangkasan
       |
       v
   [TANDAI JALUR]             : jalan ke atas lewat parent, set tanda = 1
       |
       v
   [HAPUS SIMPUL TANDA 0]     : hapusnol() -> delChild() -> delAll()
       |
       v
   [PRINT POHON AKHIR]         : printTree() sesudah pemangkasan + total value
       |
       v
   [SEMUA PELUANG]             : semuapeluang()
```

### Kompleksitas

| Operasi                        | Kompleksitas                                    |
| ------------------------------ | ----------------------------------------------- |
| `makeTree`                     | O(1)                                            |
| `addChild`                     | O(k), k = jumlah anak pada simpul induk (mencari sibling terakhir). |
| `findSimpul`                   | O(N) worst case, rekursif DFS.                  |
| `hapusnol` + `delChild`        | O(N × k) worst case, karena penghapusan dilakukan per-nama. |
| `printTree` / `semuapeluang`   | O(N + total panjang string peluang).             |

`N` = jumlah simpul, `k` = jumlah anak.

---

## Contoh Testcase

Menggunakan `testcase.txt` (16 simpul) dengan nama tujuan `buka_cabang`:

```bash
tp.exe < testcase.txt
```

### Pohon sebelum dipangkas

```
setelahSMA - 0
[menjadi_dewasa]
[power_sendiri]

                kuliah - 110
                [peluang_belajar]
                [peluang_network]
                [peluang_mendapat_skill]

                                            kuliah_dengan_benar - 200
                                            [dapat_pekerjaan_baik]
                                            [memperbaiki_hidup]
                                            [punya_value]

                                                                            wirausaha - 500
                                                                            [latihan_endurance]
                                                                            [peluang_pendapatan_eksponensial]
                                                                            [peluang_network]
                                                                            [peluang_ekspansi]
                                                                            [peluang_manfaat]

                                                                                                             buka_cabang - 500
                                                                                                             [peluang_berkembang]
                                                                                                             [peluang_pensiun_dini]

                                                                            bekerja_di_big_four - 500
                                                                            [latihan_endurance]
                                                                            [peluang_pendapatan_baik]

                                                                            petani - 500
                                                                            [ketenangan]
                                                                            [peluang_cukup]

                                            kuliah_hanya_sekedar_kuliah - 10
                                            [kemungkinan_pengangguran]

                                                                            pengangguran - 10
                                                                            [banyak_waktu]

                                                                            berjualan - 200
                                                                            [mengurangi_stres]
                                                                            [peluang_tercukupi]

                kerja - 100
                [berlatih_disiplin]
                [rutinitas_masuk_hari_kerja]
                [dapat_gaji]

                menganggur - 10
                [serba_salah]
                [merenung]

                                            berdagang - 200
                                            [mengurangi_stres]
                                            [peluang_cukup]

                menikah - 50
                [ngurus_rumah]
                [ngurus_keluarga]
                [ngurus_anak]
                [punya_keluarga]

                                            pasangan_ekonomi_kuat - 300
                                            [peluang_cukup]
                                            [peluang_konsentrasi_keluarga]

                                            pasangan_ekonomi_lemah - 10

```

### Pohon setelah dipangkas

```
setelahSMA - 0
[menjadi_dewasa]
[power_sendiri]

                kuliah - 110
                [peluang_belajar]
                [peluang_network]
                [peluang_mendapat_skill]

                                        kuliah_dengan_benar - 200
                                        [dapat_pekerjaan_baik]
                                        [memperbaiki_hidup]
                                        [punya_value]

                                                                 wirausaha - 500
                                                                 [latihan_endurance]
                                                                 [peluang_pendapatan_eksponensial]
                                                                 [peluang_network]
                                                                 [peluang_ekspansi]
                                                                 [peluang_manfaat]

                                                                                                  buka_cabang - 500
                                                                                                  [peluang_berkembang]
                                                                                                  [peluang_pensiun_dini]

```

### Ringkasan akhir

```
peluang akhir yang diambil: buka_cabang
total value: 1310
semua peluang:
[menjadi_dewasa]
[power_sendiri]
[peluang_belajar]
[peluang_network]
[peluang_mendapat_skill]
[dapat_pekerjaan_baik]
[memperbaiki_hidup]
[punya_value]
[latihan_endurance]
[peluang_pendapatan_eksponensial]
[peluang_network]
[peluang_ekspansi]
[peluang_manfaat]
[peluang_berkembang]
[peluang_pensiun_dini]
```

Verifikasi total value: `0 + 110 + 200 + 500 + 500 = 1310` — sesuai.

Perhatikan bahwa seluruh cabang samping seperti `kerja`, `menganggur`, `menikah`,
`kuliah_hanya_sekedar_kuliah`, `bekerja_di_big_four`, dan `petani` beserta
seluruh keturunannya telah hilang. Yang tersisa hanyalah satu jalur dari akar
menuju `buka_cabang`.

---

## Catatan Teknis & Batasan

1. **Urutan input menentukan bentuk pohon.** Induk harus diinput sebelum anak;
   `findSimpul` mengembalikan hasil pencarian pertama (DFS pre-order), sehingga
   nama simpul sebaiknya unik.
2. **Nama tujuan tidak ditemukan** → tidak ada simpul yang ditandai, seluruh anak
   akar terhapus dan hanya akar yang tersisa (total value = value akar).
3. **Kapasitas `hapusnol`** menggunakan array `char hapus[50][101]`, sehingga
   maksimal 50 anak per tingkat dapat dihapus dalam satu pemanggilan.
4. **`strtoint()`** hanya menangani bilangan non-negatif.
5. **Indentasi output** bertambah sebesar lebar kolom terpanjang pada tingkat
   sibling (`lebarsimpul`), bukan kelipatan spasi tetap. Akibatnya anak selalu
   mulai tepat di kanan kolom teks induknya.
6. **Baris “peluang akhir yang diambil”** mencetak nama simpul tujuan (variabel
   `pita.huruf` dipakai ulang), bukan nama peluang.
7. Memori simpul yang tersisa tidak dibebaskan di akhir program (proses langsung
   berakhir, dampaknya tidak signifikan).
8. Kompilasi bersih tanpa peringatan pada `gcc -std=c11 -Wall -Wextra`.

---

## Teknologi

- Bahasa: **C** (C99/C11)
- Struktur data: **pohon jamak (n-tree)** dengan pointer `sibling`
- Parsing: **mesin kata** (kata automata) dengan delimiter `#`
- I/O: `scanf` / `printf` standar (`stdio.h`)

---

## Penulis

**Jaka Permana Herawan**


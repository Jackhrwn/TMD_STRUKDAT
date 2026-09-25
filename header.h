#include <stdio.h>
#include <string.h>
#include <malloc.h>
/*
Saya Jaka Permana Herawan mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah 
Algoritma dan Struktur Data untuk keberkahanNya maka saya tidak melakukan 
kecurangan seperti yang telah dispesifikasikan. Aamiin.
*/
//--Ntree--
typedef struct{
    char huruf[201];                                //deklarasi huruf untuk menyimpan karakter 
    int value;                                      //deklarasi value untuk value dari simpul
    int jmlpeluang;                                 //deklarasi jmlpeluang untuk menyimpan jumlah peluang
    char peluang[50][101];                          //deklarasi peluang untuk menyimpan banyak peluang yang ada di simpul
}data;

typedef struct node *alamatsimpul;                  //deklarasi pointer alamatsimpul untuk menunjuk simpul lain
typedef struct node{
    data kontainer;                                 //deklarasi data dengan nama kontainer 
    alamatsimpul sibling;                           //deklarasi pointer alamatsimpul untuk menunjuk simpul sibling
    alamatsimpul child;                             //deklarasi pointer alamatsimpul untuk menunjuk simpul child
    alamatsimpul parent;                            //deklarasi pointer alamatsimpul untuk menunjuk simpul parent
    int tanda;                                      //deklarasi tanda untuk menandai simpul yang akan dihapus, 1 = gk dihapus, 0 = dihapus
}simpul;

typedef struct{
    simpul *root;                                   //deklarasi pointer simpul untuk menunjuk simpul root
}tree;

//Dekalarasi prosedur dan fungsi tree
void makeTree(data temp,tree *T);                   //deklarasi prosedur untuk membuat tree 
void addChild(data temp,simpul *root);              //deklarasi prosedur untuk menambahkan simpul pada simpul root
void delAll(simpul *root);                          //deklarasi prosedur untuk menghapus semua simpul pada tree
void delChild(char nama[],simpul *root);            //deklarasi prosedur untuk menghapus simpul pada simpul root
simpul *findSimpul(char nama[],simpul *root);       //deklarasi fungsi untuk mencari simpul pada tree

//Deklarasi prosedur tambahan
int strtoint(char str[]);                           //deklarasi fungsi untuk mengubah string menjadi integer
int digit(simpul *root);                            //deklarasi fungsi untuk mendapatkan digit dari value simpul
int lebarsimpul(simpul *root);                      //deklarasi fungsi untuk mendapatkan panjang kata terpanjang dari sibling
void printTree(simpul *root,int spasi,int *jumlah); //deklarasi prosedur untuk menampilkan struktur tree
void hapusnol(simpul *root);                        //deklarasi prosedur untuk menghapus simpul yang tidak terpilih(tanda = 0)
void semuapeluang(simpul *root);                    //deklarasi prosedur untuk menampilkan semua peluang dari simpul yang terpilih

//--mesin kata--
extern int indeks;                                  //deklarasi indeks untuk menyimpan posisi karakter pada pita
extern int panjangkata;                             //deklarasi panjangkata untuk menyimpan panjang kata pada pita
extern char ckata[201];                             //deklarasi ckata untuk menyimpan kata pada pita

int EOP(char pita[]);                               //deklarasi fungsi untuk mengecek end of pita
char* GETKATA(void);                                //deklarasi fungsi untuk mendapatkan kata pada pita
void INC(char pita[]);                              //deklarasi prosedur untuk menggeser posisi karakter pada pita   
void START(char pita[]);                            //deklarasi prosedur untuk memulai mesin kata pada pita
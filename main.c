#include "header.h"
/*
Saya Jaka Permana Herawan mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah 
Algoritma dan Struktur Data untuk keberkahanNya maka saya tidak melakukan 
kecurangan seperti yang telah dispesifikasikan. Aamiin.
*/
int main(){
    tree T;                                 //deklarasi tree T
    data pita;                              //deklarasi data pita untuk menyimpan input dari user
    int n;                                  //deklarasi n untuk jumlah dari simpul
    scanf("%d", &n);                        //input jumlah n
    for(int i=0;i<n;i++){                   //looping untuk menginput simpul
        scanf(" %200[^\n]",pita.huruf);     //membaca input dari user dan menyimpannya pada data huruf pada pita
        getchar();                          //membuang karakter newline yang tersisa pada input buffer
        
        START(pita.huruf);                  //mulai mesin kata
        char nama[101];                     //deklarasi nama untuk menyimpan nama simpul
        strcpy(nama,GETKATA());             //copy kata sekarang ke dalam nama

        INC(pita.huruf);                    //pindah ke kata berikutnya pada pita
        char ortu[101];                     //deklarasi ortu untuk menyimpan nama ortu yang dituju
        strcpy(ortu,GETKATA());             //copy kata sekarang ke dalam ortu

        INC(pita.huruf);                    //pindah ke kata berikutnya pada pita
        int value=strtoint(GETKATA());      //ambil nilai kata sekarang yang telah diubah menjadi int ke variabel value

        INC(pita.huruf);                    //pindah ke kata berikutnya pada pita
        int m=strtoint(GETKATA());          //ambil nilai kata sekarang yang telah diubah menjadi int ke variabel m

        data baru;                          //deklarasi data baru untuk membuat simpul
        strcpy(baru.huruf,nama);            //copy nama ke simpul baru
        baru.value=value;                   //simpan value ke simpul baru
        baru.jmlpeluang=m;                    //simpan m ke simpul baru
        for(int j=0;j<m;j++){               //looping untuk mentimpan peluang yang ada di simpul sebanyak m
            scanf("%s",baru.peluang[j]);    //input peluang dan simpan dalam array
        }
        if(strcmp(ortu,"null")==0){         //jika nama ortu itu "null"
            makeTree(baru,&T);              //buat tree
        }else{                              //jika tidak
            simpul *target=findSimpul(ortu,T.root);//deklarasi pointer simpul target untuk menyimpan simpul yang sesuai dengan ortu yang dicari
            if(target!=NULL){               //jika target tidak null
                addChild(baru,target);      //panggil prosedur addChild dengan paramater data baru dan target
            }
        }
    }
    scanf("%s",pita.huruf);                 //input nama tujuan akhir
    int jumlah=0;                           //deklarasi jumlah untuk menghitung seluruh value dari simpul yang terpilih
    printTree(T.root,0,&jumlah);            //panggil printTree untuk menampilkan struktur tree saat ini
    simpul *tujuan=findSimpul(pita.huruf,T.root);//deklarasi pointer simpul tujuan untuk menyimpan simpul yang sesuai dengan tujuan akhir yang dicari
    while(tujuan!=NULL){                    //selama tujuan tidak null
        tujuan->tanda=1;                    //ubah pointer tanda pada simpul tujuan dengan 1(memastikan agar tidak dihapus)
        tujuan=tujuan->parent;              //pointer tujuan menunjuk pointer parent pada simpul tujuan
    }
    hapusnol(T.root);                       //panggil prosedur hapusnol dengan T.root untuk menghapus simpul yang tdiak terpilih(simpul dengan tanda = 0)
    jumlah=0;                               //reset jumlah dengan 0
    printTree(T.root,0,&jumlah);            //panggil printTree untuk menampilkan struktur tree saat ini
    printf("peluang akhir yang diambil: %s\n",pita.huruf);//tampilkan peluang akhir yang dicari
    printf("total value: %d\n",jumlah);     //tampilkan value dari seluruh simpul akhir
    printf("semua peluang:\n");             //tampilkan semua peluang
    semuapeluang(T.root);                   //panggil prosedur semuapeluang untuk menampilkan seluruh peluang dari simpul
    return 0;
}
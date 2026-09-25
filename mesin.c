#include "header.h"
/*
Saya Jaka Permana Herawan mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah 
Algoritma dan Struktur Data untuk keberkahanNya maka saya tidak melakukan 
kecurangan seperti yang telah dispesifikasikan. Aamiin.
*/

//--Ntree--
void makeTree(data temp,tree *T){
    simpul *node;                                   //deklarsi pointer simpul untuk membuat simpul baru
    node=(simpul *) malloc (sizeof(simpul));        //alokasi memori untuk simpul baru
    node->kontainer=temp;                           //masukan data temp ke dalam kontainer pada simpul baru
    node->sibling=NULL;                             //inisialisasi pointer sibling pada simpul baru dengan NULL
    node->child=NULL;                               //inisialisasi pointer child pada simpul baru dengan NULL
    node->parent=NULL;                              //inisialisasi pointer parent pada simpul baru dengan NULL
    node->tanda=0;                                  //inisialisasi pointer dengan 0 untuk simpul yang baru dibuat
    T->root=node;                                   //menunjuk simpul root pada tree T ke simpul baru
    node=NULL;                                      //kosongkan pointer node
}

void addChild(data temp,simpul *root){
    if(root!=NULL){                                 //jika pointer simpul root tidak NULL
        simpul *baru;                               //deklarsi pointer simpul untuk membuat simpul baru
        baru=(simpul *) malloc (sizeof(simpul));    //alokasi memori untuk simpul baru
        baru->kontainer=temp;                       //masukan data temp ke dalam kontainer pada simpul baru
        baru->child=NULL;                           //inisialisasi pointer child pada simpul baru dengan NULL
        baru->parent=root;                          //pointer parent pada simpul baru menunjuk ke simpul root
        baru->tanda=0;                              //inisialisasi pointer dengan 0 untuk simpul yang baru dibuat
        if(root->child==NULL){                      //jika pointer child pada simpul root masih NULL
            baru->sibling=NULL;                     //inisialisasi pointer sibling pada simpul baru dengan NULL
            root->child=baru;                       //pointer child pada simpul root menunjuk simpul baru
        }else{                                      //jika tidak
            if(root->child->sibling==NULL){         //jika pointer sibling pada simpul child pada simpul root masih NULL
                baru->sibling=root->child;          //pointer sibling pada simpul baru menunjuk simpul child pada simpul root
                root->child->sibling=baru;          //pointer sibling pada simpul child pada simpul root menunjuk simpul baru
            }else{                                  //jika tidak
                simpul *last=root->child;           //deklarsi pointer simpul untuk mencari simpul terakhir pada sibling
                while(last->sibling!=root->child){  //selama pointer sibling pada simpul last tidak menunjuk ke simpul child pada simpul root
                    last=last->sibling;             //pointer last menunjuk simpul sibling pada simpul last
                }
                baru->sibling=root->child;          //pointer sibling pada simpul baru menunjuk simpul child pada simpul root
                last->sibling=baru;                 //pointer sibling pada simpul last menunjuk simpul baru
                last=NULL;                          //kosongkan pointer last
            }
        }
    }
}

void delAll(simpul *root){
    if(root!=NULL){                                 //jika pointer simpul root tidak NULL
        if(root->child!=NULL){                      //jika pointer child pada simpul root tidak NULL
            if(root->child->sibling==NULL){         //jika pointer sibling pada simpul child pada simpul root masih NULL
                delAll(root->child);                //panggil prosedur delAll untuk menghapus semua simpul pada sub pohon child
            }else{                                  //jika tidak
                simpul *bantu;                      //deklarsi pointer simpul bantu untuk mencari simpul terakhir pada sibling
                simpul *proses;                     //deklarsi pointer simpul proses untuk menyimpan simpul yang akan dihapus       
                bantu=root->child;                  //pointer bantu menunjuk simpul child pada simpul root
                while(bantu->sibling!=root->child){ //selama pointer sibling pada simpul bantu tidak menunjuk ke simpul child pada simpul root
                    proses=bantu;                   //pointer proses menunjuk simpul bantu
                    bantu=bantu->sibling;           //pointer bantu menunjuk simpul sibling pada simpul bantu
                    proses->sibling=NULL;           //pointer sibling pada simpul proses menunjuk ke NULL
                    delAll(proses);                 //panggil prosedur delAll untuk menghapus semua simpul pada sub pohon proses
                }
                bantu->sibling=NULL;                //pointer sibling pada simpul bantu menunjuk ke NULL
                delAll(bantu);                      //panggil prosedur delAll untuk menghapus semua simpul pada sub pohon bantu
            }
        }
        root->parent=NULL;                          //putus pointer parent
        root->child=NULL;                           //putus pointer child
        root->sibling=NULL;                         //putus pointer sibling                               
        free(root);                                 //free memori untuk simpul root
    }
}

void delChild(char nama[],simpul *root){
    if(root!=NULL){                                                                 //jika pointer simpul root tidak NULL
        simpul *hapus=root->child;                                                  //deklarsi pointer simpul hapus untuk mencari simpul yang akan dihapus
        if(hapus!=NULL){                                                            //jika pointer hapus tidak NULL
            if(hapus->sibling==NULL){                                               //jika pointer sibling pada simpul hapus masih NULL
                if(strcmp(hapus->kontainer.huruf,nama)==0){                         //jika data pada kontainer huruf pada simpul child pada simpul root sama dengan data pada temp
                    delAll(hapus);                                                  //panggil prosedur delAll untuk menghapus semua simpul pada sub pohon hapus
                    root->child=NULL;                                               //pointer child pada simpul root menunjuk ke NULL
                }
            }else{                                                                  //jika tidak
                simpul *prev=NULL;                                                  //deklarsi pointer simpul prev untuk menyimpan simpul sebelum simpul hapus
                int ketemu=0;                                                       //inisialisasi ketemu dengan 0
                while((hapus->sibling!=root->child) && (ketemu==0)){                //selama pointer sibling pada simpul hapus tidak menunjuk ke simpul child pada simpul root dan ketemu masih 0
                    if(strcmp(hapus->kontainer.huruf,nama)==0){                     //jika data pada kontainer huruf pada simpul hapus sama dengan data pada temp
                        ketemu=1;                                                   //ubah nilai ketemu menjadi 1
                    }else{                                                          //jika tidak
                        prev=hapus;                                                 //pointer prev menunjuk simpul hapus
                        hapus=hapus->sibling;                                       //pointer hapus menunjuk simpul sibling pada simpul hapus
                    }
                }
                if((ketemu==0) && (strcmp(hapus->kontainer.huruf,nama)==0)){        //jika ketemu masih 0 dan data pada kontainer huruf pada simpul hapus sama dengan data pada temp
                    ketemu=1;                                                       //ubah nilai ketemu menjadi 1
                }
                if(ketemu==1){                                                      //jika ketemu 1
                    simpul *last=root->child;                                       //deklarsi pointer simpul last untuk mencari simpul terakhir pada sibling
                    while(last->sibling!=root->child){                              //selama pointer sibling pada simpul last tidak menunjuk ke simpul child pada simpul root
                        last=last->sibling;                                         //pointer last menunjuk simpul sibling pada simpul last
                    }
                    if(prev==NULL){                                                 //jika pointer prev masih NULL 
                        if((hapus->sibling==last) && (last->sibling==root->child)){ //jika pointer sibling pada simpul hapus menunjuk ke simpul last dan pointer sibling pada simpul last menunjuk ke simpul child pada simpul root
                            root->child=last;                                       //pointer child pada simpul root menunjuk simpul last
                            last->sibling=NULL;                                     //pointer sibling pada simpul last menunjuk ke NULL 
                        }else{                                                      //jika tidak                               
                            root->child=hapus->sibling;                             //pointer child pada simpul root menunjuk simpul sibling pada simpul hapus
                            last->sibling=root->child;                              //pointer sibling pada simpul last menunjuk ke simpul child pada simpul root
                        }
                    }else{                                                          //jika tidak
                        if((prev==root->child) && (hapus->sibling==root->child)){   //jika pointer prev menunjuk ke simpul child pada simpul root dan pointer sibling pada simpul hapus menunjuk ke simpul child pada simpul root
                            root->child->sibling=NULL;                              //pointer sibling pada simpul child pada simpul root menunjuk ke NULL
                        }else{                                                      //jika tidak
                            prev->sibling=hapus->sibling;                           //pointer sibling pada simpul prev menunjuk simpul sibling pada simpul hapus
                        }
                    }
                    hapus->sibling=NULL;                                            //pointer sibling pada simpul hapus menunjuk ke NULL
                    prev=NULL;                                                      //pointer simpul prev menunjuk null
                    last=NULL;                                                      //pointer simpul last menunjuk null
                    delAll(hapus);                                                  //panggil prosedur delAll untuk menghapus semua simpul pada sub pohon hapus
                }
            }
        }   
    }
}

simpul *findSimpul(char nama[],simpul *root){
    simpul *hasil=NULL;                                                             //deklarasi pointer simpul hasil untuk menyimpan simpul yang dicari
    if(root!=NULL){                                                                 //jika simpul root itu tidak null
        if(strcmp(root->kontainer.huruf,nama)==0){                                  //jika nama simpul root itu sama dengan nama yang dicari
            hasil=root;                                                             //pointer hasil menunjuk simpul root
        }else{                                                                      //jika tidak
            simpul *bantu=root->child;                                              //deklarasi pointer simpul bantu untuk mengecek seluruh tree dengan pointer child pada simpul root
            if(bantu!=NULL){                                                        //jika bantu tidak null
                if(bantu->sibling==NULL){                                           //jika pointer sibling pada simpul bantu itu null
                    hasil=findSimpul(nama,bantu);                                   //simpan nama simpul yang dicari dengan pointer bantu ke simpul hasil
                }else{                                                              //jika tidak
                    simpul *awal=bantu;                                             //deklarasi pointer simpul awal dengan bantu untuk penanda simpul pertama
                    do{                                                             //looping secara do while selama pointer bantu tidak sama dengan pointer awal
                        hasil=findSimpul(nama,bantu);                               //panggil secara rekursif dengan parameter bantu dan simpan ke pointer hasil
                        if(hasil!=NULL){                                            //jika hasil tidak null
                            return hasil;                                           //kembalikan hasil
                        }
                        bantu=bantu->sibling;                                       //pointer bantu menunjuk pointer sibling pada simpul bantu
                    }while(bantu!=awal);
                }
            }
        }
    }
    return hasil;                                                                   //kembalikan hasil
}

int digit(simpul *root){
    int maksimal=0;                                                                 //inisialisasi maksimal dengan 0 untuk menyimpan digit terpanjang
    int digit=0;                                                                    //inisialisasi digit dengan 0 untuk nilai awal digit
    int angka=root->kontainer.value;                                                //masukan simpul root value sekarang ke dalam variabel angka
    if(angka==0){                                                                   //jika angka itu 0
        digit=1;                                                                    //maka ubah digit jadi 1
    }
    while(angka!=0){                                                                //selama angka tidak 0
        digit++;                                                                    //iterasi digit
        angka=angka/10;                                                             //operasi jumlah digit
    }
    if(digit>maksimal){                                                             //jika digit lebih besar dari maksimal
        maksimal=digit;                                                             //ubah nilai maksimal dengan digit
    }
    return maksimal;                                                                //kembalikan maksimal
}
int lebarsimpul(simpul *root){
    int maks=0;                                                                     //inisialisasi maks dengan 0 untuk menyimpan panjang kata terpanjang
    if(root!=NULL){                                                                 //jika root tidak null
        if(root->sibling==NULL){                                                    //jika pointer sibling pada simpul root itu null
            int panjang=strlen(root->kontainer.huruf)+3+digit(root);                //ambil panjang kata nama simpul, +3 = " - ", dan digit value simpan di variabel panjang
            if(panjang>maks){                                                       //jika panjang lebih dari maks
                maks=panjang;                                                       //ubah nilai maks dengan panjang
            }
            for(int i=0;i<root->kontainer.jmlpeluang;i++){                            //looping untuk mendapatkan kata terpanjang dari peluang simpul sekarang sebanyak jmlvalue
                panjang=strlen(root->kontainer.peluang[i])+2;                       //ambil panjang kata nama peluang pada simpul root dan +2 = "[]" ke dalam variabel panjang
                if(panjang>maks){                                                   //jika panjang lebih dari maks
                    maks=panjang;                                                   //ubah nilai maks dengan panjang
                }
            }
        }else{
            simpul *awal=root;
            simpul *bantu=root;
            do{                                                                     //looping secara do while selama pointer bantu tidak sama dengan pointer awal
                int panjang=strlen(bantu->kontainer.huruf)+3+digit(bantu);          //ambil panjang kata nama simpul, 3 = " - ", dan digit value simpan di variabel panjang
                if(panjang>maks){                                                   //jika panjang lebih dari maks
                    maks=panjang;                                                   //ubah nilai maks dengan panjang
                }
                for(int i=0;i<bantu->kontainer.jmlpeluang;i++){                     //looping untuk mendapatkan kata terpanjang dari peluang simpul sekarang sebanyak jmlvalue
                    panjang=strlen(bantu->kontainer.peluang[i])+2;                  //ambil panjang kata nama peluang pada simpul root dan +2 = "[]" ke dalam variabel panjang
                    if(panjang>maks){                                               //jika panjang lebih dari maks
                        maks=panjang;                                               //ubah nilai maks dengan panjang
                    }       
                }
                bantu=bantu->sibling;                                               //pointer bantu menunjuk pointer sibling pada simpul bantu
            }while(bantu!=awal);
        }
    }
    return maks;                                                                    //kembalikan maks
}
void printTree(simpul *root,int spasi,int *jumlah){
    if(root!=NULL){                                                                 //jika root tidak null
        for(int i=0;i<spasi;i++){                                                   //looping untuk mencetak spasi sebanyak variabel spasi
            printf(" ");                                                            //tampilkan spasi
        }
        printf("%s - %d\n",root->kontainer.huruf,root->kontainer.value);            //tampilkan nama simpul dan valuenya
        for(int j=0;j<root->kontainer.jmlpeluang;j++){                              //looping untuk mencetak semua peluang simpul sekarang sebanyak jmlvalue
            for(int k=0;k<spasi;k++){                                               //looping untuk mecetak spasi sebanyak variabel spasi
                printf(" ");                                                        //tampilkan spasi
            }
            printf("[%s]\n",root->kontainer.peluang[j]);                            //tampilkan nama peluang ke j
        }
        printf("\n");
        (*jumlah)=(*jumlah)+root->kontainer.value;                                  //iterasi variabel jumlah dengan value dari simpul
        int panjang=lebarsimpul(root);                                              //ambil panjang kata terpanjang dengan paramater root disimpan ke variabel panjang
        simpul *bantu=root->child;                                                  //deklarasi pointer simpul bantu untuk mengecek seluruh tree dengan pointer child pada simpul root
        if(bantu!=NULL){                                                            //jika bantu tidak null
            if(bantu->sibling==NULL){                                               //jika pointer sibling pada simpul bantu itu null
                printTree(bantu,spasi+panjang,jumlah);                              //panggil secara rekursif prosedur printTree dengan parameter bantu,spasi bertambah dengan panjang dan jumlah
            }else{                                                                  //jika tidak
                simpul *awal=bantu;                                                 //deklarasi pointer simpul awal dengan bantu untuk penanda simpul pertama
                do{                                                                 //looping secara do while selama pointer bantu tidak sama dengan pointer awal
                    printTree(bantu,spasi+panjang,jumlah);                          //panggil secara rekursif prosedur printTree dengan parameter bantu,spasi bertambah dengan panjang dan jumlah
                    bantu=bantu->sibling;                                           //pointer bantu menunjuk pointer sibling pada simpul bantu
                }while(bantu!=awal);
            }
        }
    }
}

void hapusnol(simpul *root){
    if(root!=NULL){                                                                 //jika root tidak null
        simpul *bantu=root->child;                                                  //deklarasi pointer simpul bantu untuk mengecek seluruh tree dengan pointer child pada simpul root
        if(bantu!=NULL){                                                            //jika bantu tidak null
            char hapus[50][101];                                                    //deklarasi hapus untuk menyimpan nama simpul yang akan dihapus dengan pointer tanda 0
            int n=0;                                                                //inisialisasi n dengan 0 untuk jumlah nama simpul yang dihapus
            if(bantu->sibling==NULL){                                               //jika pointer sibling pada simpul bantu itu null
                if(bantu->tanda==0){                                                //jika pointer tanda pada simpul bantu itu 0
                    strcpy(hapus[n],bantu->kontainer.huruf);                        //copy nama simpul ke hapus 
                    n++;                                                            //iterasi n
                }else{                                                              //jika tidak
                    hapusnol(bantu);                                                //panggil secara rekursif prosedur hapusnol dengan parammeter bantu
                }
            }else{                                                                  //jika tidak
                simpul *awal=bantu;                                                 //deklarasi pointer simpul awal dengan bantu untuk penanda simpul pertama
                do{                                                                 //looping secara do while selama pointer bantu tidak sama dengan pointer awal
                    if(bantu->tanda==0){                                            //jika pointer tanda pada simpul bantu itu 0
                        strcpy(hapus[n],bantu->kontainer.huruf);                    //copy nama simpul ke hapus
                        n++;                                                        //iterasi n
                    }else{                                                          //jika tidak
                        hapusnol(bantu);                                            //panggil secara rekursif prosedur hapusnol dengan parammeter bantu
                    }
                    bantu=bantu->sibling;                                           //pointer bantu menunjuk pointer sibling pada simpul bantu
                }while(bantu!=awal);
            }
            for(int i=0;i<n;i++){                                                   //looping untuk menghapus simpul yang tidak terpilih dengan pointer tanda = 0
                delChild(hapus[i],root);                                            //panggil prosedur delChild dengan paramter nama hapus ke i dan simpul root
            }
        }
    }
}
void semuapeluang(simpul *root){
    if(root!=NULL){                                                                 //jika root tidak null
        for(int i=0;i<root->kontainer.jmlpeluang;i++){                              //looping untuk mencetak nama peluang yang ada pada simpul root sebanyak jmlvalue
            printf("[%s]\n",root->kontainer.peluang[i]);                            //tampilkan nama peluang ke i
        }
        if(root->child!=NULL){                                                      //jika pointer child pada simpul root tidak null
            semuapeluang(root->child);                                              //panggil secara rekursif prosedur semuapeluang dengan parameter pointer child pada simpul root
        }
    }
}
int strtoint(char str[]){
    int hasil=0;                                    //inisialisasi hasil untuk menyimpan int dari string               
    int i=0;                                        //inisialisasi i untuk indeks karakter
    while(str[i]!='\0'){                            //selama indeks karakter i itu bukan karakter null
        hasil=(hasil*10) + (str[i]-'0');            //operasi mengubah string to int
        i++;                                        //iterasi i
    }
    return hasil;                                   //kembalikan ke hasil
}


//--mesin kata--
int indeks;                                         //posisi karakter sekarang
int panjangkata;                                    //panjang kata sekarang
char ckata[201];                                    //kata sekarang

int EOP(char pita[]){
    if(pita[indeks] == '\0'){                       //akhir perintah
        return 1;                                   //true = sudah EOP
    }else{
        return 0;                                   //false = belum
    }
}
void START(char pita[]){
    indeks=0;                                       //inisialisasi indeks dengan 0
    panjangkata=0;                                  //inisialisasi panjangkata dengan 0
    while(pita[indeks] == '#'){                     //selama pita ke indeks itu pagar
        indeks++;                                   //iterasi indeks
    }
    while((pita[indeks] != '#') && (EOP(pita)==0)){ //selama pita ke indeks itu bukan pagar fan belum EOP
        ckata[panjangkata] = pita[indeks];          //simpan pita ke indeks ke dalam ckata ke panjangkata
        indeks++;                                   //iterasi indeks
        panjangkata++;                              //iterasi panjangkata
    }
    ckata[panjangkata]='\0';                        //batasi ckata ke panjangakata dengan null karakter
}
void INC(char pita[]){
    panjangkata=0;                                  //inisialisasi panjangkata dengan 0
    while(pita[indeks] == '#'){                     //selama pita ke indeks itu pagar
        indeks++;                                   //iterasi indeks
    }
    while((pita[indeks] != '#') && (EOP(pita)==0)){ //selama pita ke indeks itu bukan pagar fan belum EOP
        ckata[panjangkata] = pita[indeks];          //simpan pita ke indeks ke dalam ckata ke panjangkata
        indeks++;                                   //iterasi indeks
        panjangkata++;                              //iterasi panjangkata
    }
    ckata[panjangkata]='\0';                        //batasi ckata ke panjangakata dengan null karakter
    
}
char* GETKATA(){
    return ckata;                                   //kemablikan ckata(kata saat ini)
}
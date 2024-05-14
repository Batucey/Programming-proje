#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char adi[100];
    int fiyati;
    int hazirlanma_suresi;
    int mevcutluk;
} yemek;

yemek yemekler[20];
int yemek_sayisi = 0;

typedef struct {
    char id[100];
    char adi[100];
    int fiyati;
    char siparis_verilme_zamani[100];
    char hazirlanma_zamani[100];
    char kullanici[100];
    char sef[100];
} siparis;

siparis siparisler[50];
int siparis_sayisi = 0;

//Yemeklerin oldugu dosyayi aciyor dosya acilmazsa hata veriyor
void yemek_dosyasi(const char* YemekListesi) {
    FILE* dosya = fopen(YemekListesi, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi. %s\n", YemekListesi);
        exit(1);
    }

    while (yemek_sayisi < 20 && fgets(yemekler[yemek_sayisi].adi, 100, dosya) != NULL) {//veri cekimi baslýyor
        fgets(yemekler[yemek_sayisi].adi, 100, dosya);
        fgets(yemekler[yemek_sayisi].fiyati, 100, dosya);
        fgets(yemekler[yemek_sayisi].hazirlanma_suresi, 100, dosya);
        fgets(yemekler[yemek_sayisi].mevcutluk, 100, dosya);

        yemekler[yemek_sayisi].adi[strcspn(yemekler[yemek_sayisi].adi, "\n")] = '\0';// \0 yerine !EOF de kullanilabir ikisi de ayni islevi goruyor satirlar karismasin diye kullaniliyor
// strcspn de kütüphane kodu belli karakterleri aramak icin kullanýlýyo
        yemek_sayisi++;
    }

    fclose(dosya);
}

//Siparislerin oldugu dosyayi aciyor dosya acilmazsa hata veriyor
//const char* da pointer const da degistirelemeyecegini gosteriyor
void siparisler_dosyasi(const char* MevcutSiparisler) {
    FILE* dosya = fopen(MevcutSiparisler, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi. %s\n", MevcutSiparisler);
        exit(1);
    }

    while (siparis_sayisi < 50 && fgets(siparisler[siparis_sayisi].id, 100, dosya) != NULL) {
        fgets(siparisler[siparis_sayisi].adi, 100, dosya);
        fgets(siparisler[siparis_sayisi].fiyati,100 ,dosya);
        fgets(siparisler[siparis_sayisi].siparis_verilme_zamani, 100, dosya);
        fgets(siparisler[siparis_sayisi].hazirlanma_zamani, 100, dosya);
        fgets(siparisler[siparis_sayisi].kullanici, 100, dosya);
        fgets(siparisler[siparis_sayisi].sef, 100, dosya);

        siparisler[siparis_sayisi].id[strcspn(siparisler[siparis_sayisi].id, "\n")] = '\0';
        siparisler[siparis_sayisi].adi[strcspn(siparisler[siparis_sayisi].adi, "\n")] = '\0';
        siparisler[siparis_sayisi].siparis_verilme_zamani[strcspn(siparisler[siparis_sayisi].siparis_verilme_zamani, "\n")] = '\0';
        siparisler[siparis_sayisi].hazirlanma_zamani[strcspn(siparisler[siparis_sayisi].hazirlanma_zamani, "\n")] = '\0';
        siparisler[siparis_sayisi].kullanici[strcspn(siparisler[siparis_sayisi].kullanici, "\n")] = '\0';
        siparisler[siparis_sayisi].sef[strcspn(siparisler[siparis_sayisi].sef, "\n")] = '\0';
        siparis_sayisi++;
    }

    fclose(dosya);
}

int main() {
    yemek_dosyasi("yemeklistesi.txt");
    siparisler_dosyasi("MevcutSiparisler.txt");

    return 0;
}


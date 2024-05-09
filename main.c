#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Siparis {
    char sip_id[10];
    char sip_detay[100];
};

void siparisleri_oku(char* MevcutSiparisler, struct Siparis siparisler[], int* siparis_sayisi) {
    FILE* belge = fopen(MevcutSiparisler, "r");//Belgeden okuma
    if (belge == NULL) {
        printf("Aktif siparis bulunamadi.\n");
        return;
    }
    //Siparislerin oldugu dosyayi okuyon fonk
    //Siparislerin oldugu dosyayi okuyup eger aktif siparis yoksa siparis bulunamadi outputunu veriyor.
    *siparis_sayisi = 0;
    while (fscanf(belge, "%s %[^\n]", siparisler[*siparis_sayisi].sip_id, siparisler[*siparis_sayisi].sip_detay) != EOF) {
        (*siparis_sayisi)++;
        // %s %[^\n] Yazilan bütün seyleri okumasi için kullanilan bi kullanim.
    }
    fclose(belge);

}
void siparisleri_yonet(struct Siparis siparisler[], int siparis_sayisi) {
    char onay;
    for (int i = 0; i < siparis_sayisi; i++) {
        printf("Siparis idsi: %s, Detay: %s\n", siparisler[i].sip_id, siparisler[i].sip_detay);
        printf("Siparisi onaylamak icin '1', reddetmek icin '2' girin: ");
        scanf(" %c", &onay); //"%c" char okumak için kullanilir
        if (onay == '1') {
            strcat(siparisler[i].sip_detay, "Siparis Onaylandi.");
        }
        if  (onay == '2') {
            strcat(siparisler[i].sip_detay, "Siparis Reddedildi.");
        }
    }
}
//Bu fonk gelen siparisleri kontrol edip onay veya reddetmeye yariyor.
//Restoran onay verir onaylandi vermezse reddedildi outputunu veriyor.
int main() {
    char MevcutSiparisler[100];
    printf("Yeni siparisler belgesinin adi: ");
    scanf("%s", MevcutSiparisler);

    struct Siparis siparisler[100];
    int siparis_sayisi;

    siparisleri_oku(MevcutSiparisler, siparisler, &siparis_sayisi);
    siparisleri_yonet(siparisler, siparis_sayisi);

    return 0;
}

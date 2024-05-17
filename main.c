#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 100
#define ASCI_SAYISI 3
int arrayYemekSira[] = {1, 2, 3, 4, 5, 6};
char *arrayYemek[] = {
    "Lahmacun",
    "Hamburger",
    "Manti",
    "Tost",
    "Tavuk Durum",
    "Et Durum"};
int arrayYemekFiyat[] = {75, 250, 170, 60, 80, 160};
int arrayYemekSure[] = {20, 30, 45, 10, 15, 15};
char *arrayYemekMevcudiyet[] = {
    "Mevcuttur",
    "Mevcuttur",
    "Mevcut Degildir",
    "Mevcuttur",
    "Mevcuttur",
    "Mevcut degildir"};
int randomNumbers[MAX_SIZE];

// Asci yapısı
typedef struct {
    int id;
    int bosta;
    int musaitlik; // Ascinin sonraki musait olma zamani
} asci;

asci ascilar[ASCI_SAYISI];

void randomNumberGenerator()
{
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++)
    {
        randomNumbers[i] = rand() % 1000 + 1;
    }
}

// Ascilari baslat
void Ascilar_baslat()
{
    for (int i = 0; i < ASCI_SAYISI; i++)
    {
        ascilar[i].id = i + 1;
        ascilar[i].bosta = 1; // Hepsi bosta
        ascilar[i].musaitlik = 0;
    }
}

// Musait asciyi bul fonku
int musait_asciyi_bul(){
    for (int i = 0; i < ASCI_SAYISI; i++)
    {
        if (ascilar[i].bosta)
        {
            return i;
        }
    }
    return -1; // Bos asci bulunamadi
}
void yemekListesiGoster()
{
    FILE *yemekListesi = fopen("YemekListesi.txt", "r");
    char sira[500];

    if (yemekListesi == NULL)
    {
        printf("Dosya Bulunamadi!");
        exit(1);
    }

    while (fgets(sira, sizeof(sira), yemekListesi) != NULL)
    {
        printf("%s", sira);
    }

    fclose(yemekListesi);
}

void musteriPanel()
{

    yemekTakip();
}

void yeniSiparis()
{

    int yeniYemekSiparis;
    yemekListesiGoster();

    do
    {
        printf("\nYemek istediginiz numarayi giriniz:");
        scanf("%d", &yeniYemekSiparis);
        if (yeniYemekSiparis < 1 || yeniYemekSiparis > 6 || yeniYemekSiparis == 3 || yeniYemekSiparis == 6)
        {
            printf("%d numarali menu yoktur.\n", yeniYemekSiparis);
            printf("Gecerli bir menu seciniz:\n");
        }
    } while (yeniYemekSiparis < 1 || yeniYemekSiparis > 6 || yeniYemekSiparis == 3 || yeniYemekSiparis == 6);

    FILE *yeniSiparisEklemeTXT = fopen("MevcutSiparisler.txt", "a");
    if (yeniSiparisEklemeTXT == NULL)
    {
        printf("Dosya bulunamadi!");
        return;
    }

        int musait_asci_sayisi = musait_asciyi_bul();
    if (musait_asci_sayisi == -1)
    {
        printf("Su anda musait asci yok. Lutfen daha sonra tekrar deneyiniz.\n");
        return;
    }

    asci *asci = &ascilar[musait_asci_sayisi];

    int i = yeniYemekSiparis;
    int currentTime = time(NULL);
    int hazirlanmaSure = arrayYemekSure[i - 1];
    int tamamlanmaZamani = currentTime + hazirlanmaSure * 60;

    fprintf(yeniSiparisEklemeTXT, "ID numarasi:%d\n", randomNumbers[i - 1]);
    fprintf(yeniSiparisEklemeTXT, "-%s\n", arrayYemek[i - 1]);
    fprintf(yeniSiparisEklemeTXT, "-Fiyati %d TL\n", arrayYemekFiyat[i - 1]);
    fprintf(yeniSiparisEklemeTXT, "-Hazirlanma suresi %d dakika\n", hazirlanmaSure);
    fprintf(yeniSiparisEklemeTXT, "-Asci ID:%d\n", asci->id);
    fprintf(yeniSiparisEklemeTXT, "-Tamamlanmazamani: %s", ctime(&tamamlanmaZamani));
    fprintf(yeniSiparisEklemeTXT, "\n");

    fclose(yeniSiparisEklemeTXT);

    printf("%d numarali siparis asci %d tarafindan hazirlanacak ve %d dakika icinde tamamlanacak.\n", yeniYemekSiparis, asci->id, hazirlanmaSure);

    asci->bosta = 0;
    asci->musaitlik = tamamlanmaZamani;

    sleep(hazirlanmaSure * 60); // Gercek zamanli uyku belirtilen süre kadar bekler

    asci->bosta = 1; // Asci tekrar musait
}

void eskiSiparisler()
{
    FILE *oncekiSiparisler = fopen("OncekiSiparisler.txt", "r");
    char oncekiYemek[100]; // Changed to array to store lines

    if (oncekiSiparisler == NULL)
    {
        printf("Dosya Bulunamadi!");
        return;
    }

    while (fgets(oncekiYemek, sizeof(oncekiYemek), oncekiSiparisler) != NULL)
    {
        printf("%s", oncekiYemek);
    }

    fclose(oncekiSiparisler);
}

void mevcutSiparisler()
{
    FILE *mevcutSiparisListesi = fopen("MevcutSiparisler.txt", "r");
    char mevcutYemek[100]; // Changed to array to store lines

    if (mevcutSiparisListesi == NULL)
    {
        printf("Dosya bulunamadi!");
        return;
    }
    printf("\n");

    while (fgets(mevcutYemek, sizeof(mevcutYemek), mevcutSiparisListesi) != NULL)
    {
        printf("%s", mevcutYemek);
        fprintf(mevcutSiparisListesi, "\n");
    }

    fclose(mevcutSiparisListesi);
}

void yemekTakip()
{
    int secenek;
    int secim;

    printf("1-Yeni Siparis\n");
    printf("2-Mevcut Siparisler\n");
    printf("3-Eski Siparisler\n");
    printf("Seciminizi giriniz: ");
    scanf("%d", &secenek);
    printf("\n");

    if (secenek == 1)
    {
        yeniSiparis();
    }
    else if (secenek == 2)
    {
        mevcutSiparisler();
    }
    else if (secenek == 3)
    {
        eskiSiparisler();
    }
    else
    {
        printf("Gecersiz tusladiniz! Tekrar deneyin!\n");
        yemekTakip();
    }
} /* !********************************************************************************************************************************************************************************************! */
void restoranPanel()
{
    yemekSecimIslemleri();
}
void arrayiDosyayaYaz(FILE *dosya)
{
    for (int i = 0; i < sizeof(arrayYemekFiyat) / sizeof(arrayYemekFiyat[0]); i++)
    {
        fprintf(dosya, "%d-%s\n-Fiyati %d TL\n-Hazirlanma suresi %d dakika\n-%s\n\n", arrayYemekSira[i], arrayYemek[i], arrayYemekFiyat[i], arrayYemekSure[i], arrayYemekMevcudiyet[i]);
    }
}

void yemekIslemleri()
{
    int yemekIslem;
    printf("1-Guncelleme\n");
    printf("2-Silme\n");
    printf("3-Ekleme\n");
    printf("Yapmak istediginiz islemi secin:");
    scanf("%d", &yemekIslem);

    if (yemekIslem == 1)
    {
        yemekGuncelleme();
    }
    else if (yemekIslem == 2)
    {
        yemekSilme();
    }
    else if (yemekIslem == 3)
    {
        yemekEkleme();
    }
    else
    {
        printf("Gecersiz islem! Tekrar Deneyiniz.\n");
        yemekIslemleri();
    }
}

void yemekGuncelleme()
{
    FILE *yemekListesi = fopen("YemekListesi.txt", "r+");
    char karakter[500];

    if (yemekListesi == NULL)
    {
        printf("Dosya bulunamadi!");
    }

    while (fgets(karakter, sizeof(karakter), yemekListesi) != NULL)
    {
        printf("%s", karakter);
    }

    int arraySecim;
    printf("islem yapmak istediginiz kismi secin: 1-i,2-f,3-s,4-m : ");
    scanf("%d", &arraySecim);

    int arrayMenuSecim;
    printf("degistirmek istediginiz menuyu secin: ");
    scanf("%d", &arrayMenuSecim);

    if (arraySecim == 1)
    {
        char yeniYemek[20];
        printf("yeni yemek ismi :");
        scanf(" %[^\n]", yeniYemek);
        arrayYemek[arrayMenuSecim - 1] = yeniYemek;
    }
    else if (arraySecim == 2)
    {
        int yeniYemekFiyat;
        printf("yeni yemek fiyatini girin:");
        scanf("%d", &yeniYemekFiyat);
        arrayYemekFiyat[arrayMenuSecim - 1] = yeniYemekFiyat;
    }
    else if (arraySecim == 3)
    {
        int yeniYemekSure;
        printf("yeni yemek suresini girin:");
        scanf("%d", &yeniYemekSure);
        arrayYemekSure[arrayMenuSecim - 1] = yeniYemekSure;
    }
    else if (arraySecim == 4)
    {
        char yeniYeniMevcut[20];
        printf("yeni yemek mevcudiyetini girin:");
        scanf(" % [^\n] ", yeniYeniMevcut);
        arrayYemekMevcudiyet[arrayMenuSecim - 1] = yeniYeniMevcut;
    }

    // Dosyayı yeniden yazarak güncellenmiş array verilerini dosyaya aktar
    rewind(yemekListesi);
    arrayiDosyayaYaz(yemekListesi);

    fclose(yemekListesi);
}
void yemekEkleme()
{
    FILE *YemekListesi;
    YemekListesi = fopen("YemekListesi.txt", "a");
    if (YemekListesi == NULL)
    {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    char **arrayYemek;
    int arrayBoyutYemek = 1;
    arrayYemek = (char **)malloc(arrayBoyutYemek * sizeof(char *));

    char **arrayYemekMevcut;
    int arrayBoyutYemekMevcut = 1;
    arrayYemekMevcut = (char **)malloc(arrayBoyutYemekMevcut * sizeof(char *));

    int *yemekArrayFiyat;
    int arrayBoyutFiyat = 1;
    yemekArrayFiyat = (int *)malloc(arrayBoyutFiyat * sizeof(int));

    int *yemekBoyutSure;
    int arrayBoyutSure = 1;
    yemekBoyutSure = (int *)malloc(arrayBoyutSure * sizeof(int));

    printf("Eklemek istediginiz yemegi yazin: ");
    char yemekIsmi[100];
    scanf(" %[^\n]", yemekIsmi);

    printf("Eklemek istediginiz yemegin fiyatini yazin: ");
    int yemekFiyat;
    scanf("%d", &yemekFiyat);

    printf("Eklemek istediginiz yemegin hazirlanma suresini girin: ");
    int yemekSure;
    scanf("%d", &yemekSure);

    printf("Eklemek istenilen yemek mevcudiyeti:");
    char yemekMevcut[15];
    scanf(" %[^\n]", yemekMevcut);

    arrayYemek[arrayBoyutYemek - 1] = strdup(yemekIsmi);
    yemekArrayFiyat[arrayBoyutFiyat - 1] = yemekFiyat;
    yemekBoyutSure[arrayBoyutSure - 1] = yemekSure;
    arrayYemekMevcut[arrayBoyutYemekMevcut - 1] = strdup(yemekMevcut);

    FILE *yemekListesi = fopen("YemekListesi.txt", "r");
    char karakter;
    int satirSayisi = 0;

    if (yemekListesi == NULL)
    {
        printf("yemek listesi bulunamadi!");
        return 1;
    }

    while ((karakter = fgetc(yemekListesi)) != EOF)
    {
        if (karakter == '\n')
        {
            satirSayisi++;
        }
    }

    int yemekSatirSayisi = satirSayisi / 5 + 1;

    fprintf(YemekListesi, "\n%d-%s:.\n-%d TL.\n-Hazirlanma suresi %d dakikadir.\n-%s\n", yemekSatirSayisi, yemekIsmi, yemekFiyat, yemekSure, yemekMevcut);

    free(arrayYemek);
    free(yemekArrayFiyat);
    free(yemekBoyutSure);

    fclose(YemekListesi);
    yemekListesiGoster();
}

void yemekSilme(int index)
{
    int silinecekIndex;
    printf("Silmek istediginiz menuyu secin: ");
    scanf("%d", &silinecekIndex);

    // Menüyü sil
    menuSil(silinecekIndex - 1);

    // Dosyayı yeniden yazarak güncellenmiş array verilerini dosyaya aktar
    FILE *dosya = fopen("YemekListesi.txt", "w");
    if (dosya == NULL)
    {
        printf("Dosya açılamadı!\n");
        return;
    }
    arrayiDosyayaYaz(dosya);
    fclose(dosya);

    printf("\nYeni yemek listesi:\n\n");

    yemekListesiGoster();
}

void menuSil(int index)
{
    // Silinecek menüye ait verileri boşalt
    for (int i = index; i < sizeof(arrayYemek) / sizeof(arrayYemek[0]); i++)
    {
        arrayYemek[i] = arrayYemek[i + 1];
        arrayYemekFiyat[i] = arrayYemekFiyat[i + 1];
        arrayYemekSure[i] = arrayYemekSure[i + 1];
        arrayYemekMevcudiyet[i] = arrayYemekMevcudiyet[i + 1];
    }

    // Dizinin boyutunu bir azalt
    int yeniBoyut = sizeof(arrayYemek) / sizeof(arrayYemek[0]) - 1;
    arrayYemekSira[yeniBoyut] = 0;
    arrayYemek[yeniBoyut] = NULL;
    arrayYemekFiyat[yeniBoyut] = 0;
    arrayYemekSure[yeniBoyut] = 0;
    arrayYemekMevcudiyet[yeniBoyut] = NULL;

    // SİLİNEN YERE 0 VE NULL YAZMAYACAK VE BİRDEN FAZLA KEZ SİLME İŞLEMİ YAPABİLECEK KOD ORDA KALDIK
}

void onayRedIslemleri()
{
    FILE *mevcutSiparisler = fopen("MevcutSiparisler.txt", "r");
    char karakter[500];

    if (mevcutSiparisler == NULL)
    {
        printf("Dosya Bulunamadi!");
        return;
    }

    while (fgets(karakter, sizeof(karakter), mevcutSiparisler) != NULL)
    {
        printf("%s", karakter);
    }

    fclose(mevcutSiparisler);

    int onayRedSecim;
    printf("Islem yapmak istediginiz menu ID girin: ");
    scanf("%d", &onayRedSecim);

    int IDBulundu = 0;
    int onayRed;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (onayRedSecim == randomNumbers[i])
        {
            IDBulundu = 1;

            printf("Onaylamak icin :1\n");
            printf("Reddetmek icin :2\n");
            scanf("%d", &onayRed);

            if (onayRed == 1)
            {
                printf("ID dogru!\n");
                FILE *onaylananSiparisler = fopen("onaylananSiparisler.txt", "a");
                if (onaylananSiparisler == NULL)
                {
                    printf("Dosya Bulunamadi!\n");
                    return;
                }

                fprintf(onaylananSiparisler, "ID numarasi:%d\n", randomNumbers[i]);
                fprintf(onaylananSiparisler, "-%s\n", arrayYemek[i]);
                fprintf(onaylananSiparisler, "-Fiyati %d TL\n", arrayYemekFiyat[i]);
                fprintf(onaylananSiparisler, "-Hazirlanma suresi %d dakika\n", arrayYemekSure[i]);
                fprintf(onaylananSiparisler, "\n");
                fclose(onaylananSiparisler);
                printf("Siparis onaylandi.");
                printf("\n");
                break;
            }
            else if (onayRed == 2)
            {
                printf("ID dogru!\n");
                printf("Siparis reddedildi.\n");
                break;
            }
            else
            {
                printf("Gecersiz secim!\n");
            }
        }
    }

    if (!IDBulundu)
    {
        printf("ID bulunamadi!\n");
    }
}

void yemekSecimIslemleri()
{
    int islemSecim;

    printf("1-Yemek ekleme-guncelleme-silme \n");
    printf("2-Yeni siparis onay/red \n");
    printf("3-Gunluk rapor alma/goruntuleme \n");
    printf("4-Analizler \n");
    printf("Yapmak istediginiz islemi secin:");
    scanf("%d", &islemSecim);
    printf("\n");

    switch (islemSecim)
    {
    case 1:
        yemekIslemleri();
        break;
    case 2:
        onayRedIslemleri();
        break;
    }
}
/* !********************************************************************************************************************************************************************************************! */

int main()
{
    int secim;
    randomNumberGenerator();

    while (1)
    {
        printf("\n1. Musteri Paneli\n");
        printf("2. Restoran Paneli\n");
        printf("3. Cikis\n");
        printf("Seciminizi yapiniz: ");
        scanf("%d", &secim);
        printf("\n");

        if (secim == 1)
        {
            musteriPanel();
        }
        else if (secim == 2)
        {
            restoranPanel();
        }
        else if (secim == 3)
        {
            break;
        }
        else
        {
            printf("Gecersiz secim! Tekrar deneyiniz.\n");
        }
    }
    return 0;
}

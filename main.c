#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 100
#define MAX_LINE_LENGTH 1000
static int arrayYemekSira[] = {1, 2, 3, 4, 5, 6};
static char *arrayYemek[] = {
    "Lahmacun",
    "Hamburger",
    "Manti",
    "Tost",
    "Tavuk Durum",
    "Et Durum"};
static int arrayYemekFiyat[] = {75, 250, 170, 60, 80, 160};
static int arrayYemekSure[] = {20, 30, 45, 10, 15, 15};
static char *arrayYemekMevcudiyet[] = {
    "Mevcuttur",
    "Mevcuttur",
    "Mevcut Degildir",
    "Mevcuttur",
    "Mevcuttur",
    "Mevcut degildir"};
int totalYemekFiyat[MAX_SIZE];
int size = 0;
int arrayBoyut = sizeof(arrayYemek) / sizeof(arrayYemek[0]);
char *arrayAsci[] = {"Asci1", "Asci2", "Asci3", "Asci4", "Asci5"};

int randomNumbers[MAX_SIZE];
void randomNumberGenerator()
{
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++)
    {
        randomNumbers[i] = rand() % 1000 + 1;
    }
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
        if (yeniYemekSiparis < 1 || yeniYemekSiparis > arrayBoyut || yeniYemekSiparis == 3 || yeniYemekSiparis == 6)
        {
            printf("%d numarali menu yoktur.\n", yeniYemekSiparis);
            printf("Gecerli bir menu seciniz:\n");
        }
    } while (yeniYemekSiparis < 1 || yeniYemekSiparis > arrayBoyut || yeniYemekSiparis == 3 || yeniYemekSiparis == 6);

    FILE *yeniSiparisEklemeTXT = fopen("MevcutSiparisler.txt", "a");
    if (yeniSiparisEklemeTXT == NULL)
    {
        printf("Dosya bulunamadi!");
        return;
    }

    int i = yeniYemekSiparis;
    fprintf(yeniSiparisEklemeTXT, "ID numarasi:%d\n", randomNumbers[i - 1]);
    fprintf(yeniSiparisEklemeTXT, "-%s\n", arrayYemek[i - 1]);
    fprintf(yeniSiparisEklemeTXT, "-Fiyati %d TL\n", arrayYemekFiyat[i - 1]);
    fprintf(yeniSiparisEklemeTXT, "-Hazirlanma suresi %d dakika\n", arrayYemekSure[i - 1]);
    fprintf(yeniSiparisEklemeTXT, "\n");
    printf("%d siparisi eklendi\n", yeniYemekSiparis);
    printf("\n");
    fclose(yeniSiparisEklemeTXT);
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
    for (int i = 0; i < MAX_SIZE; i++)
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
        scanf("%[^\n] ", yeniYeniMevcut);
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
        return;
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
        return;
    }

    while ((karakter = fgetc(yemekListesi)) != EOF)
    {
        if (karakter == '\n')
        {
            satirSayisi++;
        }
    }

    int yemekSatirSayisi = satirSayisi / 5 + 1;

    fprintf(YemekListesi, "\n%d-%s\n-%d TL\n-Hazirlanma suresi %d dakikadir\n-%s\n", yemekSatirSayisi, yemekIsmi, yemekFiyat, yemekSure, yemekMevcut);

    free(arrayYemek);
    free(yemekArrayFiyat);
    free(yemekBoyutSure);

    fclose(YemekListesi);
    yemekListesiGoster();
}

void yemekSilme()
{
    int silinecekIndex;
    printf("Silmek istediginiz menuyu secin: ");
    scanf("%d", &silinecekIndex);

    menuSil(silinecekIndex - 1);

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
    arrayBoyut--;
    for (int i = index; i < arrayBoyut; i++)
    {
        arrayYemek[i] = arrayYemek[i + 1];
        arrayYemekFiyat[i] = arrayYemekFiyat[i + 1];
        arrayYemekSure[i] = arrayYemekSure[i + 1];
        arrayYemekMevcudiyet[i] = arrayYemekMevcudiyet[i + 1];
    }
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
                printf("Siparis onaylandi.\n");
                printf("\n");
                siparisHazirlama();

                break;
            }
            else if (onayRed == 2)
            {
                printf("ID dogru!\n");
                printf("Siparis reddedildi.\nSiparis listeden silindi!\n");

                // Mevcut siparislerden reddedilen siparisi sil
                FILE *mevcutSiparisler = fopen("MevcutSiparisler.txt", "r");
                FILE *geciciDosya = fopen("GeciciMevcutSiparisler.txt", "w");
                char satir[500];
                int skip = 0;

                if (mevcutSiparisler == NULL || geciciDosya == NULL)
                {
                    printf("Dosya bulunamadi!\n");
                    return;
                }

                while (fgets(satir, sizeof(satir), mevcutSiparisler) != NULL)
                {
                    // Reddedilen siparisi atla
                    if (strstr(satir, "ID numarasi:") && atoi(&satir[strlen("ID numarasi:")]) == randomNumbers[i])
                    {
                        skip = 5; // ID ve 4 satiri atla (ID, yemek, fiyat, sure ve bos satir)
                    }
                    if (skip > 0)
                    {
                        skip--;
                        continue;
                    }
                    fputs(satir, geciciDosya);
                }

                fclose(mevcutSiparisler);
                fclose(geciciDosya);

                // Orijinal dosyayi sil ve gecici dosyayi yeniden adlandir
                remove("MevcutSiparisler.txt");
                rename("GeciciMevcutSiparisler.txt", "MevcutSiparisler.txt");

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
void mevcutSiparislerdenMenuSilme()
{

    int oncekiSiparisBuyukluk = sizeof(randomNumbers) / sizeof(randomNumbers[0]);
    for (int i = 0; i < oncekiSiparisBuyukluk; i++)
    {
        FILE *mevcutSiparisler = fopen("MevcutSiparisler.txt", "r");
        FILE *geciciDosya = fopen("GeciciMevcutSiparisler.txt", "w");
        char satir[500];
        int skip = 0;

        if (mevcutSiparisler == NULL || geciciDosya == NULL)
        {
            printf("Dosya bulunamadi!\n");
            return;
        }

        while (fgets(satir, sizeof(satir), mevcutSiparisler) != NULL)
        {
            // Reddedilen siparisi atla
            if (strstr(satir, "ID numarasi:") && atoi(&satir[strlen("ID numarasi:")]) == randomNumbers[i])
            {
                skip = 5; // ID ve 4 satiri atla (ID, yemek, fiyat, sure ve bos satir)
            }
            if (skip > 0)
            {
                skip--;
                continue;
            }
            fputs(satir, geciciDosya);
        }

        fclose(mevcutSiparisler);
        fclose(geciciDosya);

        // Orijinal dosyayi sil ve gecici dosyayi yeniden adlandir
        remove("MevcutSiparisler.txt");
        rename("GeciciMevcutSiparisler.txt", "MevcutSiparisler.txt");
    }
}

void siparisHazirlama(int *totalYemekFiyat)
{
    FILE *onaylananSiparisler = fopen("onaylananSiparisler.txt", "r");
    char karakter[500];

    if (onaylananSiparisler == NULL)
    {
        printf("Dosya Bulunamadi!\n");
        return;
    }

    while (fgets(karakter, sizeof(karakter), onaylananSiparisler) != NULL)
    {
        printf("%s", karakter);
    }

    int hazirlanacakSiparis;
    printf("Hazirlanacak Siparisi ID Seciniz: ");
    scanf("%d", &hazirlanacakSiparis);

    int IDBulundu = 0;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (hazirlanacakSiparis == randomNumbers[i])
        {
            printf("ID Dogru!\n");
            mevcutSiparislerdenMenuSilme();
            FILE *hazirlananSiparisler = fopen("hazirlananSiparisler.txt", "a");
            if (hazirlananSiparisler == NULL)
            {
                printf("Dosya Bulunamadi!\n");
                return;
            }
            fprintf(hazirlananSiparisler, "ID numarasi:%d\n", randomNumbers[i]);
            fprintf(hazirlananSiparisler, "-%s\n", arrayYemek[i]);
            fprintf(hazirlananSiparisler, "-Fiyati %d TL\n", arrayYemekFiyat[i]);
            fprintf(hazirlananSiparisler, "-Hazirlanma suresi %d dakika\n", arrayYemekSure[i]);
            fprintf(hazirlananSiparisler, "\n");
            fclose(hazirlananSiparisler);
            printf("Siparisiniz hazirlaniyor...\n");

            int aktifAsci = 3; // Örnek aşçı sayısı
            sleep(3);
            hazirlanmisSiparisler();
            printf("Siparisiniz Yola cikti!\n");
            sleep(3);

            int siparisOnayKod = 1234;
            int siparisOnayMusteriKod;

            do
            {
                printf("Siparis Teslim Kodunuzu Girin: ");
                scanf("%d", &siparisOnayMusteriKod);

                if (siparisOnayKod == siparisOnayMusteriKod)
                {
                    printf("Siparisiniz Teslim Edildi\n");

                    FILE *oncekiSiparisler = fopen("OncekiSiparisler.txt", "a");
                    if (oncekiSiparisler == NULL)
                    {
                        printf("Dosya Bulunamadi!\n");
                        return;
                    }

                    fprintf(oncekiSiparisler, "%d-", i + 1);
                    fprintf(oncekiSiparisler, "%s\n", arrayYemek[i]);
                    fprintf(oncekiSiparisler, "-Fiyati %d TL\n", arrayYemekFiyat[i]);
                    fprintf(oncekiSiparisler, "\n");
                    fclose(oncekiSiparisler);
                }
                else
                {
                    printf("Teslim Kodunuz Yanlis! Tekrar Deneyin!\n");
                }
            } while (siparisOnayKod != siparisOnayMusteriKod);

            FILE *onaylananSiparisler = fopen("onaylananSiparisler.txt", "r");
            FILE *geciciDosya = fopen("geciciDosya.txt", "w");

            char satir[500];
            int skip = 0;

            if (onaylananSiparisler == NULL || geciciDosya == NULL)
            {
                printf("Dosya Bulunamadi!\n");
                if (onaylananSiparisler != NULL)
                    fclose(onaylananSiparisler);
                if (geciciDosya != NULL)
                    fclose(geciciDosya);
                return;
            }

            while (fgets(satir, sizeof(satir), onaylananSiparisler) != NULL)
            {
                char *ptr = strstr(satir, "ID numarasi: ");
                if (ptr != NULL && atoi(ptr + strlen("ID numarasi: ")) == randomNumbers[i])
                {
                    skip = 5; // ID ve 4 satiri atla (ID, yemek, fiyat, sure ve bos satir)
                }
                if (skip > 0)
                {
                    skip--;
                    continue;
                }
                fputs(satir, geciciDosya);
            }

            fclose(onaylananSiparisler);
            fclose(geciciDosya);
            remove("onaylananSiparisler.txt");
            rename("geciciDosya.txt", "onaylananSiparisler.txt");
        }
    }
}

void hazirlanmisSiparisler()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        FILE *hazirlananSiparisler = fopen("hazirlananSiparisler.txt", "r");
        FILE *geciciHazirlananSiparisler = fopen("GecicihazirlananSiparisler.txt", "w");
        char satir[500];
        int skip = 0;

        if (hazirlananSiparisler == NULL || geciciHazirlananSiparisler == NULL)
        {
            printf("Dosya bulunamadi!\n");
            return;
        }

        while (fgets(satir, sizeof(satir), hazirlananSiparisler) != NULL)
        {
            // Reddedilen siparisi atla
            if (strstr(satir, "ID numarasi:") && atoi(&satir[strlen("ID numarasi:")]) == randomNumbers[i])
            {
                skip = 5; // ID ve 4 satiri atla (ID, yemek, fiyat, sure ve bos satir)
            }
            if (skip > 0)
            {
                skip--;
                continue;
            }
            fputs(satir, geciciHazirlananSiparisler);
        }

        fclose(hazirlananSiparisler);
        fclose(geciciHazirlananSiparisler);

        // Orijinal dosyayi sil ve gecici dosyayi yeniden adlandir
        remove("hazirlananSiparisler.txt");
        rename("GecicihazirlananSiparisler.txt", "hazirlananSiparisler.txt");
    }
}

void yemekSecimIslemleri()
{
    int islemSecim;

    printf("1-Yemek ekleme-guncelleme-silme \n");
    printf("2-Yeni siparis onay/red \n");
    printf("3-Analizler \n");
    // ANALİZ İÇERİSİNDE FOR İLE HER GÜNE AİT BİLGİLERİ *1.GÜN *2.GÜN ŞEKLİNDE TİME İLE BELİRTİLECEK.
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
    case 3:
        analizIslemleri(totalYemekFiyat, &size);
        break;
    }
}
void analizIslemleri(int *totalYemekFiyat, int *size)
{
    FILE *siparisler = fopen("OncekiSiparisler.txt", "r");
    char satir[MAX_LINE_LENGTH];
    int index = -1;
    int total = 0;

    if (siparisler == NULL)
    {
        printf("Dosya Bulunamadi!");
        return;
    }

    while (fgets(satir, sizeof(satir), siparisler))
    {
        satir[strcspn(satir, "\n")] = '\0';

        if (strstr(satir, "-Fiyati") != NULL)
        {
            sscanf(satir, "-Fiyati %d TL", &totalYemekFiyat[index]);
            total += totalYemekFiyat[index];
            index++;
        }
    }

    fclose(siparisler);

    *size = index;

    printf("Gunluk Toplam Ciro: %d TL", total);
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

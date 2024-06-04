
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define MAX_TIKET 255

void inisialisasiKursi(int (*kursi)[10], int *e)
{
    for (int c = 0; c < 6; c++)
    {
        for (int d = 0; d < 10; d++)
        {
            kursi[c][d] = *e;
            (*e)++;
        }
    }
}
void inisialisasiKursi2(int (*kursi2)[10], int *f1)
{
    for (int c = 0; c < 6; c++)
    {
        for (int d = 0; d < 10; d++)
        {
            kursi2[c][d] = *f1;
            (*f1)++;
        }
    }
}
void inisialisasiKursi3(int (*kursi3)[10], int *g1)
{
    for (int c = 0; c < 6; c++)
    {
        for (int d = 0; d < 10; d++)
        {
            kursi3[c][d] = *g1;
            (*g1)++;
        }
    }
}
void inisialisasiKursi4(int (*kursi4)[10], int *h1)
{
    for (int c = 0; c < 6; c++)
    {
        for (int d = 0; d < 10; d++)
        {
            kursi4[c][d] = *h1;
            (*h1)++;
        }
    }
}

int main(int argc, char const *argv[])
{
    /*deklarasi backup*/
    int backupcode[255], backupcodelogin, backupcodeaktivasi;
    /*deklarasi Histori Film*/
    int histori = 1, history_code[255];
    char history_film[255][255], history_jam[255][255], hist;
    /*Login,aktivasi , dan register*/
    int i, aktivasicek, passcek, percobaan = 1, pilih_film, menu_awal, menu_login, menu_register;
    char aktivasi[255][255], usernameaktivasi[255][255], passwordaktivasi[255][255];
    char username[255][255], password[255][255], usernamelogin[255][255], passwordlogin[255][255], usernamebackup[255][255], passwordbackup[255][255];
    /*deklarasi Pemesanan FILM*/
    int pilihmenu1, pilihfilm, kursifilm[6][10], kursifilm2[6][10], kursifilm3[6][10], kursifilm4[6][10], jumlah_kursi_film1, pilih_kursi, kode_film, c, d, e = 1, z, f = 1, f1 = 1, g1 = 1, h1 = 1;
    int pembayaran, total_pembayaran, pilih_setelah_bayar;
    int nomor_kursi[255], histori_nomor[255];
    char nama_film[255][255] = {"The Garfield Movie", "Do You See What I See", "Vina", "Haikyuu!! The Dumpster Battle"};
    char jam_film[255][255] = {"(17:00 - 19:00)", "(19:30-21:00)", "(10:00-12:00)", "(21:30-23:00)"};
    /*Deklarasi Pembayaran*/
    char gopay[12] = "";
    char dana[12] = "";
    char ovo[12] = "";
    int pin1, pin3, pin4, pin5, pin6;
    int nmr;
    int cekpin = 0, cekpin1 = 0, cekpin2 = 0;
    int pin2;

    printf(ANSI_COLOR_GREEN "  _______ _____  _____    _____ _____ _   _ ______ __  __          \n");
    printf(ANSI_COLOR_GREEN " |__   __|  __ \\|_   _|  / ____|_   _| \\ | |  ____|  \\/  |   /\\    \n");
    printf(ANSI_COLOR_GREEN "    | |  | |__) | | |   | |      | | |  \\| | |__  | \\  / |  /  \\   \n");
    printf(ANSI_COLOR_GREEN "    | |  |  _  /  | |   | |      | | | . ` |  __| | |\\/| | / /\\ \\  \n");
    printf(ANSI_COLOR_GREEN "    | |  | | \\ \\ _| |_  | |____ _| |_| |\\  | |____| |  | |/ ____ \\ \n");
    printf(ANSI_COLOR_GREEN "    |_|  |_|  \\_\\_____|  \\_____|_____|_| \\_|______|_|  |_/_/    \\_\\ \n");
    printf(ANSI_COLOR_GREEN "                                                                    \n");

    printf(ANSI_COLOR_RESET " ");

    inisialisasiKursi(kursifilm, &e);
    inisialisasiKursi2(kursifilm2, &f1);
    inisialisasiKursi3(kursifilm3, &g1);
    inisialisasiKursi4(kursifilm4, &h1);

menu_awal:
    printf("\n--- SILAHKAN LOGIN/REGISTER TERLEBIH DAHULU ---");
    printf("\n 1. Login ");
    printf("\n 2. Register");
    printf("\n 3. Aktivasi Akun ");
    printf("\n 4. Exit ");
    printf("\n\n Pilih :");
    scanf("%d", &menu_awal);
    switch (menu_awal)
    {
    case 1:
        goto login;
        break;
    case 2:
        goto register1;
        break;
    case 3:
        goto aktivasi;
        break;
    case 4:
        goto exit;
        break;

    default:

        break;
    }

    if (menu_awal == 1 || menu_awal == 2 || menu_awal == 3 || menu_awal == 4)
    {
    }
    else
    {
        printf("\nTolong Pilih Antara 1-4");
        goto menu_awal;
    }

/*Halaman Login*/
login:
    printf("\n------ LOGIN ------\n");
    printf("\n Username : ");
    scanf("%s", usernamelogin[1]);

    for (i = 1; i < 255; i++)
    {

        if (strcmp(username[i], usernamelogin[1]) == 0)
        {
            break;
        }
        else
        {
            printf("Username Tidak Terdaftar \n");
            goto menu_awal;
        }
    }

    for (passcek = 0; passcek < 255; passcek++)
    {
        printf("\n Password : ");
        scanf("%s", passwordlogin[1]);
        if (strcmp(password[i], passwordlogin[1]) == 0)
        {
            printf("\n--- Login Berhasil --- \n");
            goto menu1;
        }
        else
        {
            if (percobaan > 3)
            {
                break;
            }

            printf("\nPassword Salah, percobaan (%d/3)\n", percobaan);
            percobaan++;
        }
    }

    printf("\nAKUN ANDA TERBLOKIR");
    printf("\nMasukkan Code Backup : ");
    scanf("%d", &backupcodelogin);

    if (backupcode[i] != backupcodelogin)
    {
        strcpy(usernamebackup[i], username[i]);
        strcpy(passwordbackup[i], password[i]);
        username[i][0] = '\0';
        password[i][0] = '\0';
        printf("\nBackup Code Salah , Akun Dinonaktifkan, Silahkan melakukan aktivasi kembali \n");
        getchar();
        goto menu_awal;
    }
    else
    {
        goto menu1;
    }

/*Halaman Register*/
register1:
    printf("\n--------- REGISTER ---------\n");
    printf("\n Username : ");
    scanf("%s", username[1]);
    printf("\n Password : ");
    scanf("%s", password[1]);
    printf("\n--- Registrasi Berhasil ---\n");

    srand(time(NULL));

    backupcode[1] = rand() % 9000 + 1000;
    ;

    printf("\nCode backup akun anda : %d", backupcode[1]);
    printf("\n(code backup digunakan jika akun terblokir)\n");

    goto menu_awal;

/*Halaman Aktivasi*/
aktivasi:
    printf("\n--------- aktivasi ---------\n");

    printf("\nMasukkan Code Backup : ");
    scanf("%d", &backupcodeaktivasi);

    if (backupcode[i] == backupcodeaktivasi)
    {
        strcpy(username[i], usernamebackup[i]);
        strcpy(password[i], passwordbackup[i]);
        usernamebackup[i][0] = '\0';
        passwordbackup[i][0] = '\0';
        printf("Username anda adalah : %s", username[i]);
        printf("\nPassword anda adalah :%s", password[i]);
        printf("\nBackup Berhasil, Akun diaktifkan kembali\n");
        getchar();
        goto menu_awal;
    }
    else
    {
        printf("\n Backup code salah , aktivasi gagal\n");
        goto menu_awal;
    }

    /*Menu 1*/

menu1:

    printf("\n\nWelcome Back, ");
    printf(ANSI_COLOR_YELLOW "%s \n", username[i]);
    printf(ANSI_COLOR_RESET " ");
    printf("\n----- Menu -----");
    printf("\n 1. Nonton Film ");
    printf("\n 2. Cek Tiket ");
    printf("\n 3. Profil \n");
    printf("\nPilih :");
    scanf("%d", &pilihmenu1);

    if (pilihmenu1 == 1 || pilihmenu1 == 2 || pilihmenu1 == 3)
    {
    }
    else
    {
        printf("\nTolong Pilih Antara 1-3");
        goto menu1;
    }

    switch (pilihmenu1)
    {
    case 1:
        goto film;
        break;
    case 2:
        goto tiket;
        break;
    case 3:
        goto profil;
        break;

    default:
        break;
    }

film:
    printf("-------------------- TRI CINEMA --------------------");
    printf("\n|-------------------- SHOWING --------------------|");
    printf("\n 1. The Garfield Movie (17:00 - 19:00)");
    printf("\n 2. Do You See What I See (19:30-21:00)");
    printf("\n 3. Vina (10:00-12:00)");
    printf("\n 4. Haikyuu!! The Dumpster Battle (21:30-23:00)");
    printf("\n----------------------------------------------------\n");
    printf("\n 5. Kembali ke Home");
    printf("\nPilih : ");
    scanf("%d", &pilih_film);
    if (pilih_film == 1 || pilih_film == 2 || pilih_film == 3 || pilih_film == 4 || pilih_film == 5)
    {
    }
    else
    {
        printf("\nTolong Pilih Antara 1-5\n");
        goto film;
    }
    kode_film = pilih_film - 1;

    switch (pilih_film)
    {
    case 1:

        goto film1;
        break;
    case 2:
        goto film2;
        break;
    case 3:
        goto film3;
        break;
    case 4:
        goto film4;
        break;
    case 5:
        goto menu1;
        break;

    default:
        break;
    }

film1:
    printf("\nPilih Tempat Duduk :\n");
    printf(ANSI_COLOR_YELLOW "------------------- Layar ---------------------\n\n");
    printf(ANSI_COLOR_RESET "");
    for (c = 0; c <= 5; c++)
    {
        printf("\n\t");
        for (d = 0; d <= 9; d++)
        {
            if (kursifilm[c][d] == 0)
            {
                printf(ANSI_COLOR_RED "%02d ", kursifilm[c][d]);
            }
            else
            {
                printf(ANSI_COLOR_CYAN "%02d ", kursifilm[c][d]);
            }
        }
    }
    printf(ANSI_COLOR_RESET "");
    printf(ANSI_COLOR_YELLOW "\n-----------------------------------------------\n");
    printf(ANSI_COLOR_RESET "");
    printf("\nBerapa Kursi : ");
    scanf("%d", &jumlah_kursi_film1);
    for (c = 1; c <= jumlah_kursi_film1; c++)
    {

        int kursi_penuh = 1;
        while (kursi_penuh)
        {
            printf("Nomor Kursi-%d : ", c);
            scanf("%d", &pilih_kursi);
            for (d = 0; d <= 5; d++)
            {
                for (e = 0; e <= 9; e++)
                {
                    if (kursifilm[d][e] == pilih_kursi)
                    {
                        nomor_kursi[f] = pilih_kursi;
                        kursifilm[d][e] = 00;
                        kursi_penuh = 0;
                        f++;
                    }
                }
            }
        }
    }
    goto bayar;

film2:
    printf("\nPilih Tempat Duduk :\n");
    printf(ANSI_COLOR_YELLOW "------------------- Layar ---------------------\n\n");
    printf(ANSI_COLOR_RESET "");
    for (c = 0; c <= 5; c++)
    {
        printf("\n\t");
        for (d = 0; d <= 9; d++)
        {
            if (kursifilm2[c][d] == 0)
            {
                printf(ANSI_COLOR_RED "%02d ", kursifilm2[c][d]);
            }
            else
            {
                printf(ANSI_COLOR_CYAN "%02d ", kursifilm2[c][d]);
            }
        }
    }
    printf(ANSI_COLOR_RESET "");
    printf(ANSI_COLOR_YELLOW "\n-----------------------------------------------\n");
    printf(ANSI_COLOR_RESET "");
    printf("\nBerapa Kursi : ");
    scanf("%d", &jumlah_kursi_film1);
    for (c = 1; c <= jumlah_kursi_film1; c++)
    {

        int kursi_penuh = 1;
        while (kursi_penuh)
        {
            printf("Nomor Kursi-%d : ", c);
            scanf("%d", &pilih_kursi);
            for (d = 0; d <= 5; d++)
            {
                for (e = 0; e <= 9; e++)
                {
                    if (kursifilm2[d][e] == pilih_kursi)
                    {
                        nomor_kursi[f] = pilih_kursi;
                        kursifilm2[d][e] = 00;
                        kursi_penuh = 0;
                        f++;
                    }
                }
            }
        }
    }
    goto bayar;
film3:

    printf("\nPilih Tempat Duduk :\n");
    printf(ANSI_COLOR_YELLOW "------------------- Layar ---------------------\n\n");
    printf(ANSI_COLOR_RESET "");
    for (c = 0; c <= 5; c++)
    {
        printf("\n\t");
        for (d = 0; d <= 9; d++)
        {
            if (kursifilm3[c][d] == 0)
            {
                printf(ANSI_COLOR_RED "%02d ", kursifilm3[c][d]);
            }
            else
            {
                printf(ANSI_COLOR_CYAN "%02d ", kursifilm3[c][d]);
            }
        }
    }
    printf(ANSI_COLOR_RESET "");
    printf(ANSI_COLOR_YELLOW "\n-----------------------------------------------\n");
    printf(ANSI_COLOR_RESET "");
    printf("\nBerapa Kursi : ");
    scanf("%d", &jumlah_kursi_film1);
    for (c = 1; c <= jumlah_kursi_film1; c++)
    {

        int kursi_penuh = 1;
        while (kursi_penuh)
        {
            printf("Nomor Kursi-%d : ", c);
            scanf("%d", &pilih_kursi);
            for (d = 0; d <= 5; d++)
            {
                for (e = 0; e <= 9; e++)
                {
                    if (kursifilm3[d][e] == pilih_kursi)
                    {
                        nomor_kursi[f] = pilih_kursi;
                        kursifilm3[d][e] = 00;
                        kursi_penuh = 0;
                        f++;
                    }
                }
            }
        }
    }
    goto bayar;
film4:
    printf("\nPilih Tempat Duduk :\n");
    printf(ANSI_COLOR_YELLOW "------------------- Layar ---------------------\n\n");
    printf(ANSI_COLOR_RESET "");
    for (c = 0; c <= 5; c++)
    {
        printf("\n\t");
        for (d = 0; d <= 9; d++)
        {
            if (kursifilm4[c][d] == 0)
            {
                printf(ANSI_COLOR_RED "%02d ", kursifilm4[c][d]);
            }
            else
            {
                printf(ANSI_COLOR_CYAN "%02d ", kursifilm4[c][d]);
            }
        }
    }
    printf(ANSI_COLOR_RESET "");
    printf(ANSI_COLOR_YELLOW "\n-----------------------------------------------\n");
    printf(ANSI_COLOR_RESET "");
    printf("\nBerapa Kursi : ");
    scanf("%d", &jumlah_kursi_film1);
    for (c = 1; c <= jumlah_kursi_film1; c++)
    {

        int kursi_penuh = 1;
        while (kursi_penuh)
        {
            printf("Nomor Kursi-%d : ", c);
            scanf("%d", &pilih_kursi);
            for (d = 0; d <= 5; d++)
            {
                for (e = 0; e <= 9; e++)
                {
                    if (kursifilm4[d][e] == pilih_kursi)
                    {
                        nomor_kursi[f] = pilih_kursi;
                        kursifilm4[d][e] = 00;
                        kursi_penuh = 0;
                        f++;
                    }
                }
            }
        }
    }
bayar:
    printf("\n---------- Pembayaran ----------\n");
    printf("Nama Film \t\t Jumlah\t Harga");
    printf("\n %s \t %d \t %d", nama_film[kode_film], jumlah_kursi_film1, (jumlah_kursi_film1 * 35000));
    printf("\n\nPilih Metode Pemabayaran :");
    printf("\n 1. Gopay ");
    printf("\n 2. Dana ");
    printf("\n 3. OVO ");
    printf("\nPilih :");
    scanf("%d", &pembayaran);
    if (pembayaran == 1 || pembayaran == 2 || pembayaran == 3)
    {
    }
    else
    {
        printf("\n------------PEMBAYARAN GAGAL, COBA LAGI------------\n\n");
        goto bayar;
    }

    switch (pembayaran)
    {
    case 1:
        if (cekpin == 0)
        {
            printf("----Akun anda belum terhubung----\n");
            printf("\nMasukkan Nomor Telepon Gopay (08xxxx):");
            scanf("%s", gopay);
            printf("Masukkan Pin Gopay :");
            scanf("%d", &pin1);
            cekpin = pin1;
            goto pembayaran_berhasil;
        }
        else
        pingopay:
            printf("\nMasukkan pin GoPay anda :");
        scanf("%d", &pin2);
        if (cekpin != pin2)
        {
            printf("\n\nPin anda salah");
            goto pingopay;
        }
        else
            goto pembayaran_berhasil;

        break;
    case 2:
        if (cekpin1 == 0)
        {
            printf("----Akun anda belum terhubung----\n");
            printf("\nMasukkan Nomor Telepon DANA (08xxxx):");
            scanf("%s", dana);
            printf("Masukkan Pin DANA :");
            scanf("%d", &pin3);
            cekpin1 = pin3;
            goto pembayaran_berhasil;
        }
        else
        pindana:
            printf("\nMasukkan pin DANA anda :");
        scanf("%d", &pin4);
        if (cekpin1 != pin4)
        {
            printf("\n\nPin anda salah");
            goto pindana;
        }
        else
            goto pembayaran_berhasil;

        break;

    case 3:
        if (cekpin2 == 0)
        {
            printf("----Akun anda belum terhubung----\n");
            printf("\nMasukkan Nomor Telepon OVO (08xxxx):");
            scanf("%s", dana);
            printf("Masukkan Pin OVO :");
            scanf("%d", &pin5);
            cekpin2 = pin4;
            goto pembayaran_berhasil;
        }
        else
        pinovo:
            printf("\nMasukkan pin OVO anda :");
        scanf("%d", &pin5);
        if (cekpin1 != pin6)
        {
            printf("\n\nPin anda salah");
            goto pinovo;
        }
        else
            goto pembayaran_berhasil;

        break;
    default:
        break;
    }

pembayaran_berhasil:
    printf("Verifikasi Pembayaran");

    for (i = 0; i < 3; i++)
    {
        fflush(stdout);
        sleep(1);
        printf(".");
    }

    printf("\nPembayaran Berhasil\n");

    printf("\n-------------- RECEIPT ---------------\n");
    printf("\n Nama Film \t: %s", nama_film[kode_film]);
    printf("\n Jumlah Tiket \t: %d", jumlah_kursi_film1);
    printf("\n Total Pembayaran : 35000 x %d = %d", jumlah_kursi_film1, jumlah_kursi_film1 * 35000);
    printf("\n------------------------------------------\n");
    printf("\nTiket : ");
    srand(time(NULL));

    for (c = 1; c <= jumlah_kursi_film1; c++)
    {

        int random_number = rand() % 90000 + 10000;
        printf("\n\n------------------ TICKET ------------------\n");
        printf("\nKode Tiket : %d\n", random_number);
        history_code[histori] = random_number;
        printf("\nNomor Kursi : %d\n", nomor_kursi[histori]);
        histori_nomor[histori] = nomor_kursi[histori];
        printf("\nNama Film : %s\n", nama_film[kode_film]);
        strcpy(history_film[histori], nama_film[kode_film]);
        printf("\nJam Tayang : %s\n", jam_film[kode_film]);
        strcpy(history_jam[histori], jam_film[kode_film]);
        histori++;

        printf("\nNB: Tiket Hanya Berlaku 1 Hari Setelah Pemesanan");
        printf("\n---------------------------------------------\n");
    }

    printf("\n\n 1. Kembali HOME");
    printf("\n 2. Selesai");
    printf("\n\nPilih :");
    scanf("%d", &pilih_setelah_bayar);

    switch (pilih_setelah_bayar)
    {
    case 1:
        goto menu1;
        break;
    case 2:
        goto exit;
        break;

    default:
        break;
    }

tiket:
    printf("\n--------------- Daftar Ticket --------------- \n");

    for (z = 1; z < histori; z++)
    {
        printf("\n\n------------------ TICKET ------------------\n");

        printf("\nKode Tiket : %d\n", history_code[z]);
        printf("\nNomor Kursi : %d\n", nomor_kursi[z]);
        printf("\nNama Film : %s\n", history_film[z]);
        printf("\nJam Tayang : %s\n", history_jam[z]);
        printf("\nNB: Tiket Hanya Berlaku 1 Hari Setelah Pemesanan");
        printf("\n---------------------------------------------\n");
    }

    printf("\n\n\n 1. Nonton Film ");
    printf("\n 2. Profil ");
    printf("\nPilih :");
    scanf("%d", &pilihmenu1);

    if (pilihmenu1 == 1 || pilihmenu1 == 2)
    {
    }
    else
    {
        printf("\nTolong Pilih Antara 1 dan 2");
        goto menu1;
    }
    switch (pilihmenu1)
    {
    case 1:
        goto film;
        break;
    case 2:
        goto profil;
        break;

    default:
        break;
    }

profil:
    printf("\n");
    printf("\n");
    printf("\n");

    printf("--------------------PROFIL--------------------");
    printf("\nAkun : %s\n", username[1]);
    if (strlen(gopay) != 0)
    {
        printf("+------------------------------------------+");
        printf("\n|GoPay    --> %s                       \n", gopay);
        printf("+------------------------------------------+\n\n");
    }
    else
    {
        printf("+----------------------------------------+");
        printf("\n|Gopay    --> Akun GoPay belum terhubung |\n");
        printf("+----------------------------------------+\n\n");
    }

    if (strlen(dana) != 0)
    {
        printf("+------------------------------------------+");
        printf("\n|DANA     --> %s                       \n", dana);
        printf("+------------------------------------------+\n\n");
    }
    else
    {
        printf("+--------------------------------------+");
        printf("\n|DANA     --> Akun DANA belum terhubung|\n");
        printf("+--------------------------------------+\n\n");
    }

    if (strlen(ovo) != 0)
    {
        printf("+----------------------------------------+");
        printf("\n|OVO      --> %s                       \n", ovo);
        printf("+----------------------------------------+");
    }
    else
    {
        printf("+----------------------------------------+");
        printf("\n|OVO      --> Akun OVO belum terhubung   |\n");
        printf("+----------------------------------------+\n");
    }
    printf("\n---------------------------------------------");
    printf("\n\n\n 1. Nonton Film ");
    printf("\n 2. Cek Tiket ");
    printf("\nPilih :");
    scanf("%d", &pilihmenu1);

    if (pilihmenu1 == 1 || pilihmenu1 == 2)
    {
    }
    else
    {
        printf("\nTolong Pilih Antara 1 dan 2");
        goto menu1;
    }
    switch (pilihmenu1)
    {
    case 1:
        goto film;
        break;
    case 2:
        goto tiket;
        break;

    default:
        break;
    }

exit:
    return 0;
}
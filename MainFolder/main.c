#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Universal Function
int getSaldo(int ID)
{
    int finded = 0;
    FILE *fptr = fopen("account.csv", "r");

    if (fptr == NULL)
    {
        printf("|+|Error, File account.csv tidak ditemukan|+|\n");
        exit(1);
    }

    char buffer[200];

    int read_id;
    int saldo;
    char password[100];
    //mencari saldo berdasarkan id
    while ((fscanf(fptr,"%d, %d, %s", &read_id, &saldo, &password)) != -1)
    {
        if (ID == read_id){
            finded = 1;
            break;
        }
    }
    fclose(fptr);
    if(finded == 1)
        return saldo;
    else
        return -1;
}
int TampilkanDaftarAkun(int ID, int nama, int saldo){
    system("cls");
    FILE * fpointer, *fp;
    fpointer = fopen("account.csv", "r");

    char dumpCsv[100];
    char dumpTxt[100];
    char fileNameTXT[15];
    char IdLog[15];
    char saldoLog[100];
    char *token;
    int cek = 0;
    while (fgets(dumpCsv, sizeof(dumpCsv), fpointer)){
        cek++;
    }
    if(cek == 1){
        printf("|+|Maaf,Tidak ada akun yang terdaftar|+|\n");
        return 1;
    }
    fclose(fpointer);
    fpointer = fopen("account.csv", "r");
    fgets(dumpCsv, sizeof(dumpCsv), fpointer);
    while (fgets(dumpCsv, sizeof(dumpCsv), fpointer)){
        token = strtok(dumpCsv, ",");
        strcpy(IdLog, token);
        token = strtok(NULL, ",");
        strcpy(saldoLog, token);

        if (ID == 1){
            printf("  |*|ID: %s\n", IdLog);
        }

        strcpy(fileNameTXT,IdLog);
        strcat(fileNameTXT, ".txt");
        fp = fopen(fileNameTXT, "r");
        fscanf(fp, "%[^\n]", dumpTxt);
        if (nama == 1){
            printf("  %s\n", strtok(dumpTxt, " "));
        }

        if (saldo == 1){
            printf("  |*|Saldo: %s\n", saldoLog);
        }
        printf("\n");
    }
    fclose(fp);
    fclose(fpointer);
    printf("-----------------------------\n");
    return 0;
}
int setorTunai(int ID, int Nominal, int mode){ // PAKAI INI UNTUK SETOR TUNAI
    //mode : 0 = setor tunai, 1 = transfer masuk
    system("cls");
    int nominalDump;
    char fileTXT[15];

    itoa(ID, fileTXT, 10);
    strcat(fileTXT, ".txt");

    FILE *fpointer, *fp;
    fpointer = fopen("account.csv", "r");
    fp = fopen("temp.csv", "w");

    char dump[100], dump2[100], charNominal[100];
    char *token;
    fgets(dump, sizeof(dump), fpointer);
    fprintf(fp, dump);
    while (fgets(dump, sizeof(dump), fpointer)){
        strcpy(dump2, dump);
        token = strtok(dump, ",");
        if (atoi(token) == ID){
            fprintf(fp, token);
            fprintf(fp, ",");
            token = strtok(NULL, ",");
            nominalDump = atoi(token);
            nominalDump = nominalDump + Nominal;
            itoa(nominalDump, charNominal, 10);
            fprintf(fp, charNominal);
            fprintf(fp, ",");
            token = strtok(NULL, ",");
            fprintf(fp, token);
        }else{
            fprintf(fp, dump2);
        }
    }
    fclose(fp);
    fclose(fpointer);

    fpointer = fopen("temp.csv", "r");
    fp = fopen("account.csv", "w");

    while (fgets(dump, sizeof(dump), fpointer)){
        fprintf(fp, dump);
    }

    fclose(fp);
    fclose(fpointer);
    remove("temp.csv");

    char tgl[20], waktu[20];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char Bulan[10],Hari[10],Jam[10],Menit[10],Detik[10];
    itoa(tm.tm_year + 1900, tgl,10); strcat(tgl, "/");
    itoa(tm.tm_mon + 1, Bulan, 10);
    itoa(tm.tm_mday, Hari, 10);
    strcat(tgl,Bulan); strcat(tgl, "/");
    strcat(tgl,Hari);

    itoa(tm.tm_hour, waktu, 10); strcat(waktu, ":");
    itoa(tm.tm_min, Menit, 10);
    itoa(tm.tm_sec, Detik, 10);
    strcat(waktu,Menit); strcat(waktu, ":");
    strcat(waktu,Detik);


    fpointer = fopen(fileTXT, "a");
    if(mode == 0)
        fprintf(fpointer, "[+] SETOR TUNAI [+]\n");
    else if(mode == 1)
        fprintf(fpointer, "[+] TRANSFER MASUK [+]\n");

    fprintf(fpointer, " |TGL: %s   \n", tgl);

    fprintf(fpointer, " |PUKUL: %s\n", waktu);
    fprintf(fpointer, " |NOMINAL: %d   \n\n", Nominal);

    fclose(fpointer);
}

int tarikTunai(int ID, int Nominal, int mode)
{ // PAKAI INI UNTUK TARIK TUNAI
    //mode : 0 = tarik tunai, 1 = transfer keluar
    system("cls");
    int nominalDump;
    char fileTXT[15];

    itoa(ID, fileTXT, 10);
    strcat(fileTXT, ".txt");

    FILE *fpointer, *fp;
    fpointer = fopen("account.csv", "r");
    fp = fopen("temp.csv", "w");

    char dump[100], dump2[100], charNominal[100];
    char *token;
    fgets(dump, sizeof(dump), fpointer);
    fprintf(fp, dump);
    while (fgets(dump, sizeof(dump), fpointer))
    {
        strcpy(dump2, dump);
        token = strtok(dump, ",");
        if (atoi(token) == ID)
        {
            fprintf(fp, token);
            fprintf(fp, ",");
            token = strtok(NULL, ",");
            nominalDump = atoi(token);
            nominalDump = nominalDump - Nominal;
            if (nominalDump < 0)
            {
                return 0;
            }
            itoa(nominalDump, charNominal, 10);
            fprintf(fp, charNominal);
            fprintf(fp, ",");
            token = strtok(NULL, ",");
            fprintf(fp, token);
        }
        else
        {
            fprintf(fp, dump2);
        }
    }
    fclose(fp);
    fclose(fpointer);

    fpointer = fopen("temp.csv", "r");
    fp = fopen("account.csv", "w");

    while (fgets(dump, sizeof(dump), fpointer))
    {
        fprintf(fp, dump);
    }

    fclose(fp);
    fclose(fpointer);
    remove("temp.csv");

    char tgl[20], waktu[20];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char Bulan[10], Hari[10], Jam[10], Menit[10], Detik[10];
    itoa(tm.tm_year + 1900, tgl, 10);
    strcat(tgl, "/");
    itoa(tm.tm_mon + 1, Bulan, 10);
    itoa(tm.tm_mday, Hari, 10);
    strcat(tgl, Bulan);
    strcat(tgl, "/");
    strcat(tgl, Hari);

    itoa(tm.tm_hour, waktu, 10);
    strcat(waktu, ":");
    itoa(tm.tm_min, Menit, 10);
    itoa(tm.tm_sec, Detik, 10);
    strcat(waktu, Menit);
    strcat(waktu, ":");
    strcat(waktu, Detik);

    fpointer = fopen(fileTXT, "a");
    if(mode == 0)
        fprintf(fpointer, "[-] TARIK TUNAI [-]\n");
    else if(mode == 1)
        fprintf(fpointer, "[-] TRANSFER KELUAR [-]\n");

    fprintf(fpointer, " |TGL: %s\n", tgl);

    fprintf(fpointer, " |PUKUL: %s\n", waktu);
    fprintf(fpointer, " |NOMINAL: %d\n\n", Nominal);

    fclose(fpointer);
    return 1;
}

void lihatDetailAkun(int ID, int mode)
{
    system("cls");
    char buff[100], txtFile[15];
    itoa(ID, txtFile, 10);
    strcat(txtFile, ".txt");
    //membuka akun file txt
    FILE *fptr = fopen(txtFile, "r");

    if (fptr == NULL)
    {
        printf("Error, file %d.txt tidak ditemukan\n", ID);
        exit(1);
    }

    printf("   PROGRAM KAS KELAS\n"
           "   LIHAT DETAIL AKUN\n");
    if (mode == 0)
        printf("       --ADMIN--\n");
    else
        printf("       --USER--\n");
    printf("INFORMASI AKUN :\n");

    printf("|*|ID : %d\n", ID);
    for (int i = 0; i < 4; i++)
    {
        fgets(buff, sizeof(buff), fptr);
        printf("%s", buff);
    }
    //mencari saldo id bersangkutan di account.csv
    printf("Saldo : %d\n", getSaldo(ID));
    //mencetak keseluruhan isi file akun txt
    while (fgets(buff, sizeof(buff), fptr))
        printf("%s", buff);

    printf("\n----------------------------\n");
    system("pause");
    fclose(fptr);
    system("cls");
}

//   MODE ADMIN
int adminMode();
int tambahAkun();
int hapusAkun();
int setorAdmin();
int tarikAdmin();
int detailAdmin();
//   MODE USER
int userMode(int ID);
int tarikUser(int ID);
void transferRek(int ID);

int main(){
    system("cls");
    int pilih, ID;
    char password[100];
    char *token;
    printf("|+|---------------------------------|+|\n");
    printf("|+|     |   PROGRAM KAS KELAS  |    |+|\n");
    printf("|+|---------------------------------|+|\n");
    printf("|+|     |   1. ADMIN           |    |+|\n");
    printf("|+|---------------------------------|+|\n");
    printf("|+|     |   2. USER            |    |+|\n");
    printf("|+|---------------------------------|+|\n");
    printf("|+|     |   3. EXIT            |    |+|\n");
    printf("|+|---------------------------------|+|\n");
    while (1){
        printf("|+|Pilih Menu:");
        scanf("%d", &pilih);

        if (pilih == 1){ // 1. Admin
            while (1){
                printf("|+|Masukan ID:");
                scanf("%d", &ID);
                fflush(stdin);
                printf("|+|Masukan password:");
                fgets(password, sizeof(password), stdin);

                FILE *fpointer;
                fpointer = fopen("account.csv", "r");

                char akun[100];
                while (fgets(akun, sizeof(akun), fpointer)){
                    token = strtok(akun, ",");
                    while (token != NULL){
                        if ((ID == atoi(token)) && (ID / 100000 == 10)){
                            token = strtok(NULL, ",");
                            token = strtok(NULL, ",");
                            if(strcmp(token, password) == 0){
                                fclose(fpointer);
                                adminMode();
                                return 0;
                            }
                        }
                        token = strtok(NULL, ",");
                    }
                }
                if (token == NULL){
                    printf("|+|Maaf,ID atau Password salah|+|\n");
                }
            }
        }
        else if (pilih == 2){ // 2. User
            while (1){
                printf("|+|Masukan ID:");
                scanf("%d", &ID);
                fflush(stdin);
                printf("|+|Masukan password:");
                fgets(password, sizeof(password), stdin);

                FILE *fpointer;
                fpointer = fopen("account.csv", "r");

                char akun[100];
                while (fgets(akun, sizeof(akun), fpointer)){
                    token = strtok(akun, ",");
                    while (token != NULL){
                        if ((ID == atoi(token)) && (ID / 100000 == 20)){
                            token = strtok(NULL, ",");
                            token = strtok(NULL, ",");
                            if(strcmp(token, password) == 0){
                                fclose(fpointer);
                                userMode(ID);
                                return 0;
                            }
                        }
                        token = strtok(NULL, ",");
                    }
                }
                if (token == NULL){
                    printf("|+|ID atau Password salah|+|\n");
                }
            }
        }
        else if (pilih == 3){
            exit(0);
        } else{
            printf("|+|Input tidak ada dalam menu\n");
        }
    }
    return 0;
}

///  MODE ADMIN

int adminMode(){
    system("cls");
    int pilih;
    while (1){
        printf("|*|-------------------------------|*|\n");
        printf("|*|       PROGRAM KAS KELAS       |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|-------------ADMIN-------------|*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       1. TAMBAH AKUN          |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       2. HAPUS AKUN           |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       3. SETOR TUNAI          |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       4. TARIK TUNAI          |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       5. LIHAT DETAIL AKUN    |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       6. EXIT                 |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|Pilih:");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                tambahAkun();
                break;
            case 2:
                hapusAkun();
                break;
            case 3:
                setorAdmin();
                break;
            case 4:
                tarikAdmin();
                break;
            case 5:
                detailAdmin();
                break;
            case 6:
                exit(0);
            default:
                printf("|*|maaf tidak ada dalam menu\n");
        }
    }
    return 0;
}

int tambahAkun(){
    system("cls");
    int umur, pilKelamin, ID;
    char nama[50], tanggal[12], jenisKelamin[12], password[100];
    printf("|*|-------------------------------|*|\n");
    printf("|*|       PROGRAM KAS KELAS       |*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|-------------ADMIN-------------|*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|          TAMBAH AKUN          |*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|NAMA:");
    fflush(stdin);
    scanf("%s", nama);
    fflush(stdin);
    printf("|*|UMUR:");
    scanf("%d", &umur);
    fflush(stdin);
    printf("|*|TANGGAL LAHIR (dd/mm/yy):");
    fgets(tanggal, sizeof(tanggal), stdin);
    fflush(stdin);
    printf("|*|JENIS KELAMIN:\n");
    printf("|*|1. Laki-laki   |  2. Perempuan\n");
    printf("pilih:");
    scanf("%d", &pilKelamin);
    if(pilKelamin == 1){
        strcpy(jenisKelamin, "Laki-laki");
    }
    else if (pilKelamin = 2){
        strcpy(jenisKelamin, "Perempuan");
    }
    printf("------------------------------------\n");
    srand(time(0));
    ID = (10*200000)+(rand()%100000);
    printf("|*|ID: %d (ingat ID ini baik-baik)|*|\n", ID);
    printf("|*|Masukan password:");
    fflush(stdin);
    fgets(password, sizeof(password), stdin);
    char passRepeat[100];
    while (1){
        printf("|*|Masukan kembali password:");
        fgets(passRepeat, sizeof(passRepeat), stdin);
        if (strcmp(passRepeat, password)==0){
            printf("|*|Pembuatan akun berhasil|*|\n");
            break;
        }else{
            printf("|*|Password tidak sesuai dengan sebelumnya, masukan kembali|*|\n");
        }
    }

    //Write to database BEGIN
    char txtFile[15];
    itoa(ID, txtFile, 10);
    strcat(txtFile, ".txt");

    FILE *fpointer;
    fpointer = fopen(txtFile, "w");
    fprintf(fpointer, "|*|NAMA:%s\n"
                      "|*|UMUR:%d\n"
                      "|*|TANGGAL LAHIR:%s"
                      "|*|KELAMIN:%s\n"
                      "------History Transaksi------\n",nama, umur, tanggal, jenisKelamin);
    fclose(fpointer);

    fpointer = fopen("account.csv", "a");
    fprintf(fpointer, "%d,0,%s", ID, password);
    fclose(fpointer);
    //Write to database END


    system("pause");
    system("cls");
    return 0;
}

int hapusAkun(){
    system("cls");
    int pilID;
    if (TampilkanDaftarAkun(1,1,0))
    {
        return 0;
    }else{
        printf("|*|-------------------------------|*|\n");
        printf("|*|       PROGRAM KAS KELAS       |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|-------------ADMIN-------------|*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|          HAPUS AKUN           |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|PILIH ID:");
        scanf("%d", &pilID);
    }

    FILE *fpointer, *fp;
    fpointer = fopen("account.csv", "r");
    fp = fopen("temp.csv", "w");

    char dump[50];
    char dump2[50];
    char *token;
    fgets(dump, sizeof(dump), fpointer);
    fprintf(fp,dump);
    token = strtok(dump, ",");
    while (fgets(dump, sizeof(dump), fpointer)){
        strcpy(dump2, dump);
        token = strtok(dump, ",");

        if (atoi(token) != pilID){
            fprintf(fp, dump2);
        }

    }
    fclose(fp);
    fclose(fpointer);

    fpointer = fopen("temp.csv", "r");
    fp = fopen("account.csv", "w");

    while (fgets(dump, sizeof(dump), fpointer)){
        fprintf(fp, dump);
    }

    fclose(fp);
    fclose(fpointer);

    remove("temp.csv");
    char fileTarget[15];
    itoa(pilID, fileTarget, 10);
    strcat(fileTarget, ".txt");
    remove(fileTarget);

    printf("|*|HAPUS AKUN BERHASIL|*|\n");
    system("pause");
    system("cls");
}

int setorAdmin(){
    system("cls");
    int plhID, nominal;
    if (TampilkanDaftarAkun(1,1,1))
    {
        return 0;
    }else{
        printf("|*|-------------------------------|*|\n");
        printf("|*|       PROGRAM KAS KELAS       |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|-------------ADMIN-------------|*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|          SETOR TUNAI          |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|PILIH ID:");
        scanf("%d", &plhID);
    }

    FILE *fpointer;
    fpointer = fopen("account.csv", "r");

    char dump[100];
    char *token;
    while (fgets(dump, sizeof(dump), fpointer)){
        token = strtok(dump, ",");
        if (atoi(token) == plhID){
            printf("|*|Masukan nominal:");
            scanf("%d", &nominal);
            setorTunai(plhID, nominal, 0);
            printf("|*|Setor tunai berhasil dilakukan|*|\n");
            system("pause");
            fclose(fpointer);
            return 0;
        }
    }

    fclose(fpointer);
    printf("|*|Akun tidak ditemukan!!|*|\n");
    system("pause");
    system("cls");
}

int tarikAdmin()
{
    system("cls");
    int plhID, nominal;
    if (TampilkanDaftarAkun(1,1,1))
    {
        return 0;
    }else{
        printf("|*|-------------------------------|*|\n");
        printf("|*|       PROGRAM KAS KELAS       |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|-------------ADMIN-------------|*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|          TARIK TUNAI          |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|PILIH ID:");
        scanf("%d", &plhID);
    }

    FILE *fpointer;
    fpointer = fopen("account.csv", "r");

    char dump[100];
    char *token;
    while (fgets(dump, sizeof(dump), fpointer))
    {
        token = strtok(dump, ",");
        if (atoi(token) == plhID)
        {
            printf("|*|Masukan nominal:");
            scanf("%d", &nominal);
            if (tarikTunai(plhID, nominal, 0))
            {
                printf("|*|Tarik tunai berhasil dilakukan|*|\n");
            }
            else
            {
                printf("|*|Tarik tunai gagal karena saldo tidak mencukupi|*|\n");
            }
            system("pause");
            fclose(fpointer);
            return 0;
        }
    }

    fclose(fpointer);
    printf("|*|Akun tidak ditemukan!!|*|\n");
    system("pause");
    system("cls");
}

int detailAdmin(){
    system("cls");
    int plhID, nominal;
    if (TampilkanDaftarAkun(1,1,0))
    {
        return 0;
    }else{
        printf("|*|-------------------------------|*|\n");
        printf("|*|       PROGRAM KAS KELAS       |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|-------------ADMIN-------------|*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       LIHAT DETAIL AKUN       |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|PILIH ID:");
        scanf("%d", &plhID);
    }
    lihatDetailAkun(plhID, 0);
}

//   MODE USER
int userMode(int ID){
    int pilih;
    while (1){
        system("cls");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       PROGRAM KAS KELAS       |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|-------------USER--------------|*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       1. LIHAT INFORMASI AKUN |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       2. TARIK TUNAI          |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       3. TRANSFER             |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|       4. EXIT                 |*|\n");
        printf("|*|-------------------------------|*|\n");
        printf("|*|Pilih:");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                lihatDetailAkun(ID, 1);
                break;
            case 2:
                tarikUser(ID);
                break;
            case 3:
                transferRek(ID);
                break;
            case 4:
                exit(0);
            default:
                printf("|*|maaf pilihan tidak ada dalam menu\n");
                system("pause");
        }
    }
    return 0;
}

int tarikUser(int ID)
{
    system("cls");
    int nominal;
    printf("|*|-------------------------------|*|\n");
    printf("|*|       PROGRAM KAS KELAS       |*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|-------------USER--------------|*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|          TARIK TUNAI          |*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|Masukan nominal:");
    scanf("%d", &nominal);

    if (tarikTunai(ID, nominal, 0))
    {
        printf("|*|Tarik tunai berhasil dilakukan|*|\n");
    }
    else
    {
        printf("|*|Tarik tunai gagal karena saldo tidak mencukupi|*|\n");
    }
    system("pause");
    return 0;
}

void transferRek(int ID){
    system("cls");
    int ID_tujuan, saldo_tujuan, saldo_user, nominal;
    char nama_tujuan;

    printf("|*|-------------------------------|*|\n");
    printf("|*|       PROGRAM KAS KELAS       |*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|-------------USER--------------|*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|           TRANSFER            |*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|Informasi Tujuan :\n");
    printf("|*|ID :");
    scanf("%d", &ID_tujuan);
    printf("|*|Masukkan Nominal :");
    scanf("%d", &nominal);

    saldo_user = getSaldo(ID);
    saldo_tujuan = getSaldo(ID_tujuan);

    if(saldo_tujuan == -1){
        printf("|*|Akun tujuan tidak ditemukan|*|\n");
        system("pause");
        return;
    }

    if(saldo_user < nominal){
        printf("|*|Saldo anda tidak mencukupi untuk melakukan transfer|*|\n");
        system("pause");
        return;
    }

    char user_file[100], tujuan_file[100];

    itoa(ID, user_file, 10);
    itoa(ID_tujuan, tujuan_file, 10);
    strcat(user_file, ".txt");
    strcat(tujuan_file, ".txt");

    FILE *fptr_user = fopen(user_file, "a+");
    FILE *fptr_tujuan = fopen(tujuan_file, "a+");
    fgets(user_file, 100, fptr_user);   //scanf nama user
    fseek(fptr_user, 100, SEEK_SET);
    fgets(tujuan_file, 100, fptr_tujuan); //scanf nama tujuan

    printf("|*|-------------------------------|*|\n");
    printf("|*|        DETAIL TRANSFER        |*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|-------------USER--------------|*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|           TRANSFER            |*|\n");
    printf("|*|-------------------------------|*|\n");
    printf("|*|Rekening Asal :\n");
    printf("|*|     ID : %d\n", ID);
    printf("|*|%s\n", user_file);
    printf("|*|Rekening Tujuan :\n");
    printf("|*|     ID : %d\n", ID_tujuan);
    printf("|*|%s\n", tujuan_file);

    printf("|*|Besar Nominal transfer : %ld\n", nominal);

    int is_continue;

    label_check_continue_transfer:

    printf("|*|Lakukan transfer (1 = yes, 0 = no) :");
    scanf("%d", &is_continue);

    if(is_continue == 1){
        setorTunai(ID_tujuan, nominal, 1);
        tarikTunai(ID, nominal, 1);
        fprintf(fptr_user, "|*|REKENING TUJUAN: %d\n\n", ID_tujuan);
        fprintf(fptr_tujuan, "|*|REKENING PENGIRIM: %d\n\n", ID);
        printf("|*|Transfer berhasil dilakukan ke rekening dengan ID %d\n", ID_tujuan);
        printf("|*|Saldo anda saat ini : %d|*|\n", getSaldo(ID));
        printf("\n|*|----------------------------|*|\n");
        system("pause");
        fclose(fptr_user);
        fclose(fptr_tujuan);
    }else if(is_continue == 0){
        printf("|*|Transfer dibatalkan\n");
        fclose(fptr_user);
        fclose(fptr_tujuan);
        system("pause");
        return;
    }else{
        printf("|*|Input salah\n");
        goto label_check_continue_transfer;
    }
}

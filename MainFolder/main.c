#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Universal Function
int getSaldo(int ID)
{
    FILE *fptr = fopen("account.csv", "r");

    if (fptr == NULL)
    {
        printf("Error, File account.csv tidak ditemukan\n");
        exit(1);
    }

    char buffer[200];

    int read_id;
    long int saldo;
    char password[100];
    //mencari saldo berdasarkan id
    while (fscanf(fptr, "%d,%ld,[^,]", &read_id, &saldo, &password))
    {
        if (ID == read_id)
            break;
    }
    fclose(fptr);
    return saldo;
}
int TampilkanDaftarAkun(int ID, int nama, int saldo){
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
        printf("Tidak ada akun yang terdaftar\n");
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
            printf("  ID: %s\n", IdLog);
        }

        strcpy(fileNameTXT,IdLog);
        strcat(fileNameTXT, ".txt");
        fp = fopen(fileNameTXT, "r");
        fscanf(fp, "%[^\n]", dumpTxt);
        if (nama == 1){
            printf("  %s\n", strtok(dumpTxt, " "));
        }

        if (saldo == 1){
            printf("  Saldo: %s\n", saldoLog);
        }
        printf("\n");
    }
    fclose(fp);
    fclose(fpointer);
    printf("-----------------------------\n");
    return 0;
}
int setorTunai(int ID, int Nominal){ // PAKAI INI UNTUK SETOR TUNAI
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
    fprintf(fpointer, "[+] SETOR TUNAI\n");

    fprintf(fpointer, "    TGL: %s\n", tgl);

    fprintf(fpointer, "    PUKUL: %s\n", waktu);
    fprintf(fpointer, "    NOMINAL: %d\n\n", Nominal);

    fclose(fpointer);
}

int tarikTunai(int ID, int Nominal)
{ // PAKAI INI UNTUK TARIK TUNAI
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
            if (nominalDump == 0)
            {
                return 0;
            }
            nominalDump = nominalDump - Nominal;
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
    fprintf(fpointer, "[-] TARIK TUNAI\n");

    fprintf(fpointer, "    TGL: %s\n", tgl);

    fprintf(fpointer, "    PUKUL: %s\n", waktu);
    fprintf(fpointer, "    NOMINAL: %d\n\n", Nominal);

    fclose(fpointer);
    return 1;
}

void lihatDetailAkun(int ID, int mode)
{
//    system("cls");
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

    printf("     ID : %d\n", ID);
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


int main(){
    int pilih, ID;
    char password[100];
    char *token;

    printf("     PROGRAM KAS KELAS     \n");
    printf("1. Admin\n");
    printf("2. User\n");
    printf("3. Keluar Program\n");
    while (1){
        printf("Pilih Menu:");
        scanf("%d", &pilih);

        if (pilih == 1){ // 1. Admin
            while (1){
                printf("Masukan ID:");
                scanf("%d", &ID);
                fflush(stdin);
                printf("Masukan password:");
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
                    printf("ID atau Password salah\n");
                }
            }
        }
        else if (pilih == 2){ // 2. User
            while (1){
                printf("Masukan ID:");
                scanf("%d", &ID);
                fflush(stdin);
                printf("Masukan password:");
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
                    printf("ID atau Password salah\n");
                }
            }
        }
        else if (pilih == 3){
            exit(0);
        } else{
            printf("Input tidak ada dalam menu\n");
        }
    }
    return 0;
}

///  MODE ADMIN

int adminMode(){
    int pilih;
    while (1){
        printf("   PROGRAM KAS KELAS\n"
               "       --ADMIN--\n"
               "1. TAMBAH AKUN\n"
               "2. HAPUS AKUN\n"
               "3. SETOR TUNAI\n"
               "4. TARIK TUNAI\n"
               "5. LIHAT DETAIL AKUN\n"
               "6. exit\n");
        printf("pilih:");
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
                printf("maaf tidak ada dalam menu\n");
        }
    }
    return 0;
}

int tambahAkun(){
    int umur, pilKelamin, ID;
    char nama[50], tanggal[12], jenisKelamin[12], password[100];
    printf("   PROGRAM KAS KELAS\n"
           "       --ADMIN--\n"
           "      TAMBAH AKUN\n");
    printf("NAMA:");
    fflush(stdin);
    scanf("%s", nama);
    fflush(stdin);
    printf("UMUR:");
    scanf("%d", &umur);
    fflush(stdin);
    printf("TANGGAL LAHIR (dd/mm/yy):");
    fgets(tanggal, sizeof(tanggal), stdin);
    fflush(stdin);
    printf("JENIS KELAMIN:\n");
    printf("1. Laki-laki   |  2. Perempuan\n");
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
    printf("ID: %d (ingat ID ini baik-baik)\n", ID);
    printf("Masukan password:");
    fflush(stdin);
    fgets(password, sizeof(password), stdin);
    int passRepeat[100];
    while (1){
        printf("Masukan kembali password:");
        fgets(passRepeat, sizeof(passRepeat), stdin);
        if (strcmp(passRepeat, password)==0){
            printf("Pembuatan akun berhasil\n");
            break;
        }else{
            printf("Password tidak sesuai dengan sebelumnya, masukan kembali\n");
        }
    }

    //Write to database BEGIN
    char txtFile[15];
    itoa(ID, txtFile, 10);
    strcat(txtFile, ".txt");

    FILE *fpointer;
    fpointer = fopen(txtFile, "w");
    fprintf(fpointer, "     NAMA:%s\n"
                      "     UMUR:%d\n"
                      "     TANGGAL LAHIR:%s"
                      "     KELAMIN:%s\n"
                      "------History Transaksi------\n",nama, umur, tanggal, jenisKelamin);
    fclose(fpointer);

    fpointer = fopen("account.csv", "a");
    fprintf(fpointer, "%d,0,%s", ID, password);
    fclose(fpointer);
    //Write to database END


    system("pause");
    return 0;
}

int hapusAkun(){
    int pilID;
    printf("   PROGRAM KAS KELAS\n"
           "       --ADMIN--\n"
           "      HAPUS AKUN\n"
           "AKUN YANG TERDAFTAR\n");
    if (TampilkanDaftarAkun(1,1,0))
    {
        return 0;
    }else{
        printf("PILIH ID:");
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

    printf("HAPUS AKUN BERHASIL\n");
    system("pause");
}

int setorAdmin(){
    int plhID, nominal;
    printf("   PROGRAM KAS KELAS\n"
           "       --ADMIN--\n"
           "      SETOR TUNAI\n"
           "AKUN YANG TERDAFTAR\n");
    if (TampilkanDaftarAkun(1,1,0))
    {
        return 0;
    }else{
        printf("PILIH ID:");
        scanf("%d", &plhID);
    }

    FILE *fpointer;
    fpointer = fopen("account.csv", "r");

    char dump[100];
    char *token;
    while (fgets(dump, sizeof(dump), fpointer)){
        token = strtok(dump, ",");
        if (atoi(token) == plhID){
            printf("Masukan nominal:");
            scanf("%d", &nominal);
            setorTunai(plhID, nominal);
            printf("Setor tunai berhasil dilakukan\n");
            system("pause");
            fclose(fpointer);
            return 0;
        }
    }

    fclose(fpointer);
    printf("Akun tidak ditemukan!!\n");
    system("pause");
}

int tarikAdmin()
{
    int plhID, nominal;
    printf("   PROGRAM KAS KELAS\n"
           "       --ADMIN--\n"
           "      TARIK TUNAI\n"
           "AKUN YANG TERDAFTAR\n");
    if (TampilkanDaftarAkun(1,1,0))
    {
        return 0;
    }else{
        printf("PILIH ID:");
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
            printf("Masukan nominal:");
            scanf("%d", &nominal);
            if (tarikTunai(plhID, nominal))
            {
                printf("Tarik tunai berhasil dilakukan\n");
            }
            else
            {
                printf("Tarik tunai gagal karena saldo tidak mencukupi\n");
            }
            system("pause");
            fclose(fpointer);
            return 0;
        }
    }

    fclose(fpointer);
    printf("Akun tidak ditemukan!!\n");
    system("pause");
}

int detailAdmin(){
    int plhID, nominal;
    printf("   PROGRAM KAS KELAS\n"
           "       --ADMIN--\n"
           "      TARIK TUNAI\n"
           "AKUN YANG TERDAFTAR\n");
    if (TampilkanDaftarAkun(1,1,0))
    {
        return 0;
    }else{
        printf("PILIH ID:");
        scanf("%d", &plhID);
    }
    lihatDetailAkun(plhID, 0);
}

//   MODE USER
int userMode(int ID){
    int pilih;
    while (1){
        printf("   PROGRAM KAS KELAS\n"
               "       --USER--\n"
               "1. LIHAT INFORMASI AKUN\n"
               "2. TARIK TUNAI\n"
               "3. TRANSFER\n"
               "4. exit\n");
        printf("pilih:");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                lihatDetailAkun(ID, 1);
                break;
            case 2:
                tarikUser(ID);
                break;
            case 3:
                // transfer();
                break;
            case 4:
                exit(0);
            default:
                printf("maaf tidak ada dalam menu\n");
        }
    }
    return 0;
}

int tarikUser(int ID)
{
    int nominal;
    printf("   PROGRAM KAS KELAS\n"
           "       --USER--\n"
           "      TARIK TUNAI\n"
           "AKUN YANG TERDAFTAR\n");
    printf("Masukan nominal:");
    scanf("%d", &nominal);

    if (tarikTunai(ID, nominal))
    {
        printf("Tarik tunai berhasil dilakukan\n");
    }
    else
    {
        printf("Tarik tunai gagal karena saldo tidak mencukupi\n");
    }
    system("pause");
    return 0;
}

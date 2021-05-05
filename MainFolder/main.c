#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

//   MODE ADMIN
int adminMode();
int tambahAkun();

//   MODE USER
int userMode(int ID);

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
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
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
    char nama[50], tanggal[10], jenisKelamin[12], password[100];
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
                      "     TANGGAL LAHIR:%s\n"
                      "     KELAMIN:%s\n"
                      "------History Transaksi------",nama, umur, tanggal, jenisKelamin);
    fclose(fpointer);

    fpointer = fopen("account.csv", "a");
    fprintf(fpointer, "%d,0,%s", ID, password);
    fclose(fpointer);
    //Write to database END


    system("pause");
    return 0;
}

//   MODE USER
int userMode(int ID){
    printf("ANDA MASUK SEBAGAI USER\n");
    system("pause");
    return 0;
}
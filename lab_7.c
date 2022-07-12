#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 255
#define sep ';'
#define FN "auto.csv"
#define Delta 5
#define GEAR_MAX 3

typedef struct AUTO {
    char *MARK;
    char *MODEL;
    int YEAR;
    int MASS;
    float VAL;
    float AC;
    float GEAR[GEAR_MAX];
} AUTO;


int LoadFile(AUTO**,int*,int*);
int Add(AUTO,AUTO**,int*,int*);
void PrintAll(AUTO*,int);
int AddCar(AUTO**,int*,int*);
int SearchMark(AUTO,char *);
int SearchModel(AUTO,char *);
void Search(AUTO *CARS,int ,int (*SearchM) (AUTO,char *), int flag);

int main()
{
    int i,key,key1;
    int st = 0;
    int stmax = 0;
    AUTO *CAR;
    if (LoadFile(&CAR,&st,&stmax)) {

        do {
            system("cls");
            fflush(stdin);
            printf ("1.Add car\n");
            printf("2.Print all\n");
            printf("3.Search Mark \n");
            printf("0.Exit program\n");
            printf("\n");
            printf("Select key: ");
            scanf("%d",&key);
            fflush(stdin);
            switch (key) {
                case 1:
                    printf("1.Add car\n");
                    AddCar(&CAR,&st,&stmax);
                    break;
                case 2:
                    printf("2.Print all\n");
                    PrintAll(CAR,st);
                    break;
                case 3:
                    printf("3.Search Mark\n");
                    printf("1 Sort for YEAR\n");
                    printf("2 Sort for MASS\n");
                    printf("3 Sort for VAL\n");
                    printf("4 Sort for AC\n");
                    printf("5 Sort for GEAR 1\n");
                    printf("6 Sort for GEAR 2\n");
                    printf("7 Sort for GEAR 3\n");
                    printf("Select key for sort: ");
                    scanf("%d",&key1);
                    fflush(stdin);
                    if(key1 > 0 && key1 < 8) {
                        Search(CAR,st,SearchMark,key1);
                    }
                    else {
                        printf("Error key!");
                    }
                    break;
            }
        }while (key != 0);

        for (i = 0;i < st;i++) {
            free(CAR[i].MARK);
            free(CAR[i].MODEL);
        }
        free(CAR);
    }
    else {
        printf("Error file!");
    }
    return 0;

}

int LoadFile(AUTO **CAR,int *st,int *stmax)
{
    char s1[MAX_LEN];
    char s2[MAX_LEN];
    FILE *f;
    int j,count;
    int flag = 0;
    AUTO Z;

    f = fopen(FN,"r");
    if (f != NULL) {
        while (!feof(f)) {
            fgets(s1,MAX_LEN,f);
            count = strchr(s1,sep) - s1;
            if (count > 0) {
                Z.MARK = (char*)malloc(sizeof(char) * (count+1));
                if (Z.MARK != NULL) {
                    strncpy(Z.MARK,s1,count);
                    Z.MARK[count] = 0;
                }
                strcpy(s1,strchr(s1,sep)+1);

                /*MODEL*/
                count = strchr(s1,sep) - s1;
                Z.MODEL = (char*)malloc(sizeof(char) * (count+1));
                if (Z.MODEL != NULL) {
                    strncpy(Z.MODEL,s1,count);
                    Z.MODEL[count] = 0;
                }
                strcpy(s1,strchr(s1,sep)+1);
                if ( (Z.MARK != NULL) && (Z.MODEL != NULL)) {

                    /*YEAR*/
                    count = strchr(s1,sep) - s1;
                    strncpy(s2,s1,count);
                    s2[count] = 0;
                    Z.YEAR = atoi(s2);
                    strcpy(s1,strchr(s1,sep)+1);

                    /*MASS*/
                    count = strchr(s1,sep) - s1;
                    strncpy(s2,s1,count);
                    s2[count] = 0;
                    Z.MASS = atoi(s2);
                    strcpy(s1,strchr(s1,sep)+1);

                    /*VAL*/
                    count = strchr(s1,sep) - s1;
                    strncpy(s2,s1,count);
                    s2[count] = 0;
                    Z.VAL = atof(s2);
                    strcpy(s1,strchr(s1,sep)+1);

                    /*AC*/
                    count = strchr(s1,sep) - s1;
                    strncpy(s2,s1,count);
                    s2[count] = 0;
                    Z.AC = atof(s2);
                    strcpy(s1,strchr(s1,sep)+1);

                    /*GEAR*/
                    for (j = 0;j < 2;j++) {
                        count = strchr(s1,sep) - s1;
                        strncpy(s2,s1,count);
                        s2[count] = 0;
                        Z.GEAR[j] = atof(s2);
                        strcpy(s1,strchr(s1,sep)+1);
                    }
                    Z.GEAR[2] = atof(s1);
                    Add(Z,CAR,st,stmax);
                    free(Z.MARK);
                    free(Z.MODEL);
                }
            }
        }
        fclose(f);
        flag = 1;
    }
    return flag;
}


int Add(AUTO Z,AUTO **CAR,int *st,int *stmax) {
    int flag = 1;
    int i;

    if (*st == *stmax) {
        if (*stmax == 0) {
            *CAR = (AUTO*)malloc(sizeof(AUTO) * Delta);
        }
        else {
            *CAR = (AUTO*)realloc(*CAR, sizeof(AUTO) * (*stmax + Delta));
        }
        if (*CAR == NULL) {
            flag = 0;
        }
        else {
            *stmax = *stmax + Delta;
        }
    }

    if (flag) {
        (*CAR)[*st].MARK = (char*)malloc(sizeof(char) * (strlen(Z.MARK)+1));
        if ((*CAR)[*st].MARK == NULL) {
            flag = 0;
        }
        else {
            strcpy((*CAR)[*st].MARK, Z.MARK);
        }

        (*CAR)[*st].MODEL = (char*)malloc(sizeof(char) * (strlen(Z.MODEL)+1));
        if ((*CAR)[*st].MODEL == NULL) {
            flag = 0;
        }
        else {
            strcpy((*CAR)[*st].MODEL, Z.MODEL);
        }

        (*CAR)[*st].YEAR = Z.YEAR;
        (*CAR)[*st].MASS = Z.MASS;
        (*CAR)[*st].VAL = Z.VAL;
        (*CAR)[*st].AC = Z.AC;
        for (i = 0;i < GEAR_MAX;i++) {
            (*CAR)[*st].GEAR[i] = Z.GEAR[i];
        }
        if (flag) {
            (*st)++;
        }
    }

    return flag;
}

void PrintAll(AUTO *CAR,int st)
{
    int i;
    printf("ID\t Mark\t\t Model\t\t Year\t Mass\t Value\t AC\t Gear1\t Gear2\t Gear3 \n");
    for (i = 0;i < st;i++) {
        printf("%d\t %10s\t %10s\t %d\t %d\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f \n",i,CAR[i].MARK,CAR[i].MODEL,CAR[i].YEAR,CAR[i].MASS,CAR[i].VAL,CAR[i].AC,CAR[i].GEAR[0],CAR[i].GEAR[1],CAR[i].GEAR[2]);
    }
    fflush(stdin);
    getchar();
}

int AddCar(AUTO **CAR,int *st,int *stmax)
{
    AUTO Z;
    int i;
    char s1[MAX_LEN];
    int flag = 1;
    printf("Enter Mark: ");
    fgets(s1,MAX_LEN,stdin);
    s1[strlen(s1)-1] = 0;
    Z.MARK = (char*)malloc((strlen(s1)+1) * sizeof(char));
    if (Z.MARK != NULL) {
        strcpy(Z.MARK,s1);
    }
    printf("\n");
    printf("Enter Model: ");
    fgets(s1,MAX_LEN,stdin);
    s1[strlen(s1)-1] = 0;
    Z.MODEL = (char*)malloc((strlen(s1)+1) * sizeof(char));
    if (Z.MODEL != NULL) {
        strcpy(Z.MODEL,s1);
    }
    printf("\n");
    if ((Z.MODEL != NULL) && (Z.MARK != NULL)) {
        printf("Enter Year: ");
        scanf("%d",&Z.YEAR);
        printf("\nEnter Mass: ");
        scanf("%d",&Z.MASS);
        printf("\nEnter Value engine: ");
        scanf("%f",&Z.VAL);
        printf("\nEnter Ac: ");
        scanf("%f",&Z.AC);
        printf("Enter gear\n");
        for (i = 0;i < GEAR_MAX;i++) {
            printf("G%d: ",i+1);
            scanf("%f",&Z.GEAR[i]);
            //printf("\n");
        }
        flag = Add(Z,CAR,st,stmax);
    }
    if (flag) {
        printf("OK!");
        getchar();
    }
    else
        printf("Error!");
    getchar();
    return flag;
}

int SearchMark(AUTO Z,char *Mark)
{
    int flag;
    if (strncmp(Z.MARK,Mark,MAX_LEN) == 0){
        flag = 1;
    }
    else {
        flag = 0;
    }
    return flag;
}

void Search(AUTO *CARS,int st,int (*SearchM) (AUTO,char *), int flag)
{
    int i,j;
    AUTO x;
    int k = 0;
    int *Idx;
    char s[MAX_LEN];

    printf("Input parametr: ");
    fgets(s,MAX_LEN,stdin);
    s[strlen(s)-1] = 0;
    Idx = (int*)malloc(st * sizeof(int));
    if (Idx != NULL) {
        for (i = 0;i < st;i++) {
            if (SearchM(CARS[i],s)) {
                Idx[k] = i;
                k++;
            }
        }
        if (k) {
            for (i = 0;i < k - 1;i++) {
                for (j = i + 1;j < k;j++) {
                    if(flag == 1) {
                        if (CARS[Idx[i]].YEAR > CARS[Idx[j]].YEAR) {
                            x = CARS[Idx[i]];
                            CARS[Idx[i]] = CARS[Idx[j]];
                            CARS[Idx[j]] = x;
                        }
                    }
                    else if(flag == 2) {
                        if (CARS[Idx[i]].MASS > CARS[Idx[j]].MASS) {
                            x = CARS[Idx[i]];
                            CARS[Idx[i]] = CARS[Idx[j]];
                            CARS[Idx[j]] = x;
                        }
                    }
                    else if(flag == 3) {
                        if (CARS[Idx[i]].VAL > CARS[Idx[j]].VAL) {
                            x = CARS[Idx[i]];
                            CARS[Idx[i]] = CARS[Idx[j]];
                            CARS[Idx[j]] = x;
                        }
                    }
                    else if(flag == 4) {
                        if (CARS[Idx[i]].AC > CARS[Idx[j]].AC) {
                            x = CARS[Idx[i]];
                            CARS[Idx[i]] = CARS[Idx[j]];
                            CARS[Idx[j]] = x;
                        }
                    }
                    else if(flag == 5) {
                        if (CARS[Idx[i]].GEAR[0] > CARS[Idx[j]].GEAR[0]) {
                            x = CARS[Idx[i]];
                            CARS[Idx[i]] = CARS[Idx[j]];
                            CARS[Idx[j]] = x;
                        }
                    }
                    else if(flag == 6) {
                        if (CARS[Idx[i]].GEAR[1] > CARS[Idx[j]].GEAR[1]) {
                            x = CARS[Idx[i]];
                            CARS[Idx[i]] = CARS[Idx[j]];
                            CARS[Idx[j]] = x;
                        }
                    }
                    else if(flag == 7) {
                        if (CARS[Idx[i]].GEAR[2] > CARS[Idx[j]].GEAR[2]) {
                            x = CARS[Idx[i]];
                            CARS[Idx[i]] = CARS[Idx[j]];
                            CARS[Idx[j]] = x;
                        }
                    }
                }
            }
            printf("%d\n",k);
            printf("ID\t Mark\t\t Model\t\t Year\t Mass\t Value\t AC\t Gear1\t Gear2\t Gear3 \n");
            for (i = 0;i < k;i++) {
                printf("%d\t %s\t %10s\t %d\t %d\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f \n",i,CARS[Idx[i]].MARK,CARS[Idx[i]].MODEL,CARS[Idx[i]].YEAR,CARS[Idx[i]].MASS,CARS[Idx[i]].VAL,CARS[Idx[i]].AC,CARS[Idx[i]].GEAR[0],CARS[Idx[i]].GEAR[1],CARS[Idx[i]].GEAR[2]);
            }
            fflush(stdin);
            getchar();
        }
        else {
            printf("No cars!");
        }
        free(Idx);
    }
    else {
        printf("Error");
    }
    getchar();
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 255
#define sep ';'
#define FN "auto.csv"
#define Delta 5
#define GEAR_MAX 5

typedef struct AUTO {
    int ID;
    char *MARK;
    char *MODEL;
    int YEAR;
    int MASS;
    float VAL;
    float AC;
    float GEAR[GEAR_MAX];
    struct AUTO *next;
}AUTO;


int LoadFile(AUTO**);
void PrintList(AUTO*);
void systemPause();
void ClearBuff();
void AddCar(AUTO**,int);

int quantity(AUTO *head) {

    int count = 0;
    AUTO *p;

    p = head;
    if (head != NULL) {
        while(p != NULL) {
            p = p->next;
            count++;
        }
    }

    return count;
}

int main(){
    int key,id;
    AUTO *head = NULL;
    if (LoadFile(&head)) {

        do {
            system("cls");
            printf("1.Print all\n");
            printf("2.Add car\n");
            printf("0.Exit program\n");
            printf("\n");
            printf("Select key: ");
            scanf("%d",&key);
            ClearBuff();
            switch (key) {
                case 1:
                    printf("1.Print all\n");
                    PrintList(head);
                    systemPause();
                    break;
                case 2:
                    printf("2.Add car\n");
                    printf("Input ID: ");
                    scanf("%d",&id);
                    ClearBuff();
                    if (quantity(head) > id) {
                        id = quantity(head) - id;
                        printf("ID = %d\n",id);
                    }
                    else {
                        id = 1;
                        printf("ID = %d\n",id);
                    }
                    AddCar(&head,id);
                    systemPause();
                    break;
            }
        } while (key != 0);
    }
    else {
        printf("Error file!");
    }
    return 0;

}

int LoadFile(AUTO **head){
    char s1[MAX_LEN];
    char s2[MAX_LEN];
    FILE *f;
    int i,j,count;
    int flag = 0;
    AUTO *p = NULL;
    AUTO Z;

    i = 1;
    f = fopen("auto.txt","r");
    if (f != NULL) {
        while (!feof(f)) {
            fgets(s1,MAX_LEN,f);
            if (p == NULL) {
                p = (AUTO*)malloc(sizeof(AUTO));
                *head = p;
            }
            else {
                p->next = (AUTO*)malloc(sizeof(AUTO));
                p = p->next;
            }
            Z.ID = i;
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
                    for (j = 0;j < 4;j++) {
                        count = strchr(s1,sep) - s1;
                        strncpy(s2,s1,count);
                        s2[count] = 0;
                        Z.GEAR[j] = atof(s2);
                        strcpy(s1,strchr(s1,sep)+1);
                    }
                    Z.GEAR[4] = atof(s1);
                    *p = Z;
                    i++;
                    p->next = NULL;
                }
            }

        }
        fclose(f);
        flag = 1;
    }
    return flag;
}


void PrintList(AUTO* head) {
    if (head == NULL) {
        printf("List is empty!\n");

    }
    else {
        printf("Mark      Model       Year Mass Value AC   Gear1  Gear2  Gear3  Gear4  Gear5 \n");
        do {
            printf("%10s %10s %4d %4d %4.2f %5.2f %4.2f %6.2f %6.2f %6.2f %6.2f \n",head->MARK,head->MODEL,head->YEAR,head->MASS,head->VAL,head->AC,head->GEAR[0],head->GEAR[1],head->GEAR[2],head->GEAR[3],head->GEAR[4]);
            head = head->next;
        } while (head != NULL);

    }
}


void systemPause(){

    printf("\n");
    printf("Press ENTER to continue\n");
    getchar();
}


void ClearBuff() {
    int i;

    while ( (i != EOF) && (i != '\n')) {
        i = getchar();
    }
}


void AddCar(AUTO **head,int id){
    AUTO *p = NULL;
    AUTO *temp;
    AUTO Z;
    int i;
    int count = 0;
    char s1[MAX_LEN];

    p = (AUTO*)malloc(sizeof(AUTO));

    if (p != NULL) {
        printf("Enter Mark: ");
        fgets(s1,MAX_LEN,stdin);
        s1[strlen(s1)-1] = 0;
        Z.MARK = (char*)malloc((strlen(s1)+1) * sizeof(char));
        if(Z.MARK != NULL) {
            strcpy(Z.MARK,s1);
            printf("Enter Model: ");
            fgets(s1,MAX_LEN,stdin);
            s1[strlen(s1)-1] = 0;
            Z.MODEL = (char*)malloc((strlen(s1)+1) * sizeof(char));
            if (Z.MODEL != NULL) {
                strcpy(Z.MODEL,s1);

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
                }

                *p = Z;
                p->next = NULL;
                if (*head == NULL) {
                    *head = p;
                }
                else {
                    temp = *head;
                    while(count != id - 1) {
                        count++;
                        temp = temp->next;
                    }
                    p->next = temp->next;
                    temp->next = p;

                }
                printf("Ready!\n");
                getchar();
            }
        }
    }
    else {
        printf("Error memory!\n");
    }

}

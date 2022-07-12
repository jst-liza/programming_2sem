#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	MAX_LEN = 255,
	sep = ';',
	GEAR_MAX = 5,
	MAX_NUM = 10
};

typedef struct MARKA {
    int ID;
	char *NAME;
	struct MARKA *next;
	struct MARKA *prev;
} MARKA;

typedef struct AUTO {
	MARKA *MARK;
	char *MODEL;
	int YEAR;
	int MASS;
	float VAL;
	float AC;
	float GEAR[GEAR_MAX];
	struct AUTO *next;
}AUTO;

int LoadFile(AUTO**,MARKA**);
void PrintList(AUTO*,MARKA*);
MARKA* FindMarka(char*,MARKA*);
MARKA* AddMarka(char*,MARKA**,int,int);
void AddCar(MARKA**,AUTO**);
int quantity(MARKA*);

int main() {
	AUTO *head = NULL;
	MARKA *head_mark = NULL;
	char s[MAX_LEN];
	int key,id;

	if (LoadFile(&head,&head_mark)) {

		do {
			system("cls");
			fflush(stdin);
			printf("1. Print list's\n");
			printf("2. Add mark\n");
			printf("3. Add car\n");
			printf("0. Exit program\n");
			printf("\n");
			printf("Select key: ");
			scanf("%d",&key);
			fflush(stdin);
			switch (key) {
				case 1:
					printf("1.Print list's\n");
					PrintList(head,head_mark);
					printf("To continue press ENTER\n");
					getchar();
					break;
				case 2:
					printf("2. Add mark\n");
					printf("Enter mark name: ");
					fgets(s,MAX_LEN,stdin);
					s[strlen(s)-1] = 0;
					if (FindMarka(s,head_mark) == NULL) {
                        printf("Input id\n");
                        scanf("%d",&id);
                        fflush(stdin);
                        if (quantity(head_mark) > id) {
                            id = quantity(head_mark) - id;
                            printf("ID = %d\n",id);
                        }
                        else {
                            id = 1;
                            printf("ID = %d\n",id);
                        }
                        AddMarka(s,&head_mark,2,id);
					}
					else {
						printf("This mark is listed!\n");

					}
					printf("To continue press ENTER\n");
					getchar();
					break;
				case 3:
					printf("3. Add car\n");
					AddCar(&head_mark,&head);
					printf("To continue press ENTER\n");
					getchar();
					break;
			}
		}while (key != 0);
	}
	else {
		printf("Error file!");
	}
	return 0;
}

int LoadFile(AUTO **head,MARKA **head_mark)
{
	char s1[MAX_LEN];
	char s2[MAX_LEN];
	FILE *f;
	int j,count;
	int flag = 0;
	AUTO *p = NULL;
	AUTO Z;
	MARKA *q;

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
			count = strchr(s1,sep) - s1;
			if (count > 0) {
				strncpy(s2,s1,count);
		        s2[count] = 0;
				q = FindMarka(s2,*head_mark);
				if (q == NULL) {
					q = AddMarka(s2,head_mark,1,0);

				}

				Z.MARK = q;
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
					p->next = NULL;
				}
			}

		}
		fclose(f);
		flag = 1;
	}
	return flag;
}

void PrintList(AUTO* head,MARKA* head_mark) {
	MARKA *p;

	p = head_mark;
	if (p == NULL) {
		printf("Mark's list is empty!\n");
	}
	else {
		printf("Mark\n");
		do {
			printf("%s\n",p->NAME);
			p = p->next;
		} while(p != NULL);
	}

	printf("\n");

	if (head == NULL) {
		printf("List is empty!\n");

	}
	else {
		printf("Mark      Model       Year Mass Value AC   Gear1  Gear2  Gear3  Gear4  Gear5 \n");
		do {
			printf("%10s %10s %4d %4d %4.2f %5.2f %4.2f %6.2f %6.2f %6.2f %6.2f \n",(head->MARK)->NAME,head->MODEL,head->YEAR,head->MASS,head->VAL,head->AC,head->GEAR[0],head->GEAR[1],head->GEAR[2],head->GEAR[3],head->GEAR[4]);
	    	head = head->next;
  		} while (head != NULL);

	}
}

MARKA* FindMarka(char* name,MARKA* head) {
	MARKA *p;
	int flag = 0;

	p = head;
	if (p != NULL) {
		do {
			if (!strncmp(name,p->NAME,MAX_LEN)) {
				flag = 1;
			} else {
				p = p->next;
			}
		} while((p != NULL)	&& (!flag));
	}

	return p;
}

MARKA* AddMarka(char* name,MARKA** head,int flag,int id)
{
    MARKA *p,*q,*r;
    int count = 0;

    p = (MARKA*)malloc(sizeof(MARKA));
    if (p != NULL) {
        p->NAME = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        if (p->NAME != NULL) {
            strcpy(p->NAME,name);
            p->next = NULL;
            if (*head == NULL) {
                *head = p;
            }
            else {
                if (flag == 1) {
                    q = *head;
                    while (q->next != NULL) {
                        q = q->next;
                    }
                    q->next = p;
                }
                else if (flag == 2) {
                    q = *head;
                    if(id == quantity(*head)) {
                        while (q->next != NULL) {
                            q = q->next;
                        }
                        q->next = p;
                    }
                    else {
                        while (count != id-1) {
                            count++;
                            q = q->next;
                        }
                        r = q->next;
                        q->next = p;
                        p->prev = q;
                        r->prev = p;
                        p->next = r;

                    }
                }
            }
        }
        else {
            free(p);
            p = NULL;
        }
    }

    return p;
}

void AddCar(MARKA **head_mark,AUTO **head)
{
	AUTO *p = NULL;
	AUTO *temp;
	AUTO Z;
	MARKA *q;
	int i;
	char s1[MAX_LEN];

	p = (AUTO*)malloc(sizeof(AUTO));

	if (p != NULL) {
		printf("Enter Mark: ");
		fgets(s1,MAX_LEN,stdin);
		s1[strlen(s1)-1] = 0;
		q = FindMarka(s1,*head_mark);
		if (q == NULL) {
			q = AddMarka(s1,head_mark,1,0);
		}
		Z.MARK = q;

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
				while(temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = p;

			}
			printf("Ready!\n");
			getchar();
		}
	}
	else {
		printf("Error memory!\n");
	}
}

int quantity(MARKA *head) {

    int count = 0;
    MARKA *p;

    p = head;
    if (head != NULL) {
        while(p != NULL) {
            p = p->next;
            count++;
        }
    }

    return count;
}

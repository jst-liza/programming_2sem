#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 255


typedef struct MARK {
	char NAME[MAX_LEN];
	struct MARK *next;
} MARK;

int LoadFile (MARK**);
void RingList(MARK*);
void PrintList(MARK*);
MARK *ReverseList(MARK*);
void Delete(MARK**);

int main()
{
	MARK *head = NULL;
	int key;

	if (LoadFile(&head)) {
        printf("Input 1 to print straight list or 2 to print reverse list\n");
        printf("Enter key: ");
        scanf("%d",&key);
        fflush(stdin);
        if (key == 1) {
            Delete(&head);
            RingList(head);
            PrintList(head);
            printf("To continue press ENTER\n");
            getchar();
        }
        else if (key == 2) {
            head = ReverseList(head);
            Delete(&head);
            RingList(head);
            PrintList(head);
            printf("To continue press ENTER\n");
            getchar();
        }
        else {
            printf("Exit\n");
            printf("To continue press ENTER\n");
            getchar();
        }
	}
	else {
		printf("Error file!");
	}
	return 0;
}

int LoadFile(MARK **head){
	char s[MAX_LEN];
	MARK *p = NULL;
	FILE *f;
	int flag = 0;

	f = fopen("mark.txt","r");
	if (f != NULL) {
		while (!feof(f)) {
			fgets(s,MAX_LEN,f);
			s[strlen(s)-1] = 0;
			if (p == NULL) {
				p = (MARK*)malloc(sizeof(MARK));
				*head = p;
			}
			else {
				p->next = (MARK*)malloc(sizeof(MARK));
				p = p->next;
			}

			strcpy(p->NAME,s);
			p->next = NULL;
		}
		fclose(f);
		flag = 1;
	}

	return flag;
}


void RingList(MARK *head) {
	MARK *p;

	p = head;
	while(p->next != NULL) {
		p = p->next;
	}
	p->next = head;

}


void PrintList(MARK* head) {
	MARK *p;

	p = head;

	if (head == NULL) {
		printf("List is empty!\n");
	}
	else {
		do {
	    	printf("%s\n",head->NAME);
	    	head = head->next;
  		} while ( (head != NULL) && (head != p));
  		printf("\n");
	}
}

MARK* ReverseList(MARK* head) {
	MARK *sled = NULL;
	MARK *pred = NULL;

	do {
		sled = head->next;
		head->next = pred;
		pred = head;
		head = sled;
	} while(head != NULL);
	head = pred;

	return head;
}

void Delete(MARK **head)
{
    MARK *p,*q;

    p = *head;
    while((p->next)->next != NULL) {
        p = p->next;
    }
    q = p->next;
    free(q);
    p->next = NULL;
}


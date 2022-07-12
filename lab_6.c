#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define pause getchar() /*задержка экрана*/
#define CLS system("cls") /*очистка экрана*/
#define MAX_LEN 64 /*макс. длина названия книги*/


struct BOOK{
    char Name[MAX_LEN];
    char Publisher[MAX_LEN];
    int Year;
    float Price;
    char Authors[4][MAX_LEN];
};


char menu(){
    char m;
    puts("1. File input");
    puts("2. Keyboard input");
    puts("3. Data pre-check");
    puts("4. Filter");
    puts("0. Exit");
    m = getchar();
    getchar();
    return m;
}


char *str_reader(){
    char *name = (char*) malloc(128*sizeof(char));
    fgets(name, 128, stdin);
    name[strlen(name)-1] = '\0';
    return name;
}


int book_counter(FILE *name, fpos_t *p){
    int count = 0;
    fsetpos(name, p);
    while(!feof(name)){
        if(fgetc(name) == '\n'){
            count++;
            if(count == 1)
                fgetpos(name, p);
        }
    }
    return count;
}


void catalog_sort(struct BOOK* LIB, int* LIB_amount){
    for (int i = 0; i < (*LIB_amount) - 1; i++){
        for (int j = i + 1; j < *LIB_amount; j++){
            if (strcmp(LIB[i].Publisher, LIB[j].Publisher) > 0){
                struct BOOK tmp = LIB[i];
                LIB[i] = LIB[j];
                LIB[j] = tmp;
            }
        }
    }
}


struct BOOK* file_input(struct BOOK* CATALOG, int* amount_books){
    char* file_name;
    char price[10];
    char year[4];
    char sim;
    FILE *file;
    int i, j, k;
    fpos_t pos2;
    fpos_t *position;

    puts("Enter file's directory:");
    file_name=str_reader();
    file=fopen(file_name,"r");
    if(file!=NULL){
        fgetpos(file, &pos2);
        position = &pos2;
        (*amount_books) = book_counter(file, position);
        printf("There is/are %d books", *amount_books);
            if (*amount_books > 0)
                CATALOG = malloc((*amount_books) * sizeof(struct BOOK));
            fsetpos(file, position);
            if (CATALOG != NULL){
                for (i = 0; i < *amount_books; i++){
                    fscanf(file, "%[A-z ]%[^;]%s", CATALOG[i].Name);
                    sim = fgetc(file);
                    fscanf(file, "%[A-z ]%[^;]%s", CATALOG[i].Publisher);
                    sim = fgetc(file);
                    fscanf(file, "%[0-9]%[^;]%s", year);
                    CATALOG[i].Year = atoi(year);
                    sim = fgetc(file);
                    fscanf(file, "%[0-9.]%[^;]%s", price);
                    price[strlen(price)] = '\0';
                    CATALOG[i].Price = atof(price);
                    sim = fgetc(file);
                    j = 0;
                    k = 0;
                            while (sim != '\n' && sim != '\0' && k != 1){
                                fscanf(file, "%[A-z. ]%[^,\n]%s", CATALOG[i].Authors[j]);
                                fgetpos(file, &pos2);
                                position = &pos2;
                                sim = fgetc(file);
                                fsetpos(file, position);
                                if (fgetc(file) == EOF)
                                    k = 1;
                                j++;
                            }
                            for (j; j < 4; j++){
                                CATALOG[i].Authors[j][0] = '\0';
                            }
                        }
                        fclose(file);
                        catalog_sort(CATALOG, amount_books);
                    } else
                        puts("Memory allocation failure.");
                }else
                    puts("File opening error.");
    return CATALOG;
}


int main(){
    char menu_item;
    int i, j;
    struct BOOK *CATALOG=NULL;
    int flag1=0;/*проверка создан ли масссив*/
    int flag2=0;/*проверка введены ли данные*/
    int flag3=0;/*проверка найдены ли нужные авторы*/
    int amount_books = 0;
    int amount_authors = 0;
    char *author_name = NULL;
    int *amount_sort_books = NULL;


    do{
        switch(menu_item=menu()){
            case '1':{
                CLS;
                if(flag1==1){
                    flag1 = 0;
                    flag2 = 0;
                    free(CATALOG);
                    CATALOG=NULL;
                }
                CATALOG = file_input(CATALOG, &amount_books);
                if (CATALOG != NULL){
                    flag1=1;
                    flag2=1;
                }
                pause;
                CLS;
                break;
            }

            case '2':{
                CLS;
                if (flag1==1){
                    flag1=0;
                    flag2=0;
                    free(CATALOG);
                    CATALOG=NULL;
                }
                puts("Input amount of books:");
                scanf("%d", amount_books);
                pause;
                if(amount_books>0)
                    CATALOG = malloc(amount_books * sizeof(struct BOOK));
                CLS;
                if(CATALOG!=NULL){
                    flag1=1;
                    flag2=1;
                    for (i = 0;i<amount_books;i++){
                        printf("Book num.%d\n",i+1);
                        printf("Name: ");
                        fgets(CATALOG[i].Name, MAX_LEN, stdin);
                        CATALOG[i].Name[strlen(CATALOG[i].Name) - 1] = '\0';
                        printf("Publisher: ");
                        fgets(CATALOG[i].Publisher, MAX_LEN - 2, stdin);
                        CATALOG[i].Publisher[strlen(CATALOG[i].Publisher) - 1] = '\0';
                        printf("Year: ");
                        scanf("%d", &CATALOG[i].Year);
                        getchar();
                        printf("Price: ");
                        scanf("%f", &CATALOG[i].Price);
                        getchar();
                        puts("Enter amount of authors(1 to 3):");
                        scanf("%d", &amount_authors);
                        for (j = 0; j < amount_authors; j++){
                            printf("Author num.%d:",j+1);
                            fgets(CATALOG[i].Authors[j], MAX_LEN, stdin);
                            CATALOG[i].Authors[j][strlen(CATALOG[i].Authors[j]) - 1] = '\0';
                        }
                        for (j = amount_authors; j < 4; j++)
                            CATALOG[i].Authors[j][0] = '\0';
                        puts("");
                    }
                    catalog_sort(CATALOG, &amount_books);
                }
                else
                    puts("Memory allocation failure.");
                pause;
                CLS;
                break;
            }

            case '3':
                CLS;
                printf("%30s %20s %6s %10s %20s\n","Name","Publisher","Year","Price","Authors");
                for (i = 0; i < amount_books; i++){
                    printf("%30s %20s %7d %11.2f %20s\n",
                    CATALOG[i].Name,CATALOG[i].Publisher,CATALOG[i].Year,CATALOG[i].Price,CATALOG[i].Authors[0]);
                    for (j = 1; j < 4; j++){
                        if (CATALOG[i].Authors[j][0] != '\0')
                            printf("%30s %20s %7s %11s %20s \n", "", "", "", "",CATALOG[i].Authors[j]);
                        }
                        puts("");
                }
                pause;
                CLS;
                break;


            case '4':
                CLS;
                if (flag2==1){
                    puts("Enter Author:");
                    author_name=str_reader();
                    amount_sort_books=malloc(amount_books * sizeof(int));
                    if(amount_sort_books!=NULL){
                        for (i = 0; i < amount_books; i++)
                            amount_sort_books[i]=0;

                        for (i = 0; i < amount_books; i++){
                            for(j=0;CATALOG[i].Authors[j][0]!='\0';j++){
                                if (strcmp(CATALOG[i].Authors[j], author_name) == 0){
                                    amount_sort_books[i] = 1;
                                    flag3=1;
                                }
                            }
                        }
                        if(flag3==1){
                            flag3=0;
                            printf("Result:");
                            puts("");
                            printf("%30s %20s %6s %10s %20s\n","Name","Publisher","Year","Price","Authors");
                            for (i = 0; i < amount_books; i++){
                                if (amount_sort_books[i] == 1){
                                    printf("%30s %20s %7d %11.2f %20s\n",
                                            CATALOG[i].Name,CATALOG[i].Publisher,CATALOG[i].Year,CATALOG[i].Price,CATALOG[i].Authors[0]);
                                    for (j = 1; j < 4; j++){
                                        if (CATALOG[i].Authors[j][0] != '\0')
                                            printf("%30s %20s %7s %11s %20s \n", "", "", "", "", CATALOG[i].Authors[j]);
                                    }
                                    puts("");

                                }
                            }
                        }
                        else puts("Books not found.");
                        free(amount_sort_books);
                    }else puts("Memory allocation failure.");
                }else puts("Enter initial data.");
                pause;
                CLS;
                break;

            case '0':{
                if (flag1 == 1)
                    free(CATALOG);
                CLS;
                break;
            }

            default:{
                CLS;
                puts("Wrong menu item.");
                puts("Try again.");
                pause;
                CLS;
                break;
            }
        }
    }while(menu_item!='0');
    return 0;
}

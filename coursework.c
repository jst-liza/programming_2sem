#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>


int menu();
int menu_input();
int menu_output();

void help();
void system_pause();
void text_free(char**text, int amount_of_str);
void text_output_doc(char **text, int count_str);
void text_output_console(char** text, int amount_of_str, int output_type);

char** text_input_console(int* amount_of_str);
char* word_or_str_input(int flag);
char** new_text_gen(char** text, char* word,char* new_str, int amount_of_str);
char** text_input_doc(int* amount_of_str);


int main(){

    setlocale(LC_ALL, "RUS");

    int menu_item, menu_doc_or_console, output_type, amount_of_str = 0;
    int flag_text = 0, flag_new_text = 0, flag_word_or_str = 0, flag_change;

    char **raw_text = NULL;
    char **new_text = NULL;
    char *word = NULL;
    char *new_str = NULL;

    do{
        fflush(stdin);
        menu_item = menu();
        fflush(stdin);
        system("cls");

    switch(menu_item){

        case 1:

                        if (raw_text!= NULL)
                            text_free(raw_text, amount_of_str);
                        menu_doc_or_console = menu_input();
                        if ((menu_doc_or_console == '1') || (menu_doc_or_console == '2')){
                           if (menu_doc_or_console == '1'){
                                raw_text = text_input_console(&amount_of_str);
                                    flag_text = 1;
                                    flag_new_text = 0;
                            }
                            else{
                                raw_text = text_input_doc(&amount_of_str);
                                    if (raw_text != NULL){
                                        flag_text = 1;
                                        flag_new_text = 0;
                                    }
                            }
                        }
                        system_pause();
                        break;

        case 2:
                        if (flag_text == 0){
                            puts(" _________________________________________________________");
                            puts("|   ������! ������� ������� �����, ������ 1 ����� ����    |");
                            puts("|_________________________________________________________|");
                        }
                        else{
                            output_type = 1;
                            text_output_console(raw_text, amount_of_str, output_type);
                        }
                        system_pause();
                        break;

        case 3:
                        if (word != NULL){
                            puts(" _________________________________________________________");
                            puts("|                    �������� �����:                      |");
                            puts("|_________________________________________________________|");;
                            puts(word);
                            puts("");
                            puts(" _________________________________________________________");
                            puts("|    ���� ������ �������� �������� �����, ������� 1       |");
                            puts("|_________________________________________________________|");
                            flag_change = getchar();
                            fflush(stdin);
                        }
                        if ((word == NULL)||(flag_change == '1')){
                            puts(" _________________________________________________________");
                            puts("|               ������� �������� �����:                   |");
                            puts("|_________________________________________________________|");
                            if(flag_change == '1'){
                                free(word);
                                word = NULL;
                            }
                            flag_word_or_str = 0;
                            flag_new_text = 0;
                            word = word_or_str_input(flag_word_or_str);
                        }
                        system_pause();
                        break;

        case 4:
                        if (new_str != NULL){
                            puts(" _________________________________________________________");
                            puts("|                   �������� ������:                      |");
                            puts("|_________________________________________________________|");;
                            puts(new_str);
                            puts("");
                            puts(" _________________________________________________________");
                            puts("|    ���� ������ �������� �������� ������, ������� 1      |");
                            puts("|_________________________________________________________|");
                            flag_change = getchar();
                            fflush(stdin);
                        }
                        if ((new_str == NULL)||(flag_change == '1')){
                            puts(" _________________________________________________________");
                            puts("|               ������� �������� ������:                  |");
                            puts("|_________________________________________________________|");
                            if(flag_change == '1'){
                                free (new_str);
                                new_str = NULL;
                            }
                            flag_word_or_str = 1;
                            flag_new_text = 0;
                            new_str = word_or_str_input(flag_word_or_str);
                            }
                        system_pause();
                        break;

        case 5:
                        if (flag_text == 0){
                            puts(" _________________________________________________________");
                            puts("|   ������! ������� ������� �����, ������ 1 ����� ����    |");
                            puts("|_________________________________________________________|");
                        }
                        else{
                            if (new_text != NULL)
                                text_free(new_text, amount_of_str);
                            if ((new_str != NULL)&&(word != NULL)){
                                new_text = new_text_gen(raw_text, word, new_str, amount_of_str);
                                flag_new_text = 1;
                            puts(" _________________________________________________________");
                            puts("|           ����� ����� ��� ������� �����������           |");
                            puts("|_________________________________________________________|");
                            }
                            else{
                                puts(" _________________________________________________________");
                                puts("|   ������! ��������� ������� ��������� ����� � ������    |");
                                puts("|_________________________________________________________|");
                            }
                        }
                        system_pause();
                        break;

        case 6:
                        if (flag_new_text == 0){
                            puts(" _________________________________________________________");
                            puts("|        ������! ������� ����������� ����� �����         |");
                            puts("|_________________________________________________________|");
                        }
                        else{
                            menu_doc_or_console = menu_output();
                            if ((menu_doc_or_console == '1') || (menu_doc_or_console == '2')){
                                if (menu_doc_or_console == '1'){
                                    output_type = 2;
                                    text_output_console(new_text, amount_of_str, output_type);
                                }
                                else
                                    text_output_doc(new_text, amount_of_str);
                            }
                        }
                        system_pause();
                        break;

        case 7:
                        help();
                        system_pause();
                        break;

        case 0:
                        if (raw_text!= NULL)
                            text_free(raw_text, amount_of_str);
                        if (new_text != NULL)
                            text_free(new_text, amount_of_str);
                        if (word != NULL)
                            free(word);
                        if (new_str != NULL)
                            free(new_str);
                        system_pause();
                        break;
        default:
                        puts(" _________________________________________________________");
                        puts("|           ������! ������� ����� ���� ������             |");
                        puts("|_________________________________________________________|");
                        system_pause();
        }
    }while(menu_item != 0);
}


int menu(){
    int menu_item;

    puts(" _________________________________________________________");
    puts("|                        ����                             |");
    puts("|---------------------------------------------------------|");
    puts("| 1 | ������ �������� �����                               |");
    puts("|---------------------------------------------------------|");
    puts("| 2 | �������� �������� �����                             |");
    puts("|---------------------------------------------------------|");
    puts("| 3 | ������ / �������� /�������� �������� �����          |");
    puts("|---------------------------------------------------------|");
    puts("| 4 | ������ / �������� /�������� �������� ������         |");
    puts("|---------------------------------------------------------|");
    puts("| 5 | ������������ ����� �����                            |");
    puts("|---------------------------------------------------------|");
    puts("| 6 | �������� ����� �����                                |");
    puts("|---------------------------------------------------------|");
    puts("| 7 | ������ � ������ � ����������                        |");
    puts("|---------------------------------------------------------|");
    puts("| 0 | ��������� ���������                                 |");
    puts("|_________________________________________________________|");
    puts("");
    printf("   ��������� ����:  ");
    scanf("%d", &menu_item);
    return menu_item;

}


int menu_input(){
    int doc_or_console;

    puts(" _________________________________________________________");
    puts("|               �������� ������ ����� ������.             |");
    puts("|         ��� ������� ����� ����� ������� ������� 1.      |");
    puts("|         ��� ���������� ������ �� ����� �������  2.      |");
    puts("|_________________________________________________________|");
    puts("");
    doc_or_console = getchar();
    puts("");
    fflush(stdin);
    if(doc_or_console == '1' || doc_or_console =='2')
        return doc_or_console;
    else{
        puts(" _________________________________________________________");
        puts("|        ������! ������������ ����� ������� �����.        |");
        puts("|_________________________________________________________|");
        return 0;
    }
}


int menu_output(){
    int doc_or_console;

    puts(" _________________________________________________________");
    puts("|              �������� ������ ������ ������.             |");
    puts("|            ��� ������ ����� ������� ������� 1.          |");
    puts("|          ��� ������ ������ ����� ���� �������  2.       |");
    puts("|_________________________________________________________|");
    puts("");
    doc_or_console = getchar();
    puts("");
    fflush(stdin);
    if(doc_or_console == '1' || doc_or_console =='2')
        return doc_or_console;
    else{
        puts(" _________________________________________________________");
        puts("|        ������! ������������ ����� ������� ������.       |");
        puts("|_________________________________________________________|");
        return 0;
    }
}


void system_pause(){
    puts("\n");
    system("pause");
    system("cls");
}


void help(){

    puts(" _________________________________________________________");
    puts("|               ������ � ������ � ����������:             |");
    puts("|---------------------------------------------------------|");
    puts("| 1 | ������� ��������� ������, ��������� �������������   |");
    puts("| ��������� ���������.                                    |");
    puts("|---------------------------------------------------------|");
    puts("| 2 | ��� ����������� ����� ��������� ������ �����        |");
    puts("| ������� ������ ������� ENTER.                           |");
    puts("|---------------------------------------------------------|");
    puts("| 3 | ��� ����� ������ � �����, ������������� ��� ������  |");
    puts("| ������ ����� ������. ��� ���������� ��� �����������     |");
    puts("| ����� �������� ������.                                  |");
    puts("|---------------------------------------------------------|");
    puts("| 4 | ���� ���������� ������ ������ � ������, ��          |");
    puts("| ����������� ���� ��� ������.                            |");
    puts("|---------------------------------------------------------|");
    puts("| 5 | ������������ ����� ����� ������ - 80 ��������.      |");
    puts("| ������ �����������, ��� ������ ������� ����� ��������.  |");
    puts("|---------------------------------------------------------|");
    puts("| 6 | ������� ������ ���� ����������� ����� / ������.     |");
    puts("|---------------------------------------------------------|");
    puts("| 7 | ������ ����������� ��� ����� �������� �����,        |");
    puts("| ��������� ������������� � �������.                      |");
    puts("|---------------------------------------------------------|");
    puts("| 8 | ����������� �����: ���� - default_intput.txt        |");
    puts("|                        ����� - default_output.txt       |");
    puts("|_________________________________________________________|");
}


void text_output_console(char** text, int amount_of_str, int flag_type){

    int i, j;

    if(flag_type == 1){
        puts(" _________________________________________________________");
        puts("|                   �������� �����:                       |");
        puts("|_________________________________________________________|");
        puts("");
    }
    else{
        puts(" _________________________________________________________");
        puts("|               �������������� �����:                     |");
        puts("|_________________________________________________________|");
        puts("");
    }

    for(i = 0; i < amount_of_str; i ++){
        for(j = 0; j < strlen(*(text+i)); j ++)
            printf("%c", *(*(text+i)+j));
        printf("\n");
    }
}


void text_output_doc(char **text, int amount_of_str){

    char* way = NULL;
    int i;
    int w;
    char flag_choice;
    FILE *doc;

    system("cls");
    puts(" _________________________________________________________");
    puts("|        �������� ����, ��� ������ �������� ������        |");
    puts("|  ������� 1, ����� ������������ ����������� ���� ������  |");
    puts("|  ������� ����� ������, ����� ������� ������ � ��������  |");
    puts("|  ����                                                   |");
    puts("|_________________________________________________________|");
    flag_choice = getchar();
    puts("");

    if (flag_choice == '1'){
        doc=fopen("default_output.txt", "w");
    }
    else{
        puts(" _________________________________________________________");
        puts("|     ������� �������� �����, ������������ � ����� �      |");
        puts("| ���������� ���� ������� ���������� ������������ �����   |");
        puts("|_________________________________________________________|");
        fflush(stdin);
        for(int n = 0; w!=1; n ++){
            way =(char*)realloc(way, (n+1)*sizeof(char));
            *(way+n) = getchar();
            if(*(way+n) == '\n') {
                w = 1;
                way[n] = '\0';
            }
        }
        doc = fopen(way, "w");
    }
    if (doc == NULL){
        puts(" _________________________________________________________");
        puts("|          ������! ��������� �������� ���������          |");
        puts("|_________________________________________________________|");
    }
    else{
        for (i = 0; i < amount_of_str; i++)
            fprintf(doc, "%s\n", text[i]);
        fclose(doc);
        puts(" _________________________________________________________");
        puts("|          �������������� ����� ������� � ����            |");
        puts("|_________________________________________________________|");
    }
}

void text_free(char** text, int amount_of_str){

    int i;

    for (i = 0; i < amount_of_str; i ++)
        free (text[i]);
    free(text);
    text = NULL;
}


char** text_input_console(int* amount_of_str){

    char** text = NULL;
    int i, j;
    int w, v;
    char s[81];

    puts(" _________________________________________________________");
    puts("|                    ������� �����:                       |");
    puts("|_________________________________________________________|");

    v = 0;
    for(i = 0; v != 1; i++){
        w = 0;
        for(j = 0; w != 1; j++){
            s[j] = getchar();
            if(s[j] == '\n'){
                w = 1;
                s[j] = '\0';
            }
            if(s[0] == '\0')
                v = 1;
            if(j == 79){
                w = 1;
                s[80] = '\0';
            }
        }
        text = (char**)realloc(text,(i+1)*sizeof(char*));
        text[i] = (char*) malloc((strlen(s)+1)*sizeof(char));
        strcpy(text[i], s);
        for(j = 0; j < strlen(s); j++)
            s[j] = 0;
    }
    *amount_of_str = i;
    return text;
}


char** text_input_doc(int *amount_of_str){

    char** text = NULL;
    char* way = NULL;
    int i, j;
    int w, v;
    char s[81], flag_choice;
    FILE *doc;

    system("cls");
    puts(" _________________________________________________________");
    puts("|        �������� ����, ��� ����� �������� ������         |");
    puts("|  ������� 1, ����� ������������ ����������� ���� �����   |");
    puts("|  ������� ����� ������, ����� ������ ������ �� ��������� |");
    puts("|  �����                                                  |");
    puts("|_________________________________________________________|");
    flag_choice = getchar();
    puts("");

    if (flag_choice == '1'){
        doc=fopen("default_input.txt","r");
    }
    else{
        puts(" _________________________________________________________");
        puts("|     ������� �������� �����, ������������ � ����� �      |");
        puts("| ���������� ���� ������� ���������� ������������ �����   |");
        puts("|_________________________________________________________|");
        fflush(stdin);
        for(int n = 0; w!=1; n ++){
            way =(char*)realloc(way, (n+1)*sizeof(char));
            *(way+n) = getchar();
            if(*(way+n) == '\n') {
                w = 1;
                way[n] = '\0';
            }
        }
        doc = fopen(way, "r");
    }
    if (doc == NULL){
        puts(" _________________________________________________________");
        puts("|          ������! ��������� �������� ���������          |");
        puts("|_________________________________________________________|");
        return NULL;
    }
    else{
        v = 0;
        for(i = 0; v != 1; i++){
            w = 0;
            for(j = 0; w != 1; j++){
                s[j] = fgetc(doc);
                if(s[j] == '\n'){
                    w = 1;
                    s[j] = '\0';
                }
                if(s[0] == '\0' || (s[0] == '\n'))
                    v = 1;
                if(j == 79){
                    w = 1;
                    s[80] = '\0';
                }
            }
            text = (char**)realloc(text,(i+1)*sizeof(char*));
            text[i] = (char*) malloc((strlen(s)+1)*sizeof(char));
            strcpy(text[i], s);
            for(j = 0; j < strlen(s); j++)
                s[j] = 0;

        }
        *amount_of_str = i;
        fclose (doc);
        if (text != NULL){
            puts(" _________________________________________________________");
            puts("|                 ����� ������� ������                    |");
            puts("|_________________________________________________________|");
            return text;
        }
    }
}


char* word_or_str_input(int flag){

    char* current_word = NULL;
    int n, w;

    n = 0;
    w = 0;
    for(n = 0; w != 1; n ++){
        current_word =(char*)realloc(current_word, (n+1)*sizeof(char));
        *(current_word+n) = getchar();
        if (flag == 0){
            if((*(current_word+n) == ' ') || (*(current_word+n) == '\n')) {
                w = 1;
                current_word[n] = '\0';
            }
        }
        else{
            if(*(current_word+n) == '\n'){
                w = 1;
                current_word[n] = '\0';
            }
        }
    }
    return current_word;
}


char** new_text_gen(char** text, char* word, char* new_str, int amount_of_str){

    int match;
    int i, j;
    int finder;
    char** newtext = NULL;

    for(i = 0; i < amount_of_str; i ++){
        match = 0;
        finder = 0;
        for(j = 0; ((j < strlen(*(text+i))) && (finder != 1)); j ++){
            if (text[i][j] == word[match]){
                match++;
                if(match == strlen(word))
                    finder = 1;
            }
            else
                match = 0;
        }
        if (finder == 1){
            newtext = (char**)realloc(newtext,(i+1)*sizeof(char*));
            newtext[i] = (char*)malloc((strlen(new_str)+1)*sizeof(char));
            strcpy(newtext[i], new_str);
        }
        else{
            newtext = (char**)realloc(newtext,(i+1)*sizeof(char*));
            newtext[i] = (char*)malloc((strlen(new_str)+1)*sizeof(char));
            strcpy(newtext[i], text[i]);
        }
    }
    return newtext;
}

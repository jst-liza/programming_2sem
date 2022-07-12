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
                            puts("|   Ошибка! Сначала введите текст, выбрав 1 пункт меню    |");
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
                            puts("|                    Ключевое слово:                      |");
                            puts("|_________________________________________________________|");;
                            puts(word);
                            puts("");
                            puts(" _________________________________________________________");
                            puts("|    Если хотите заменить ключевое слово, введите 1       |");
                            puts("|_________________________________________________________|");
                            flag_change = getchar();
                            fflush(stdin);
                        }
                        if ((word == NULL)||(flag_change == '1')){
                            puts(" _________________________________________________________");
                            puts("|               Введите ключевое слово:                   |");
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
                            puts("|                   Ключевая строка:                      |");
                            puts("|_________________________________________________________|");;
                            puts(new_str);
                            puts("");
                            puts(" _________________________________________________________");
                            puts("|    Если хотите заменить ключевую строку, введите 1      |");
                            puts("|_________________________________________________________|");
                            flag_change = getchar();
                            fflush(stdin);
                        }
                        if ((new_str == NULL)||(flag_change == '1')){
                            puts(" _________________________________________________________");
                            puts("|               Введите ключевую строку:                  |");
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
                            puts("|   Ошибка! Сначала введите текст, выбрав 1 пункт меню    |");
                            puts("|_________________________________________________________|");
                        }
                        else{
                            if (new_text != NULL)
                                text_free(new_text, amount_of_str);
                            if ((new_str != NULL)&&(word != NULL)){
                                new_text = new_text_gen(raw_text, word, new_str, amount_of_str);
                                flag_new_text = 1;
                            puts(" _________________________________________________________");
                            puts("|           Новый текст был успешно сформирован           |");
                            puts("|_________________________________________________________|");
                            }
                            else{
                                puts(" _________________________________________________________");
                                puts("|   Ошибка! Проверьте наличие ключевого слова и строки    |");
                                puts("|_________________________________________________________|");
                            }
                        }
                        system_pause();
                        break;

        case 6:
                        if (flag_new_text == 0){
                            puts(" _________________________________________________________");
                            puts("|        Ошибка! Сначала сформируйте новый текст         |");
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
                        puts("|           Ошибка! Введите пункт меню заново             |");
                        puts("|_________________________________________________________|");
                        system_pause();
        }
    }while(menu_item != 0);
}


int menu(){
    int menu_item;

    puts(" _________________________________________________________");
    puts("|                        Меню                             |");
    puts("|---------------------------------------------------------|");
    puts("| 1 | Ввести исходный текст                               |");
    puts("|---------------------------------------------------------|");
    puts("| 2 | Показать исходный текст                             |");
    puts("|---------------------------------------------------------|");
    puts("| 3 | Ввести / Показать /Заменить ключевое слово          |");
    puts("|---------------------------------------------------------|");
    puts("| 4 | Ввести / Показать /Заменить ключевую строку         |");
    puts("|---------------------------------------------------------|");
    puts("| 5 | Сформировать новый текст                            |");
    puts("|---------------------------------------------------------|");
    puts("| 6 | Показать новый текст                                |");
    puts("|---------------------------------------------------------|");
    puts("| 7 | Помощь в работе с программой                        |");
    puts("|---------------------------------------------------------|");
    puts("| 0 | Завершить программу                                 |");
    puts("|_________________________________________________________|");
    puts("");
    printf("   Выбранный пукт:  ");
    scanf("%d", &menu_item);
    return menu_item;

}


int menu_input(){
    int doc_or_console;

    puts(" _________________________________________________________");
    puts("|               Выберите способ ввода текста.             |");
    puts("|         Для ручного ввода через консоль нажмите 1.      |");
    puts("|         Для считывания текста из файла нажмите  2.      |");
    puts("|_________________________________________________________|");
    puts("");
    doc_or_console = getchar();
    puts("");
    fflush(stdin);
    if(doc_or_console == '1' || doc_or_console =='2')
        return doc_or_console;
    else{
        puts(" _________________________________________________________");
        puts("|        Ошибка! Некорректный выбор способа ввода.        |");
        puts("|_________________________________________________________|");
        return 0;
    }
}


int menu_output(){
    int doc_or_console;

    puts(" _________________________________________________________");
    puts("|              Выберите способ вывода текста.             |");
    puts("|            Для вывода через консоль нажмите 1.          |");
    puts("|          Для вывода текста через файл нажмите  2.       |");
    puts("|_________________________________________________________|");
    puts("");
    doc_or_console = getchar();
    puts("");
    fflush(stdin);
    if(doc_or_console == '1' || doc_or_console =='2')
        return doc_or_console;
    else{
        puts(" _________________________________________________________");
        puts("|        Ошибка! Некорректный выбор способа вывода.       |");
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
    puts("|               Помощь в работе с программой:             |");
    puts("|---------------------------------------------------------|");
    puts("| 1 | Вводите текстовые данные, используя исключительно   |");
    puts("| латинскую раскладку.                                    |");
    puts("|---------------------------------------------------------|");
    puts("| 2 | Для прекращения ввода текстовых данных через        |");
    puts("| консоль дважды нажмите ENTER.                           |");
    puts("|---------------------------------------------------------|");
    puts("| 3 | При вводе данных с файла, предусмотрите две пустые  |");
    puts("| строки после текста. Они необходимы для корректного     |");
    puts("| ввода исходных данных.                                  |");
    puts("|---------------------------------------------------------|");
    puts("| 4 | Если необходимы пустые строки в тексте, то          |");
    puts("| используйте один раз пробел.                            |");
    puts("|---------------------------------------------------------|");
    puts("| 5 | Максимальная длина одной строки - 80 символов.      |");
    puts("| Будьте внимательны, все лишние символы будут обрезаны.  |");
    puts("|---------------------------------------------------------|");
    puts("| 6 | Вводите только одно контрольное слово / строку.     |");
    puts("|---------------------------------------------------------|");
    puts("| 7 | Будьте внимательны при вводе кодового слова,        |");
    puts("| программа чувствительна к регисту.                      |");
    puts("|---------------------------------------------------------|");
    puts("| 8 | Стандартные файлы: ввод - default_intput.txt        |");
    puts("|                        вывод - default_output.txt       |");
    puts("|_________________________________________________________|");
}


void text_output_console(char** text, int amount_of_str, int flag_type){

    int i, j;

    if(flag_type == 1){
        puts(" _________________________________________________________");
        puts("|                   Исходный текст:                       |");
        puts("|_________________________________________________________|");
        puts("");
    }
    else{
        puts(" _________________________________________________________");
        puts("|               Сформированный текст:                     |");
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
    puts("|        Выберете файл, для вывода исходных данных        |");
    puts("|  Введите 1, чтобы использовать стандартный файл вывода  |");
    puts("|  Нажмите любую кнопку, чтобы вывести данные в заданный  |");
    puts("|  файл                                                   |");
    puts("|_________________________________________________________|");
    flag_choice = getchar();
    puts("");

    if (flag_choice == '1'){
        doc=fopen("default_output.txt", "w");
    }
    else{
        puts(" _________________________________________________________");
        puts("|     Укажите название файла, находящегося в папке с      |");
        puts("| программой либо введите директорию необходимого файла   |");
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
        puts("|          Ошибка! Проверьте введённые параметры          |");
        puts("|_________________________________________________________|");
    }
    else{
        for (i = 0; i < amount_of_str; i++)
            fprintf(doc, "%s\n", text[i]);
        fclose(doc);
        puts(" _________________________________________________________");
        puts("|          Сформированный текст записан в файл            |");
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
    puts("|                    Введите текст:                       |");
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
    puts("|        Выберете файл, для ввода исходных данных         |");
    puts("|  Введите 1, чтобы использовать стандартный файл ввода   |");
    puts("|  Нажмите любую кнопку, чтобы ввести данные из заданного |");
    puts("|  файла                                                  |");
    puts("|_________________________________________________________|");
    flag_choice = getchar();
    puts("");

    if (flag_choice == '1'){
        doc=fopen("default_input.txt","r");
    }
    else{
        puts(" _________________________________________________________");
        puts("|     Укажите название файла, находящегося в папке с      |");
        puts("| программой либо введите директорию необходимого файла   |");
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
        puts("|          Ошибка! Проверьте введённые параметры          |");
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
            puts("|                 Текст успешно считан                    |");
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

#include<stdio.h>

int main(){
    long int raw_num;
    long int result_num;
    int shift,i;
    puts("Implementing a cyclic right shift for an integer");
    shift = shift % (sizeof(shift)*8);
    puts("Enter number:");
    scanf("%ld", &raw_num);
    puts("Number of positions to shift:");
    scanf("%d", &shift);
    if (shift >0){
        if (raw_num >= 0){
                result_num = (raw_num>>shift)|(raw_num<<(sizeof(raw_num)*8-shift));
            }
        else{
            result_num = (raw_num>>shift)&(raw_num>>(sizeof(raw_num)*8-shift));
            for (i = 0; i<shift; i++)
                    result_num = (result_num | (0>>i));
            }
            puts("\nNew num 10's base:");
            printf("%ld", result_num);
            puts("\nOld num 2's base:");
            for(i=(sizeof(raw_num)*8 - 1);i>=0;i--)
                printf("%d",(raw_num>>i)&(0x1));
            puts("\nNew num 2's base:");
            for(i=(sizeof(raw_num)*8 - 1);i>=0;i--)
                printf("%d",(result_num>>i)&(0x1));
        }
        else puts("Number should be positive");
    return 0;
}

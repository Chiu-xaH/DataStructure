/*
有1对小兔子，从第3个月开始，每月可生1对兔子。
新生兔子生产规律类似，
问：第3年每个月的兔子总数为多少？
*/
#include <stdio.h>

typedef struct {
    int BigRubbit;
    int MiddleRubbit;
    int SmallRubbit;
    int TotalRubbit;
} Rubbit;

void BearRubbit(Rubbit rubbit,int month) {
    if(month >= 1 && month <= 8) {
        //打印
        printf("month %d have %d\n",month,rubbit.TotalRubbit);
    }
    if(month <= 36) {
        rubbit.BigRubbit += rubbit.MiddleRubbit;
        rubbit.MiddleRubbit = rubbit.SmallRubbit;
        rubbit.SmallRubbit = rubbit.BigRubbit;
        rubbit.TotalRubbit = rubbit.BigRubbit + rubbit.MiddleRubbit + rubbit.SmallRubbit;
        month++;
        BearRubbit(rubbit,month);
    }
}

int main() {
    Rubbit rubbit;
    rubbit.BigRubbit = 0;
    rubbit.MiddleRubbit = 0;
    rubbit.SmallRubbit = 2;
    rubbit.TotalRubbit = 2;

    BearRubbit(rubbit,1);
}
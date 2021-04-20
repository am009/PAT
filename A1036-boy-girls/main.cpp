// 又是简单的最值

#include <cstdio>

struct Stu {
    bool absent;
    char name[15];
    char gender;
    char ID[15];
    int grade;
};

int main () {
    int count;
    scanf("%d", &count);
    struct Stu maxF, minM, tmp;
    maxF.absent = true;
    minM.absent = true;
    tmp.absent = false;
    while(count --){ 
        scanf("%s %c %s %d", tmp.name, &tmp.gender, tmp.ID, &tmp.grade);
        if (tmp.gender == 'M' && minM.absent) {
            minM = tmp;
            continue;
        }
        if (tmp.gender == 'F' && maxF.absent) {
            maxF = tmp;
            continue;
        }
        if (tmp.gender == 'M') {
            if (tmp.grade < minM.grade){
                minM = tmp;
            }
        }
        if (tmp.gender == 'F') {
            if (tmp.grade > maxF.grade){
                maxF = tmp;
            }
        }
    }
    // output --------
    if (maxF.absent) {
        printf("Absent");
    } else {
        printf("%s %s", maxF.name, maxF.ID);
    }
    if (minM.absent) {
        printf("\nAbsent");
    } else {
        printf("\n%s %s", minM.name, minM.ID);
    }
    if (minM.absent || maxF.absent) {
        printf("\nNA");
    } else {
        printf("\n%d", maxF.grade - minM.grade);
    }
}
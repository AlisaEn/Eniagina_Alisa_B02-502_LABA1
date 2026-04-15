#include <iostream>
using namespace std;
struct date_time{ //Можем указывать кол-во отводимых бит на каждый эл-т;
    unsigned day: 5;
    unsigned month :4;
    unsigned year : 12;
    unsigned hour : 5;
    unsigned min : 6;
    unsigned sec : 6;
};

int main(){
    struct date_time dt = {3, 5, 2023, 11, 7, 10};
    printf("%d\n", sizeof(dt));
    printf("%02d/%02d/%d %02d:%02d:%02d\n", dt.day, dt.month, dt.year, dt.hour, dt.min, dt.sec);
    return 0;
};
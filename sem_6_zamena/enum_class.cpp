#include <iostream>
using namespace std;

enum class weekday_t {Mon, Tue, Wed, Thu, Fri, Sut, Sun};
void print_wd(weekday_t day){
    switch(day){
        case weekday_t::Mon : cout<<"Monday"<<endl; break;
        case weekday_t::Tue : cout<<"Tuesday"<<endl; break;
        case weekday_t::Wed : cout<<"Wednesday"<<endl; break;
        case weekday_t::Thu : cout<<"Thursday"<<endl; break;
        case weekday_t::Fri : cout<<"Friday"<<endl; break;
        case weekday_t::Sut : cout<<"Suturday"<<endl; break;
        case weekday_t::Sun : cout<<"Sunday"<<endl; break;
    
    }
}
weekday_t next_day(weekday_t day){
    if(day==weekday_t::Sun) return weekday_t::Mon;
    return static_cast<weekday_t>(static_cast<int>(day)+1);
}
int main(){
    int temp;
    weekday_t today;
    cin>>temp;
    today = static_cast<weekday_t>(temp-1);
    print_wd(today);
    print_wd(next_day(today));
    return 0;
}
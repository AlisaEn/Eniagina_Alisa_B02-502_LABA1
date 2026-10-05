#include <iostream>
#include <algorithm>
#include <random>
using namespace std;
//Задание 1 Рефакторинг
class WithRoll{
public:
    virtual unsigned roll() = 0;
    virtual ~WithRoll() = default;
};
class Dice: public WithRoll {
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
public:
    Dice(unsigned max, unsigned seed):max(max), dstr(1, max), reng(seed) {}
    unsigned roll() override{
        return dstr(reng);
    }
};

class ThreeDicePool: public WithRoll{
    WithRoll& r1, &r2, &r3;
public:
    ThreeDicePool(WithRoll& r1, WithRoll& r2, WithRoll& r3): r1(r1), r2(r2), r3(r3){}
    unsigned roll() override{
        return(r1.roll()+r2.roll()+r3.roll());
    }
};

double expected_value(WithRoll &r, unsigned number_of_rolls){
    unsigned res = 0;
    for(unsigned i = 0; i<number_of_rolls; i++){
        res+=r.roll();
    }
    return static_cast<double>(res)/number_of_rolls;
}
//Задание 2 Штрафы и преимущества
class PenaltyDice:public virtual WithRoll{
    WithRoll &r;
public:
    PenaltyDice(WithRoll &r): r(r){}
    unsigned roll() override{
        unsigned answ1 = r.roll();
        unsigned answ2 = r.roll();
        return min(answ1, answ2);
    }
};
class BonusDice: public virtual WithRoll{
    WithRoll &r;
public:
    BonusDice(WithRoll &r): r(r){}
    unsigned roll() override{
        unsigned answ1 = r.roll();
        unsigned answ2 = r.roll();
        return max(answ1, answ2);
    }
};
double value_probability(unsigned value, WithRoll &d, unsigned number_of_rolls = 1){ //в процентах
    unsigned count = 0;
    for (unsigned i=0; i<number_of_rolls; i++){
        if (d.roll()==value) count++;
    }
    return static_cast<double>(count*100)/number_of_rolls;
}
void print_probability(WithRoll &r, string name, unsigned max, unsigned n){ //n = number_of_rolls
    cout<<"probability for " <<name<<", number_of_rolls = "<<n<<endl;
    cout<<'[';
    double summa = 0;
    for (unsigned i=1; i<max; i++){
        double p =value_probability(i, r, n);
        summa+=p;
        cout<<p<<", ";
    }
    cout<<value_probability(max, r, n)<<']'<<endl;
    cout<<"summ of probabilities = "<<summa<<"\n\n";
}

//Задание 3
class DoubleDice: public PenaltyDice, public BonusDice{
public:
    DoubleDice(Dice &dice): PenaltyDice(dice), BonusDice(dice){}
    unsigned roll() override{
        return (this->PenaltyDice::roll()+this->BonusDice::roll());
    }
};
        //Без множественного наследования:
class SecondDoubleDice: public WithRoll{
    PenaltyDice penalty;
    BonusDice bonus;
public:
    SecondDoubleDice(Dice &dice): penalty(dice), bonus(dice){}
    unsigned roll() override{
        return (penalty.roll()+bonus.roll());
    }
};


int main(){
    //Задание 1
    Dice dice_6(6, 10), dice_100(100, 1), dice_2(2, 3);
    ThreeDicePool three_dice(dice_6, dice_100, dice_2);
    for(unsigned i = 0; i < 5; i++) cout<<dice_6.roll()<<" ";
    cout<<"\n";
   cout<<"expected_value(dice_6, 10000) ="<<expected_value(dice_6, 10000)<<endl;
    cout<<"expected_value(dice_100, 10000) ="<<expected_value(dice_100, 10000)<<endl;
    cout<<"expected_value(dice_2, 10000) ="<<expected_value(dice_2, 10000)<<endl;
    cout<<"expected_value(three_dice, 10000) ="<<expected_value(three_dice, 10000)<<endl;
    cout<<"\n\n";
    //Задание 2;
    PenaltyDice p100(dice_100);
    BonusDice b100(dice_100);
    Dice d2(6, 4), d3(6, 5);
    ThreeDicePool three_6(dice_6, d2,d3);
    print_probability(dice_100, "dice_100", 100, 100000);
    print_probability(p100, "p100", 100, 100000);
    print_probability(b100, "b100", 100, 100000);
    print_probability(three_6, "three_6", 18, 100000);

    //Задание 3
    DoubleDice double_dice_100(dice_100);
    SecondDoubleDice s_d_d_100(dice_100);
    cout<<"expected_value(double_dice_100, 100000) ="<<expected_value(double_dice_100, 100000)<<endl;
    cout<<"expected_value(s_d_d_100, 100000) ="<<expected_value(s_d_d_100, 100000)<<endl;
    print_probability(double_dice_100, "double_dice-100", 200, 100000);
    
    
    return 0;
}
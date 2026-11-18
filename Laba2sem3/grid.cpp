#include <iostream>
#include <cassert>
template<typename T>
class Grid final {
public:
    using value_type=T;
    using size_type =unsigned;
private:
    T* data = nullptr;
    size_type y_size=0;
    size_type x_size = 0;
    void copy_data(T* const other_data){ //if data is empty, size одинаковы
        for(size_type i = 0; i<x_size*y_size; i++){
            data[i] = other_data[i];
        }
    }
    void swap_g(Grid<T> &other) noexcept{ //перемещение
        std::swap(x_size, other.x_size);
        std::swap(y_size, other.y_size);
        std::swap(data, other.data);
    }
public:
    Grid(T*data, size_type y_size, size_type x_size): data(data), y_size(y_size), x_size(x_size) {}
    Grid(Grid<T> const & other){ //Копирующий конструктор
        if(other.data!= nullptr){
            y_size = other.y_size;
            x_size = other.x_size;
            data = new T[y_size*x_size];
            copy_data(other.data);
        }
    }
    Grid(Grid<T>&& other) noexcept { // Перемещающий конструктор
        swap_g(other);
    }
    Grid<T>&operator=(Grid<T> const &other){//Копирующий оператор
        if(this!=&other){
            Grid<T> tmp(other);
            swap_g(tmp);
        }
        return *this;
    } 
    Grid<T>&operator=(Grid<T>&& other) noexcept { //Оператор перемещения
        if(this!=&other){
            swap_g(other);
        }
        return *this;
    } 
    Grid(T const &t):  data(new T[1]), y_size(1), x_size(1){ //неявное преобразование типов
        data[0] = t;
    }
    //Далее второй и третий дополнительный конструкторы в одном
    Grid(size_type y_size, size_type x_size, T const &t = T{}): data(new T[y_size*x_size]), 
                                                                y_size(y_size), x_size(x_size){
        for(size_type i =0; i<y_size*x_size; i++){
            data[i] = t;
        }
    }

    const T operator()(size_type y_idx, size_type x_idx) const { 
        return data[y_idx * x_size +x_idx];
    }

    T&operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size +x_idx];
    }

    const T* operator[](size_type y_idx) const{
        return data+(y_idx * x_size);
    }
    T* operator[](size_type y_idx){
        return data+(y_idx * x_size);
    }
    Grid<T>&operator=(T const &t) {
        for ( auto it =data, end=data+x_size * y_size;it != end; ++it)*it = t;
        return *this;
    }
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
    T* get_data() const {return data;}
    ~Grid(){
        delete[] data;
    }
 
 };
 template<typename T>
void print_grid(Grid<T> const& g){
    if(std::is_arithmetic_v<T>){
        using gsize_t = Grid<int>::size_type;
        for(gsize_t y_idx = 0; y_idx<g.get_y_size(); ++y_idx){//Индексы без редактирования
            for(gsize_t x_idx = 0; x_idx<g.get_x_size(); ++x_idx){
                std::cout<<g[y_idx][x_idx]<<' ';
            }
            std::cout<<'\n';
        }
        std::cout<<'\n';
    }
    
}
int main(){
    Grid<float> g(3, 2, 0.0f); //конструктор по 3-м параметрам
    assert(3==g.get_y_size());
    assert(2==g.get_x_size());
    using gsize_t = Grid<int>::size_type;
    for(gsize_t y_idx = 0; y_idx<g.get_y_size(); ++y_idx){//Индексы без редактирования
        for(gsize_t x_idx = 0; x_idx<g.get_x_size(); ++x_idx){
            assert(0.0f==g[y_idx][x_idx]);
        }
    }
    for(gsize_t y_idx = 0; y_idx<g.get_y_size(); ++y_idx){ //индексы с редактированием
        for(gsize_t x_idx = 0; x_idx<g.get_x_size(); ++x_idx){
            g[y_idx][x_idx] =1.0f;
        }
    }
    for(gsize_t y_idx = 0; y_idx<g.get_y_size(); ++y_idx){
        for(gsize_t x_idx = 0; x_idx<g.get_x_size(); ++x_idx){
            assert(1.0f==g[y_idx][x_idx]);
        }
    }
    //std::cout<<"Everything is ok"<<std::endl;
    //Собственные тесты
    std::cout<<"конструктор с 2-мя параметрами"<<'\n';
    Grid<float> g2(2, 1); 
    print_grid(g2);
    std::cout<<"неявное преобразование типов"<<'\n';
    Grid<char> g3 = 'a';
    print_grid(g3);
    std::cout<<"конструктор копирования"<<'\n';
    Grid<float> g4 = g;
    print_grid(g4);
    std::cout<<"конструктор присваивания"<<'\n';
    Grid<char> g5 = std::move(g3);
    print_grid(g5);
    if(g3.get_data()==nullptr) {
        std::cout<<"g3 очищен -> конструктор присваивания работает корректно"<<std::endl;
    }
    std::cout<<"оператор копирования"<<'\n';
    g2 = g;
    print_grid(g2);
    std::cout<<"оператор перемещения"<<'\n';
    Grid<char> g6(2, 3, 'b');
    g5 = std::move(g6);
    print_grid(g5);
    print_grid(g6);
    return 0;

}
#include <iostream>
#include <cassert>
template<typename T, size_t N>
class Grid final {
public:
    using value_type=T;
    using size_type =unsigned;
    using SubGrid  = Grid<T, N-1>;
private:
    SubGrid* data = nullptr;
    size_type m_size=0;
    void copy_data(SubGrid* const other_data){ //if data is empty, size одинаковы
        for(size_type i = 0; i<m_size; i++){
            data[i] = other_data[i];
        }
    }
    void swap_g(Grid<T, N> &other) noexcept{ //перемещение
        std::swap(m_size, other.m_size);
        std::swap(data, other.data);
    }
public:
    Grid() = default;
    template <typename... Args>
    explicit Grid(size_type first_size, Args... other_sizes): m_size(first_size) {
        //static_assert(sizeof...(Args) == N - 1, "Количество размеров должно совпадать с размерностью N");
        if (m_size > 0) {
            data = new SubGrid[m_size];
            for (std::size_t i = 0; i < m_size; ++i) {
                data[i] = SubGrid(other_sizes...);
            }
        }
    }
    Grid(Grid<T, N> const & other){ //Копирующий конструктор
        if(other.data!= nullptr){
            m_size = other.m_size;
            data = new SubGrid[m_size];
            copy_data(other.data);
        }
    }
    Grid(Grid<T, N>&& other) noexcept { // Перемещающий конструктор
        swap_g(other);
    }
    Grid<T, N>&operator=(Grid<T, N> const &other){//Копирующий оператор
        if(this!=&other){
            Grid<T, N> tmp(other);
            swap_g(tmp);
        }
        return *this;
    } 
    Grid<T, N>&operator=(Grid<T,N>&& other) noexcept { //Оператор перемещения
        if(this!=&other){
            swap_g(other);
        }
        return *this;
    } 
    Grid(T const &t):  data(new SubGrid[1]), m_size(1){ //неявное преобразование типов
        data[0] = SubGrid(t);
    }
    const SubGrid& operator[](size_type idx) const { return data[idx]; }
    SubGrid& operator[](size_type idx) { return data[idx]; }
    template <typename... Args>
     const T& operator()(size_type first_idx, Args... other_idx) const { 
        return data[first_idx](other_idx...);
    }
    template <typename... Args>
    T&operator()(size_type first_idx, Args... other_idx) {
        return data[first_idx](other_idx...);
    }
    Grid<T, N>&operator=(T const &t) {
        for (size_type i =0; i<m_size; i++){
            data[i] = t;
        }
        return *this;
    }
    size_type get_m_size() const { return m_size; }
    ~Grid(){
        delete[] data;
    }
 };

template<typename T>
class Grid<T, 1> final {
public:
    using value_type=T;
    using size_type =unsigned;
private:
    T* data = nullptr;
    size_type m_size=0;
    void copy_data(T* const other_data){ //if data is empty, size одинаковы
        for(size_type i = 0; i<m_size; i++){
            data[i] = other_data[i];
        }
    }
    void swap_g(Grid<T,1> &other) noexcept{ //перемещение
        std::swap(m_size, other.m_size);
        std::swap(data, other.data);
    }
public:
    Grid() = default;
    Grid(T*data, size_type size): data(data), m_size(size) {}
    Grid(Grid<T,1> const & other){ //Копирующий конструктор
        if(other.data!= nullptr){
            m_size = other.m_size;
            data = new T[m_size];
            copy_data(other.data);
        }
    }
    Grid(Grid<T,1>&& other) noexcept { // Перемещающий конструктор
        swap_g(other);
    }
    Grid<T,1>&operator=(Grid<T,1 > const &other){//Копирующий оператор
        if(this!=&other){
            Grid<T,1> tmp(other);
            swap_g(tmp);
        }
        return *this;
    } 
    Grid<T,1>&operator=(Grid<T,1>&& other) noexcept { //Оператор перемещения
        if(this!=&other){
            swap_g(other);
        }
        return *this;
    } 
    Grid(T const &t):  data(new T[1]), m_size(1){ //неявное преобразование типов
        data[0] = t;
    }
    //Далее второй и третий дополнительный конструкторы в одном
    Grid(size_type size, T const &t = T{}){
        if(size>0){
            data=new T[size];
            m_size=size;
        }
        for(size_type i =0; i<m_size; i++){
            data[i] = t;
        }
    }
    const T& operator()(size_type idx) const { 
        return data[idx];
    }

    T&operator()(size_type idx) {
        return data[idx];
    }
    const T& operator[](size_type idx) const{
        return data[idx];
    }
    T& operator[](size_type idx){
        return data[idx];
    }
    Grid<T, 1>&operator=(T const &t) {
        for ( auto it =data, end=data+m_size;it != end; ++it)*it = t;
        return *this;
    }
    size_type get_m_size() const { return m_size; }
    T* get_data() const {return data;}
    ~Grid(){
        delete[] data;
    }
 };

int main(){
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f==g3(1,1,1));
    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f==g2(1,1));
    g2= g3[1];
    assert(1.0f==g2(1,1));
    //std::cout<<"Everything is ok"<<std::endl;
    return 0;
}
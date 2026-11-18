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
    template <typename Second, typename... Args>
    explicit Grid(size_type first_size,Second second_size, Args... other_sizes): m_size(first_size) {
        if (m_size > 0) {
            data = new SubGrid[m_size];
            for (std::size_t i = 0; i < m_size; ++i) {
                data[i] = SubGrid(static_cast<size_type>(second_size), other_sizes...);
              
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

template <typename T>
void print_grid(const Grid<T, 1>& g) {
    if (g.get_m_size() == 0) {
        std::cout << "[]]\n";
        return;
    }
    std::cout << "[ ";
    for (unsigned i = 0; i < g.get_m_size(); ++i) {
        std::cout << g[i] << " ";
    }
    std::cout << "]\n";
}

template <typename T, size_t N>
void print_grid(const Grid<T, N>& g) {
    if (g.get_m_size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << "[\n";
    for (unsigned i = 0; i < g.get_m_size(); ++i) {
        print_grid(g[i]); // Рекурсивно печатаем подсетки
    }
    std::cout << "]\n";
}
int main(){
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f==g3(1,1,1));
    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f==g2(1,1));
    g2= g3[1];
    assert(1.0f==g2(1,1));
    //std::cout<<"Everything is ok"<<std::endl;
    Grid<float, 3> grid(2, 2, 3, 5.5f);

    std::cout << " Конструктор с размерами без значения (по умолчанию 0):" << '\n';
    Grid<float, 3> grid2(2, 1, 2);
    print_grid(g2);

    std::cout << "\nНеявное преобразование типов (сетка 1x1x1):" << '\n';
    Grid<char, 3> grid3 = 'a';
    print_grid(g3);

    std::cout << "\n Конструктор копирования:" << '\n';
    Grid<float, 3> grid4 = grid;
    print_grid(grid4);

    std::cout << "\n Конструктор перемещения:" << '\n';
    Grid<char, 3> grid5 = std::move(grid3);
    print_grid(grid5);
    if (grid3.get_m_size() == 0) {
        std::cout << "grid3 очищен -> конструктор перемещения работает корректно" << std::endl;
    }

    std::cout << "\n Оператор копирующего присваивания:" << '\n';
    grid2 = grid;
    print_grid(grid2);

    std::cout << "\n Оператор перемещающего присваивания:" << '\n';
    Grid<char, 3> grid6(2, 2, 2, 'b');
    grid5 = std::move(grid6);
    std::cout << "grid5 после перемещения:\n";
    print_grid(grid5);
    std::cout << "grid6 после перемещения (должен содержать старые данные grid5 — 'a'):\n";
    print_grid(grid6);

    std::cout << "\n Проверка индексации () и [] и присваивания скаляра:" << '\n';
    grid = 1.0f;          // Заполняем всю 3D-сетку единицами
    grid(1, 0, 2) = 9.9f; // Меняем через круглые скобки
    grid[0][1][1] = 7.7f; // Меняем через квадратные скобки
    assert(grid(1, 0, 2) == 9.9f);
    assert(grid[0][1][1] == 7.7f);
    print_grid(grid);
    return 0;
}
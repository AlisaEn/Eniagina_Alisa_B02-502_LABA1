#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
template<typename T>
class Test{
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
    void swap_g(Test<T> &other) noexcept{ //перемещение
        std::swap(x_size, other.x_size);
        std::swap(y_size, other.y_size);
        std::swap(data, other.data);
    }
public:
    Test() = default;
    Test(T*data, size_type y_size, size_type x_size): data(data), y_size(y_size), x_size(x_size) {}

    Test(Test<T> const & other)  { //Копирующий конструктор
        if(other.data != nullptr){
            y_size = other.y_size;
            x_size = other.x_size;
            data = new T[y_size*x_size];
            copy_data(other.data);
        }
    }
    //Конструктор по 3-м параметрам
    Test(size_type y_size, size_type x_size, T const &t): data(new T[x_size*y_size]) , y_size(y_size), x_size(x_size){
        for(size_type i =0; i<y_size*x_size; i++){
            data[i] = t;
        }
    }
    Test(Test<T>&& other) noexcept { // Перемещающий конструктор
        swap_g(other);
    }
    Test<T>&operator=(Test<T> const &other){//Копирующий оператор
        if(this!=&other){
            Test<T> tmp(other);
            swap_g(tmp);
        }
        return *this;
    } 
    Test<T>&operator=(Test<T>&& other) noexcept { //Оператор перемещения
        if(this!=&other){
            swap_g(other);
        }
        return *this;
    } 
    ~Test(){
        delete[] data;
    }

};
int main(){
    Test<int> t1(1000, 1000, 5);
    auto start = std::chrono::steady_clock::now();
    Test<int>t2 = std::move(t1);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    std::cout << "Время выполнения: " << elapsed.count() << "\n";
    /*С noexcept 0.2, без - тоже. Потому что std::move напрямую вызывает перемещение.
    */
    std::vector<Test<int>> vec;
    for (int i = 0; i < 10; ++i) {
        vec.emplace_back(1000, 1000, 5); // каждый объект на ~4 МБ
    }

    auto start2 = std::chrono::steady_clock::now();
    vec.reserve(vec.capacity() + 1); 
    auto end2 = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::micro> elapsed2 = end2 - start2;

    std::cout << "Время перемещения вектора: " << elapsed2.count() << " \n";
    /// C noexcept - порядка 4, без - 25720 - создаёт копию.

    return 0;
}
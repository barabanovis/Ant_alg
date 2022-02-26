



//@ подключение начальных библиотек
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
using namespace std;



//! Создание важной констатны, хранящей в себе максимально-возможное
//! количество городов
const int MAX_CITY_COUNT=100;



// Просто матрица расстояний между городами
// ? Почему размеры матрицы указаны как 101 на 101?
// * Заметим, что расстояние размеры матрицы указаты как 101 на 101
// * потому, что количество городов, которые будет принимать программа
// $ не превышает 100 для лучшей показательности
 long double Distance[MAX_CITY_COUNT+1][MAX_CITY_COUNT+1]; // +1 ��� 1-���������

 // @ Структура "точка" задаваемая как точка на плоскости Oxy
 struct point{
 ll x_coordinate,y_coordinate;
 point(ll x,ll y){ // просто конструктор для этой структуры
 x_coordinate=x;
 y_coordinate=y;
 }
 };



// ~ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ~ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


 //@ Структура "Муравей"
 struct Ant{
  // вектор, который будет хранить номера посещённых городов
 vector<long long> list_of_visited_cities;
 set<long long> set_of_visited_cities;
 long long route_length; // длина пути, который уже пройден муравьём

long long last_visited_city;


 // todo задание стартового города муравью
 void set_start_city(long long start_city){
 clear();
 last_visited_city=start_city;
 // добавление города в список
 list_of_visited_cities.push_back(start_city);
 set_of_visited_cities.insert(start_city);
 }


 // todo перемещение муравья в определённый город
 void Go_to_city(long long city_number){ 
     // @ Обновление пройденного пути
     route_length+=Distance[last_visited_city][city_number];
     // @ Добавление города в список пройденных городов
     list_of_visited_cities.push_back(city_number); 
     last_visited_city=city_number;
     set_of_visited_cities.insert(city_number);

 };


 // todo Очистка полей муравья
 void clear(){
    last_visited_city=0; 
    route_length=0;
    list_of_visited_cities.clear();
    set_of_visited_cities.clear();
 };

//todo метод, проверяющий, был ли муравей в определённом городе
 bool was_in_city(long long city_number){
     if(set_of_visited_cities.count(city_number)==0) return false;
     return true;
 }





 };

//ч 
long double distance_between_points(point A, point B){
// ? Как получается результат? 
// * На основе теоремы Пифагора считается расстояние между точками
long long d1_square=(A.x_coordinate-B.x_coordinate)*(A.x_coordinate-B.x_coordinate);// ���������� ������� ���������� ������������ Oy
long long d2_square=(A.y_coordinate-B.y_coordinate)*(A.y_coordinate-B.y_coordinate);

return sqrt(d1_square+d2_square);

}


// ~ +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ~ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 int main(){
// ! чтобы можно было выводить в консоль русские символы
 setlocale(LC_ALL,"RUS"); 


ll count_of_cities;
cout << "Enter number of cities: ";
cin >> count_of_cities; // получаем число городов
cout << '\n'; // переходим на новую строку 
vector<point> cities(count_of_cities);
// Создаем вектор из городов



// todo принимаем каждый город по очереди
for(int cur_city=1;cur_city<=count_of_cities;cur_city++){
    cout << "Enter coordinates city number " << cur_city << ": ";
    cin >> cities[cur_city].x_coordinate >> cities[cur_city].y_coordinate;

}
// todo заполняем матрицу расстояний
//? Почему именно так?
// * Учитывая, что Distance[i][j]=Distance[j][i] можно значительно ускорить вычисления
for(ll i=1;i<count_of_cities+1;i++){
    for(ll j=1;j<i;j++){
            
            ll temp=distance_between_points(cities[i],cities[j]);
            Distance[i][j]=temp;
            Distance[j][i]=temp;

    
    }
}

// todo инициализация матрицы расстояний
// ? Каким образом? 
// * Обнуление всех ячеек.
for(int i=1;i<=count_of_cities;i++){
    Distance[i][i]=0;
}


// Создание вектора, олицетворяющего рой муравьёв
vector<Ant> Roy(count_of_cities);

//todo Установка начальных положений муравьёв
for(ll i=1;i<=count_of_cities;i++){
    Roy[i].set_start_city(i); // Сообщаем i-тому муравью его начальный
    // город
}


//todo Инициализируем необходимые константы
const long long ALPHA=1;
const long long BETA=1;
const long long e=1;
const long long Q=1;
//! Особенно важная переменная
//? За что она отвечает?
//* За изначальную концентрацию феромона на поле/графе
const long double start_pheromon_concentration=0.5;

//* Учтя, что количество городов по всем входным данным не 
//* превосходит 100, можем сразу установить предесы матрицы
long double pheromone[MAX_CITY_COUNT+1][MAX_CITY_COUNT+1];

for(ll i=1;i<count_of_cities+1;i++){
    for(ll j=1;j<=i;j++){
        pheromone[i][j]=start_pheromon_concentration;
        pheromone[j][i]=start_pheromon_concentration;
    }
}
// Создание отдельных контейнеров для хранения наилучшего найденного
// пути
//? Зачем?
//* Так удобнее сохранять результаты.
vector<int> best_way(0);
long double best_length=0;

//todo Задание стартового маршрута, для сравнения
//? Каким он является?
//* Маршрут через все города по очереди в порядке возрастания
for(int i=1;i<=count_of_cities;i++){
    best_way.push_back(i);
    best_length+=Distance[i][best_way.back()];
}


//todo Получение времени жизни колонии
cout << '\n'; // Новая строчка
cout << "Enter colony lifetime (iterations): ";
ll colony_time_limit; // Сама переменная для хранения этого предела
cin >> colony_time_limit; // Принятие этой самой переменной




long long count_of_ants=count_of_cities;
// todo Цикл по времени жизни колонии ==== 0
for(ll current_time=1;current_time<=colony_time_limit;current_time++){
    //todo Цикл по всем муравьям ==== 1
    for(ll cur_ant_number=1;cur_ant_number<=count_of_ants;cur_ant_number++){
      // todo Построить маршрут по описанному правилу ==== 2
      //? Как это сделать?
      //* Будем использовать уже известную формулу, основанную на вероятностном выборе
     
      //$ Для начала подсчитаем вероятность перехода в каждый город
      //? То есть?
      //* Подсчитаем значение числителей из поставленной формулы и запишем их в массив(вектор)
      vector<long double> probabilities(count_of_cities+1,0);
      // $ Параллельно подсчитаем сумму всех числителей
      //? Как?
      //* Просто создадим соответствующую переменную, куда каждый раз будем прибавлять полученное число.
      long double sum_of_probabilities=0;
      for(long long cur_city=1,cur_city<=count_of_cities;cur_city++){
         probabilities[cur_city]=pow(pheromon[Roy[cur_ant_number].])

      } 

      
      

    
    }


}



}















//@ подключение начальных библиотек
#include <iostream>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

//w Удобное объявление
//? Зачем?
//* Мне так удобнее
typedef long long ll;



//! Создание важной констатны, хранящей в себе максимально-возможное
//! количество городов
const int MAX_CITY_COUNT=100;



// Просто матрица расстояний между городами
// ? Почему размеры матрицы указаны как 101 на 101?
// * Заметим, что расстояние размеры матрицы указаты как MAX_CITY_COUNT+1 на MAX_CITY_COUNT+1
// * потому, что количество городов, которые будет принимать программа
// $ не превышает MAX_CITY_COUNT для лучшей показательности
 long double Distance[MAX_CITY_COUNT+1][MAX_CITY_COUNT+1]; 

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

//w Функция для расчёта расстояния между точками
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
//ч чтобы можно было выводить в консоль русские символы
 setlocale(LC_ALL,"RUS"); 


int count_of_cities;
cout << "Введите количество городов: ";
cin >> count_of_cities; // получаем число городов
cout << '\n'; // переходим на новую строку 
vector<point> cities(count_of_cities);
// Создаем вектор из городов



// todo принимаем каждый город по очереди
for(int cur_city=1;cur_city<=count_of_cities;cur_city++){
    cout << "Введите координаты города под номером " << cur_city << ": ";
    cin >> cities[cur_city].x_coordinate >> cities[cur_city].y_coordinate;

}

// todo инициализация матрицы расстояний
// ? Каким образом? 
// * Обнуление всех ячеек.
for(long long i=1;i<=count_of_cities;i++){
    for(long long j =1;j<=count_of_cities;j++) Distance[i][j]=0;
}

// todo заполняем матрицу расстояний
//? Почему именно так?
// * Учитывая, что Distance[i][j]=Distance[j][i] можно значительно ускорить вычисления
for(int i=1;i<=count_of_cities;i++){
    for(int j=1;j<i;j++){
            
        ll temp=distance_between_points(cities[i],cities[j]);
        Distance[i][j]=temp;
        Distance[j][i]=temp;

    
    }
}


//w Заполнение матрицы обратных расстояний
vector<vector<long double>> matrix_of_seen(count_of_cities+1,vector<long double> (count_of_cities+1,0));
for(int i=2;i<=count_of_cities;i++){
    for(int j=1;j<i;j++){
        matrix_of_seen[i][j]=1/Distance[i][j];
        matrix_of_seen[j][i]=1/Distance[i][j];
    }
}






//w Создание вектора, олицетворяющего рой муравьёв
vector<Ant> Roy(count_of_cities+1);

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
const long double start_pheromone_concentration=0.5;

//* Учтя, что количество городов по всем входным данным не 
//* превосходит 100, можем сразу установить пределы матрицы
long double pheromone[MAX_CITY_COUNT+1][MAX_CITY_COUNT+1];

for(ll i=1;i<=count_of_cities;i++){
    for(ll j=1;j<i;j++){
        pheromone[i][j]=start_pheromone_concentration;
        pheromone[j][i]=start_pheromone_concentration;
    }
}
//todo Создание отдельных контейнеров для хранения наилучшего найденного
//todo пути
//? Зачем?
//* Так удобнее сохранять результаты.
vector<ll> best_way(0);
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
// todo Цикл по времени жизни колонии 
for(ll current_time=1;current_time<=colony_time_limit;current_time++){
    //todo Цикл по всем муравьям 
    for(ll cur_ant_number=1;cur_ant_number<=count_of_ants;cur_ant_number++){
      // todo Построить маршрут по описанному правилу 
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
      for(long long cur_city=1;cur_city<=count_of_cities;cur_city++){
         probabilities[cur_city]=pow(pheromone[Roy[cur_ant_number].last_visited_city][cur_city],ALPHA)*pow(back_Distance[Roy[cur_ant_number].last_visited_city][cur_city],BETA);
         sum_of_probabilities+=probabilities[cur_city];
        } 

      //w Теперь будем подсчитывать вероятности в тот-же вектор. Значение знаменателя сохранено.
      ll sum_of_probabilities_ll=0;
      for(ll cur_city=1;cur_city<=count_of_cities;cur_city++){
          while(Roy[cur_ant_number].was_in_city(cur_city) && cur_city<=count_of_cities) cur_city+=1;
          probabilities[cur_city]=(ll)(probabilities[cur_city]/sum_of_probabilities)*1e6;
          sum_of_probabilities_ll+=(ll)probabilities[cur_city];
      }  
      
      //w Теперь мы должны реализовать рулетку выбора
      //@ Создадим префиксный массив для массива probabiities;
      vector<ll> prefix(count_of_cities,0);
      prefix[0]=probabilities[1];
      for(ll i=2;i<=count_of_cities;i++){
          prefix[i]=prefix[i-1]+probabilities[i];
      }
      
      //w Запускаем рандомайзер, путём выбора случайного числа из предложенного предела 
       
       // Здесь будет код, который будет выбирать город из диапазона
       // пусть он будет называться selected_city
       ll selected_city;

      //ч Выбранный муравей отправляется в выбранный город
      Roy[cur_ant_number].Go_to_city(selected_city);
      //* Остальные предподсчёты сделает использованный метод структуры
    }

    //~ КОНЕЦ ЦИКЛА ПО МУРАВЬЯМ
    
    // todo Выбираем лучший маршрут
    //w Делается это очень просто:
    //@ Выбираем муравья с наименьшим путем, и сравниваем его путь с найденным ранее.
    //* На самомо деле, мы будем "сравнивать" каждого муравья с наилучшим маршрутом таким образом не упустим 
    //* наилучший вариант, если таковой имеется.

    for(int cur_ant_number=1;cur_ant_number<=count_of_ants;cur_ant_number++){
        if(best_length>Roy[cur_ant_number].route_length){ // если маршрут муравья cur_ant_number лучше раннее
            // найденного...
            best_length=Roy[cur_ant_number].route_length; // обновление длины лучшего маршрута
            best_way.assign(Roy[cur_ant_number].list_of_visited_cities.begin(),Roy[cur_ant_number].list_of_visited_cities.end());
             // ^^
             // ||
             // обновление самого маршрута
        }
    }
    
    //todo Обновление феромона
    //ч Будем поочерёдно обследовать маршруты каждого муравья и изменять значения феромона
    for(ll cur_ant_number=1;cur_ant_number<=count_of_ants;cur_ant_number++){
        Ant cur_ant=Roy[cur_ant_number]; // Подобное объявнение допустимо, так как мы не будем изменять 
        // характеристики муравья
        
        //todo Обновление феромона для маршрута выбранного муравья
        for(ll current_city_index=1;current_city_index<(ll)cur_ant.list_of_visited_cities.size();current_city_index++){
           ll current_city=cur_ant.list_of_visited_cities[current_city_index];
           ll next_city=cur_ant.list_of_visited_cities[current_city_index+1];
           long double delta_pheromone=0; // Переменная, которая будет хранить в себе изменение значения феромона.
           

           delta_pheromone=Q/(cur_ant.route_length);

           // Обновление значения феромона по формуле
           //! Завершить формулу!!!
           pheromone[current_city][next_city]=(1-p)*pheromone[current_city][next_city]; 


        }    


    }




}



}











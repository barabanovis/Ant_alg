



//@ подключение начальных библиотек
#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <ctime>

using namespace std;


//w Герератор псевдослучайных чисел
//? Как он работает?
//* Он использует время в секундах с момента запуска компьютера как зерно (seed), затем производит
//* псевдослучайное число в пределах от заданного l до r невключительно
int getrandom(int l,int r){
unsigned ran=(8<<rand())+rand();
ran=(ran*(r-l+3)+(r-l+234))%(r-l);
return ran+l;
}



//w Удобное объявление
//? Зачем?
//* Мне так удобнее
typedef long long ll;



//! Создание важной констатны, хранящей в себе максимально-возможное
//! количество городов
const int MAX_CITY_COUNT=150;



// Просто матрица расстояний между городами
// ? Почему размеры матрицы указаны как MAX_CITY_COUNT+1 на MAX_CITY_COUNT+1?
// * Заметим, что расстояние размеры матрицы указаты как MAX_CITY_COUNT+1 на MAX_CITY_COUNT+1
// * потому, что количество городов, которые будет принимать программа
// $ не превышает MAX_CITY_COUNT для лучшей показательности
 long double Distance[MAX_CITY_COUNT+1][MAX_CITY_COUNT+1];

 // @ Структура "точка" задаваемая как точка на плоскости Oxy
 struct point{
 ll x_coordinate,y_coordinate;

 };



// ~ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ~ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


 //@ Структура "Муравей"
 struct Ant{
  // вектор, который будет хранить номера посещённых городов
 vector<int> list_of_visited_cities;
 set<int> set_of_visited_cities;
 long double route_length; // длина пути, который уже пройден муравьём

 int last_visited_city;


 // todo задание стартового города муравью
 void set_start_city(int start_city){
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
 bool was_in_city(int city_number){
     if(set_of_visited_cities.count(city_number)==0) return false;
     return true;
 }





 };

//w Функция для расчёта расстояния между точками
long double distance_between_points(point A, point B){
// ? Как получается результат?
// * На основе теоремы Пифагора считается расстояние между точками
long long d1_square=(A.x_coordinate-B.x_coordinate)*(A.x_coordinate-B.x_coordinate);
long long d2_square=(A.y_coordinate-B.y_coordinate)*(A.y_coordinate-B.y_coordinate);

return sqrt(d1_square+d2_square);

}


// ~ +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ~ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 int main(){
//* Для работы генератора случайных чисел
//$ getrandom
srand(time(0));


cout << "Do you want to see the details for the developer? (Y/N)" << '\n';
bool dev_det;
char ask;
cin >> ask;
if(ask=='Y' || ask=='y'){
    dev_det=true;
}else{
    dev_det=false;
}



//todo Инициализируем необходимые константы
cout << "Enter constants " << '\n';

cout << "ALPHA = ";
int ALPHA;
cin >> ALPHA;
cout << '\n';

int BETTA;
cout << "BETTA = ";
cin >> BETTA;
cout << '\n';


int Q=1;
cout << "Q = ";
cin >> Q;
cout << '\n';

long double p;
cout << "p = ";
cin >> p;
cout  << '\n';


//! Особенно важная переменная
//? За что она отвечает?
//* За изначальную концентрацию феромона на поле/графе
float start_pheromone_concentration;
cout << "start_pheromone_concentration = ";
cin >> start_pheromone_concentration;
cout << '\n';



int count_of_cities;
cout << "Enter count of cities: ";
cin >> count_of_cities; // получаем число городов
cout << '\n'; // переходим на новую строку
vector<point> cities(count_of_cities+1);
// Создаем вектор из городов



// todo принимаем каждый город по очереди
for(int cur_city=1;cur_city<=count_of_cities;cur_city++){
    cout << "Enter coordinates of city number " << cur_city << ": ";
    cin >> cities[cur_city].x_coordinate >> cities[cur_city].y_coordinate;

}



if(dev_det){
    cout << "Initializing Distance ";
}


// todo инициализация матрицы расстояний
// ? Каким образом?
// * Обнуление всех ячеек.
for(int i=1;i<=count_of_cities;i++){
    for(int j =1;j<=count_of_cities;j++) Distance[i][j]=0;
}


if(dev_det){
    cout << "COMPLETED" << '\n';
    cout << "Calculating Distance " ;
}
// todo заполняем матрицу расстояний
//? Почему именно так?
// * Учитывая, что Distance[i][j]=Distance[j][i] можно значительно ускорить вычисления
for(int i=1;i<=count_of_cities;i++){
    for(int j=1;j<i;j++){

        long double temp=distance_between_points(cities[i],cities[j]);
        Distance[i][j]=temp;
        Distance[j][i]=temp;
        

    }
}






if(dev_det){
    cout << "COMPLETED" << '\n';

    cout << "Distance =" << '\n';
    for(int i=1;i<=count_of_cities;i++){
        for(int j=1;j<=count_of_cities;j++) cout << Distance[i][j] << " ";
        cout << '\n';
    }




    cout << "Initializing matrix_of_seen ";
}
//w Заполнение матрицы обратных расстояний
vector<vector<long double>> matrix_of_seen(count_of_cities+1,vector<long double> (count_of_cities+1,0));
for(int i=2;i<=count_of_cities;i++){
    for(int j=1;j<i;j++){
        matrix_of_seen[i][j]=1/Distance[i][j];
        matrix_of_seen[j][i]=1/Distance[i][j];
    }
}
if(dev_det){
 cout << "COMPLETED" << '\n';
 cout << "Initializing the Roy ";
}





//w Создание вектора, олицетворяющего рой муравьёв
vector<Ant> Roy(count_of_cities+1);

//todo Установка начальных положений муравьёв
for(int i=1;i<=count_of_cities;i++){
    Roy[i].set_start_city(i); // Сообщаем i-тому муравью его начальный
    // город
}

if (dev_det){
    cout << "COMPLETED" << '\n';
    cout << "Initialization preromone ";
}





//* Учтя, что количество городов по всем входным данным не
//* превосходит 100, можем сразу установить пределы матрицы
long double pheromone[MAX_CITY_COUNT+1][MAX_CITY_COUNT+1];

for(int i=1;i<=count_of_cities;i++){
    for(int j=1;j<i;j++){
        pheromone[i][j]=start_pheromone_concentration;
        pheromone[j][i]=start_pheromone_concentration;
    }
}

if (dev_det){
    cout << "COMPLETED" << '\n';
    cout << "Creating containers for answer ";
}



//todo Создание отдельных контейнеров для хранения наилучшего найденного
//todo пути
//? Зачем?
//* Так удобнее сохранять результаты.
vector<int> best_way(0);
long double best_length=0;

if(dev_det){
    cout << "COMPLETED" << '\n';
    cout << "Initialization containers for best way ";
}



//todo Задание стартового маршрута, для сравнения
//? Каким он является?
//* Маршрут через все города по очереди в порядке возрастания
best_way.clear();
for(int i=1;i<=count_of_cities;i++){
    best_way.push_back(i);
}

for(int i=1;i<count_of_cities;i++){
    best_length+=Distance[i][i+1];
}



if(dev_det){
    cout << "COMPLETED" << '\n';
}



//todo Получение времени жизни колонии
cout << '\n'; // Новая строчка
cout << "Enter colony lifetime (iterations): ";
int colony_time_limit; // Сама переменная для хранения этого предела
cin >> colony_time_limit; // Принятие этой самой переменной


if(dev_det){
    cout << "Calculating answer ";
}

int count_of_ants=count_of_cities;
// todo Цикл по времени жизни колонии
for(int current_time=1;current_time<=colony_time_limit;current_time++){
    //todo Цикл по всем муравьям
    for(int cur_ant_number=1;cur_ant_number<=count_of_ants;cur_ant_number++){
      // todo Построить маршрут по описанному правилу
      for(int cur_number_of_visited_cities=1;cur_number_of_visited_cities<count_of_cities;cur_number_of_visited_cities++){
      //? Как это сделать?
      //* Будем использовать уже известную формулу, основанную на вероятностном выборе

      //$ Для начала подсчитаем вероятность перехода в каждый город
      //? То есть?
      //* Подсчитаем значение числителей из поставленной формулы и запишем их в массив(вектор)
      vector<long double> wishes(count_of_cities+1,0);

      //@ Предподсчитаем сумму всех числителей, записывая их в вектор wishes и дополнительно
      //@ домножив на 10^4, чтобы те были целыми числами. Это необходимо для алгоритма вероятностного выбора
      //@ города для перехода.
      //? Что я для этого предприму?
      //* Создам саму переменную
      ll sum_of_probabilities=0;
      //* Далее буду увеличивать её по мере прохождения цикла

      if(dev_det){
          cout << "Calculating wishes ";
      }

      for(long long cur_city=1;cur_city<=count_of_cities;cur_city++){
         if(Roy[cur_ant_number].was_in_city(cur_city)==false){
             wishes[cur_city]=(ll)(pow(pheromone[Roy[cur_ant_number].last_visited_city][cur_city],ALPHA)*pow(matrix_of_seen[Roy[cur_ant_number].last_visited_city][cur_city],BETTA)*10000);
         }
         sum_of_probabilities+=wishes[cur_city];
        }
        if(dev_det){
            cout << "COMPLETED" << '\n';
            cout << "Choosing city ";
        }



      //w Запускаем рандомайзер, путём выбора случайного числа из предложенного предела

       // Здесь будет код, который будет выбирать город из диапазона
       // пусть он будет называться selected_city
       int selected_city;

      //? Каким образом будет работать алгоритм?
      //* Воспользуемся простой конструкцией, основанной на описанной в текстовой части работы.
      //* Предподсчитав сумму всех числителей, выбираем какое-нибудь число из заданного диапазона.
      ll rand_val=getrandom(1,sum_of_probabilities);
      //* Далее по циклу будем вычитать из числа rand_val желание перехода муравья в каждый из городов, пока
      //* значение rand_val не станет меньше нуля. Когда это случится, город, желание в который было вычтено,
      //* будет считаться городом для перехода.

      for(int cur_city=1;cur_city<=count_of_cities;cur_city++){
          rand_val-=(ll)wishes[cur_city];
          if(rand_val<0){
              selected_city=cur_city;
              cur_city=count_of_cities+1;
          }
        }

      

        



      //ч Выбранный муравей отправляется в выбранный город
      Roy[cur_ant_number].Go_to_city(selected_city);
      //* Остальные предподсчёты сделает использованный метод структуры
      }
    }

    //~ КОНЕЦ ЦИКЛА ПО МУРАВЬЯМ

    // todo Выбираем лучший маршрут
    //w Делается это очень просто:
    //@ Выбираем муравья с наименьшим путем, и сравниваем его путь с найденным ранее.
    //* На самом деле, мы будем "сравнивать" каждого муравья с наилучшим маршрутом таким образом не упустим
    //* наилучший вариант, если таковой имеется.
    
    if(dev_det){
        cout << "Updating best way ";
    }


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


    if(dev_det){
        cout << "COMPLETED" << '\n';
        cout << "Updating pheromon" << '\n';
        cout << "All" << '\n';
    }


    //todo Обновление феромона
    //ч В начале испарим весь феромон по всему полю
    for(int cur_city=1;cur_city<=count_of_cities;cur_city++){
        for(int next_city=1;next_city<cur_city;next_city++){
            pheromone[cur_city][next_city]*=(1-p);
            pheromone[next_city][cur_city]=pheromone[cur_city][next_city];
        }
    }
    if(dev_det){
        cout << "COMPLETED" << '\n';
        cout << "marsruts ";
    }




    
    //ч Теперь будем идти по порядку по всем маршрутам, заканчивая обновление феромона
    for(int ant_number=1;ant_number<=count_of_ants;ant_number++){
        int prev_city_number=0;
        for(auto cur_city_number : Roy[ant_number].list_of_visited_cities){
            pheromone[cur_city_number][prev_city_number]+=Q/Roy[ant_number].route_length;
            pheromone[prev_city_number][cur_city_number]=pheromone[cur_city_number][prev_city_number];
            prev_city_number=cur_city_number;
        }
    }

    if(dev_det){
        cout << "COMPLETED" << '\n';
    }


}

if(dev_det){
    cout << "COMPLETED" << '\n';
}

cout << "Answer calculated!" << '\n';
cout << "The way is: " << '\n';

//w Вывод найденного маршрута
for(auto i : best_way){
    cout << i << ", ";
}
cout << '\n';

cout << "The best way has length " << best_length << '\n';



}











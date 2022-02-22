



// подключение начальных библиотек
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll; // ? Зачем нужна эта строчка
// * По сути, эта строчка не нужна, мне просто удобнее писать ll
// * в замен long long

// Просто матрица расстояний между городами
// ? Почему размеры матрицы указаны как 101 на 101?
// * Заметим, что расстояние размеры матрицы указаты как 101 на 101
// * потому, что количество городов, которые будет принимать программа
// * не превышает 100 для лучшей показательности
 long double Distance[101][101]; // +1 ��� 1-���������

 // * Структура "точка" задаваемая как точка на плоскости Oxy
 struct point{
 ll x_coordinate,y_coordinate;
 point(ll x,ll y){ // просто конструктор для этой структуры
 x_coordinate=x;
 y_coordinate=y;
 }
 };

 // Структура "Муравей"
 struct Ant{
  // вектор, который будет хранить номера посещённых городов
 vector<long long> list_of_visited_cities;

 long long route_length; // длина пути, который уже пройден муравьём


 // todo задание стартового города муравью
 void set_start_city(long long start_city){
 list_of_visited_cities.clear(); // Очистка списка посещённых городов

// добавление города в список
 list_of_visited_cities.push_back(start_city);
 }


 // todo перемещение муравья в определённый город
 void Go_to_city(long long city_number){ // ��� � ����� ����� city_number
     // * Обновление пройденного пути
     route_length+=Distance[list_of_visited_cities.back()][city_number];
     // * Добавление города в список пройденных городов
     list_of_visited_cities.push_back(city_number); // ���������� ������ � �������


 };


 // todo Очистка полей муравья
 void clear(){
    route_length=0;
    list_of_visited_cities.clear();
 };

 };

long double distance_between_points(point A, point B){
// ? Как получается результат? 
// * На основе теоремы Пифагора считается расстояние между точками
long long d1_square=(A.x_coordinate-B.x_coordinate)*(A.x_coordinate-B.x_coordinate);// ���������� ������� ���������� ������������ Oy
long long d2_square=(A.y_coordinate-B.y_coordinate)*(A.y_coordinate-B.y_coordinate);

return sqrt(d1_square+d2_square);

}




 int main(){

 setlocale(LC_ALL,"RUS"); // ! чтобы можно было выводить в консоль русские символы


ll count_of_cities;
cout << "������ ���������� �������: ";
cin >> count_of_cities; // получаем число городов
cout << '\n'; // переходим на новую строку 
vector<point> cities(count_of_cities);
// Создаем вектор из городов



// todo принимаем каждый город по очереди
for(int cur_city=1;cur_city<=count_of_cities;cur_city++){
    cout << "������� ���������� ������ " << cur_city << ": ";
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

// ������, ������� �� ������� ��������� ����� ��������, ��� ���
// ���������� �� ����� �� �� ����� ����� ����
for(int i=1;i<=count_of_cities;i++){
    Distance[i][i]=0;
}
//����� ������������� �������(�������) ����������




// ��� ��������� ��� ��������
vector<Ant> Roy(count_of_cities);

// i-��� ������� ���������� ��������� � ������ ����� i
for(ll i=1;i<=count_of_cities;i++){
    Roy[i].clear(); // ������� ������� i
    Roy[i].list_of_visited_cities.push_back(i); // ���������� ���������� ������ �
    // ������ ���������� �������
}


// ������������� ���������� ���������
const long long ALPHA=1;
const long long BETA=1;
const long long e=1;
const long long Q=1;
// ��������� ����������� ��������
const long double start_feromom_concentration=0.5;

long double feromon[101][101];

for(ll i=1;i<count_of_cities+1;i++){
    for(ll j=1;j<=i;j++){
        feromon[i][j]=0.5;
        feromon[j][i]=0.5;
    }
}

// ����� ���������� ����������� ��������
// ����� ��� ����� ������� �� ���� ������� �� ������� �� �������

vector<int> best_way(0);
long double best_length=0;

for(int i=1;i<=count_of_cities;i++){
    best_way.push_back(i);
    best_length+=Distance[i][best_way.back()];
}


//���� �� ������� ����� �������
cout << '\n';
cout << "������� ����� ����� �������: ";
ll colony_time_limit;
cin >> colony_time_limit;


// �� ����
for(ll current_time=1;current_time<=colony_time_limit;current_time++){
    // ���� �� ���� ��������
    for(ll cur_ant_number=1;cur_ant_number<=count_of_cities;cur_ant_number++){



    }


}



}











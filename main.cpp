



// 0sdf ����d
// ����������� ����������� ���������� iostream
#include <iostream>
#include <cmath>
#include <vector>

typedef long long ll;

 // ����������� ����������� ��������(�������)

 // ������� ���������� ����� ��������
 // ������������ ���������� ������� - 100
 long long Distance[101][101]; // +1 ��� 1-���������

 //����� �� ��������� �xy
 struct point{
 ll x_coordinate,y_coordinate;
 point(ll x,ll y){ // ����������� ��� ����� ��������� point
 x_coordinate=x;
 y_coordinate=y;
 }
 };

 //�������
 struct Ant{
  // ������ ���������� �������
 vector<long long> list_of_visited_cities;

 long long route_length; // ����� ��� ����������� ����

 // �����������
 void set_start_city(long long start_city){
 list_of_visited_cities.clear(); // ������� ������ ��� ���������� �������
 // �� ������ ������

 list_of_visited_cities.push_back(start_city); // ��������� ��������� ����� � �������
 }


 // ������
 void Go_to_city(long long city_number){ // ��� � ����� ����� city_number
     // ���������� ����� ����
     route_length+=Distance[list_of_visited_cities.back()][city_number];

     list_of_visited_cities.push_back(city_number); // ���������� ������ � �������


 };


 // ������� ����������� ��������
 void clear(){
    route_length=0;
    list_of_visited_cities.clear();
 };

 };

long double distance_between_points(point A, point B){
// ��� ������� ��������� ���������� ����� 2 ������� ��������� Oxy
// ���ר�
// ���������� ������� ���������� ������������ Ox
long long d1_square=(A.x_coordinate-B.x_coordinate)*(A.x_coordinate-B.x_coordinate);
// ���������� ������� ���������� ������������ Oy
long long d2_square=(A.y_coordinate-B.y_coordinate)*(A.y_coordinate-B.y_coordinate);
// �������� ������� �������� ���������� �������� ���������� � ���������
// �� �� ����� ���������� ������, ������� ����������� ���������
// � �����, ���������� ���
return sqrt(d1_square+d2_square);
// ����� ���ר���
// ����� �������
}




 int main(){

 setlocale(LC_ALL,"RUS");
 /*
 ���������� ��� ����, �����
 ���� �������� �������� ������� ����� ��������� �������
 cout
 */

// 1 ����: ��Ȩ� �������� ������ � ����������� ��������
//��� ������ ��� ���������� ������� ��������� ����� �� ���������
// Oxy

ll count_of_cities;
cout << "������ ���������� �������: ";
cin >> count_of_cities; //  ���� ��������� ������� ����������
cout << '\n'; // ������� �� ����� ������
vector<point> cities(count_of_cities); // �������� ������� �� �������
// count_of_cities + 1 ��� 1-���������

for(int cur_city=1;cur_city<=count_of_cities;cur_city++){
    cout << "������� ���������� ������ " << cur_city << ": ";
    cin >> cities[cur_city].x_coordinate >> cities[cur_city].y_coordinate;

}

// ������������� ������� ����������


/*
��������� ���� ������� �����������, �� �������� � �� ��
O(n^2), � �� O((n^2)/2), ��������� ��� ������� �����������
*/

for(ll i=1;i<count_of_cities+1;i++){
    for(ll j=1;j<i;j++){
            /*
            ��������� ���� � ��� �� ������ �� ����� ������ � 2 ������ ������,
            ����� ������� ��������� ��������� ������� � ��������� ���������� � ���������
            ������� �� ��������
            */
            // ������� � temp
            ll temp=distance_between_points(cities[i],cities[j]);
            Distance[i][j]=temp;
            Distance[j][i]=temp;

    /* �������, ��� ���������� temp ���������� ������ ������ �������
    ����� FOR, ��� ��������, ��� ������������� ���� ����������  � ������ ������ ���
    � �������������/���������� ����������, �� ���� ����� ������ ��������� ��� ������
    */
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











#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int silnia(int n) {
    return n == 0 || n == 1 ? 1 : n*silnia(n-1);
}

void interpolacja_hermita(vector<double> wezly, 
    map<double, vector<double>> func, double x)
{
    vector<vector<double>> result;
    vector<double> temp;

    for(int i=0; i<wezly.size(); i++){
        temp.push_back(func[wezly[i]][0]);
    }
    result.push_back(temp);

    for(int i=1; i<wezly.size(); i++)
    {
        temp.clear();
        for(int j=0; j<wezly.size() - i; j++)
        {
            if(wezly[j] == wezly[j+i]){
                temp.push_back(func[wezly[j]][i]/silnia(i));
            }else {
                temp.push_back((result[i-1][j+1] - result[i-1][j])/(wezly[j+i]-wezly[j]));
            }
        }
        result.push_back(temp);
    }


    double wynik = result[0][0];
    for(int i=1; i<result.size(); i++)
    {
        double iloczyn = result[i][0];
        for(int j=0; j<i; j++)
            iloczyn *= (x - wezly[j]);
        wynik += iloczyn;
    }

    cout << wynik << endl;
    cout << endl;

}

int main()
{
    int iloscWezlow;

    cout << "podaj ilosc wezlow: ";
    cin >> iloscWezlow;

    map<double, vector<double>> func;
    vector<double> wezly;

    double wezel, pochodna;
    int krotnosc;

    for(int i=0; i<iloscWezlow; i++)
    {
        cout << "podaj wartosc " << i << " wezla oraz krotnosc tego wezla: ";
        cin >> wezel >> krotnosc;

        for(int j=0; j<krotnosc; j++)
        {
            wezly.push_back(wezel);
            cout << "   podaj wartosc " << j << " pochodnej tego wezla: ";
            cin >> pochodna;

            func[wezel].push_back(pochodna);
        }

    }

    interpolacja_hermita(wezly, func, 1.5);
   
    return 0;

}
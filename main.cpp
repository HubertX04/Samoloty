#include <iostream>(@
#include <vector>
#include <algorithm>
#include <windows.h>
#include <ctime>
#include <string>
#include <queue>

using namespace std;

const int rozmiar_planszy = 70; //wektor jest kwadratem (zmienna wieksza od szerokosci i wysokosci +5)
const int szerokosc = 60, wysokosc = 10; // minimialna szerokosc to 30

struct samoloty {
    char litera;
    int odwiedzony = 0;
    string nazwa = "test";
    int kierunek=0; // 1 - w lewo, 0 - w prawo
    queue <int> up_down;
    queue <int> o_ile;
}*w;

void samolot_prawa(int plansza_samolotow[rozmiar_planszy][rozmiar_planszy], int &i, int &j)
{
    char znaczek = char(92);
    if (w[plansza_samolotow[i][j]].up_down.size() == 0)
    {
        plansza_samolotow[i][j - 1] = plansza_samolotow[i][j];
        w[plansza_samolotow[i][j - 1]].odwiedzony = 1;
        plansza_samolotow[i][j] = -1;

        w[plansza_samolotow[i][j - 1]].nazwa = "(";
        w[plansza_samolotow[i][j - 1]].nazwa.push_back(w[plansza_samolotow[i][j - 1]].litera);
        w[plansza_samolotow[i][j - 1]].nazwa.push_back('0');
        w[plansza_samolotow[i][j - 1]].nazwa.push_back(')');
        w[plansza_samolotow[i][j - 1]].nazwa.push_back('=');
    }
    else
    {
        if (w[plansza_samolotow[i][j]].up_down.front() == 1)//w gore
        {
            if (i - 1 != 0)
            {
                plansza_samolotow[i - 1][j - 1] = plansza_samolotow[i][j];
                w[plansza_samolotow[i - 1][j - 1]].odwiedzony = 1;
                plansza_samolotow[i][j] = -1;

                w[plansza_samolotow[i - 1][j - 1]].nazwa = "(";
                w[plansza_samolotow[i - 1][j - 1]].nazwa.push_back(w[plansza_samolotow[i-1][j - 1]].litera);
                w[plansza_samolotow[i - 1][j - 1]].nazwa.push_back(w[plansza_samolotow[i - 1][j - 1]].o_ile.front()+47);
                w[plansza_samolotow[i - 1][j - 1]].nazwa.push_back(')');
                w[plansza_samolotow[i - 1][j - 1]].nazwa.push_back('/');
            }

            if (w[plansza_samolotow[i - 1][j - 1]].o_ile.front() == 1)
            {
                if (w[plansza_samolotow[i - 1][j - 1]].o_ile.size() > 0)
                {
                    w[plansza_samolotow[i - 1][j - 1]].o_ile.pop();
                    w[plansza_samolotow[i - 1][j - 1]].up_down.pop();
                }
            }
            else
            {
                w[plansza_samolotow[i - 1][j - 1]].o_ile.front() -= 1;
            }

        }
        else//w dol
        {
            if (i + 1 != wysokosc)
            {
                plansza_samolotow[i + 1][j - 1] = plansza_samolotow[i][j];
                w[plansza_samolotow[i + 1][j - 1]].odwiedzony = 1;
                plansza_samolotow[i][j] = -1;

                w[plansza_samolotow[i + 1][j - 1]].nazwa = "(";
                w[plansza_samolotow[i + 1][j - 1]].nazwa.push_back(w[plansza_samolotow[i + 1][j - 1]].litera);
                w[plansza_samolotow[i + 1][j - 1]].nazwa.push_back(w[plansza_samolotow[i + 1][j - 1]].o_ile.front() + 47);
                w[plansza_samolotow[i + 1][j - 1]].nazwa.push_back(')');
                w[plansza_samolotow[i + 1][j - 1]].nazwa.push_back(znaczek);
            }

            if (w[plansza_samolotow[i + 1][j - 1]].o_ile.front() == 1)
            {
                if (w[plansza_samolotow[i + 1][j - 1]].o_ile.size() > 0)
                {
                    w[plansza_samolotow[i + 1][j - 1]].o_ile.pop();
                    w[plansza_samolotow[i + 1][j - 1]].up_down.pop();
                }
            }
            else
            {
                w[plansza_samolotow[i + 1][j - 1]].o_ile.front() -= 1;
            }
        }
    }
}

void samolot_lewa(int plansza_samolotow[rozmiar_planszy][rozmiar_planszy], int &i, int &j)
{
    char znaczek = char(92);
    if (w[plansza_samolotow[i][j]].up_down.size() == 0) //prosto
    {
        plansza_samolotow[i][j + 1] = plansza_samolotow[i][j];
        w[plansza_samolotow[i][j + 1]].odwiedzony = 1;
        plansza_samolotow[i][j] = -1;

        w[plansza_samolotow[i][j + 1]].nazwa = "=(";
        w[plansza_samolotow[i][j + 1]].nazwa.push_back(w[plansza_samolotow[i][j + 1]].litera);
        w[plansza_samolotow[i][j + 1]].nazwa.push_back('0');
        w[plansza_samolotow[i][j + 1]].nazwa.push_back(')');
    }
    else
    {
        if (w[plansza_samolotow[i][j]].up_down.front() == 1)//w gore
        {
            //wyzej nie da rady
            if (i - 1 != 0)
            {
                plansza_samolotow[i - 1][j + 1] = plansza_samolotow[i][j];
                w[plansza_samolotow[i - 1][j + 1]].odwiedzony = 1;
                plansza_samolotow[i][j] = -1;

                w[plansza_samolotow[i - 1][j + 1]].nazwa = znaczek;
                w[plansza_samolotow[i - 1][j + 1]].nazwa.push_back('(');
                w[plansza_samolotow[i - 1][j + 1]].nazwa.push_back(w[plansza_samolotow[i - 1][j + 1]].litera);
                w[plansza_samolotow[i - 1][j + 1]].nazwa.push_back(w[plansza_samolotow[i - 1][j + 1]].o_ile.front() + 47);
                w[plansza_samolotow[i - 1][j + 1]].nazwa.push_back(')');
            }

            if (w[plansza_samolotow[i - 1][j + 1]].o_ile.front() == 1)
            {
                if (w[plansza_samolotow[i - 1][j + 1]].o_ile.size() > 0)
                {
                    w[plansza_samolotow[i - 1][j + 1]].o_ile.pop();
                    w[plansza_samolotow[i - 1][j + 1]].up_down.pop();
                }
            }
            else
            {
                w[plansza_samolotow[i - 1][j + 1]].o_ile.front() -= 1;
            }
        }
        else//w dol
        {
            if (i + 1 != wysokosc)
            {
                plansza_samolotow[i + 1][j + 1] = plansza_samolotow[i][j];
                w[plansza_samolotow[i + 1][j + 1]].odwiedzony = 1;
                plansza_samolotow[i][j] = -1;

                w[plansza_samolotow[i + 1][j + 1]].nazwa = znaczek;
                w[plansza_samolotow[i + 1][j + 1]].nazwa.push_back('(');
                w[plansza_samolotow[i + 1][j + 1]].nazwa.push_back(w[plansza_samolotow[i + 1][j + 1]].litera);
                w[plansza_samolotow[i + 1][j + 1]].nazwa.push_back(w[plansza_samolotow[i + 1][j + 1]].o_ile.front() + 47);
                w[plansza_samolotow[i + 1][j + 1]].nazwa.push_back(')');
            }

            if (w[plansza_samolotow[i + 1][j + 1]].o_ile.front() == 1)
            {
                if (w[plansza_samolotow[i + 1][j + 1]].o_ile.size() > 0)
                {
                    w[plansza_samolotow[i + 1][j + 1]].o_ile.pop();
                    w[plansza_samolotow[i + 1][j + 1]].up_down.pop();
                }
            }
            else
            {
                w[plansza_samolotow[i + 1][j + 1]].o_ile.front() -= 1;
            }
        }
    }
}

void ustawianie_samolotow(int plansza_samolotow[rozmiar_planszy][rozmiar_planszy])
{
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j <= szerokosc + 1; j++)
        {
            if (w[plansza_samolotow[i][j]].odwiedzony == 0)
            {
                if (plansza_samolotow[i][j] >= 0)
                {
                    if ((j == 3 && w[plansza_samolotow[i][j]].kierunek == 1) || (j == szerokosc - 4 && w[plansza_samolotow[i][j]].kierunek == 0))
                    {
                        plansza_samolotow[i][j] = -1;
                    }
                    else
                    {
                        if (w[plansza_samolotow[i][j]].kierunek == 0) // z lewej do prawej
                        {
                            samolot_lewa(plansza_samolotow, i, j);
                        }
                        else //z prawej do lewej
                        {
                            samolot_prawa(plansza_samolotow, i, j);
                        }
                    }
                }
            }
        }
    }
}

void generowanie(int &generuj, int &ktory_samolot, int plansza_samolotow[rozmiar_planszy][rozmiar_planszy])
{
    int losuj_strony, losuj_h;
    generuj += 1;
    if (generuj == 5)
    {
        generuj = 0;

        losuj_strony = rand() % 2;// 0 - lewo, 1 - prawo
        losuj_h = (rand() % (wysokosc - 2)) + 1;

        w[ktory_samolot % 25].kierunek = losuj_strony;

        if (losuj_strony == 0)
        {
            plansza_samolotow[losuj_h][losuj_strony * szerokosc] = ktory_samolot % 25;
        }
        else
        {
            plansza_samolotow[losuj_h][losuj_strony * szerokosc + 1] = ktory_samolot % 25;
        }
        ktory_samolot += 1;
    }
}

void czyszczenie_struktury(int i)
{
    w[i].odwiedzony = -1;
    while (w[i].up_down.size() > 0)
    {
        w[i].up_down.pop();
        w[i].o_ile.pop();
    }
}

void wpisywanie_komend()
{
    int numer_samolotu, ilee;
    string znaki;
    while (true)
    {
        getline(cin, znaki);

        if (znaki == "<spacja>")
        {
            break;
        }

        if (znaki.size() > 7)
        {
            numer_samolotu = znaki[1] - 65;
            ilee = znaki[7] - 48;
            if (znaki[4] == '/')//do gory
            {
                w[numer_samolotu].up_down.push(1);
                w[numer_samolotu].o_ile.push(ilee);
            }
            else if (znaki[4] == 'c')//anulowanie
            {
                if (w[numer_samolotu].up_down.size() > 0)
                {
                    w[numer_samolotu].up_down.pop();
                    w[numer_samolotu].o_ile.pop();
                }
            }
            else//w dol
            {
                w[numer_samolotu].up_down.push(-1);
                w[numer_samolotu].o_ile.push(ilee);
            }
        }
    }
}

void zderzenia(int plansza_samolotow[rozmiar_planszy][rozmiar_planszy])
{
    int kierunek, pom;
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 1; j <= szerokosc; j++)
        {
            if (plansza_samolotow[i][j] >= 0)
            {
                kierunek = w[plansza_samolotow[i][j]].kierunek;

                if (kierunek == 1)//z prawej do lewej
                {
                    //krwawedz
                    if (j - 7 == 0)
                    {
                        czyszczenie_struktury(plansza_samolotow[i][j]);
                        plansza_samolotow[i][j] = -1;
                        continue;
                    }
                    //samoloty przed nim
                    for (int k = 1; k <= 12; k++)
                    {
                        pom = j - k;
                        if (pom > 0)
                        {
                            if (plansza_samolotow[i][pom] >= 0)
                            {
                                czyszczenie_struktury(plansza_samolotow[i][j]);
                                plansza_samolotow[i][j] = -1;
                                czyszczenie_struktury(plansza_samolotow[i][pom]);
                                plansza_samolotow[i][pom] = -1;
                                continue;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                else if (kierunek == 0)//z lewej do prawej
                {
                    //krwawedz
                    if (j + 6 == szerokosc)
                    {
                        czyszczenie_struktury(plansza_samolotow[i][j]);
                        plansza_samolotow[i][j] = -1;
                        continue;
                    }
                    //samoloty przed nim
                    for (int k = 1; k <= 11; k++)
                    {
                        pom = k + j;
                        if (pom < szerokosc)
                        {
                            if (plansza_samolotow[i][pom] >= 0)
                            {
                                czyszczenie_struktury(plansza_samolotow[i][j]);
                                plansza_samolotow[i][j] = -1;
                                czyszczenie_struktury(plansza_samolotow[i][pom]);
                                plansza_samolotow[i][pom] = -1;
                                continue;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }

            }
        }
    }
}

int main()
{
    srand(time(NULL));

    vector < vector < char > > plansza; //wektor wektorów
    vector < char > pom(rozmiar_planszy); // wektor intów
    int plansza_samolotow[rozmiar_planszy][rozmiar_planszy];

    int ktory_samolot = 0; // do litery Z, potem znowu A
    int generuj = 4; // co 5 generuje nowy samolot
    string nazwa_pom;

    //generowanie planszy_samolotow
    for (int i = 0; i < rozmiar_planszy; i++)
    {
        for (int j = 0; j < rozmiar_planszy; j++)
        {
            plansza_samolotow[i][j] = -1;
        }
    }

    fill(pom.begin(), pom.end(), ' '); //wypelnienie wektora spacja
    w = new samoloty[40];
    for (int i = 0; i < rozmiar_planszy; i++)
    {
        plansza.push_back(pom);
    }

    //generowanie planszy
    for (int i = 1; i < wysokosc; i++)
    {
        plansza[i][1] = '|';
        plansza[i][szerokosc] = '|';
    }
    for (int j = 1; j <= szerokosc; j++)
    {
        plansza[wysokosc - 1][j] = '=';
        plansza[0][j] = '=';
    }

    //ustawianie litery i indeskow dla struktury
    for (int i = 0; i < 25; i++)
    {
        w[i].litera = char(i + 65);
    }

    //**********************************************************

    while (true)
    {
        //--------------------------zderzenia i krawedzie planszy-----------------------
        zderzenia(plansza_samolotow);

        ustawianie_samolotow(plansza_samolotow);
        generowanie(generuj, ktory_samolot, plansza_samolotow);
        //-------------------stan poczatkowy---------------------
        for (int i = 0; i < wysokosc; i++)
        {
            for (int j = 0; j <= szerokosc + 1; j++)
            {
                plansza[i][j] = ' ';
            }
        }
        for (int i = 1; i < wysokosc; i++)
        {
            plansza[i][1] = '|';
            plansza[i][szerokosc] = '|';
        }
        for (int j = 1; j <= szerokosc; j++)
        {
            plansza[wysokosc - 1][j] = '=';
            plansza[0][j] = '=';
        }

        //----------------------zapisywanie do tablicy----------------------
        for (int i = 0; i < wysokosc; i++)
        {
            for (int j = 0; j <= szerokosc + 1; j++)
            {
                if (plansza_samolotow[i][j] >= 0)
                {
                    w[plansza_samolotow[i][j]].odwiedzony = 0;
                    if (j == 0 || j == szerokosc + 1) //pojedynczy znak
                    {
                        plansza[i][j] = w[plansza_samolotow[i][j]].litera;
                    }
                    else //nazwy
                    {
                        nazwa_pom = w[plansza_samolotow[i][j]].nazwa;
                        if (nazwa_pom[0] == '(')
                        {
                            //leci z prawej do lewej
                            for (int k = 0; k < nazwa_pom.size(); k++)
                            {
                                plansza[i][j + k - 5] = nazwa_pom[k];
                            }
                        }
                        else
                        {
                            //leci z lewej do prawej
                            for (int k = 0; k < nazwa_pom.size(); k++)
                            {
                                plansza[i][j + k + 1] = nazwa_pom[k];
                            }
                        }

                    }
                }
            }
        }

        //------------------ wypisywanie -------------------------
        for (int i = 0; i < wysokosc; i++)
        {
            for (int j = 0; j <= szerokosc + 1; j++)
            {
                cout << plansza[i][j];
            }
            cout << endl << endl;
        }

        //------------------ wpisywanie komend --------------
        wpisywanie_komend();
        system("cls");
    }

    delete[]w;

    return 0;
}

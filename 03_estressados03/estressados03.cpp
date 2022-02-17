#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using std::cout; using std::cin; using std::vector; using std::string;

// módulo: Map
vector<int> sozinhos(const vector<int>& stress)
{
    vector <int> aux{};
    int soma{0};
    for (int i = 0; i < (int)stress.size(); i++)
    {
        for (int j = 0; j < (int)stress.size(); j++)
        {
            if (abs(stress[i]) == abs(stress[j]) && j != i) soma++;
        }
        if (soma == 0) aux.push_back(abs(stress[i]));
        soma = 0;
    }
    return aux;
}
int mais_ocorrencias(const vector<int>& stress)
{
    int maior{-1};
    int quantidade{1};
    for (int i = 0; i < (int)stress.size(); i++)
    {
        for (int j = 0; j < (int)stress.size(); j++)
        {
            if (abs(stress[i]) == abs(stress[j]) && j != i) quantidade++;
        }
        if (quantidade > maior) maior = quantidade;
        quantidade = 1;
    }
    return maior;
}
vector <int> mais_recorrentes(const vector<int>& stress)
{
    vector<int> aux{};
    int quantidade{1};
    int maior{-1};
    int aux2{1};
    for (int i = 0; i < (int)stress.size(); i++)
    {
        for (int j = 0; j < (int)stress.size(); j++)
        {
            if (abs(stress[i]) == abs(stress[j]) && j != i) quantidade++;
        }
        if (quantidade > maior) maior = quantidade;
        quantidade = 1;
    }
    for (int i = 0; i < (int)stress.size(); i++)
    {   
        for (int j = 0; j < (int)stress.size(); j++)
        {
            if (abs(stress[i]) == abs(stress[j]) && j != i) quantidade++;
        }
        for (int z = 0; z < (int)aux.size(); z++)
        {
            if (abs(stress[i]) == aux[z]) aux2++;
        }
        if (quantidade == maior && aux2 == 1) aux.push_back(abs(stress[i]));
        aux2 = 1;
        quantidade = 1;
    }
    return aux;
}


// módulo: proximidade
int briga(const vector<int>& stress)
{
    int soma{0};
    for (int i = 1; i < (int)stress.size() - 1; i++)
    {
        if (abs(stress[i]) > 50 && abs(stress[i - 1]) > 30 && abs(stress[i + 1]) > 30) soma++;
    }
    return soma;
}
vector<int> apaziguados(const vector<int>& stress)
{
    vector<int> newV{};
    for (int i = 0; i < (int)stress.size(); i++)
    {
        if (abs(stress[i]) > 80 && (abs(stress[i - 1]) < 10 || abs(stress[i + 1]) < 10)) newV.push_back(i);
    }
    return newV;
}


// módulo: Sequências
int quantos_times(const vector<int>& stress)
{
    int resp{0};
    for (int i = 0; i < (int)stress.size() - 1; i++)
    {
        if (i == 0 && stress[i] > 0 && stress[i + 1] > 0) resp++;
        else if ((stress[i] > 0 && stress[i + 1] > 0 && stress[i - 1] < 0) || (stress[i] < 0 && stress[i + 1] < 0 && stress[i - 1] > 0)) resp++;
    }
    return resp;
}
vector<int> maior_time(const vector<int>& stress)
{
    vector<int> newV{};
    int num{1};
    int maior{0};
    int maiorpos{};
    for (int i = 0; i < (int)stress.size() - 1; i++)
    {
        for (int j = i + 1; j < (int)stress.size(); j++)
        {
            while ((stress[i] > 0 && stress[j] > 0) || (stress[i] < 0 && stress[j] < 0)) num++;
        }
        if (num > maior)
        {
            maior = num;
            maiorpos = i;
        }
        num = 1;
    }
    for (int i = maiorpos; i < (int)stress.size(); i++)
    {
        newV.push_back(stress[i]);
        maior--;
        if (maior == 0) break;
    }
    return newV;
}
int sem_time(vector<int> stress)
{   
    int resp{0};
    for (int i = 0; i < (int)stress.size(); i++)
    {   
        if (i == 0 && ((stress[i] > 0 && stress[i + 1] < 0) || (stress[i] < 0 && stress[i + 1] > 0))) resp++;
        else if ((i == (int)stress.size() - 1) && ((stress[(int)stress.size() - 1] > 0 && stress[(int)stress.size() - 2] < 0) || (stress[(int)stress.size() - 1] < 0 && stress[(int)stress.size() - 2] > 0))) resp++;
        else if ((stress[i] > 0 && stress[i + 1] < 0 && stress[i - 1] < 0) || (stress[i] < 0 && stress[i + 1] > 0 && stress[i - 1] > 0)) resp++;
    }
    return resp;
}


// módulo: Grupos
int casais(vector<int> stress)
{   
    int casais{0};
    int aux{0};
    for (int i = 0; i < (int)stress.size(); i++)
    {
        if (stress[i] > 0)
        {
            for (int j = 0; j < (int)stress.size(); j++)
            {
                aux = stress[i] * -1;
                if (stress[j] == aux) casais++;
            }
        }
    }
    return casais;
}
int trios(vector<int> stress)
{
    int trios{0};
    for (int i = 0; i < (int)stress.size() - 2; i++)
    {
        for (int j = i + 1; j < (int)stress.size() - 1; j++)
        {
            if (stress[i] == stress[j])
            {
                for (int k = j + 1; k < (int)stress.size(); k++)
                {
                    if (stress[i] == stress[k]) trios++;
                }
            }
        }
    }
    return trios;
}


// módulo: Alteração
vector<int> remove(vector<int>& stress, int a)
{
    stress.erase(stress.begin() + a);
    return stress;
}
vector<int> insert(vector<int>& stress, int pos, int valor)
{
    stress.insert(stress.begin() + pos, valor);
    return stress;
}
vector<int> dance(vector<int> stress)
{
    for (int i = 0; i < (int)stress.size() - 1; i++)
    {
        if (abs(stress[i]) == abs(stress[i + 1]))
        {
            stress.erase(stress.begin() + i + 1);
            stress.erase(stress.begin() + i);
            stress = dance(stress);
        }
    }
    return stress;
}
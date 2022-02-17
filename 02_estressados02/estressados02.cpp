#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using std::cout; using std::cin; using std::vector; using std::string;


// módulo: busca
bool repet(vector<int> a, int b)
{
    int aux {0};
    for (int i = 0; i < (int)a.size(); i++){
        if  (a[i] == b){
            aux++;
        }
    }
    if (aux > 1) return true;
    return false;

}
bool exist(vector<int> a, int b)
{
    for(int i = 0; i < (int)a.size(); i++)
    {
        if (a[i] == b) return true;
    }
    return false;
}


// módulo: filter
vector<int> clonar(const vector<int>& stress) 
{
    vector<int> newV;

    for (int i = 0; i < (int) (int)stress.size(); i++) 
    {
        newV.push_back(stress[i]);
    }
    return newV;
}
vector<int> pegar_homens(const vector<int>& stress)
{
    vector<int> men;

    for (int i = 0; i < (int)stress.size(); i++)
    {
        if (stress[i] > 0) men.push_back(stress[i]);
    }

    return men;
}
vector<int> pegar_calmos(const vector<int>& stress)
{
    vector<int> calm;

    for (int i = 0; i < (int)stress.size(); i++)
    {
        if (stress[i] != 0 && abs(stress[i]) < 10) calm.push_back(stress[i]);
    }

    return calm;
}
vector<int> pegar_mulheres_calmas(const vector<int>& stress)
{
    vector<int> calmW;

    for (int i = 0; i < (int)stress.size(); i++)
    {
        if (stress[i] < 0 && stress[i] > -10) calmW.push_back(stress[i]);
    }

    return calmW;
}



// acesso
vector<int> inverter_com_copia(const vector<int>& stress)
{
    vector<int> invert;
    for (int i = ((int)stress.size() - 1); i >= 0; i--) 
    {
        invert.push_back(stress[i]);
    }
    return invert;
}
void inverter_inplace(vector<int>& stress)
{
    int aux = 0, aux2 = ((int)stress.size() - 1), aux3 = 0;
    for (int i = 0; i < (int)stress.size() / 2; i++)
    {
        aux = stress[i];
        aux3 = stress[aux2];
        stress[i] = aux3;
        stress[aux2] = aux;
        aux2--;
    }
}
int sortear(const vector<int>& stress)
{
    srand (time(NULL));
    int a {rand() % (int)stress.size()};
    return stress[a];
}
void embaralhar(vector<int>& stress)
{
    srand (time(NULL));
    for (int i = 0; i < (int)stress.size() / 2; i++)
	{
		int z{0}, a{0};
        while (z == 0)
        {
            a = rand() % (int)stress.size();
            if (a != 0) z = 1;
        }
		int aux = stress[i];
		stress[i] = stress[a];
		stress[a] = aux;
	}
}
void ordenar(vector<int>& stress)
{
    sort(stress.begin(), stress.end());
}



// Conjuntos
vector<int> exclusivos(const vector<int>& stress)
{
    vector<int> newV {};
    for (int i = 0; i < (int)stress.size(); i++) 
    {
        int aux{0};
        for (int j = 0; j < (int)newV.size(); j++) 
        {
            if(stress[i] == newV[j]) 
            {
                aux++;
            }
        }
        if (aux == 0) newV.push_back(stress[i]);
    }
    return newV;
}
vector<int> diferentes(const vector<int>& stress)
{
    vector<int> newV {};
    for (int i = 0; i < (int)stress.size(); i++) 
    {
        int aux{0};
        for (int j = 0; j < (int)newV.size(); j++) 
        {
            if(abs(stress[i]) == abs(newV[j])) 
            {
                aux++;
            }
        }
        if (aux == 0) newV.push_back(abs(stress[i]));
    }
    return newV;
}
vector<int> abandonados(const vector<int>& stress)
{
    vector<int> aux{};

    for (int i = 0; i < (int)stress.size(); i++)
    {
        if (repet(stress, stress[i]) && !exist(aux,stress[i]))
        {
            aux.push_back(stress[i]);       
        }
    }
    return aux;
}
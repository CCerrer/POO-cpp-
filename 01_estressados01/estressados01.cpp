#include <iostream>
#include <vector>
#include <algorithm>


// módulo: busca
std::string existe(std::vector<int> stress, int x)
{
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i] == x) return "Existe";
    }
    return "Não existe";
}
int contar(std::vector<int> stress, int x)
{
    int soma = 0;
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i] == x) soma++;
    }
    return soma;
}
int procurar_valor(std::vector<int> stress, int x)
{
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i] == x) return i;
    }
}
int procurar_valor_apos(std::vector<int> stress, int valor, int inicial)
{
    for (int i = inicial; i< stress.size(); i++)
    {
        if (stress[i] == valor) return i;
    }
}



// módulo: melhor caso
int procurar_menor(std::vector<int> stress)
{
    return *min_element(stress.begin(), stress.end());
}
int procurar_maior(std::vector<int> stress)
{
    return *max_element(stress.begin(), stress.end());
}
int procurar_menor_pos(std::vector<int> stress)
{
    int x = *min_element(stress.begin(), stress.end());
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i] == x) return i;
    }
}
int procurar_menor_pos_apos(std::vector<int> stress, int x)
{
    int aux {101};
    for (int i = x; i < stress.size(); i++)
    {
        if (stress[i] < aux) aux = stress[i];
    }
    return aux;
}
int procurar_melhor_se(std::vector<int> stress)
{
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i] <= 0) stress[i] = 99999;
    }
    int x = *min_element(stress.begin(), stress.end());
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i] == x) return i;
    }
}



// módulo: contagem
float calcular_stress_medio(std::vector<int> stress)
{
    float media = 0;
    for (int i = 0; i < stress.size(); i++)
    {
        media += abs(stress[i]);
    }
    media = media/stress.size();
    return media;
}
std::string mais_homens_ou_mulheres(std::vector<int> stress)
{
    int mulheres = 0, homens = 0;
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i]>0) homens++;
        else mulheres++;
    }
    if (mulheres>homens) return "Mulheres";
    else if (mulheres = homens) return "Números iguais";
    else return "Homens";
}
std::string qual_metade_eh_mais_estressada(std::vector<int> stress)
{
    int v1 = 0, v2 = 0;
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i] > 0) v1 += stress[i];
        else v2 += abs(stress[i]);
    }
    if (v1 > v2) return "Homens";
    else if (v1 == v2) return "Tem o mesmo nível de stress";
    else return "Mulheres";
}
std::string homens_sao_mais_estressados_que_mulheres(std::vector<int> stress)
{
    int v1 = 0, v2 = 0, h = 0, m = 0;
    for (int i = 0; i < stress.size(); i++)
    {
        if (stress[i] > 0) 
        {
            v1 += stress[i];
            h++;
        }
        else 
        {
            v2 += abs(stress[i]);
            m++;
        }
    }
    v1 = v1/h;
    v2 = v2/m;
    if (v1 > v2) return "Sim";
    else if (v1 == v2) return "A média do stress dos homens e das mulheres é igual";
    else return "Não";
}
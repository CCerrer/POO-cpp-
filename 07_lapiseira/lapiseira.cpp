#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>

struct Grafite
{
    float caliber {0.0};

    std::string toughness {""};

    int size {0};

    Grafite(float caliber = 0.0, std::string toughness = "", int size = 0)
        : caliber(caliber), toughness(toughness), size(size)
    {
    }

    int damage_per_sheet()
    {
        if (this->toughness == "HB")
            return 1;
        else if (this->toughness == "2B")
            return 2;
        else if (this->toughness == "4B")
            return 4;
        else if (this->toughness == "6B")
            return 6;
        return 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Grafite& grafite)
    {
        os << "[" << grafite.caliber << ":" << grafite.toughness << ":" << grafite.size << "]";
        return os;
    }
};


struct Lapiseira
{
    float caliber {0.0};

    std::vector<Grafite> grafites;

    Grafite* bico {nullptr};

    Lapiseira(float caliber = 0.0)
        : caliber(caliber)
    {
    }

    bool insert_grafite(Grafite& grafite)
    {
        if (grafite.caliber != this->caliber)
        {
            std::cout << "fail: calibre incompatível\n";
            return false;
        }
        this->grafites.push_back(grafite);

        return false;
    }

    bool pull_grafite()
    {
        if (this->bico == nullptr)
        {
            this->bico = &this->grafites[0]; 
            return true;
        }
        else
        {
            std::cout << "fail: ja existe grafite no bico\n";
            return false;
        }
    }

    bool remove_grafite()
    {
        if (this->bico != nullptr)
        {
            this->bico = nullptr;
            this->grafites.erase(this->grafites.begin());
            return true;
        }
        else
        {
            std::cout << "fail: insira um grafite primeiro\n";
            return false;
        }
    }

    void write_page(int pages) 
    {
        int aux{0};

        if (this->bico == nullptr)
        {
            std::cout << "fail: insira um grafite primeiro\n";
        }

        else
        {
            if(this->bico->size == 10)
            {
                std::cout << "fail: grafite pequeno demais\n";
            }

            else if((this->grafites[0].size - this->grafites[0].damage_per_sheet()) <= 10)
            {
                std::cout << "fail: folha incompleta\n";
                this->grafites[0].size = 10;
            }

            else
            {
            this->grafites[0].size -= this->grafites[0].damage_per_sheet(); 
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Lapiseira& lapiseira)
    {
        os << "calibre: ";
        if (lapiseira.caliber == 0)
            std::cout << "null";
        else 
            std::cout << lapiseira.caliber;

        if (lapiseira.bico != nullptr)
        {
            os << ", bico: " << *lapiseira.bico;
        }
        else
        {
            os << ", bico: {}";
        }

        if (lapiseira.grafites.empty())
        {
            os << ", tambor: {}";
        }
        else
        {
            os << ", tambor: {";
            for (int i = 0; i < (int)lapiseira.grafites.size(); i++) 
            {
                if (i == 0 && lapiseira.bico != nullptr) continue;
                os << lapiseira.grafites[i];
            }   
            os << "}";
        }

        return os;
    }

};

int main()
{
    Lapiseira faber_castell;

    while (true)
    {
        std::cout << "$";

        std::string line;

        std::getline(std::cin, line);

        std::stringstream ss(line);

        std::string cmd;

        ss >> cmd;

        if (cmd == "end")
        {
            break;
        }

        else if (cmd == "show")
        {
            std::cout << faber_castell << std::endl;
        }

        else if (cmd == "init")
        {
            float caliber;

            ss >> caliber;
            
            faber_castell = Lapiseira(caliber);
        }

        else if (cmd == "insert")
        {
            float caliber;

            std::string toughness;

            int size;

            ss >> caliber >> toughness >> size;

            Grafite grafite(caliber, toughness, size);

            faber_castell.insert_grafite(grafite);
        }

        else if (cmd == "pull")
        {
            faber_castell.pull_grafite();
        }

        else if (cmd == "remove")
        {
            faber_castell.remove_grafite();
        }

        else if (cmd == "write")
        {
            int pages;

            ss >> pages;

            faber_castell.write_page(pages);
        }

        else
        {
            std::cout << "fail: comando inválido" << std::endl;
        }
    }
}
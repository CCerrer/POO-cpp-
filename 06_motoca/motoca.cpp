#include <iostream>
#include <sstream>

struct Pessoa
{
    std::string nome;
    int idade;

    Pessoa(std::string nome = "", int idade = 0) : nome(nome), idade(idade)
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const Pessoa &pessoa)
    {
        os << "[Nome: " << pessoa.nome << ", Idade: " << pessoa.idade << "]";
        return os;
    }
    
};

struct Motinha
{
    int potencia{1};
    int tempo {0};
    Pessoa *pessoa {nullptr};

    Motinha()
    {
    }

    Motinha(int potencia) : potencia(potencia)
    {
    }

    std::string buzinar()
    {
        return "B" + std::string(this->potencia, 'i');
    }

    bool dirigir(int tempo)
    {
        if (this->pessoa->idade > 10)
        {
            std::cout << "fail: muito grande para andar de motoca" << std::endl;
            return false;
        }

        if (this->pessoa->idade < 4)
        {
            std::cout << "fail: muito pequeno para andar de motoca" << std::endl;
            return false;
        }

        if (this-> tempo == 0)
        {
            std::cout << "fail: tempo zerado" << std::endl;
            return false;
        }

        if (tempo > this->tempo)
        {
            std::cout << "fail: andou " << this->tempo << " min e acabou o tempo" << std::endl;
            this->tempo = 0;
            return false;
        }

        if (tempo < this->tempo)
        {
            this->tempo -= tempo;
            return true;
        }
        return false;
    }

    Pessoa *remover_pessoa()
    {
        Pessoa *p = this->pessoa;
        this->pessoa = nullptr;
        return p;
    }

    bool inserir_pessoa(Pessoa *pessoa)
    {
        if (this->pessoa != nullptr)
        {
            return false;
        } 
        this -> pessoa = pessoa;
        return true;
    }

    bool buy(int valor)
    {
        this->tempo += valor;
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, const Motinha &motinha)
    {
        os << "potencia: " << motinha.potencia << ", minutos: " << motinha.tempo << ", pessoa: ";
        if (motinha.pessoa != nullptr)
        {
            os << "[" << motinha.pessoa->nome << ":" << motinha.pessoa->idade << "]";
        }
        else
        {
            os << "null";
        }
        return os;
    }

};


int main()
{
    Motinha m;

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
        if (cmd == "init")
        {
            int potencia{0};
            ss >> potencia;
            m = Motinha(potencia);
        }
        else if (cmd == "show")
        {
            std::cout << m << std::endl;
        }
        else if (cmd == "in")
        {
            std::string nome{""};
            int idade{0};
            ss >> nome;
            ss >> idade;
            Pessoa *p = new Pessoa(nome, idade);
            if(!m.inserir_pessoa(p))
            {
                std::cout << "Não foi possível inserir a pessoa" << std::endl;
                delete p;
            }
            m.inserir_pessoa(p);
        }
        else if (cmd == "out")
        {
            Pessoa *p = m.remover_pessoa();
            if (p != nullptr)
            {
                delete p;
            }
            else
                std::cout << "fail: moto vazia" << std::endl;
        }
        else if (cmd == "honk")
        {
            if (m.pessoa != nullptr)
                std::cout << m.buzinar() << std::endl;
            else
                std::cout << "fail: moto vazia" << std::endl;
        }
        else if (cmd == "buy")
        {
            int valor{0};
            ss >> valor;
            m.buy(valor);
        }
        else if (cmd == "drive")
        {
            int tempo{0};
            ss >> tempo;
            m.dirigir(tempo);
        }
        else if (cmd == "drive")
        {
            int tempo{0};
            ss >> tempo;
            m.dirigir(tempo);
        }
        else 
        {
            std::cout << "Comando inválido" << std::endl;
        }
    }
}
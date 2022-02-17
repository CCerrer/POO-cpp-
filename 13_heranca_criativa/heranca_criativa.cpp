#include <iostream>
#include <ctime>
#include <sstream>
#include <stdlib.h>
#include <iomanip>


class Person
{
protected:
    std::string tag {"Person"};

    bool alive {true};

public:
    Person()
    {
        std::cout << "Person created" << std::endl;
    }

    virtual ~Person()
    {
        std::cout << "Body destroyed" << std::endl;
    }

    bool isAlive() const
    {
        return alive;
    }

    virtual void kill()
    {
        this->alive = false;
    }
};


class Beggar : public Person
{
protected:
    std::string name {"sem nome lek"};

    double money {0.0};

    double debt {0.0};

public:
    Beggar(std::string name,double debt) : Person()
    {
        this->name = name;
        this->debt = debt;
        this->tag = ", the Beggar ";
    }

    friend std::ostream& operator<<(std::ostream& os, const Beggar& beggar)
    {
        os << "\nName: " << beggar.name << beggar.tag << std::endl;
        os << "Debt: " << std::setprecision(3) << beggar.debt << std::endl;
        os << "Money: " << std::setprecision(3) << beggar.money << std::endl;
        os << "Alive: " << (beggar.isAlive() ? "Yes" : "No") << std::endl;
        return os;
    }

    void donation(double amount)
    {
        this->money += amount;

        if(debt > 0)
        {
            debt -= amount;
        }

        std::cout << std::setprecision(3) << this->name << " has now " << this->money << "$ money and has " << this->debt << "$ debt" << std::endl;
    }

    void setName(std::string name)
    {
        if(this->name == "")
        {
            this->name = name;

            std::cout << "Name set to " << this->name << std::endl;
        }

        else
        {
            this->name = name;

            std::cout << "Name changed to " << this->name << std::endl;
        }

    }

    void setDebt(double debt)
    {
        this->debt = debt;

        std::cout << std::setprecision(3) << "Debt set to " << this->debt << std::endl;
    }

    void setMoney(double money)
    {
        this->money = money;

        std::cout << std::setprecision(3) << "Money set to " << this->money << std::endl;
    }

    void beg()
    {
        srand(time(NULL));

        double amount = std::rand() % 20 + 1;

        std::cout << "The poor" << this->name << " earned " << amount << "$" << std::endl;

        this->donation(amount);
    }

    void kill()
    {
        Person::kill();

        std::cout << this->name << " has been brutally killed by a street dog while sleeping" << std::endl;
    }
};

void commandRoom(Beggar& beggar)
{
    std::cout << "You are in the god room" << std::endl;

    std::cout << "You see a beggar, what's his name?\n" << std::endl;

    std::string name;

    std::cin >> name;

    beggar.setName(name);

    std::cout << "\nSay 'cmd' to see the commands\n" << std::endl;

    std::string command{""};

    bool first{false};

    while(true)
    {
        if (first)
        {
            std::cout << "\n";
        }

        first = true;

        getline(std::cin, command);

        std::stringstream ss{command};

        std::string cmd{""};

        ss >> cmd;

        if(cmd == "cmd")
        {
            std::cout << "\ncommands:\n1-('name' + the name) change the name\n2-('debt' + quantity) set a debt\n3-('donate' + quantity) give money\n4-(beg) make him beg on Avenida Paulista for a whole day\n5-(kill) kill the poor beggar\n6-(show) see the beggar informations\n7-(cmd) see the commands\n8- (end)leave god room" << std::endl;
        }

        else if(cmd == "name")
        {
            std::string name{""};

            ss >> name;

            beggar.setName(name);
        }

        else if(cmd == "debt")
        {
            double debt{0.0};

            ss >> debt;

            beggar.setDebt(debt);
        }

        else if(cmd == "donate")
        {
            double amount{0.0};

            ss >> amount;

            beggar.donation(amount);
        }

        else if(cmd == "beg")
        {
            beggar.beg();
        }

        else if(cmd == "lottery")
        {
            beggar.donation(2.0);
        }

        else if(cmd == "kill")
        {
            beggar.kill();
        }

        else if(cmd == "end")
        {
            break;
        }

        else if(cmd == "show")
        {
            std::cout << beggar;
        }
    }
}

int main()
{
    Beggar beggar {"", {}};

    commandRoom(beggar);

    return 0;
}
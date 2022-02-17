#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <vector>
#include <iomanip>


class Account
{
protected:
    float balance {0.0};
    
    std::string clientId {""};

    int id {0};

    std::string type {""};

public:
    Account(int id, std::string clientId)
    {
        this->id = id;

        this->clientId = clientId;
    }

    virtual ~Account()
    {
    }

    virtual void monthlyUpdate() = 0;

    void deposit(float value)
    {
        this->balance += value;
    }

    void withdraw(float value)
    {
        this->balance -= value;
    }

    void transfer(Account &account, float value)
    {
        this->withdraw(value);

        account.deposit(value);
    }

    float getBalance()
    {
        return this->balance;
    }

    int getId()
    {
        return this->id;
    }

    std::string getClientId()
    {
        return this->clientId;
    }

    std::string getType()
    {
        return this->type;
    }

    friend std::ostream &operator<<(std::ostream& os, Account& account)
    {
        os << account.getId() << ":" << account.getClientId() << ":" << std::setprecision(2) << std::fixed << account.getBalance() << ":" << account.getType();

        return os;
    }
};


class SavingsAccount : public Account
{
public:
    SavingsAccount(int id, std::string clientId) : Account(id, clientId)
    {
        this->type = "CP";
    }

    virtual void monthlyUpdate() 
    {
        balance += balance/100;
    }
};


class CheckingAccount : public Account
{
public:
    CheckingAccount(int id, std::string clientId) : Account(id, clientId)
    {
        this->type = "CC";
    }

    virtual void monthlyUpdate()
    {
        balance -= 20;
    }
};


class Client
{
private:
    std::vector<std::shared_ptr<Account>> accounts {};

    std::string clientId {""};

public:
    Client(std::string clientId)
    {
        this->clientId = clientId;
    }

    void addAccount(std::shared_ptr<Account> account)
    {
        accounts.push_back(account);
    }

    std::string getClientId()
    {
        return this->clientId;
    }

    std::vector<std::shared_ptr<Account>> getAccounts()
    {
        return this->accounts;
    }

    void setAccounts(std::vector<std::shared_ptr<Account>> accounts)
    {
        this->accounts = accounts;
    }

    void setClientId(std::string clientId)
    {
        this->clientId = clientId;
    }

    friend std::ostream &operator<<(std::ostream& os, const Client& client) 
    {
        for(auto& account : client.accounts)
        {
            os << *account << "\n";
        }

        return os;
    }
};


class BankAgency
{
private:
    std::map<int, std::shared_ptr<Account>> accounts {};

    std::map<std::string, std::shared_ptr<Client>> clients {};

    int nextAccountId {0};

    std::shared_ptr<Account> getAccount(int id)
    {
        return accounts[id];
    }

public:
    BankAgency() {}

    void addClient(std::string clientId)
    {
        this->clients[clientId] = std::make_shared<Client>(clientId);

        this->accounts[nextAccountId] = std::make_shared<CheckingAccount>(nextAccountId, clientId);

        this->clients[clientId].get()->addAccount(this->getAccount(nextAccountId));

        nextAccountId++;
        
        this->accounts[nextAccountId] = std::make_shared<SavingsAccount>(nextAccountId, clientId);

        this->clients[clientId].get()->addAccount(this->getAccount(nextAccountId));

        nextAccountId++;
    }

    void deposit(int accountId, float value)
    {
        if(accountId < 0 || accountId >= nextAccountId)
        {
            std::cout << "fail: conta nao encontrada\n";
        }

        else
        {
            this->getAccount(accountId).get()->deposit(value);
        }
    }

    void withdraw(int accountId, float value)
    {
        if(accountId < 0 || accountId >= nextAccountId)
        {
            std::cout << "fail: conta nao encontrada\n";
        }

        else if(this->getAccount(accountId).get()->getBalance() < value)
        {
            std::cout << "fail: saldo insuficiente\n";
        }

        else
        {
            this->getAccount(accountId).get()->withdraw(value);
        }
    }

    void transfer(int Id, int Id2, float value)
    {
        if(Id < 0 || Id >= nextAccountId || Id2 < 0 || Id2 >= nextAccountId)
        {
            std::cout << "fail: conta nao encontrada\n";
        }

        else if(this->getAccount(Id).get()->getBalance() < value)
        {
            std::cout << "fail: saldo insuficiente\n";
        }

        else
        {
            this->getAccount(Id).get()->transfer(*this->getAccount(Id2).get(), value);
        }
    }

    void update()
    {
        for(auto& client : this->clients)
        {
            for(auto& account : client.second.get()->getAccounts())
            {
                account.get()->monthlyUpdate();
            }
        }
    }

    friend std::ostream &operator<<(std::ostream& os, const BankAgency& bank){
        
        os << "Clients:\n";

        for(auto client : bank.clients)
        {
            os << "- " << client.first << "[";

            int i = 1;

            for(auto& clientAccount : client.second.get()->getAccounts())
            {
                if(i < (int) client.second.get()->getAccounts().size())
                {
                    os << clientAccount->getId() << ", ";

                    i++;
                }

                else
                {
                    os << clientAccount->getId();
                }
            }

            os << "]\n";
        }

        os << "Accounts:\n";

        for(auto& account : bank.accounts)
        {
            os <<  *account.second << "\n";
        }
        
        return os;
    }
};



void command_room(BankAgency& bancoFerrer)
{
    std::string command{""};

    bool first{false};

    while(true)
    {
        if (first)
        {
            std::cout << "\n";
        }

        first = true;

        std::cout << "$";

        getline(std::cin, command);

        std::stringstream ss{command};

        std::string cmd{""};

        ss >> cmd;

        if(cmd == "end")
        {
            break;
        }

        else if(cmd == "addCli")
        {
            std::string clientId{""};

            ss >> clientId;

            bancoFerrer.addClient(clientId);
        }

        else if(cmd == "show")
        {
            std::cout << bancoFerrer;
        }

        else if(cmd == "deposito")
        {
            int id {0};

            float value {0.0};

            ss >> id >> value;

            bancoFerrer.deposit(id, value);
        }

        else if(cmd == "saque")
        {
            int id{0};

            float value{0.0};

            ss >> id >> value;

            bancoFerrer.withdraw(id, value);
        }

        else if(cmd == "transf")
        {
            int id{0};

            int id2{0};

            float value{0.0};

            ss >> id >> id2 >> value;

            bancoFerrer.transfer(id, id2, value);
        }

        else if(cmd == "update") 
        {
            bancoFerrer.update();
        }
    }
}
        


int main()
{
    BankAgency bancoFerrer;

    command_room(bancoFerrer);

    return 0;
}
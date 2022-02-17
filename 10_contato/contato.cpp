#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>
#include <sstream>

class Phone
{
private:
    std::string id;

    std::string number;

public:
    Phone(std::string id = "", std::string number = "") : id(id), number(number) {}

    bool isValid(std::string number)
    {
        for (auto i{0}; i < (int)number.size(); i++)
        {
            if((number[i] < 48 && number[i] != 40 && number[i] != 41 && number[i] != 45 && number[i] != 46) || number[i] > 57)
            {
                return false;
            }
        }
        return true;
    }

    std::string getId()
    {
        return id;
    }

    std::string getNumber()
    {
        return number;
    }

    void setNumber(std::string number)
    {
        this->number = number;
    }

    void setId(std::string id)
    {
        this->id = id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Phone& phone)
    {
        os << phone.id << ":" << phone.number;
        return os;
    }
};


class Contact
{
private:
    std::string name{""};

    std::vector<Phone> phones{};

    std::string prefix;

public:
    Contact(std::string name, std::vector<Phone> phones) : name(name), phones(phones) {}

    void addPhone(Phone phone)
    {
        if(phone.isValid(phone.getNumber()))
        {
            phones.push_back(phone);
        }

        else
        {
            std::cout << "Invalid phone number" << std::endl;
        }
    }

    std::string getName()
    {
        return name;
    }

    void setName(std::string name)
    {
        this->name = name;
    }

    std::vector<Phone> getPhones()
    {
        return phones;
    }

    void setPhones(std::vector<Phone> phones)
    {
        this->phones = phones;
    }

    void rmPhone(int index)
    {
        phones.erase(phones.begin() + index);
    }

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact)
    {
        os << "- " << contact.name << " ";

        if(!contact.phones.empty())
        {
            for (int i{0}; i < (int)contact.phones.size(); i++)
            {
                os << "[" << i << ":" << contact.phones[i] << "] ";
            }
        }
        
        return os;
    }
};


void command_room(Contact& contact)
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

        else if(cmd == "init")
        {
            std::string name{""};

            ss >> name;

            contact.setName(name);
        }

        else if(cmd == "show")
        {
            std::cout << contact << std::endl;
        }

        else if(cmd == "add")
        {
            std::string id{""};
            
            std::string number{""};

            ss >> id >> number;

            Phone a(id, number);
            
            contact.addPhone(a);
        }

        else if(cmd == "rm")
        {
            int index{0};

            ss >> index;

            contact.rmPhone(index);
        }

        else
        {
            std::cout << "Command not found" << std::endl;
        }
    }
}


int main()
{
    Contact contact{"", {}};

    command_room(contact);

    return 0;
}
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

    Contact() {}

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


class contact_book
{
private:
    std::vector<Contact> contacts;

public:
    contact_book() {}

    int getIndex(std::string name)
    {
        for (int i{0}; i < (int)contacts.size(); i++)
        {
            if(contacts[i].getName() == name)
            {
                return i;
            }
        }
        return -1;
    }

    void addContact(std::stringstream& ss, Contact contact)
    {
        std::string aux{""};

        while(ss >> aux)
        {
            std::string id{""};

            std::string number{""};

            int index = aux.find(":");

            id = aux.substr(0, index);

            number = aux.substr(index + 1, aux.size());

            Phone phone{id, number};

            contact.addPhone(phone);
        }

        int aux2 = getIndex(contact.getName());

        if(aux2 == -1)
        {
            contacts.push_back(contact);
        }

        else
        {
            for (int i{0}; i < (int)contact.getPhones().size(); i++)
            {
                contacts[aux2].addPhone(contact.getPhones()[i]);
            }
        }

        std::sort(contacts.begin(), contacts.end());
    }

    void rmContact(std::string name)
    {
        for (int i{0}; i < (int)contacts.size(); i++)
        {
            if(contacts[i].getName() == name)
            {
                contacts.erase(contacts.begin() + i);
            }
        }
    }

    std::vector<Contact> getContacts()
    {
        return contacts;
    }

    friend std::ostream& operator<<(std::ostream& os, const contact_book& contact_book)
    {
        for (int i{0}; i < (int)contact_book.contacts.size(); i++)
        {
            os << contact_book.contacts[i] << std::endl;
        }

        return os;
    }
};


void command_room(contact_book& contact_book)
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

        if(cmd == "add")
        {
            std::string string{""};

            ss >> string;

            Contact contact;

            contact.setName(string);

            contact_book.cutString(ss, contact);

            contact_book.addContact(ss, contact);            
        }

        else if(cmd == "show")
        {
            std::cout << contact_book;
        }

        else if(cmd == "end")
        {
            break;
        }
    }
}


int main(){
    contact_book contact_book;

    command_room(contact_book);

    return 0;
}
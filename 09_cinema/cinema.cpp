#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

class Client
{
private:
    std::string id;
    std::string phone;

public:
    Client(std::string id = "", std::string phone = "") : id(id), phone(phone) {}

    std::string getId()
    {
        return this->id;
    }

    std::string getPhone()
    {
        return this->phone;
    }

    void setId(std::string id)
    {
        this->id = id;
    }

    void setPhone(std::string phone)
    {
        this->phone = phone;
    }

    friend std::ostream &operator<<(std::ostream &os, const Client &client)
    {
        os << "(" << client.id << ":" << client.phone << ")";

        return os;
    }
};


class Room
{
private:
    std::vector<std::shared_ptr<Client>> chairs;

public:
    Room(int capacity = 0) : chairs(capacity) {}

    int getCapacity()
    {
        return this->chairs.size();
    }

    bool alreadyIn(std::string id)
    {
        for(int i = 0; i < (int)chairs.size(); i++)
        {
            if(chairs[i] != nullptr && chairs[i]->getId() == id)
            {
                return true;
            }
        }

        return false;
    }

    bool reserve(std::string id, std::string phone, int seat)
    {
        if (seat < 0 || seat >= this->getCapacity())
        {
            std::cout << "Seat number is out of range" << std::endl;

            return false;
        }

        if (this->chairs[seat] != nullptr)
        {
            std::cout << "Seat is already taken" << std::endl;

            return false;
        }

        if (this->alreadyIn(id))
        {
            std::cout << "Client is already in the room" << std::endl;

            return false;
        }

        this->chairs[seat] = std::make_shared<Client>(id, phone);
        
        return true;
    }

    bool cancel(std::string id)
    {
        for (auto &chair : this->chairs)
        {
            if (chair != nullptr && chair->getId() == id)
            {
                chair = nullptr;

                std::cout << "Reservation cancelled" << std::endl;

                return true;
            }
        }

        std::cout << "Reservation not found" << std::endl;

        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Room &room)
    {
        os << "[";

        for(auto chair : room.chairs)
        {
            if(chair == nullptr)
            {
                os << "- ";
            }
            else
            {
                os << *chair << "";
            }
        }

        os << "]\n";

        return os;
    }
};



void command_room(Room& room)
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

        std::stringstream ss(command);

        std::string cmd;

        ss >> cmd;

        if(cmd == "end")
        {
            break;
        }

        else if(cmd == "show")
        {
            std::cout << room;
        }

        else if(cmd == "init")
        {
            int capacity{0};

            ss >> capacity;

            room = Room(capacity);
        }

        else if(cmd == "reserve")
        {
            std::string id;

            std::string phone;

            int seat{0};

            ss >> id >> phone >> seat;

            room.reserve(id, phone, seat);
        }

        else if(cmd == "cancel")
        {
            std::string id{""};

            ss >> id;

            room.cancel(id);
        }

        else
        {
            std::cout << "Unknown command: " << cmd << "\n";
        }
    }
}


int main()
{
    Room room{};

    command_room(room);

    return 0;
}
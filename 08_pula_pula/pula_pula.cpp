#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <memory>

class Kid
{
private:
    std::string name;

    int age;

public:
    Kid(std::string name = "", int age = 0) : name(name), age(age) {}

    std::string getName()
    {
        return this->name;
    }

    int getAge()
    {
        return this->age;
    }

    void setName(std::string name) 
    {
        this->name = name;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    friend std::ostream &operator<<(std::ostream &os, const Kid &kid)
    {
        os << "(" << kid.name << ":" << kid.age << ")";

        return os;
    }
};


class Trampoline
{
private:
    std::list <std::shared_ptr<Kid>> playing;

    std::list <std::shared_ptr<Kid>> waiting;

public:
    void arrive(const std::shared_ptr<Kid>& list)
    {
        waiting.push_back(list);
    }

    void in()
    {
        if (waiting.empty())
        {
            std::cout << "fail: Waiting list empty\n";
        }

        else
        {
            playing.push_back(waiting.front());

            std::cout << this->waiting.front()->getName() << " successfully added to trampoline\n";

            waiting.pop_front();
        }
    }

    void out()
    {
        if (playing.empty())
        {
            std::cout << "fail: Playing list empty\n";
        }

        else
        {
            waiting.push_back(playing.front());

            std::cout << this->playing.front()->getName() << " removed from trampoline\n";

            playing.pop_front();
        }
    }

    void remove(std::string name)
    {
        for (auto it = waiting.begin(); it != waiting.end(); it++)
        {
            if ((*it)->getName() == name)
            {
                waiting.erase(it);

                break;
            }
        }

        for (auto it = playing.begin(); it != playing.end(); it++)
        {
            if ((*it)->getName() == name)
            {
                playing.erase(it);
                
                break;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Trampoline& trampoline)
    {
        os << "---Waiting---\n";

        if(!trampoline.waiting.empty())
        {
            for(auto it = trampoline.waiting.rbegin(); it != trampoline.waiting.rend(); it++)
            {
                os << *it->get() << "\n";
            }
        }
        
        else
        {
            os << "{No one is waiting}\n";
        }

        os << "\n---Playing---\n";

        if(!trampoline.playing.empty())
        {
            for(auto jt = trampoline.playing.rbegin(); jt != trampoline.playing.rend(); jt++)
            {
                os << *jt->get() << "\n";
            }
        }

        else
        {
            os << "{No one is playing}";
        }

        return os;
    }
};

void command_room(Trampoline& trampoline)
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

        else if(cmd == "arrive")
        {
            std::string name{""};

            int age{0};

            ss >> name >> age;

            trampoline.arrive(std::make_shared<Kid>(name, age));

            std::cout << "kid added\n";
        }

        else if(cmd == "show")
        {
            std::cout << trampoline << "\n";
        }

        else if(cmd == "enter")
        {
            trampoline.in();
        }

        else if(cmd == "leave")
        {
            trampoline.out();
        }

        else if(cmd == "remove")
        {
            std::string name{""};

            ss >> name;

            trampoline.remove(name);

            std::cout << name << " removed\n";
        }

        else
        {
            std::cout << "Invalid command\n";
        }
    }
}


int main()
{
    Trampoline trampoline;

    command_room(trampoline);

    return 0;
}
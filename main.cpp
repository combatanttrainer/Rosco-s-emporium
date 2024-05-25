#include <iostream>
#include <conio.h>
#include <string_view>
#include <string>
#include <limits>
#include <array>
#include "Random.h"

namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,

        max_potion
    };

    constexpr std::array types {healing,mana,speed,invisibility};
    constexpr std::array <std::string_view , max_potion> name{ "healing" , "mana" , "speed" , "invisibility" };
    constexpr std::array cost{20,30,12,50};
}

class Customer
{
private:
    std::string_view m_name{};
    int m_gold{};
    std::array <int , Potion::max_potion> m_inventory{};

public:
    explicit Customer(std::string_view name):
        m_name {name},
        m_gold{Random::get(80,120) }
        {

        }

    bool buy(Potion::Type type)
    {
        if (m_gold < Potion::cost[type])
            return false;

        m_gold -= Potion::cost[type];
        ++m_inventory[type];
        return true;
    }
    int gold() const {return m_gold;}
    int inventory(Potion::Type p) const {return m_inventory[p];}
};

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int charNumToInt(char c)
{
    return c - '0';
}

Potion::Type wichpotion()
{
    std::cout << '\n' << "Enter the number of potion you'd like to buy ' or 'q' to quit: ";
    char input{};
    while (true)
    {
        std::cin >> input;
        if (!std::cin)
        {
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            continue;
        }

        // If there is extraneous input, treat as failure case
        if (!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::cout << "I didn't understand what you said.  Try again: ";
            ignoreLine(); // ignore any extraneous input
            continue;
        }

        if (input == 'q')
            return Potion::max_potion;

        int sth {charNumToInt(input)};
        if (sth >= 0 && sth < Potion::max_potion)
            return static_cast<Potion::Type>(sth);

        std::cout << "That's an invalid input. try again: ";
    }
}

void shop (Customer &customer)
{
    while(true)
    {
        std::cout << '\n' << "Here is our selection for today: " << '\n';
        for (auto i:Potion::types)
            std::cout << i << ") " << Potion::name[i] << " costs " << Potion::cost[i] << '\n';

        Potion::Type which{wichpotion()};
        if (which == Potion::max_potion)
            return;

        bool sucsses { customer.buy(which) };
        if (!sucsses)
        {
            std::cout << '\n' << "You can not afford that." << '\n';
        }
        else
            std::cout << '\n' << "You purchased a potion of " << Potion::name[which] << ". You have " << customer.gold() << " gold left." << '\n';
    }
}

void inventory(Customer &customer)
{
    std::cout << '\n' << "Your inventory contains: " << '\n';
    for (auto i:Potion::types)
    {
        if (customer.inventory(i) > 0)
        std::cout << customer.inventory(i) << "X potion of  " << Potion::name[i] << '\n';
    }
    std::cout << '\n' << "You escaped with " << customer.gold() << " gold remaining." << '\n';
}

main()
{
    std::cout << "Welcome to Rosco's potion emporium!" << '\n';
    std::cout << "Enter your name: ";
    std::string name{};
    std::cin >> name;

    Customer customer{name};

    std::cout << '\n' << "Hello ," << name << ", you have " <<  customer.gold() << " gold." << '\n';

    shop(customer);

    inventory(customer);

    std::cout << '\n' << "Thanks for shopping at Rosco's potion emporium!";


    getch();
}



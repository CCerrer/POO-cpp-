#include <SFML/Graphics.hpp>
#include <iostream>

void setSize(sf::Sprite& sprite, int width, int height)
{
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Entity 
{
    int x {0}; // atributos(determinam o estado da entidade)
    int y {0};
    int step {0};
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture):
        x {x}, y {y}, step {step}, sprite(texture)
    {
    }

    void draw(sf::RenderWindow& window) // métodos
    {
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }

};

void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys)
{
    if (key == move_keys[0])
        entity.x--;
    else if (key == move_keys[1])
        entity.y--;
    else if (key == move_keys[2])
        entity.x++;
    else if (key == move_keys[3])
        entity.y++;
}

sf::Texture loadTexture(std::string path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        std::cout << "Deu erro na textura" << std::endl;
        exit(1);
    }
    return texture;
}

struct Board
{   
    // atributos
    int nc {0};
    int nl {0};
    int step {0};
    sf::Sprite sprite;
    sf::RectangleShape rect;

    // parametros
    Board(int nc, int nl, int step, sf::Texture& texture)
    {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);

        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(2);
    }
    void draw (sf::RenderWindow& window)
    {
        window.draw(this->sprite);
        for (int i = 0; i < nc; i++)
        {
            for (int j = 0; j < nl; j++)
            {
                rect.setPosition(i * step, j * step);
                window.draw(rect);
            }
        }
    }

};


int main()
{
    sf::Texture coyote_tex {loadTexture("./pictures/coyoteL.png")};
    sf::Texture beepbeep_tex {loadTexture("./pictures/beepbeepL.png")};
    sf::Texture desert_tex {loadTexture("./pictures/desert2.jpg")};

    const int STEP {100};

    Entity coyote(7, 2, STEP, coyote_tex);
    Entity beepbeep(2, 2, STEP, beepbeep_tex);
    Board board(10, 7, STEP, desert_tex);

    sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "Coyote game");


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            } else if (event.type == sf::Event::KeyPressed)
            {
                moveEntity(event.key.code, coyote, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
                moveEntity(event.key.code, beepbeep, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});
            }
        }


        window.clear();
        board.draw(window);
        coyote.draw(window);
        beepbeep.draw(window);
        window.display();
    }

    return 0;
}
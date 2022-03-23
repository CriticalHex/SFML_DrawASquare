#include<iostream>
#include<SFML\Graphics.hpp>
#include<math.h>
#include<vector>
#include<ctime>
#include<random>

class Square {
public:
    float vx;
    float vy;
    float x;
    float y;
    float s;
    float f;
    float u;
    sf::VertexArray lines;

    Square(float xpos, float ypos, float dilation, float scale) {//constructor
        x = xpos;
        y = ypos;
        s = dilation;
        f = scale;

        u = sqrt(s * pow(f, 2) - pow(f, 2));

        lines.setPrimitiveType(sf::PrimitiveType::Quads);

        lines.append(sf::Vertex(sf::Vector2f(x - f, y - u), sf::Color::Yellow));
        lines.append(sf::Vertex(sf::Vector2f(x + f, y - u), sf::Color::Green));
        lines.append(sf::Vertex(sf::Vector2f(x + f, y + u), sf::Color::Blue));
        lines.append(sf::Vertex(sf::Vector2f(x - f, y + u), sf::Color::Red));
        //lines.append(sf::Vertex(sf::Vector2f(x - f, y + u), sf::Color::Green));

        setColor();
    }
    void draw(sf::RenderWindow& window) {
        window.draw(lines);
    }
    void setVelocity(float velx, float vely) {
        vx = velx;
        vy = vely;
    }
    void move() {
        if (lines[0].position.x <= 0 or lines[3].position.x <= 0 or lines[1].position.x >= 1920 or lines[2].position.x >= 1920) {
            vx *= -1;
            setColor();
        }
        if (lines[2].position.y <= 0 or lines[3].position.y <= 0 or lines[0].position.y >= 1080 or lines[1].position.y >= 1080) {
            vy *= -1;
            setColor();
        }
        x += vx;
        y += vy;
        lines[0].position = sf::Vector2f(x - f, y + u);
        lines[1].position = sf::Vector2f(x + f, y + u);
        lines[2].position = sf::Vector2f(x + f, y - u);
        lines[3].position = sf::Vector2f(x - f, y - u);
        //lines[4].position = sf::Vector2f(x - f, y + u);
    }
    void setColor() {
        lines[0].color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
        lines[1].color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
        lines[2].color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
        lines[3].color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
    }
};

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Squares", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    //variables------------------------------------
    bool input = false;

    std::vector<Square*> squares;
    std::vector<Square*>::iterator iter;

    for (int i = 0; i < 4; i++) {
        Square* newSquare = new Square(960, 540, 2, 100);
        switch (i) {
        case 0:
            newSquare->setVelocity(3, 3);
            break;
        case 1:
            newSquare->setVelocity(-3, 3);
            break;
        case 2:
            newSquare->setVelocity(3, -3);
            break;
        case 3:
            newSquare->setVelocity(-3, -3);
            break;
        }
        squares.push_back(newSquare); //puts these missiles into the back of the vector
    }

    while (window.isOpen())
    {
        // Process events-------------------------------------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit-----------------------------------
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                window.close();
            }
        }

        window.clear();
        for (iter = squares.begin(); iter != squares.end(); iter++) {
            (*iter)->move();
            (*iter)->draw(window);
        }
        window.display();
    }
}
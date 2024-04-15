#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <time.h>
#include <vector>

// Compile g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system

void draw(sf::RenderWindow &window, std::vector<sf::RectangleShape> &snake, sf::RectangleShape &food);
void updatePosition(std::vector<sf::RectangleShape> &snake, sf::Vector2f &direction,const int &RECTANGLE_SIZE, sf::RectangleShape &food, sf::Vector2i WINDOW_SIZE);
void updateFoodPosition(sf::RectangleShape &food, sf::Vector2i WINDOW_SIZE, int RECTANGLE_SIZE);


int main()
{

    const int RECTANGLE_SIZE = 20;
    const sf::Vector2i WINDOW_SIZE(1280, 720);


    srand((unsigned) time(nullptr));


    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),"Snake");

    // + - 0 x or y to 
    sf::Vector2f direction(1,0);

    std::vector<sf::RectangleShape> snake;
    

    //The snake itself
    sf::RectangleShape rec(sf::Vector2f(RECTANGLE_SIZE,RECTANGLE_SIZE));
    //Template for snake parts
    rec.setFillColor(sf::Color::Green);
    rec.setPosition(400.0, 400.0);
    rec.setOutlineColor(sf::Color::Black);
    rec.setOutlineThickness(1);

    sf::RectangleShape food(rec);
    food.setFillColor(sf::Color::Red);
    // (rand() % ((max_number - minimum_number) / step)) * step + minimum_number
    updateFoodPosition(food, WINDOW_SIZE, RECTANGLE_SIZE);
    food.setOutlineThickness(0);
    
    // Fill the snake with starting size
    for(int i = 0; i < 5; i++)
    {
        snake.push_back(sf::RectangleShape(rec));
        snake[i].setPosition(snake[i].getPosition().x - (RECTANGLE_SIZE*i), snake[i].getPosition().y);
    }
    snake[0].setFillColor(sf::Color::Blue);

    // Gameloop
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(direction.x == 0)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    direction = sf::Vector2f(-1, 0);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    direction = sf::Vector2f(1,0);
            }
            else if(direction.y == 0)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    direction = sf::Vector2f(0,-1);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    direction = sf::Vector2f(0,1);
            }

        }
        // Gamespeed
        if(clock.getElapsedTime().asMilliseconds() >= 300)
        {
            updatePosition(snake, direction, RECTANGLE_SIZE, food, WINDOW_SIZE); 
            clock.restart();     
        }
        draw(window, snake, food);
    }
    
    return 0;
}

void draw(sf::RenderWindow &window, std::vector<sf::RectangleShape> &snake, sf::RectangleShape &food)
{
    window.clear(sf::Color::White);
    for (auto obj: snake)
        window.draw(obj);
    window.draw(food);
    window.display();
}

void updatePosition(std::vector<sf::RectangleShape> &snake, sf::Vector2f &direction, const int &RECTANGLE_SIZE, sf::RectangleShape &food, sf::Vector2i WINDOW_SIZE)
{
    std::vector<sf::RectangleShape> oldSnake = snake;
    
    snake[0].setPosition(snake[0].getPosition().x + (direction.x*RECTANGLE_SIZE), snake[0].getPosition().y + (direction.y*RECTANGLE_SIZE));
    if(snake[0].getPosition() == food.getPosition())
    {
        snake.push_back(sf::RectangleShape(snake.back()));
        updateFoodPosition(food, WINDOW_SIZE, RECTANGLE_SIZE);
    }

    for (uint i = 1; i<snake.size();i++)
    {
        snake[i].setPosition(oldSnake[i-1].getPosition());
    }
}

void updateFoodPosition(sf::RectangleShape &food, sf::Vector2i WINDOW_SIZE, int RECTANGLE_SIZE)
{
    food.setPosition((rand() % (((WINDOW_SIZE.x-RECTANGLE_SIZE) - 0) / RECTANGLE_SIZE))* RECTANGLE_SIZE + 0,
    (rand() % (((WINDOW_SIZE.y-RECTANGLE_SIZE) - 0) / RECTANGLE_SIZE))* RECTANGLE_SIZE + 0);
}
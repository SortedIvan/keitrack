#include <iostream>
#include "SFML/Graphics.hpp"
#include <deque>
#include <string>

static const sf::Vector2f keystrokeDrawableSize(50, 50);
static const sf::Color keystrokeOutlineColor(sf::Color::White);
static const sf::Color keystrokeFontColor(sf::Color::White);
static const sf::Color keystrokeFillColor(sf::Color::Transparent);
static const sf::Color backgroundColor(21, 34, 56);
static const sf::Vector2f moveBy(-75, 0);
static const sf::Vector2f spawnPoint(350, 100);
static const int keystrokeOutlineThickness = 3;


/*
    FORWARD DECLARATIONS
    TODO: Move these away        
*/ 

class Point {
private:
    sf::CircleShape shape; // Using a small circle to represent the point
    static constexpr float RADIUS = 5.0f; // Radius of the point

public:
    // Constructor to initialize the point at a given position
    Point(float x, float y) {
        shape.setRadius(RADIUS);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(RADIUS, RADIUS); // Center the point
        shape.setPosition(x, y);
    }

    // Function to draw the point on the window
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }
};


struct Keystroke {
    sf::Vector2f position;
    char keyChar;
    sf::RectangleShape shape;
    sf::Text label;

    Keystroke(char keyChar, sf::Color labelColor, sf::Color outlineColor, sf::Color fillColor, sf::Font& font) {
        shape = sf::RectangleShape(keystrokeDrawableSize);
        shape.setFillColor(fillColor);
        shape.setOrigin(sf::Vector2f(keystrokeDrawableSize.x / 2, keystrokeDrawableSize.y / 2));
        shape.setOutlineColor(outlineColor);
        shape.setOutlineThickness(keystrokeOutlineThickness);

        label.setFont(font);
        label.setFillColor(labelColor);

        std::string charString = std::string();
        charString += keyChar;

        label.setString(charString);
        label.setOrigin(sf::Vector2f(label.getCharacterSize() / 2.25, label.getCharacterSize() / 1.5));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }

    void move(sf::Vector2f moveBy) {
        position = position + moveBy;
        shape.setPosition(position);
        label.setPosition(position);
    }

    void setPosition(sf::Vector2f position) {
        this->position = position;
        label.setPosition(position);
        shape.setPosition(position);
    }
};


void createAndAddVisibleKeystroke(char keystrokeChar, sf::Font& font,
    std::deque<Keystroke>& visibleKeystrokes);
void tryLoadFont(sf::Font& font, std::string path);
void moveKeystrokesWhenNewAdded(std::deque<Keystroke>& visibleKeystrokes);
void drawVisibleKeystrokes(std::deque<Keystroke>& visibleKeystrokes, sf::RenderWindow& window);

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(400, 150),
        "key tracker thing");
    
    sf::Event e;
    
    // ====== LOAD FONTS ======
    sf::Font keystrokeFont;
    tryLoadFont(keystrokeFont, "./joystix.otf");
    std::deque<Keystroke> visibleKeystrokes;

    Keystroke testKeystroke('T', sf::Color::Yellow, sf::Color::White, sf::Color::Green, keystrokeFont);
    testKeystroke.setPosition(spawnPoint);


    // Main loop
    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::TextEntered)
            {
                char press = e.text.unicode;
                createAndAddVisibleKeystroke(press, keystrokeFont, visibleKeystrokes);
            }

            // Run updates

            // Clear the window
            window.clear(backgroundColor);

            // draw
            drawVisibleKeystrokes(visibleKeystrokes, window);


            // display
            window.display();
        }
    }
}


void drawVisibleKeystrokes(std::deque<Keystroke>& visibleKeystrokes, sf::RenderWindow& window) {
    for (auto it = visibleKeystrokes.begin(); it != visibleKeystrokes.end(); ++it) {
        it->draw(window);
    }
}

void tryLoadFont(sf::Font& font, std::string path)
{
    if (!font.loadFromFile(path))
    {
        std::cout << "Error loading the font file" << std::endl;
        system("pause");
    }
}

void moveKeystrokesWhenNewAdded(std::deque<Keystroke>& visibleKeystrokes) {
    bool firstOneProcessed = false;

    for (auto it = visibleKeystrokes.rbegin(); it != visibleKeystrokes.rend(); ++it) {
        if (!firstOneProcessed) {
            it->setPosition(spawnPoint);
            firstOneProcessed = true;
            continue;
        }

        it->move(moveBy);
    }
}

void createAndAddVisibleKeystroke(char keystrokeChar, sf::Font& font,
                            std::deque<Keystroke>& visibleKeystrokes) {
    Keystroke keystroke(keystrokeChar, keystrokeFontColor, keystrokeOutlineColor, keystrokeFillColor, font);

    if (visibleKeystrokes.size() >= 5) {
        visibleKeystrokes.pop_front();
    }

    visibleKeystrokes.push_back(keystroke);
    moveKeystrokesWhenNewAdded(visibleKeystrokes);

}

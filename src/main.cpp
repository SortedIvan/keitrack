#include <iostream>
#include "SFML/Graphics.hpp"
#include <deque>

static const sf::Vector2f keystrokeDrawableSize(50, 50);
static const sf::Color keystrokeOutlineColor(sf::Color::White);
static const sf::Color keystrokeFontColor(sf::Color::White);
static const sf::Color keystrokeFillColor(sf::Color::Transparent);
static const sf::Color backgroundColor(21, 34, 56);

/*
    FORWARD DECLARATIONS
    TODO: Move these away        
*/ 

struct Keystroke {
    char keyChar;
    sf::RectangleShape shape;
    sf::Text label;

    Keystroke(char keyChar, sf::Color labelColor, sf::Color outlineColor, sf::Color fillColor, sf::Font& font) {
        shape = sf::RectangleShape(keystrokeDrawableSize);
        shape.setFillColor(fillColor);

        label.setFont(font);
        label.setFillColor(labelColor);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }
};

void createAndAddVisibleKeystroke(char keystrokeChar, sf::Font& font,
    std::deque<Keystroke>& visibleKeystrokes);
void tryLoadFont(sf::Font& font, std::string path);

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(400, 150),
        "2D-Raycasting");
    
    sf::Event e;
    
    // ====== LOAD FONTS ======
    sf::Font keystrokeFont;
    tryLoadFont(keystrokeFont, "./8bitfont.ttf");

    std::deque<Keystroke> visibleKeystrokes;
    
    sf::RectangleShape testRect;
    testRect.setSize(sf::Vector2f(50.f, 50.f));
    testRect.setPosition(25, 75);

    // Main loop
    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::KeyReleased)
            {
                char press = (char)e.key.code;
                createAndAddVisibleKeystroke(press, keystrokeFont, visibleKeystrokes);
            }

            // Run updates

            // Clear the window
            window.clear(backgroundColor);

            // draw
            window.draw(testRect);

            // display
            window.display();
        }
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

void createAndAddVisibleKeystroke(char keystrokeChar, sf::Font& font,
                            std::deque<Keystroke>& visibleKeystrokes) {
    Keystroke keystroke(keystrokeChar, keystrokeFontColor, keystrokeOutlineColor, keystrokeFillColor, font);
    
    if (!visibleKeystrokes.empty()) {
        visibleKeystrokes.pop_front();
    }

    visibleKeystrokes.push_back(keystroke);
}

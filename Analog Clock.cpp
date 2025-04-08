#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

void drawClockHands(sf::RenderWindow &window, float hour, float minute, float second) {
    // Draw hour hand
    sf::RectangleShape hourHand(sf::Vector2f(50, 8));
    hourHand.setFillColor(sf::Color::Black);
    hourHand.setOrigin(0, 4);
    hourHand.setRotation(90 - hour * 30); // 360 degrees / 12 hours = 30 degrees per hour
    hourHand.setPosition(200, 200);
    window.draw(hourHand);

    // Draw minute hand
    sf::RectangleShape minuteHand(sf::Vector2f(70, 4));
    minuteHand.setFillColor(sf::Color::Black);
    minuteHand.setOrigin(0, 2);
    minuteHand.setRotation(90 - minute * 6); // 360 degrees / 60 minutes = 6 degrees per minute
    minuteHand.setPosition(200, 200);
    window.draw(minuteHand);

    // Draw second hand
    sf::RectangleShape secondHand(sf::Vector2f(90, 2));
    secondHand.setFillColor(sf::Color::Red);
    secondHand.setOrigin(0, 1);
    secondHand.setRotation(90 - second * 6); // 360 degrees / 60 seconds = 6 degrees per second
    secondHand.setPosition(200, 200);
    window.draw(secondHand);
}

std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%H:%M:%S");
    return oss.str();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Analog Clock with Digital Clock");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Get current time
        std::time_t now = std::time(nullptr);
        std::tm *localTime = std::localtime(&now);
        float hour = localTime->tm_hour % 12 + localTime->tm_min / 60.0f; // Convert to 12-hour format
        float minute = localTime->tm_min + localTime->tm_sec / 60.0f;
        float second = localTime->tm_sec;

        // Draw clock hands
        drawClockHands(window, hour, minute, second);

        // Draw digital clock
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) { // Make sure to have a font file in the working directory
            std::cerr << "Error loading font" << std::endl;
            return -1;
        }
        sf::Text digitalClock(getCurrentTime(), font, 30);
        digitalClock.setFillColor(sf::Color::Black);
        digitalClock.setPosition(150, 350);
        window.draw(digitalClock);

        window.display();
    }

    return 0;
}
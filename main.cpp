#include <SFML/Graphics.hpp>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include "arrow.h"
#define MAX_ARROWS 100

class ArrowList
{
    private:
        int count;
        float x;
        float y;
        float endx;
        float endy;
        sf::RenderWindow *window;
        Arrow arrows[MAX_ARROWS];
    public:
        void Add(float a, float b){
            this->arrows[count].Set(this->x,this->y,this->x+a,this->y+b,0, this->window);
            this->x += a;
            this->y += b;
            this->count++;
        };
        ArrowList(sf::RenderWindow*);
        void DrawEnd();
        void DrawAll(){
            float angle = 0.005;
            arrows[count-1].SetDotColor();
            arrows[0].Rotate(angle);
            arrows[0].Draw();
            for(int i=1; i<this->count;i++) {
                angle *=3;
                arrows[i].MoveStartAndRotate(arrows[i-1].GetEndX(), arrows[i-1].GetEndY(), angle);
                arrows[i].Draw();
            }
            endx = arrows[count-1].GetEndX();
            endy = MIDDLE*2-arrows[count-1].GetEndY();
        };
};

ArrowList::ArrowList(sf::RenderWindow* win) {
    this->window = win;
    this->count = 0;
    this->x = MIDDLE;
    this->y = MIDDLE;
}
void ArrowList::DrawEnd(){
    sf::CircleShape endDot(1.f);
    endDot.setFillColor(sf::Color::White);
    endDot.setPosition(endx, endy);
    window->draw(endDot);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(MIDDLE*2, MIDDLE*2), "koxen four");
    sf::CircleShape centreDot(4.f);
    centreDot.setFillColor(sf::Color::Red);
    centreDot.setPosition(MIDDLE-4., MIDDLE-4.);
    ArrowList arlist(&window);
    arlist.Add(128., 0.);
    arlist.Add(64., 0.);
    arlist.Add(22., 0.);
    arlist.Add(16., 0.);
    arlist.Add(8., 0.);
    arlist.Add(4., 0.);
    arlist.Add(2., 0.);
    getchar();
    window.clear(sf::Color::Black);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::Black);
        arlist.DrawAll();
        arlist.DrawEnd();
        window.draw(centreDot);
        window.display();
        usleep(5000);
    }

    return 0;
}

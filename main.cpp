#include <SFML/Graphics.hpp>
#include <cmath>
#include <unistd.h>
#include <iostream>
#define MAX_ARROWS 100
class Arrow
{
    private:
        float x0;
        float y0;
        float x1;
        float y1;
        sf::RenderWindow *window;
        sf::Vertex line[2];
    public:
    Arrow(){}
    Arrow(double, double, double, double, sf::RenderWindow*);
    ~Arrow(){};
    float Len();
    void Draw();
    float GetEndX(){return x1;}
    float GetEndY(){return y1;}
    void Rotate(double);
    void MoveStart(double x, double y);
    void MoveEnd(){x1+=0.001;y1+=000.1;}
    void Set(float a, float b, float c, float d, sf::RenderWindow* win){
    this->x0 = a;
    this->y0 = b;
    this->x1 = c;
    this->y1 = d;
    this->window = win;
    };
};
class ArrowList
{
    private:
        int count;
        float x;
        float y;
        sf::RenderWindow *window;
        Arrow arrows[MAX_ARROWS];
    public:
        void Add(float a, float b){
            this->arrows[count].Set(this->x,this->y,this->x+a,this->y+b, this->window);
            this->x += a;
            this->y += b;
            this->count++;
        };
        ArrowList(sf::RenderWindow*);
        void DrawAll(){
            this->arrows[0].MoveEnd();
            this->arrows[0].Draw();
            for(int i=1; i<this->count;i++) {
                arrows[i].MoveStart(arrows[i-1].GetEndX(), arrows[i-1].GetEndY());
                arrows[i].MoveEnd();
                arrows[i].Draw();
            }
        };
};

ArrowList::ArrowList(sf::RenderWindow* win) {
    this->window = win;
    this->count = 0;
    this->x = 200;
    this->y = 200;
}

Arrow::Arrow(double a, double b, double c, double d, sf::RenderWindow* win) {
    x0 = a;
    y0 = b;
    x1 = c;
    y1 = d;
    window = win;
    return;
}
void Arrow::MoveStart(double x, double y){
    double dx = x1-x0;
    double dy = y1-y0;
    x0 = x;
    y0 = y;
    x1 = x0+dx;
    y1 = y0+dy;
}
void Arrow::Rotate(double rad){
    float x = x1-x0;
    float y = y1-y0;
    std::cout << atan(-y/x) << std::endl;
}
float Arrow::Len() {
    return pow(this->x0-this->x1, 2.) + pow(this->y0-this->y1, 2.);
}

void Arrow::Draw(){
    line[0].position = sf::Vector2f(this->x0,this->y0);
    line[1].position = sf::Vector2f(this->x1,this->y1);
    window->draw(line, 2, sf::Lines, sf::RenderStates::Default);
    sf::CircleShape endDot(2.f);
    endDot.setFillColor(sf::Color::White);
    endDot.setPosition(x1-2.0, y1-2.0);
    window->draw(endDot);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape centreDot(4.f);
    centreDot.setFillColor(sf::Color::Red);
    centreDot.setPosition(198., 198.);
    ArrowList arlist(&window);
    arlist.Add(100., 100.);
    arlist.Add(-100., 0.);
    arlist.Add(-100., -50.);
    arlist.Add(0., -50.);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::Black);
        arlist.DrawAll();
        window.draw(centreDot);
        window.display();
        usleep(50000);
    }

    return 0;
}

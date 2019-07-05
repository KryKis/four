#include <SFML/Graphics.hpp>
#include <cmath>
#include <unistd.h>
#include <iostream>
#define MAX_ARROWS 100
#define MIDDLE 300

class Arrow
{
    private:
        float x0;
        float y0;
        float x1;
        float y1;
        float angle;
        sf::CircleShape endDot;
        sf::RenderWindow *window;
        sf::Vertex line[2];
    public:
    Arrow(){}
    Arrow(double, double, double, double, sf::RenderWindow*);
    ~Arrow(){};
    float Len();
    void Draw();
    void SetDotColor();
    float GetEndX(){return x1;}
    float GetEndY(){return y1;}
    void Rotate(double);
    void MoveStart(double x, double y);
    void MoveStartAndRotate(double x, double y, double th);
    void MoveEnd(){x1+=0.001;y1+=000.1;}
    void Set(float a, float b, float c, float d, float e, sf::RenderWindow* win){
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
            //arrows[0].Draw();
            for(int i=1; i<this->count;i++) {
                angle *=3;
                arrows[i].MoveStartAndRotate(arrows[i-1].GetEndX(), arrows[i-1].GetEndY(), angle);
 //               arrows[i].Draw();
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

Arrow::Arrow(double a, double b, double c, double d, sf::RenderWindow* win) {
    x0 = a;
    y0 = b;
    x1 = c;
    y1 = d;
    window = win;
    endDot.setRadius(5.0);
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
void Arrow::MoveStartAndRotate(double x, double y, double rad){
    double dx = x1-x0;
    double dy = y1-y0;
    double l = Len();
    x0 = x;
    y0 = y;
    angle+=rad;
    x1 = x0+cos(angle)*l;
    y1 = y0+sin(angle)*l;
}
void Arrow::Rotate(double rad){
    double l = Len();
    angle+=rad;
    x1 = x0+cos(angle)*l;
    y1 = y0+sin(angle)*l;
}
float Arrow::Len() {
    return sqrt(pow(this->x0-this->x1, 2.) + pow(this->y0-this->y1, 2.));
}

void Arrow::Draw(){
    line[0].position = sf::Vector2f(x0,2*MIDDLE-y0);
    line[1].position = sf::Vector2f(x1,2*MIDDLE-y1);
    window->draw(line, 2, sf::Lines, sf::RenderStates::Default);
    endDot.setPosition(x1-2.0, y1-2.0);
    window->draw(endDot);
}
void Arrow::SetDotColor(){
    endDot.setFillColor(sf::Color::Red);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(MIDDLE*2, MIDDLE*2), "SFML works!");
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
        window.clear(sf::Color::Black);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

   //     window.clear(sf::Color::Black);
        arlist.DrawAll();
        arlist.DrawEnd();
        window.draw(centreDot);
        window.display();
        usleep(5000);
    }

    return 0;
}

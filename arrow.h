#include <SFML/Graphics.hpp>
#include <cmath>
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

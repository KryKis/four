#include "arrow.h"

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

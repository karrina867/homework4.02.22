#include "boll.h"
#include "const.h"

Ball::Ball() {
	circle.setRadius(radius);
	circle.setPosition(SCREEN_WIDTH / 2 - radius, SCREEN_HEIGHT / 2 - radius);
	circle.setFillColor(sf::Color::Yellow);
}
sf::CircleShape Ball::getShape() { return circle; }
void Ball::reboundHorizontal() { speedx = -speedx; }
void Ball::reboundVertical() { speedy = -speedy; }
sf::Vector2f Ball::getPosition() { return circle.getPosition(); }
sf::FloatRect Ball::getHitBox() { return circle.getGlobalBounds(); }
size_t Ball::getLeftScore() { return left_score; }
size_t Ball::getRightScore() { return right_score; }
sf::Vector2f Ball::getMidTop() { return midtop; }
sf::Vector2f Ball::getMidLeft() { return midleft; }
sf::Vector2f Ball::getMidBottom() { return midbottom; }
sf::Vector2f Ball::getMidRight() { return midright; }
void Ball::setPosition(sf::Vector2f position) { circle.setPosition(position); }
float Ball::getRadius() { return radius; }
void Ball::update() {
	//âû÷èñëÿåì ñåðåäèíû ñòîðîí
	midtop = sf::Vector2f(circle.getPosition().x + radius, circle.getPosition().y);
	midleft = sf::Vector2f(circle.getPosition().x, circle.getPosition().y + radius);
	midbottom = sf::Vector2f(circle.getPosition().x + radius, circle.getPosition().y + 2 * radius);
	midright = sf::Vector2f(circle.getPosition().x + 2 * radius, circle.getPosition().y + radius);
	//äâèæåíèå ìÿ÷à
	circle.move(speedx, speedy);

	//åñëè ìÿ÷ óäàðèëñÿ îá ëåâóþ ãðàíèöó ýêðàíà





	while (speedx < 100) {
		if (getPosition().x <= 0) {
			speedx = -speedx + 0.5;

			right_score++;

			//

			//

		}
		//åñëè ìÿ÷ óäàðèëñÿ îá ïðàâóþ ãðàíèöó ýêðàíà
		if (getPosition().x + 2 * radius >= SCREEN_WIDTH) {
			speedx = -speedx + 0.5;
			left_score++;

			//

			//
		}
		if (getPosition().y <= 0 || getPosition().y + 2 * radius >= SCREEN_HEIGHT) {
			speedy = -speedy + 0.5;

		}
	}
}
	
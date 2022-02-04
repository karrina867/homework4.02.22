#include <SFML/Graphics.hpp>
#include "const.h"
#include "boll.h"
#include "bat.h"
#include "left bat.h"
#include "right bat.h"
#include "text_obj.h"


using namespace sf;

int main()
{
	enum GameState { INTRO, PLAY, GAME_OVER };
	GameState game_state = INTRO;
	// Îáúåêò, êîòîðûé, ñîáñòâåííî, ÿâëÿåòñÿ ãëàâíûì îêíîì ïðèëîæåíèÿ
	RenderWindow window(
		VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
		"ITSteps SFML Pong"
	);
	window.setFramerateLimit(FPS);
	//Ñîçäàíèå èãðîâûõ îáúåêòîâ
	Ball ball;
	LeftBat left_bat(20, SCREEN_HEIGHT / 2 - 50);
	RightBat right_bat(SCREEN_WIDTH - 40, SCREEN_HEIGHT / 2 - 50);
	TextObj left_score(SCREEN_WIDTH / 5, 20);
	TextObj right_score(4 * SCREEN_WIDTH / 5, 20);
	TextObj intro_text(SCREEN_WIDTH - 470, SCREEN_HEIGHT - 370);


	//изменено
	TextObj game_over_text(SCREEN_WIDTH - 799, SCREEN_HEIGHT -350);
	//.
	


	// Ãëàâíûé öèêë ïðèëîæåíèÿ. Âûïîëíÿåòñÿ, ïîêà îòêðûòî îêíî
	while (window.isOpen())
	{
		//1 Îáðàáàòûâàåì î÷åðåäü ñîáûòèé â öèêëå
		Event event;
		while (window.pollEvent(event))
		{
			// Ïîëüçîâàòåëü íàæàë íà «êðåñòèê» è õî÷åò çàêðûòü îêíî?
			if (event.type == Event::Closed)
				// òîãäà çàêðûâàåì åãî
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Space) {
					game_state = PLAY;
				}
				if (event.key.code == Keyboard::Z) {
					game_state = GAME_OVER;

					
				}
			}
			//.
		}
		//2 update
		switch (game_state) {
		case INTRO:
			intro_text.update("PONG");
			window.clear(Color(128, 60, 128));
			window.draw(intro_text.getText());
			window.display();
			break;
		case PLAY:
			ball.update();
			left_bat.update();
			right_bat.update();
			left_score.update(std::to_string(ball.getLeftScore()));
			right_score.update(std::to_string(ball.getRightScore()));
			//îáðàáîòêà ñòîëêíîâåíèé
			//åñëè ïðÿìîóãîëüíèê ìÿ÷à ïåðåñåêàåòñÿ ñ ïðÿìîóãîëüíèêîì ëåâîé áèòû
			if (ball.getHitBox().intersects(left_bat.getHitBox())) {
				//óäàð ñâåðõó
				if (left_bat.getHitBox().contains(ball.getMidBottom())) {
					//âûòàëêèâàåì ìÿ÷ èç ðàêåòêè ïî îñè Ó ââåðõ
					ball.setPosition(sf::Vector2f(ball.getPosition().x,
						left_bat.getPosition().y - 2 * ball.getRadius()));
					ball.reboundVertical();
				}
				//óäàð ñïðàâà
				else if (left_bat.getHitBox().contains(ball.getMidLeft())) {
					ball.setPosition(sf::Vector2f(
						left_bat.getPosition().x + left_bat.getWidth(),
						ball.getPosition().y));
					ball.reboundHorizontal();
				}
				//óäàð ñíèçó
				else if (left_bat.getHitBox().contains(ball.getMidTop())) {
					//âûòàëêèâàåì ìÿ÷ èç ðàêåòêè ïî îñè Ó âíèç
					ball.setPosition(sf::Vector2f(ball.getPosition().x,
						left_bat.getPosition().y + left_bat.getHeight()));
					ball.reboundVertical();
				}
			}
			if (ball.getHitBox().intersects(right_bat.getHitBox())) {
				ball.reboundHorizontal();
			}
			
			// Îòðèñîâêà îêíà
			window.clear(Color(100, 60, 70));
			window.draw(ball.getShape());
			window.draw(left_bat.getShape());
			window.draw(right_bat.getShape());
			window.draw(left_score.getText());
			window.draw(right_score.getText());
			window.display();
			break;
		case GAME_OVER:
			game_over_text.update(" GAME_OVER");
			window.clear(Color(188, 143, 143));
			window.draw(game_over_text.getText());
			window.display();

			break;
		}

	}
	return 0;
}
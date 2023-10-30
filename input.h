#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Input
{
	struct Button { bool left, right, up, down, escape; };

public:
	// Proto du constructeur
	Input();
	// Protos
	Button GetButton(void) const;
	void InputHandler(Event event, RenderWindow& window); //RenderWindow et Event proviennent de la SFML

private:
	Button button;
};


#endif



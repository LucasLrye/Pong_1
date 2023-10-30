#include "input.h"

// Constructeur 
Input::Input()
{
	button.left = button.right = button.up = button.down = button.escape = false;

}

// Fonction qui accède à button (struc) et nous donne l'info private
Input::Button Input::GetButton(void) const
{
	return button;
}

// Fonction de gestion des inputs
void Input::InputHandler(Event event, RenderWindow& window)
{
	// Fermer la fenetre si on clique sur la croix
	if (event.type == Event::Closed)
	{
		//ferme la fenetre
		window.close();
	}

	//gestion inputs (appuyés)
	if (event.type == Event::KeyPressed)
	{
		switch (event.key.code) // code de la touche utilisé
		{
		case Keyboard::Escape:
			button.escape = true;
			break;
		case Keyboard::Left:
			button.left = true;
			break;
		case Keyboard::Right:
			button.right = true;
			break;
		case Keyboard::Down:
			button.down = true;
			break;
		case Keyboard::Up:
			button.up = true;
			break;
		default:
			break;
		}
	}
	// relache la touche
	if (event.type == Event::KeyReleased)
	{
		switch (event.key.code) // code de la touche utilisé
		{
		case Keyboard::Escape:
			button.escape = false;
			break;
		case Keyboard::Left:
			button.left = false;
			break;
		case Keyboard::Right:
			button.right = false;
			break;
		case Keyboard::Down:
			button.down = false;
			break;
		case Keyboard::Up:
			button.up = false;
			break;
		default:
			break;
		}
	}
}

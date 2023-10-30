#include "main.h"

// Variables
 // la fenetre du jeu
RenderWindow window;
//Pour la gestion des inputs
Input input;
//Stocker la fonte
Font font;
// Stocker le texte
Text txt;

// Position raquettes
float posRaquettesLeftX = 50;
float posRaquettesRightX = WIN_WIDTH - 70;
float posRaquettesLeftY = WIN_HEIGHT / 2;
float posRaquettesRightY = posRaquettesLeftY;
float raquettesSpeed = 0.25f;
int raquettesHeight = 150;
int raquettesWidth = 20;
// Infos balle
float ballSpeed = 0.1f;
Vector2f ballDir = Vector2f(1.5f, 2.0f);
float ballPosX = WIN_WIDTH / 2;
float ballPosY = WIN_HEIGHT / 2;
// Scores
int scoreJ1 = 0;
int scoreJ2 = 0;
//Astuce pour afficher un chiffre sous forme de string
//char temp[256];

void RaquetteIA()
{
	posRaquettesRightY = ballPosY;
}


//On se place au dessus car on ne la pas défini avant en tant que proto
void UpdateBall()
{
	//Pos balle
	ballPosX += ballDir.x * ballSpeed;
	ballPosY += ballDir.y * ballSpeed;
	//Collision de balle
	//raquette gauche ou droite touché ?
	if ((ballPosX < posRaquettesLeftX + raquettesWidth && ballPosX > posRaquettesLeftX
		&& ballPosY+7 < posRaquettesLeftY + raquettesHeight && ballPosY+7 > posRaquettesLeftY)
		||
		(ballPosX > posRaquettesRightX - raquettesWidth && ballPosX < posRaquettesRightX
			&& ballPosY+7 < posRaquettesRightY + raquettesHeight && ballPosY+7 > posRaquettesRightY))
	{
		ballDir.x *= -1;
	}

	//mur gauche
	if (ballPosX < 0) {
		scoreJ2++;
		ballPosX = WIN_WIDTH / 2;
		ballPosY = WIN_HEIGHT / 2;
		ballDir.x = fabs(ballDir.x);
		ballDir.y *= -1;
		SetText(txt, to_string(scoreJ1) + " | " + to_string(scoreJ2));
	}
	//mur droite
	if (ballPosX > WIN_WIDTH) {
		scoreJ1++;
		ballPosX = WIN_WIDTH / 2;
		ballPosY = WIN_HEIGHT / 2;
		ballDir.x = -fabs(ballDir.x);
		ballDir.y *= -1;
		SetText(txt, to_string(scoreJ1) + " | " + to_string(scoreJ2));
	}
	//mur haut ou bas
	if (ballPosY > WIN_HEIGHT || ballPosY < 0) {
		ballDir.y *= -1;
	}

}
// Fonction main, point de départ du programme
int main()
{
	//Création fenetre RenderWindow
	window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Pong SFM C++", Style::Default);
	// chargement de fonte
	font.loadFromFile("res/poppins.ttf");
	//On règle toutes les propirété de celui-ci
	SetText(txt, to_string(scoreJ1) + " | " + to_string(scoreJ2));

	//préparation des formes
	// Balle
	CircleShape circleShape(15); // cercle de la SFML
	circleShape.setPosition(ballPosX, ballPosY);
	//Raquette gauche
	RectangleShape rectangleShape(Vector2f(raquettesWidth, raquettesHeight));
	rectangleShape.setPosition(posRaquettesLeftX, posRaquettesLeftY);
	//Raquette droite
	RectangleShape rectangleShape2(Vector2f(raquettesWidth, raquettesHeight));
	rectangleShape2.setPosition(posRaquettesRightX, posRaquettesRightY);

	//Boucle qui tourne tant que fenetre est ouverte
	while (window.isOpen())
	{
		Event event; //Variable pour gérer l'événement
		//On boucle sur les évenement
		while (window.pollEvent(event))
		{
			//Gestion input /event
			input.InputHandler(event, window);
		}

		//Gestion clavier
		CheckBtn();
		RaquetteIA();
		//Position raquettes, balle
		rectangleShape.setPosition(posRaquettesLeftX, posRaquettesLeftY);
		rectangleShape2.setPosition(posRaquettesRightX, posRaquettesRightY);
		//Upadte Ball
		UpdateBall();
		circleShape.setPosition(ballPosX, ballPosY);
		//Couleur arrière plan
		window.clear(Color::Black);
		//On dessine les élements du jeu à l'écran
		window.draw(txt);
		window.draw(circleShape);
		window.draw(rectangleShape);
		window.draw(rectangleShape2);
		//affiche tout
		window.display();
	}
	// Fin programme
	return 0;
}

void SetText(Text& txt, String str)
{
	//Police
	txt.setFont(font);
	//Chaine à afficher
	txt.setString(str);
	//Taille de police
	txt.setCharacterSize(26);
	//DOnne couleur
	txt.setFillColor(Color::White);
	//Position
	txt.setPosition((WIN_WIDTH / 2) - 40, 10);
}

void CheckBtn()
{
	//Raquette gauche up
	if (input.GetButton().up == true) {
		posRaquettesLeftY -= raquettesSpeed;
		if (posRaquettesLeftY < 0) {
			posRaquettesLeftY = 0;
		}
	}
	//Raquette gauche down
	if (input.GetButton().down == true) {
		posRaquettesLeftY += raquettesSpeed;
		if (posRaquettesLeftY + raquettesHeight > WIN_HEIGHT) {
			posRaquettesLeftY = WIN_HEIGHT - raquettesHeight;
		}
	}

	//Raquette droite left
	if (input.GetButton().left == true) {
		posRaquettesRightY -= raquettesSpeed;
		if (posRaquettesRightY < 0) {
			posRaquettesRightY = 0;
		}
	}
	//Raquette gauche right
	if (input.GetButton().right == true) {
		posRaquettesRightY += raquettesSpeed;
		if (posRaquettesRightY + raquettesHeight > WIN_HEIGHT) {
			posRaquettesRightY = WIN_HEIGHT - raquettesHeight;
		}
	}

	//Bouton echap
	if (input.GetButton().escape == true)
	{
		window.close();
	}

}

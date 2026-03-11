#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib> // Contiene rand() y srand()
#include <ctime>   // Contiene time()
#include <iostream>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Adivina el numero");
    window.setFramerateLimit(60);

    // --- RECURSOS ---
    sf::Color rosa(255, 105, 180); // Un rosa más agradable (Hot Pink)
    
    int current_room = 1;
    int dificultad = 5; // Empezamos en "Normal" (índice 5 de options)
	int vidas = 5;
	bool musicOn = false;
    
    sf::Texture Chica1;
    if (!Chica1.loadFromFile("Recursos/Sakura.png")) { /* error */ }
	
	sf::Texture Corazon_texture;
	if (!Corazon_texture.loadFromFile("Recursos/Heart.png")) { /* error */ }

    
    sf::Font font;
    if (!font.loadFromFile("Recursos/arial.ttf")) return -1;

    sf::Music song;
    if (song.openFromFile("Recursos/song.mp3")) {
        song.setLoop(true);
        song.play();
    }

    // --- TEXTOS ---
    sf::Text texto;
    texto.setFont(font);
    texto.setCharacterSize(42);

    sf::Text texto_Logo;
    texto_Logo.setFont(font);
    texto_Logo.setCharacterSize(64);
    texto_Logo.setFillColor(sf::Color::White);
    texto_Logo.setString("Adivina el numero");
    texto_Logo.setPosition(100.0f, 30.0f);
    
    sf::Sprite Waifu1; //Sprite de Waifu de Fondo
    Waifu1.setTexture(Chica1);
    Waifu1.setPosition(360.0f, 70.0f);
	
	sf::Sprite Hearts; //Sprite de Corazon
	Hearts.setTexture(Corazon_texture);
	Hearts.setPosition(20.0f, 20.0f);
	Hearts.setScale(0.2f, 0.2f);

    string options[] = {"Jugar", "Opciones", "Creditos", "Dificultad", "Facil", "Normal", "Dificil", "Regresar", "Musica: ", "On", "Off"};
	
	sf::RectangleShape MenuForm(sf::Vector2f (230.0f, 230.0f)); //Menu 1 de Fondo
	MenuForm.setPosition(30.0f, 320.0f);
	MenuForm.setFillColor(sf::Color::Blue);
	MenuForm.setOutlineThickness(5);
	MenuForm.setOutlineColor(sf::Color::White);
	
	sf::RectangleShape MenuForm2(sf::Vector2f (360.0f, 230.0f)); //Menu 2 de Fondo
	MenuForm2.setPosition(30.0f, 320.0f);
	MenuForm2.setFillColor(sf::Color::Blue);
	MenuForm2.setOutlineThickness(5);
	MenuForm2.setOutlineColor(sf::Color::White);

    while (window.isOpen()) {
        // 1. ACTUALIZAR POSICIÓN DEL MOUSE
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // --- LÓGICA DE CLICKS ---
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                
                if (current_room == 1) {
                    // Botón Opciones (índice 1)
                    texto.setString(options[1]);
                    texto.setPosition(30.0f, 320.0f + (1 * 80.0f));
                    if (texto.getGlobalBounds().contains(mousePos)) current_room = 2;
                    
                    // Botón Créditos (índice 2)
                    texto.setString(options[2]);
                    texto.setPosition(30.0f, 320.0f + (2 * 80.0f));
                    if (texto.getGlobalBounds().contains(mousePos)) system("Creditos.txt");;
                } 
                else if (current_room == 2) {
                    // Botón Regresar (índice 7)
                    texto.setString(options[7]);
                    texto.setPosition(30.0f, 480.0f);
                    if (texto.getGlobalBounds().contains(mousePos)) current_room = 1;

                    // Botón Cambiar Dificultad
                    texto.setString(options[3] + " = " + options[dificultad]);
                    texto.setPosition(30.0f, 320.0f);
                    if (texto.getGlobalBounds().contains(mousePos)) {
                        dificultad++;
						if (dificultad == 4){
							vidas = 8;
							
						} else if (dificultad == 5){
							vidas = 5;
							
						} else {
							
							vidas = 3;
							
						}
						
                        if (dificultad > 6) {
							dificultad = 4;
							vidas = 8;// Cicla entre 4, 5 y 6
                    }
					}
					
					if (musicOn){ // Boton Quitar Musica
					texto.setString(options[8] + options[9]);
					texto.setPosition(30.0f, 400.0f);
					if (texto.getGlobalBounds().contains(mousePos)) {
					song.stop();
					musicOn = false;
					
					}
					} else { //Boton Poner Musica
						texto.setString(options[8] + options[10]);
					texto.setPosition(30.0f, 400.0f);
					if (texto.getGlobalBounds().contains(mousePos)) {
					song.play();
										musicOn = true;

						
						
						
					}
					}
                }
            }
        }

        // --- 2. RENDERIZADO ---
        window.clear(rosa);

        if (current_room == 1) {
			 //Corazones
			for (int i = 1; i < vidas + 1; i++){
				
				Hearts.setPosition(20.0f * (3.0f * i), 20.0f);
				window.draw(Hearts);

				
				
			}
			
			
			window.draw(MenuForm);
            window.draw(texto_Logo);
            window.draw(Waifu1);
            for (int i = 0; i < 3; i++) {
                texto.setString(options[i]);
                texto.setPosition(30.0f, 320.0f + (i * 80.0f));
                
                // Efecto Hover (Brillo amarillo)
                if (texto.getGlobalBounds().contains(mousePos)) texto.setFillColor(sf::Color::Yellow);
                else texto.setFillColor(sf::Color::White);
                
                window.draw(texto);
				
            }
        } 
        else if (current_room == 2) {
										window.draw(MenuForm2);

            window.draw(texto_Logo);
            window.draw(Waifu1);


            // Dibujar Dificultad
            texto.setString(options[3] + " = " + options[dificultad]);
            texto.setPosition(30.0f, 320.0f);
            if (texto.getGlobalBounds().contains(mousePos)) texto.setFillColor(sf::Color::Yellow);
            else texto.setFillColor(sf::Color::White);
            window.draw(texto);

			// Dibujar Musica On 
			if (musicOn){
				
				texto.setString(options[8] + options[9]);
				texto.setPosition(30.0f, 400.0f);
				if (texto.getGlobalBounds().contains(mousePos)) texto.setFillColor(sf::Color::Yellow);
                else texto.setFillColor(sf::Color::White);
				window.draw(texto);
	
			} else { //Dibujar Musica Off
				
				texto.setString(options[8] + options[10]);
				texto.setPosition(30.0f, 400.0f);
				if (texto.getGlobalBounds().contains(mousePos)) texto.setFillColor(sf::Color::Yellow);
                else texto.setFillColor(sf::Color::White);
				window.draw(texto);
				
			}
			

            // Dibujar Regresar
            texto.setString(options[7]);
            texto.setPosition(30.0f, 480.0f);
            if (texto.getGlobalBounds().contains(mousePos)) texto.setFillColor(sf::Color::Yellow);
            else texto.setFillColor(sf::Color::White);
            window.draw(texto);
        } else if (current_room == 3) { //Dibujado del Gameplay
			
			
			
			
		}
		
        window.display();
    }

    return 0;
}
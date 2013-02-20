CC=g++
#
CFLAGS= -Wall -c -pedantic -Wextra
#
LIBS = -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window
#

MarioCraft.o: Main.o GameView.o Controller.o GameModel.o Batiment.o Foyer.o Caserne.o Personnage.o Joueur.o Artisan.o Combattant.o Obstacle.o Element.o Composant.o Bois.o Nourriture.o
#
	$(CC) Main.o GameView.o Controller.o GameModel.o Batiment.o Foyer.o Caserne.o Joueur.o Personnage.o Artisan.o Combattant.o Obstacle.o Element.o Composant.o  Bois.o Nourriture.o $(LIBS) -o MarioCraft

Main.o: Main.cpp
#
	$(CC) $(CFLAGS) Main.cpp -o Main.o

GameView.o: GameView.cpp
#
	$(CC) $(CFLAGS) GameView.cpp -o GameView.o

GameModel.o: GameModel.cpp
#
	$(CC) $(CFLAGS) GameModel.cpp -o GameModel.o

Controller.o: Controller.cpp
#
	$(CC) $(CFLAGS) Controller.cpp -o Controller.o

Joueur.o: Joueur.cpp
#
	$(CC) $(CFLAGS) Joueur.cpp -o Joueur.o

Element.o: Element.cpp
#
	$(CC) $(CFLAGS) Element.cpp -o Element.o

Batiment.o: Batiment.cpp
#
	$(CC) $(CFLAGS) Batiment.cpp -o Batiment.o

Foyer.o: Foyer.cpp
#
	$(CC) $(CFLAGS) Foyer.cpp -o Foyer.o

Caserne.o: Caserne.cpp
#
	$(CC) $(CFLAGS) Caserne.cpp -o Caserne.o

Composant.o: Composant.cpp
#
	$(CC) $(CFLAGS) Composant.cpp -o Composant.o

Obstacle.o: Obstacle.cpp
#
	$(CC) $(CFLAGS) Obstacle.cpp -o Obstacle.o

Bois.o: Bois.cpp
#
	$(CC) $(CFLAGS) Bois.cpp -o Bois.o

Nourriture.o: Nourriture.cpp
#
	$(CC) $(CFLAGS) Nourriture.cpp -o Nourriture.o		
		
Personnage.o: Personnage.cpp
#
	$(CC) $(CFLAGS) Personnage.cpp -o Personnage.o
	
Artisan.o: Artisan.cpp
#
	$(CC) $(CFLAGS) Artisan.cpp -o Artisan.o
	
Combattant.o: Combattant.cpp
#
	$(CC) $(CFLAGS) Combattant.cpp -o Combattant.o

clean:
#
	@rm -rfv *o *MarioCraft *orig *~

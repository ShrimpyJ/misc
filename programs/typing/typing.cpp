#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;
//void printLines(string array[], int i, string line[]);

int main(){
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Working", sf::Style::Close | sf::Style::Resize);
//	sf::Font font;
//	font.loadFromFile("times.ttf");
//	sf::Text text;
//	text.setCharacterSize(24);
//	text.setCharacterSize(24);
//	ifstream input;
//	srand(time(0));
//	string array[200];
//	string line[200];
//	string currentWord[20];
//	string userWord[20];
//	bool isRight;
//	int i = 0;
//	int totalWords;;

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					printf("New window width: %i New window height: %i\n", event.size.width, event.size.height);
					break;
				case sf::Event::TextEntered:
					if (event.text.unicode < 128){
						printf("%c", event.text.unicode);
					}
			}
		}
//		window.clear();
//		window.draw(text);
//		window.display();
	}
}

//		printLines(array, i, line);
//		text.setString(line[i]);
//		text.setFillColor(sf::Color::Red);
//		text.setFont(font);
//	input.open("words.dat");
//	while (!input.eof()){
//		input >> array[i];
//		i++;
//	}
//	input.close();
//	for (int j = 0; j < 5; j++){
//		cin >> userWord[j];
//		if (line[j] == userWord[j] == 0){
//			totalWords += 1;
//		}
//	}
//	printLines(array, i, line);
//	cout << totalWords;
//
//	return 0;
//}
//
//void printLines(string array[], int i, string line[]){
//	int maxLines = i - 2;
//	for (i = 0; i < 5; i++){
//		int r = rand() % maxLines;
//		line[i] = array[r];
//		cout << line[i] << " ";
//	}
//	cout << endl;
//}

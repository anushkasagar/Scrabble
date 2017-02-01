#ifndef ScrabbleGUI_H
#define ScrabbleGUI_H


#include <QObject>
#include <QPushButton>
#include <QString>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include "NameTime.h"

#include "Dictionary.h"
#include "Board.h"
#include "Bag.h"
#include "Player.h"
#include "Tile.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>

class ScrabbleGUI : public QWidget{						
	Q_OBJECT

public slots:
	void act();

public:

	ScrabbleGUI(NameTime* nt, Dictionary* dict, Board* b, Bag* bag, unsigned int, std::vector<Player*> players);
	~ScrabbleGUI();
	void update();

private slots:
void placePressed();
void exchangePressed();
void passPressed();

void gameOver();
bool allPassed();

private:
	QApplication *app;
	QPushButton ***board, *play;
	QLineEdit *tiles;
	QLabel *hand;
	QWidget *window;
	QHBoxLayout *h1;
	QVBoxLayout *v1;
	QGridLayout *g;
	int size;
	QPushButton* addButton;
	QMessageBox *msgbox;
	QPushButton* placeButton;
	QPushButton* exchangeButton; 
	QPushButton* passButton;
	QComboBox* direction;
	int count;

	QVBoxLayout* right;
	QGridLayout* left;
	QHBoxLayout* name;
	QHBoxLayout* score;
	QHBoxLayout* tileswidget;
	QLabel* playerName;	
	std::vector<QLabel*> playerPoints;
	int row, col;



	std::vector<Player*> numPlayers;
	

	Dictionary* _dict;
	Board* _b;
	Bag* _bag;
	unsigned int hand_size;
	int passed;




};

#endif 

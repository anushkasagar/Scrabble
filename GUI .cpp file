#include "ScrabbleGUI.h"
#include "Square.h"
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <exception>
#include <iostream>
#include <QApplication>
#include <QString>
#include <QMessageBox>
#include "Player.h"


using namespace std;

ScrabbleGUI::~ScrabbleGUI() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			delete board[i][j];
		}
		delete board[i];
	}
	delete board;
	delete g;
	delete tiles;
	delete hand;
	delete play;
	delete h1;
	delete v1;
	delete window;
}
ScrabbleGUI::ScrabbleGUI(NameTime* nt, Dictionary* dict, Board* b, Bag* bag,
	unsigned int hs, vector<Player*> players) 
	
	
{
	_b = b;
	_bag = bag;
	this->app = app;
	string board_file_name;
	string dictionary_file_name;
	string bag_file_name;
	unsigned int hand_size;
	string player_name;
	numPlayers = players;
	count = 0;
	passed = 0;

	h1 = new QHBoxLayout;
	v1 = new QVBoxLayout;
	window = new QWidget;

	g = new QGridLayout;
			
	board = new QPushButton**[_b->getx()];

	// create board and set color
	for (int i = 0; i < _b->getx(); i++) {
		board[i] = new QPushButton*[_b->getx()];
		for (int j = 0; j < _b->gety(); j++) {
			

			if (!(_b->gameboard[i][j].occupied())) {
				if(i == _b->getstarty() && j == _b->getstartx()){
					board[i][j] = new QPushButton("***");
					board[i][j]->setStyleSheet("background-color: LightCyan;");
					g->addWidget(board[i][j], i+1, j+1);
				}
				
				else if(_b->gameboard[i][j].get_lettermult() == 2){
					board[i][j] = new QPushButton("2L");
					board[i][j]->setStyleSheet("background-color: MediumPurple;");
					g->addWidget(board[i][j], i+1, j+1);

				}
				else if(_b->gameboard[i][j].get_lettermult() == 3){
					board[i][j] = new QPushButton("3L");
					board[i][j]->setStyleSheet("background-color: LightPink;");
					g->addWidget(board[i][j], i+1, j+1);

				}
				else if(_b->gameboard[i][j].get_wordmult() == 2){
					board[i][j] = new QPushButton("2W");
					board[i][j]->setStyleSheet("background-color: LightSkyBlue;");
					g->addWidget(board[i][j], i+1, j+1);

				}
				else if(_b->gameboard[i][j].get_wordmult() == 3){
					board[i][j] = new QPushButton("3W");
					board[i][j]->setStyleSheet("background-color: LightGreen;");
					g->addWidget(board[i][j], i+1, j+1);

				}

				else {
					board[i][j] = new QPushButton;
					board[i][j]->setStyleSheet("background-color: LemonChiffon");
					g->addWidget(board[i][j], i+1, j+1);
				}
				board[i][j]->setFixedSize(40, 40);

				QObject::connect(board[i][j], SIGNAL(clicked()), this, SLOT(act()));
			}
			
		}
	}
	g->setSpacing(0);
	
	window->setLayout(h1);
	h1->addLayout(g);

	// add right side of layout
	right = new QVBoxLayout();
	h1->addLayout(right);
	

	
	// for who's turn it is
	QString tempString;
	tempString = "Player ";
	tempString += QString::fromStdString(numPlayers[0]->name());
	tempString += ", it's your turn";
	playerName = new QLabel(tempString);
	right->addWidget(playerName);

	
	// for outputing scores for each player
	for(unsigned int i=0; i < numPlayers.size(); i++){
		QString temp;
		temp = temp + QString::fromStdString(numPlayers[i]->name());
		temp = temp + ": ";
		temp += QString::number(numPlayers[i]->getPoints());
		QLabel *scores = new QLabel(temp);
		right->addWidget(scores);
		playerPoints.push_back(scores);
	}
	
	

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	right->addLayout(buttonLayout);
	
	// add place button
	placeButton = new QPushButton ("&Place");
	connect(placeButton, SIGNAL(clicked()), this, SLOT(placePressed()));
	buttonLayout->addWidget (placeButton);

	// add exchange button
	exchangeButton = new QPushButton ("&Exchange");
	connect(exchangeButton, SIGNAL(clicked()), this, SLOT(exchangePressed()));
	buttonLayout->addWidget (exchangeButton);

	// add pass button
	passButton = new QPushButton ("&Pass");
	connect(passButton, SIGNAL(clicked()), this, SLOT(passPressed()));
	buttonLayout->addWidget (passButton);

	direction = new QComboBox();
	direction->addItem("Horizontal");
	direction->addItem("Vertical");
	buttonLayout->addWidget(direction);

	

	// tiles player will input
	tiles = new QLineEdit();
	
 	vector<Tile*>::iterator it;
 	QString temp;
 	
	for(it = numPlayers[0]->playerhand.begin(); it != numPlayers[0]->playerhand.end(); ++it){
	
		temp += "[";
		temp += (*it)->getLetter();
		temp += ", ";
		temp += QString::number((*it)->getPoints());
		temp += "] ";	
	}

	hand = new QLabel(temp);
	
	right->addWidget(hand);
	right->addWidget(tiles);
	window->setWindowTitle("Scrabble-Qt");
	window->show();
}
void ScrabbleGUI::act() {
	QString str = tiles->text();
	QPushButton *called = (QPushButton*) QObject::sender();
	int i=0,j=0;
	for (int x = 0; x < _b->getx(); x++) {
		for (int y = 0; y < _b->gety(); y++) {
			if (board[x][y] == called) {
				i = x;
				j = y;
			}
		}
	}
	row = i+1;
	col = j+1;
}


void ScrabbleGUI::passPressed(){
	
	QMessageBox msgbox;
	msgbox.setWindowTitle("Pass");
	msgbox.setText("Player passed their turn!");
	msgbox.setStandardButtons(QMessageBox:: Ok);
	msgbox.exec();
	
	passed++;
	update();

}

void ScrabbleGUI::exchangePressed(){


	if(tiles->text().isEmpty()){
		QMessageBox msgbox;
		msgbox.setWindowTitle("No Tiles Given");
		msgbox.setText("Uh oh! Please give tiles to be exchanged.");
		msgbox.setStandardButtons(QMessageBox:: Ok);
		msgbox.exec();
		return;
	}
	else {
		vector<char> letters;
		string temp = tiles->text().toStdString();
		for(unsigned int i = 0; i < temp.size(); i++){
			letters.push_back(temp[i]);
		}
		
		bool worked = numPlayers[count]->exchange(letters);
		if(!worked){
			QMessageBox msgbox;
			msgbox.setWindowTitle("Error");
			msgbox.setText("Uh oh! Error exchanging tiles");
			msgbox.setStandardButtons(QMessageBox:: Ok);
			msgbox.exec();
		}
		numPlayers[count]->draw();
		passed = 0;

	}

	update();





}

void ScrabbleGUI::placePressed(){
	if(tiles->text().isEmpty()){
		QMessageBox msgbox;
		msgbox.setWindowTitle("No Tiles Given");
		msgbox.setText("Uh oh! Please give tiles to be placed.");
		msgbox.setStandardButtons(QMessageBox:: Ok);
		msgbox.exec();
		return;
	}
	else{
	
		string dir;
		if(direction->currentText() == "Horizontal"){
			dir = "-";
		}
		else if(direction->currentText() == "Vertical"){
			dir = "|";
		}
		string temp = tiles->text().toStdString();
		bool worked = numPlayers[count]->place(dir, row, col, temp);
   		if(!worked){
   			QMessageBox msgbox;
			msgbox.setWindowTitle("Error");
			msgbox.setText("Uh oh! Error exchanging tiles");
			msgbox.setStandardButtons(QMessageBox:: Ok);
			msgbox.exec();
		}
		if(worked)
			passed = 0;	
	}
	
	update();
}

void ScrabbleGUI::update(){ // updates board after every turn
	
	if(count == numPlayers.size() -1)
		count = 0;
	else{
		count++;
	}

	vector<Tile*>::iterator it;
 	QString temp;
	for(it = numPlayers[count]->playerhand.begin(); it != numPlayers[count]->playerhand.end(); ++it){
		
		temp += "[";
		temp += (*it)->getLetter();
		temp += ", ";
		temp += QString::number((*it)->getPoints());
		temp += "] ";
		
	}

	hand->setText(temp);

	
	for(unsigned int i=0; i < numPlayers.size(); i++){
		QString t;
		t = t + QString::fromStdString(numPlayers[i]->name());
		t = t + ": ";
		t += QString::number(numPlayers[i]->getPoints());
		playerPoints[i]->setText(t);

	}

	tiles->setText("");
	


	QString tempString;

	tempString = "Player ";
	tempString += QString::fromStdString(numPlayers[count]->name());
	tempString += ", it's your turn";

	playerName->setText(tempString);

	for (int i = 0; i < _b->getx(); i++) {
		for (int j = 0; j < _b->gety(); j++) {
			if(_b->gameboard[i][j].get_letter() != "..."){
				string temp = _b->gameboard[i][j].get_letter();
				QString tileLetter = QString::fromStdString(temp);
				board[i][j]->setText(tileLetter);
			}
		}
	}
	// redoes board
	window->repaint();
	app->processEvents();


   	if(_bag->tilesRemaining() == 0 || allPassed() ) {
   		gameOver();
   	}



}
// ends game with popup window
void ScrabbleGUI::gameOver(){
	window->close();
	QMessageBox msgbox;
	msgbox.setWindowTitle("Game Over!");
	QString temp;
	temp = "Congratulations, game over! \n";

	temp += "Final Scores are: \n";
	for(unsigned int i=0; i < numPlayers.size(); i++){
		temp += QString::fromStdString(numPlayers[i]->name());
		temp += ": ";
		temp += QString::number(numPlayers[i]->getPoints()); 
		temp += "\n";
	}
	
	temp += "Thank you for playing!";
	msgbox.setText(temp);
	msgbox.setStandardButtons(QMessageBox:: Ok);
	msgbox.exec();
		
}

// checks if all players have passed
bool ScrabbleGUI::allPassed(){

	if(passed == numPlayers.size()){
		return true;
	}
	return false;
	
}


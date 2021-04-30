#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
using namespace sf;
using namespace std;
class Unit
{
private:
	void initUnit();
public:
	int pos1, pos2, country, type, move, strenght;
	// 0 || 1 || 2 || 3 || 4 || 5
	Unit();
	virtual ~Unit();
};
class Game
{ 
private:
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	VertexArray map;
	VertexArray selector;
	VertexArray border;
	VertexArray region;
	VertexArray units;
	VertexArray domBar;
	VertexArray arrow;
	VertexArray adjudicated;
	VertexArray menu;
	Sprite text;
	RenderTexture tex;
	Font verdana;
	Unit unit[34];
	Vector2f unitPos[78];
	int tile[2][78][11];
	int data[6][78];
	// 0 isOcean || 1 unitLocation || 2 vertexCountMap || 3 supplAreaLink & regionCountry || 4 dataInt || 5 dataExt || 6 total  
	
	//dataInt: 0 mapArrayCount || 1 borderArrayCount || 2 supplAreaCount || 3 supplAreaArrayCount || 4 cursorRegion || 5 cursorLastRegion || 6 pos1 || 7 lastPos1 || 8 pos2 || 9 lastpos2 || 10 posCount
	// 11 de || 12 oe || 13 ru || 14 fr || 15 it || 16 tr || 17 gb || 18 regionSize || 19 regionBorder
	// 20 unitSize || 21 unitBorder || 22 borderSize || 23 arrowThiccness || 24 arrowLength || 25 arrowWidth || 26 selectedUnit || 27 year (0 spring 1 fall 2 winter) || 28 fontSize || 29 

	//dataExt: 0 scale
	void initVar();
	void initWin();
	void initGame();
public:
	Game();
	virtual ~Game();
	const bool running() const;
	void pollEvents();
	void update();
	void updateColors();
	void updateSelector();
	void updatePos();
	void updateUnits();
	void moveUnit();
	void unitSelector();
	void render();
	void cursorInRegion();
	void loadGame();
	bool isInsideTriangle(Vector2f x1, Vector2f x2, Vector2f x3, Vector2f p);
	float det(Vector2f u, Vector2f v);
	void adjudicate();
	bool moveTile(int type, int pos1, int pos2);
};

 
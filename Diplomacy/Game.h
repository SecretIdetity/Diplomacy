#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
using namespace sf;
using namespace std;
//bc screw typing the whole for i stuff
#define loop(start, end, increment) for(int i = start; i < end; i += increment) //standart i for loop
#define loo(end, increment) for(int i = 0; i < end; i += increment) //standart i for loop but starting at 0
#define lo(end) for(int i = 0; i < end; i++) //standart i for loop starting from 0 with increment 1
#define llo(end, increment) for(int j = 0; j < end; j += increment) //standart j for loop but starting at 0
#define ll(end) for(int j = 0; j < end; j++) //standart j for loop starting from 0 with increment 1
class Unit
{
private:
	void initUnit();
public:
	int pos1, pos2, country, type, move, sucess;
	// 0 || 1 || 2 || 3 || 4 || 5 idk wat dis id lul
	//move: 0 move/stay || 1 supp || 2 conv || 3 canc move || 4 canc supp || 5 canc conv || 6 disband
	Unit();
	virtual ~Unit();
};
class Game
{ 
private:
	Clock timer;
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	VertexArray map;
	VertexArray selector;
	VertexArray border;
	VertexArray debugtri;
	VertexArray region;
	VertexArray units;
	VertexArray domBar;
	VertexArray arrows;
	VertexArray adjudicated;
	VertexArray menu;
	Sprite text;
	RenderTexture tex;
	Sprite fps;
	RenderTexture fp;
	Text fpt;
	Font verdana;
	Unit unit[34];
	Vector2f unitPos[78];
	int tile[2][78][11];
	int data[6][78];
	// 0 isOcean || 1 unitLocation || 2 vertexCountMap || 3 supplAreaLink & regionCountry || 4 dataInt || 5 dataExt || 6 total  
	
	//dataInt: 0 mapArrayCount || 1 borderArrayCount || 2 supplAreaCount || 3 supplAreaArrayCount || 4 cursorRegion || 5 cursorLastRegion || 6 pos1 || 7 lastPos1 || 8 pos2 || 9 lastpos2 || 10 posCount
	// 11 de || 12 au || 13 ru || 14 fr || 15 it || 16 tr || 17 gb || 18 regionSize || 19 regionBorder
	// 20 unitSize || 21 unitBorder || 22 borderSize || 23 arrowThiccness || 24 arrowLength || 25 arrowWidth || 26 selectedUnit || 27 year (0 orders 1 | 1 resolution 1 | 2 retreat/disband 1 | 3 orders 2 | 4 resulution 2 | 5 retreat/disband 2 | 6 create/disband) || 28 fontSize || 29 updatePos1 || 30 updatePos2
	// 31 total

	//dataExt: 0 fpsLimit || 1 isFpsLimit || 2 showFps || 3 showBorder || 4 debug
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
	//void moveUnit();
	void unitSelector();
	void render();
	void cursorInRegion();
	void loadGame();
	bool isInsideTriangle(Vector2f x1, Vector2f x2, Vector2f x3, Vector2f p);
	float det(Vector2f u, Vector2f v);
	void adjudicate();
	bool moveTile(Unit unit, int pos2);
	void frames();
	void keyboard(Keyboard::Key key);
	void drawArrows(int selUnit, int pos2);
	void hashUnits();
	void error(int type, string reason);
	int getChecksum(ifstream file);
	bool checkResolved(int country);
	void checkConvoy();
};


#include "Game.h"

void Game::initVar()
{
	window = nullptr;
	data[4][18] = 12;
	data[4][19] = 2;
	data[4][20] = 30;
	data[4][21] = 4;
	data[4][22] = 2;
	data[4][23] = 5;
	data[4][24] = 40;
	data[4][25] = 10;
	data[4][28] = 14;
}

//
//who needs to comment stuff you do if you can just not know what you did and redo it
//

void Game::initWin()
{
	videoMode.height = 1080;
	videoMode.width = 1920;
	//lul videoMode.bitsPerPixel = 32;
	window = new RenderWindow(videoMode, "Diplomacy", Style::Titlebar | Style::Close | Style::Resize, ContextSettings(0, 0, 1, 0, 0, 0, false));
}

void Game::initGame()
{
	int lineCount = 0;
	map.clear();
	map.setPrimitiveType(Triangles);
	map.resize(0);
	selector.clear();
	selector.setPrimitiveType(Triangles);
	selector.resize(0);
	border.clear();
	border.setPrimitiveType(Quads);
	border.resize(0);
	debugtri.clear();
	debugtri.setPrimitiveType(Lines);
	debugtri.resize(0);
	region.clear();
	region.setPrimitiveType(Quads);
	region.resize(0);
	units.clear();
	units.setPrimitiveType(Quads);
	units.resize(34 * 8);
	domBar.clear();
	domBar.setPrimitiveType(Quads);
	domBar.resize(8 * 4);
	arrows.clear();
	arrows.setPrimitiveType(Quads);
	arrows.resize(4 * 4 * 34);
	menu.clear();
	menu.setPrimitiveType(Quads);
	menu.resize(8);
	fp.create(data[4][28] * 2, data[4][28]);
	fp.setSmooth(true);
	fpt.setFont(verdana);
	fpt.setPosition(0, 0);
	fpt.setCharacterSize(data[4][28]);
	fpt.setFillColor(Color(0, 0, 0));
	string line;
	if (!verdana.loadFromFile("VERDANA.TTF")) {
		error(1, "VERDANA.TFF");
	}
	ifstream fil(".settings.txt");
	if (fil.fail())
		error(1, ".settings.txt");
	if (fil.is_open()) {
		getline(fil, line);
		vector<int> vec;
		stringstream ss(line);
		for (int i; ss >> i;) {
			vec.push_back(i);
			if (ss.peek() == ' ')
				ss.ignore();
		}
		for (size_t i = 0; i < vec.size(); i++) {
			data[5][i] = vec[i];
		}
	}
	fil.close();
	ifstream file(".data.txt");
	if (file.fail())
		error(1, ".data.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			vector<int> vec;
			stringstream ss(line);
			for (int i; ss >> i;) {
				vec.push_back(i);
				if (ss.peek() == ' ')
					ss.ignore();
			}
			if (lineCount == 0) {

			}
			if (lineCount == 1) { //isOcean
				for (size_t i = 0; i < vec.size(); i++) {
					data[0][i] = vec[i];
				}
			}
			if (lineCount == 2) { //supplAreaPos
				for (size_t i = 0; i < vec.size(); i += 2) {
					region.resize(data[4][3] + 8);
					float a = (float)vec[i + 0] * 1.880;
					float b = (float)vec[i + 1] * 1.880;
					float l = (float)data[4][18];
					float s = (float)data[4][19];
					region[data[4][3] + 0].position = Vector2f(a, b);
					region[data[4][3] + 1].position = Vector2f(a + l, b);
					region[data[4][3] + 2].position = Vector2f(a + l, b + l);
					region[data[4][3] + 3].position = Vector2f(a, b + l);
					region[data[4][3] + 4].position = Vector2f(a + s, b + s);
					region[data[4][3] + 5].position = Vector2f(a + l - s, b + s);
					region[data[4][3] + 6].position = Vector2f(a + l - s, b + l - s);
					region[data[4][3] + 7].position = Vector2f(a + s, b + l - s);
					region[data[4][3] + 0].color = Color(0, 0, 0, 255);
					region[data[4][3] + 1].color = Color(0, 0, 0, 255);
					region[data[4][3] + 2].color = Color(0, 0, 0, 255);
					region[data[4][3] + 3].color = Color(0, 0, 0, 255);
					region[data[4][3] + 4].color = Color(255, 255, 255, 255);
					region[data[4][3] + 5].color = Color(255, 255, 255, 255);
					region[data[4][3] + 6].color = Color(255, 255, 255, 255);
					region[data[4][3] + 7].color = Color(255, 255, 255, 255);
					data[4][3] += 8;
				}
			}
			if (lineCount == 3) { //supplAreaLink
				for (size_t i = 0; i < vec.size(); i++) {
					data[3][i] = vec[i];
					data[4][2]++;
				}
			}
			if (lineCount == 4) { //unitPos
				for (size_t i = 0; i < vec.size(); i += 2) {
					unitPos[i / 2].x = (float)vec[i + 0];
					unitPos[i / 2].y = (float)vec[i + 1];
				}
			}
			if (lineCount == 5) { //areaText
				if (!tex.create(609 * 1.880, 575 * 1.880)) {
					return;
				}
				tex.clear(Color(0, 0, 0, 0));
				for (size_t i = 0; i < vec.size(); i += 5) {
					Text t;
					Vector2f a = Vector2f((int)(vec[i + 0] - data[4][28] / 2) * 1.880, (int)(vec[i + 1] - data[4][28] / 3) * 1.880);
					string s = "";
					for (int j = 0; j < 3; j++) {
						char c = (char)(vec[i + j + 2]);
						s += c;
					}
					t.setString(s);
					t.setFont(verdana);
					t.setCharacterSize(data[4][28]);
					t.setFillColor(Color(0, 0, 0));
					t.setPosition(a);
					tex.draw(t);
				}
				tex.setSmooth(true);
				tex.display();
				text.setTexture(tex.getTexture());
			}
			if (lineCount == 6) {
				float a = (float)vec[0] * 2;
				float b = (float)vec[1] * 2;
				float c = (float)vec[2] * 2;
				float d = (float)vec[3] * 2;
				menu[0].position = Vector2f(a, b);
				menu[1].position = Vector2f(c, b);
				menu[2].position = Vector2f(c, d);
				menu[3].position = Vector2f(a, d);
				menu[0].color = Color(222, 222, 222);
				menu[1].color = Color(222, 222, 222);
				menu[2].color = Color(222, 222, 222);
				menu[3].color = Color(222, 222, 222);
				for (size_t i = 4; i < vec.size(); i += 4) {
					menu.resize(i + 4);
					float e = (float)vec[i + 0] * 2;
					float f = (float)vec[i + 1] * 2;
					float g = (float)vec[i + 2] * 2;
					float h = (float)vec[i + 3] * 2;
					menu[i + 0].position = Vector2f(e, f);
					menu[i + 1].position = Vector2f(g, f);
					menu[i + 2].position = Vector2f(g, h);
					menu[i + 3].position = Vector2f(e, h);
					menu[i + 0].color = Color(255, 255, 255);
					menu[i + 1].color = Color(255, 255, 255);
					menu[i + 2].color = Color(255, 255, 255);
					menu[i + 3].color = Color(255, 255, 255);
				}
			}
			if (lineCount > 6 && lineCount < 85) { //mapPos + selector
				for (size_t i = 0; i < vec.size(); i += 6) {
					int color = (lineCount * 255) / 78;//debug
					map.resize(data[4][0] + 3);
					selector.resize(data[4][0] + 3);
					float a = (float)vec[i + 0] * 1.880;
					float b = (float)vec[i + 1] * 1.880;
					float c = (float)vec[i + 2] * 1.880;
					float d = (float)vec[i + 3] * 1.880;
					float e = (float)vec[i + 4] * 1.880;
					float f = (float)vec[i + 5] * 1.880;
					map[data[4][0] + 0].position = Vector2f(a, b);
					map[data[4][0] + 1].position = Vector2f(c, d);
					map[data[4][0] + 2].position = Vector2f(e, f);
					if (!data[0][lineCount - 7]) {//<---------------------------------------------- dont forget if changing line decoding
						map[data[4][0] + 0].color = Color(223, 221, 199, 255);
						map[data[4][0] + 1].color = Color(223, 221, 199, 255);
						map[data[4][0] + 2].color = Color(223, 221, 199, 255);
					}
					else {
						map[data[4][0] + 0].color = Color(207, 208, 243, 255);
						map[data[4][0] + 1].color = Color(207, 208, 243, 255);
						map[data[4][0] + 2].color = Color(207, 208, 243, 255);

					}
					selector[data[4][0] + 0].position = Vector2f(a, b);
					selector[data[4][0] + 1].position = Vector2f(c, d);
					selector[data[4][0] + 2].position = Vector2f(e, f);
					selector[data[4][0] + 0].color = Color(0, 0, 0, 0);
					selector[data[4][0] + 1].color = Color(0, 0, 0, 0);
					selector[data[4][0] + 2].color = Color(0, 0, 0, 0);
					//debug
					if (data[5][4]) {
						int clr = (int)((color + 70) * color) % 255;
						debugtri.resize(data[4][0] * 2 + 6);
						debugtri[data[4][0] * 2 + 0].position = Vector2f(a, b);
						debugtri[data[4][0] * 2 + 1].position = Vector2f(c, d);
						debugtri[data[4][0] * 2 + 2].position = Vector2f(c, d);
						debugtri[data[4][0] * 2 + 3].position = Vector2f(e, f);
						debugtri[data[4][0] * 2 + 4].position = Vector2f(e, f);
						debugtri[data[4][0] * 2 + 5].position = Vector2f(a, b);
						debugtri[data[4][0] * 2 + 0].color = Color(clr, 1 - clr, 0, 255);
						debugtri[data[4][0] * 2 + 1].color = Color(clr, 1 - clr, 0, 255);
						debugtri[data[4][0] * 2 + 2].color = Color(clr, 1 - clr, 0, 255);
						debugtri[data[4][0] * 2 + 3].color = Color(clr, 1 - clr, 0, 255);
						debugtri[data[4][0] * 2 + 4].color = Color(clr, 1 - clr, 0, 255);
						debugtri[data[4][0] * 2 + 5].color = Color(clr, 1 - clr, 0, 255);
					}
					data[4][0] += 3;
					data[2][lineCount - 7] = data[4][0];//<---------------------------------------------- dont forget if changing line decoding
				}
			}
			if (lineCount > 84 && lineCount < 163) { //borderPos
				for (size_t i = 0; i < vec.size(); i += 2) {
					border.resize(data[4][1] + 4);
					Vector2f a = Vector2f((float)vec[i + 0] * 1.880, (float)vec[i + 1] * 1.880);
					Vector2f b = Vector2f((float)vec[(i + 2) % vec.size()] * 1.880, (float)vec[(i + 3) % vec.size()] * 1.880);
					Vector2f e = a - b;
					e = Vector2f(-e.y, e.x);
					e = Vector2f(e.x * data[4][22] / (2 * sqrt(e.x * e.x + e.y * e.y)), e.y * data[4][22] / (2 * sqrt(e.x * e.x + e.y * e.y)));
					border[data[4][1] + 0].position = a + e;
					border[data[4][1] + 1].position = b + e;
					border[data[4][1] + 2].position = b - e;
					border[data[4][1] + 3].position = a - e;
					border[data[4][1] + 0].color = Color(255, 255, 255, 255);
					border[data[4][1] + 1].color = Color(255, 255, 255, 255);
					border[data[4][1] + 2].color = Color(255, 255, 255, 255);
					border[data[4][1] + 3].color = Color(255, 255, 255, 255);
					data[4][1] += 4;
				}
			}
			if (lineCount > 162 && lineCount < 241) { //armyMovement
				for (size_t i = 0; i < vec.size() - 1; i++) {
					tile[0][lineCount - 163][i] = vec[i];//<---------------------------------------------- dont forget if changing line decoding
				}
			}
			if (lineCount > 240 && lineCount < 319) { //fleetMovement
				for (size_t i = 0; i < vec.size() - 1; i++) {
					tile[1][lineCount - 241][i] = vec[i];//<---------------------------------------------- dont forget if changing line decoding
				}
			}
			lineCount++;
		}
	}
	file.close();
	if (VideoMode::getDesktopMode().height == 1080 && VideoMode::getDesktopMode().width == 1920) {
		window->setSize(Vector2u(1920, 1001));
		window->setPosition(Vector2i(-9, -9));
	}
	else if (VideoMode::getDesktopMode().height == 144 && VideoMode::getDesktopMode().width == 2560) {
		window->setSize(Vector2u(2560, 1377));
		window->setPosition(Vector2i(-8, -8));
	}
}

Game::Game()
{
	initVar();
	initWin();
	initGame();
	loadGame();
	updateUnits();
}

Game::~Game()
{ 
	delete window;
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	//cout << "pollevents" << endl;
	while (window->pollEvent(ev)) {
		switch (ev.type) {
		case Event::Closed:
			window->close();
			break;
		case Event::KeyPressed:
			keyboard(ev.key.code);
			break;
		case Event::MouseButtonPressed:
			if (ev.mouseButton.button == Mouse::Right) {
				//right click stuffz
			}
			if (ev.mouseButton.button == Mouse::Left) {
				updatePos();
			}
			break;
		}
	}
}

void Game::update()
{
	frames();
	pollEvents();
	cursorInRegion();
	unitSelector();
}

void Game::updateColors()
{
	//0 general: (223, 221, 199) ?[609, 559]?
	//8 ocean: (207, 208, 243)
	//1 de: (156, 155, 139) (47, 47, 42)    (0, 0, 0)
	//2 oe: (217, 155, 139) (208, 47, 42)   (204, 0, 0)
	//3 ru: (212, 155, 195) (195, 47, 189)  (187, 0, 187)
	//4 fr: (201, 200, 215) (167, 167, 243) (153, 153, 255)
	//5 it: (156, 206, 139) (45, 179, 40)   (0, 170, 0)
	//6 tr: (212, 211, 139) (195, 194, 42)  (187, 187, 0)
	//7 gb: (155, 153, 188) (45, 45, 175)   (0, 0, 170)
	data[4][11] = data[4][12] = data[4][13] = data[4][14] = data[4][15] = data[4][16] = data[4][17] = 0;
	lo(34) {
		Color c1, c2;
		if (unit[i].country) {
			switch (unit[i].country) {
			case 1: c1 = Color(156, 155, 139); c2 = Color(47, 47, 42); break;
			case 2: c1 = Color(217, 155, 139); c2 = Color(208, 47, 42); break;
			case 3: c1 = Color(212, 155, 195); c2 = Color(195, 47, 189); break;
			case 4: c1 = Color(201, 200, 215); c2 = Color(167, 167, 243); break;
			case 5: c1 = Color(156, 206, 139); c2 = Color(45, 179, 40); break;
			case 6: c1 = Color(212, 211, 139); c2 = Color(195, 194, 42); break;
			case 7: c1 = Color(155, 153, 188); c2 = Color(45, 45, 175); break;
			}
			if (!data[0][unit[i].pos1 - 1]) {
				if (unit[i].pos1 == 1) {
					for (int j = 0; j < data[2][0]; j += 3) {
						map[j + 0].color = c1;
						map[j + 1].color = c1;
						map[j + 2].color = c1;
					}
				}
				else {
					for (int j = data[2][unit[i].pos1 - 2]; j < data[2][unit[i].pos1 - 1]; j += 3) {
						map[j + 0].color = c1;
						map[j + 1].color = c1;
						map[j + 2].color = c1;
					}
				}
			}
			for (int j = 0; j < 34; j++) {
				if (unit[i].pos1 == data[3][j]) {
					region[j * 8 + 4].color = c2;
					region[j * 8 + 5].color = c2;
					region[j * 8 + 6].color = c2;
					region[j * 8 + 7].color = c2;
					data[3][j + 34] = unit[i].country;
				}
			}
		}
	}
	lo(34) {
		if (data[3][i + 34])
			data[4][data[3][i + 34] + 10] += 1;
	}
	int count = 0;
	Color c1;
	lo(8) {
		switch (i) {
		case 0: c1 = Color(0, 0, 0); break;
		case 1: c1 = Color(204, 0, 0); break;
		case 2: c1 = Color(187, 0, 187); break;
		case 3: c1 = Color(153, 153, 255); break;
		case 4: c1 = Color(0, 170, 0); break;
		case 5: c1 = Color(187, 187, 0); break;
		case 6: c1 = Color(0, 0, 170); break;
		case 7: c1 = Color(255, 255, 255); break;
		}
		float a = (float)(1145 + data[4][22] * 0.94) * count / 34;
		float b = (float)(1145 + data[4][22] * 0.94) * (count + data[4][i + 11]) / 34;
		if (i == 7)
			b = (float)(1145 + data[4][22] * 0.94);
		float c = (float)(1051);
		float d = (float)(1080);
		domBar[i * 4 + 0].position = Vector2f(a, c);
		domBar[i * 4 + 1].position = Vector2f(b, c);
		domBar[i * 4 + 2].position = Vector2f(b, d);
		domBar[i * 4 + 3].position = Vector2f(a, d);
		domBar[i * 4 + 0].color = c1;
		domBar[i * 4 + 1].color = c1;
		domBar[i * 4 + 2].color = c1;
		domBar[i * 4 + 3].color = c1;
		count += data[4][i + 11];
	}
}

void Game::updateSelector()
{
	//cout << "updateselector" << endl;
	if (data[4][29]) {
		if (data[4][7]) {
			if (data[4][7] == 1) {
				loop (0, data[2][0], 3) {
					selector[i + 0].color = Color(0, 0, 0, 0);
					selector[i + 1].color = Color(0, 0, 0, 0);
					selector[i + 2].color = Color(0, 0, 0, 0);

				}
			}
			else for (int i = data[2][data[4][7] - 2]; i < data[2][data[4][7] - 1]; i += 3) {
				selector[i + 0].color = Color(0, 0, 0, 0);
				selector[i + 1].color = Color(0, 0, 0, 0);
				selector[i + 2].color = Color(0, 0, 0, 0);

			}
		}
	}
	if (data[4][30]) {
		if (data[4][9]) {// && data[4][9] != data[4][6]) {
			if (data[4][9] == 1) {
				for (int i = 0; i < data[2][0]; i += 3) {
					selector[i + 0].color = Color(0, 0, 0, 0);
					selector[i + 1].color = Color(0, 0, 0, 0);
					selector[i + 2].color = Color(0, 0, 0, 0);
				}
			}
			else for (int i = data[2][data[4][9] - 2]; i < data[2][data[4][9] - 1]; i += 3) {
				selector[i + 0].color = Color(0, 0, 0, 0);
				selector[i + 1].color = Color(0, 0, 0, 0);
				selector[i + 2].color = Color(0, 0, 0, 0);

			}
		}
	}
	if (data[4][4] != data[4][5]) {
		if (data[4][5] && data[4][5] != data[4][6] && data[4][5] != data[4][8]) {
			if (data[4][5] == 1) {
				for (int i = 0; i < data[2][0]; i += 3) {
					selector[i + 0].color = Color(0, 0, 0, 0);
					selector[i + 1].color = Color(0, 0, 0, 0);
					selector[i + 2].color = Color(0, 0, 0, 0);
				}
			}
			else for (int i = data[2][data[4][5] - 2]; i < data[2][data[4][5] - 1]; i += 3) {
				selector[i + 0].color = Color(0, 0, 0, 0);
				selector[i + 1].color = Color(0, 0, 0, 0);
				selector[i + 2].color = Color(0, 0, 0, 0);

			}
		}
	}
	if (data[4][29]) {
		if (data[4][6]) {
			if (data[4][6] == 1) {
				for (int i = 0; i < data[2][0]; i += 3) {
					selector[i + 0].color = Color(255, 127, 0, 63);
					selector[i + 1].color = Color(255, 127, 0, 63);
					selector[i + 2].color = Color(255, 127, 0, 63);
				}
			}
			else for (int i = data[2][data[4][6] - 2]; i < data[2][data[4][6] - 1]; i += 3) {
				selector[i + 0].color = Color(255, 127, 0, 63);
				selector[i + 1].color = Color(255, 127, 0, 63);
				selector[i + 2].color = Color(255, 127, 0, 63);
			}
		}
		data[4][7] = data[4][6];
		data[4][29] = 0;
	}
	if (data[4][30]) {
		if (data[4][8]){
			if (data[4][8] == 1) {
				for (int i = 0; i < data[2][0]; i += 3) {
					selector[i + 0].color = Color(0, 127, 0, 63);
					selector[i + 1].color = Color(0, 127, 0, 63);
					selector[i + 2].color = Color(0, 127, 0, 63);
				}
			}
			else for (int i = data[2][data[4][8] - 2]; i < data[2][data[4][8] - 1]; i += 3) {
				selector[i + 0].color = Color(0, 127, 0, 63);
				selector[i + 1].color = Color(0, 127, 0, 63);
				selector[i + 2].color = Color(0, 127, 0, 63);
			}
		}
		data[4][9] = data[4][8];
		data[4][30] = 0;
	}
	if (data[4][4] != data[4][5]) {
		if (data[4][4] && data[4][4] != data[4][6] && data[4][4] != data[4][8]) {
			if (!data[4][4]) {
				for (int i = 0; i < data[2][0]; i += 3) {
					selector[i + 0].color = Color(127, 127, 127, 63);
					selector[i + 1].color = Color(127, 127, 127, 63);
					selector[i + 2].color = Color(127, 127, 127, 63);
				}
			}
			else for (int i = data[2][data[4][4] - 2]; i < data[2][data[4][4] - 1]; i += 3) {
				selector[i + 0].color = Color(127, 127, 127, 63);
				selector[i + 1].color = Color(127, 127, 127, 63);
				selector[i + 2].color = Color(127, 127, 127, 63);
			}
		}
		data[4][5] = data[4][4];
	}
}

void Game::updatePos()
{
	//cout << "updatepos" << endl;
	if (!data[4][4]) {
		data[4][6] = data[4][8] = 0;
		data[4][29] = data[4][30] = 1;
		data[4][10] = 0;
	}
	else if (!data[4][10]) {
		data[4][6] = data[4][4];
		data[4][8] = 0;
		data[4][29] = data[4][30] = 1;
		data[4][10] = 1;
		drawArrows(data[1][data[4][6] - 1] - 1, data[4][6]);
	}
	else if (data[4][10] == 1) {
		data[4][8] = data[4][4];
		data[4][30] = 1;
		data[4][10] = 0;
	}
}

void Game::updateUnits()
{
	lo(34) {
		if (!unit[i].pos1) {
			units[i * 8 + 0].position = Vector2f(0, 0);
			units[i * 8 + 1].position = Vector2f(0, 0);
			units[i * 8 + 2].position = Vector2f(0, 0);
			units[i * 8 + 3].position = Vector2f(0, 0);
			units[i * 8 + 4].position = Vector2f(0, 0);
			units[i * 8 + 5].position = Vector2f(0, 0);
			units[i * 8 + 6].position = Vector2f(0, 0);
			units[i * 8 + 7].position = Vector2f(0, 0);
		}
		else {
			Color c1, c2;
			float a = (float)unitPos[unit[i].pos1 - 1].x * 1.880;
			float b = (float)unitPos[unit[i].pos1 - 1].y * 1.880;
			float l = (float)data[4][20];
			float s = (float)data[4][21];
			if (unit[i].type) {
				units[i * 8 + 0].position = Vector2f(a, b);
				units[i * 8 + 1].position = Vector2f(a + l * 2 / 3, b);
				units[i * 8 + 2].position = Vector2f(a + l * 2 / 3, b + l * 2 / 3);
				units[i * 8 + 3].position = Vector2f(a, b + l * 2 / 3);
				units[i * 8 + 4].position = Vector2f(a + s, b + s);
				units[i * 8 + 5].position = Vector2f(a + l * 2 / 3 - s, b + s);
				units[i * 8 + 6].position = Vector2f(a + l * 2 / 3 - s, b + l * 2 / 3 - s);
				units[i * 8 + 7].position = Vector2f(a + s, b + l * 2 / 3 - s);
			}
			else {
				units[i * 8 + 0].position = Vector2f(a - l / 6, b);
				units[i * 8 + 1].position = Vector2f(a + l * 5 / 6, b);
				units[i * 8 + 2].position = Vector2f(a + l / 3, b + l * 2 / 3);
				units[i * 8 + 3].position = Vector2f(a + l / 3, b + l * 2 / 3);
				units[i * 8 + 4].position = Vector2f(a + s * 20 / 9 - l / 6, b + s);
				units[i * 8 + 5].position = Vector2f(a + l * 5 / 6 - s * 20 / 9, b + s);
				units[i * 8 + 6].position = Vector2f(a + l / 3, b + l * 2 / 3 - s * 5 / 3);
				units[i * 8 + 7].position = Vector2f(a + l / 3, b + l * 2 / 3 - s * 5 / 3);
			}
			switch (unit[i].country) {
			case 1: c1 = Color(47, 47, 42); c2 = Color(0, 0, 0); break;
			case 2:	c1 = Color(208, 47, 42); c2 = Color(204, 0, 0); break;
			case 3:	c1 = Color(195, 47, 189); c2 = Color(187, 0, 187); break;
			case 4:	c1 = Color(167, 167, 243); c2 = Color(153, 153, 255);  break;
			case 5:	c1 = Color(45, 179, 40); c2 = Color(0, 170, 0); break;
			case 6:	c1 = Color(195, 194, 42); c2 = Color(187, 187, 0); break;
			case 7:	c1 = Color(45, 45, 175); c2 = Color(0, 0, 170); break;
			}
			units[i * 8 + 0].color = c2;
			units[i * 8 + 1].color = c2;
			units[i * 8 + 2].color = c2;
			units[i * 8 + 3].color = c2;
			units[i * 8 + 4].color = c1;
			units[i * 8 + 5].color = c1;
			units[i * 8 + 6].color = c1;
			units[i * 8 + 7].color = c1;
		}
	}
}

void Game::unitSelector()
{
	//cout << "unitselector" << endl;
	if (data[4][29]) {
		data[4][26] = 0;
		//data[4][26] = unit[data[1][data[4][6] - 2]].pos1 + 1;   idk what this did but ill leave it here; -2 presumably bc -1 init and -1 after hash readj
		lo(34) {
			if (unit[i].pos1 == data[4][6]) {
				data[4][26] = i + 1;
				continue;
			}
		}
	}
	if (!data[4][6])
		data[4][26] = 0;
	if (data[4][4] != data[4][5]) {
		drawArrows(data[4][26] - 1, data[4][4]);
	}
	if (data[4][6] && data[4][29]) { //update pos1
		unit[data[1][data[4][6] - 1] - 1].pos2 = unit[data[1][data[4][6] - 1] - 1].pos1;
		int l = 0;
		if (unit[data[1][data[4][6] - 1] - 1].move == 2)
			l = 1;
		unit[data[1][data[4][6] - 1] - 1].move = 0;
		lo(34) {
			if (unit[i].pos1 == unit[i].pos2)
				unit[i].move = 0;
		}
		if (l)
			checkConvoy();
		drawArrows(data[4][26] - 1, data[4][4]);
	}
	if (data[4][30] && data[4][8] && data[4][26]) { //update pos2
		if (unit[data[4][26] - 1].country && moveTile(unit[data[4][26] - 1], data[4][4]))
			unit[data[4][26] - 1].pos2 = data[4][8];
		if (data[0][unit[data[4][26] - 1].pos2 - 1] && unit[data[4][26] - 1].type)
			unit[data[4][26] - 1].move = 2;
		if (unit[data[4][26] - 1].move == 2 && data[4][8]) {// && moveTile(unit[data[4][26] - 1], data[4][4])) {
			if (data[4][4] && data[0][data[4][4] - 1] && moveTile(unit[data[4][26] - 1], data[4][4])) {
				int a = data[1][data[4][8] - 1];
				if (a)
					data[4][26] = data[1][data[4][8] - 1];
				data[4][6] = data[4][8];
				data[4][29] = 1;
				unit[data[4][26] - 1].move = 2;
				updatePos();
			}
			else {
				checkConvoy();
				drawArrows(-1, data[4][4]);
				data[4][26] = 0;
			}
		}
		else {
			data[4][26] = 0;
		}
	}
}

void Game::render()
{
	//cout << "render" << endl;
	if (data[5][4])
		window->clear(Color(255, 0, 255, 255));
	else
		window->clear(Color(255, 255, 255, 255));
	updateSelector();
	window->draw(map);
	window->draw(selector);
	window->draw(border);
	if (data[5][4])
		window->draw(debugtri);
	window->draw(region);
	window->draw(units);
	window->draw(domBar);
	window->draw(arrows);
	window->draw(text);
	window->draw(menu);
	if (data[5][2])
		window->draw(fps);
	window->display();
}

void Game::cursorInRegion()
{
	//cout << "cursorinregion" << endl;
	int v = -1;
	Vector2f m = (Vector2f)Vector2i(Mouse::getPosition(*window).x * 1920  / window->getSize().x, Mouse::getPosition(*window).y * 1080 / window->getSize().y);
	//cout << window->getSize().x << " " << window->getSize().y << " " << window->getPosition().x << " " << window->getPosition().y << endl;
	if (m.x > 1147 || m.y > 1053 || m.x < 0 || m.y < 0) {
		data[4][4] = 0;
		return;
	}
	if (m.x >= 0 && m.y >= 0)
		for (size_t i = 0; i < map.getVertexCount(); i += 3) {
			if (isInsideTriangle(map[i].position, map[i + 1].position, map[i + 2].position, m)) {
				v = i;
				continue;
			}
		}
	if (v == -1) {
		data[4][4] = 0;
		return;
	}
	if (data[2][0] > v) {
		data[4][4] = 1;
		return;
	}
	lo(78) {
		if (data[2][i] > v && data[2][i - 1] <= v) {
			data[4][4] = i + 1;
			return;
		}
	}
}

void Game::loadGame()
{
	int lineCount = 0; //linecount will be changed to allow more saves
	int unitCount = 0;
	lo(34) {
		unit[i].country = unit[i].pos1 = unit[i].pos2 = unit[i].move = 0;
	}
	string line;
	ifstream save(".save.txt");
	if(save.fail())
		error(1, ".save.txt");
	if (save.is_open()) {
		while (getline(save, line)) {
			vector<int> vec;
			stringstream ss(line);
			for (int i; ss >> i;) {
				vec.push_back(i);
				if (ss.peek() == ' ')
					ss.ignore();
			}
			if (lineCount == 1) {
				data[4][27] = vec[0];
				for (size_t i = 1; i < vec.size(); i++) {
					if (vec[i]) {
						unit[unitCount].pos2 = unit[unitCount].pos1 = i;
						unit[unitCount].type = vec[i] % 2;
						unit[unitCount].country = (vec[i] + vec[i] % 2) / 2;
						unitCount++;
					}
					if (unitCount > 34)
						error(2, ".save.txt");
				}
			}
			lineCount++;
		}
	}
	save.close();
	hashUnits();
	updateColors();
	drawArrows(0, 0);
}

bool Game::isInsideTriangle(Vector2f x1, Vector2f x2, Vector2f x3, Vector2f p)
{
	if (det(x2 - x1, p - x1) < 0 && det(x3 - x2, p - x2) < 0 && det(x1 - x3, p - x3) < 0)// || det(x2 - x1, p - x1) > 0 && det(x3 - x2, p - x2) > 0 && det(x1 - x3, p - x3) > 0)
	{
		return true;
	}
	else return false;
}

float Game::det(Vector2f u, Vector2f v)
{
	float result = u.x * v.y - u.y * v.x;
	return result;
}

void Game::adjudicate()
{
	//switch year (0 ord 1 | 1 adj 1 | 2 r&d 1 | 3 ord 2 | 4 adj 2 | 5 r&d 2 | 6 units)
	//(0 orders 1 | 1 resolution 1 | 2 retreat / disband 1 | 3 orders 2 | 4 resulution 2 | 5 retreat / disband 2 | 6 create / disband)
	//backend uhhh
	//move: 0 move/stay || 1 supp || 2 conv || 3 canc move || 4 canc supp || 5 canc conv || 6 disband
	switch (data[4][27] % 7) {
	case 0: case 3:
		lo(34) {
			if (unit[i].pos1 != 0 && unit[i].pos2 != 0 && unit[i].pos1 != unit[i].pos2 && data[1][unit[i].pos2 - 1] != 0)
				if (unit[data[1][unit[i].pos2 - 1] - 1].move == 1 || unit[data[1][unit[i].pos2 - 1] - 1].move == 2)
					unit[data[1][unit[i].pos2 - 1] - 1].move += 3;
		}
		data[4][27]++;
		break;
	case 1: case 4:

		data[4][27]++;
		break;
	case 2: case 5:

		//2: no area 5: capture area
		data[4][27]++;
		break;
	case 6:

		data[4][27]++;
		break;
	}
	updateUnits();
	hashUnits();
	drawArrows(0, 0);
}

bool Game::moveTile(Unit uni, int pos2)
{
	//cout << "movetile " << uni.pos1 << " " << uni.move << " " << pos2 << endl;
	if (!pos2)
		return 0;
	bool t = 0;
	/*

	duh gotta actually name vars

	*/
	switch (uni.move) {
	case 0:
		if (uni.pos1 == pos2)
			return 1;
		lo(11) {
			if (tile[(uni.type + 1) % 2][uni.pos1 - 1][i] == pos2)
				return 1;
		}
		if (!uni.type)
			return 0;
		lo(11) {
			if (tile[1][uni.pos1 - 1][i] == pos2 && data[1][tile[1][uni.pos1 - 1][i] - 1] && !unit[data[1][tile[1][uni.pos1 - 1][i] - 1]].type) {
				return 1;
			}
		}
		break;
	case 1:
		t = 0;
		if (!data[1][pos2 - 1] ||
			unit[data[1][pos2 - 1] - 1].pos1 == unit[data[1][pos2 - 1] - 1].pos2 ||
			unit[data[1][pos2 - 1] - 1].move ||
			unit[data[1][pos2 - 1] - 1].pos2 == uni.pos1 ||
			unit[data[1][pos2 - 1] - 1].pos1 == unit[data[1][pos2 - 1] - 1].pos2)
			return 0;
		lo(11) {
			if (tile[(uni.type + 1) % 2][uni.pos1 - 1][i] == pos2)
				t = 1;
		}
		if (t)
			lo(11) {
			if (tile[(uni.type + 1) % 2][uni.pos1 - 1][i] == unit[data[1][pos2 - 1] - 1].pos2)
				return 1;
		}
		break;
	case 2:
		if (!uni.type) {
			lo(11) {
				if (data[0][uni.pos1 - 1] && tile[1][uni.pos1 - 1][i] == pos2) {
					if (!unit[data[1][tile[1][uni.pos1 - 1][i] - 1]].move && data[1][tile[1][uni.pos1 - 1][i] - 1])
						return 1;
					if (!data[0][pos2 - 1])
						return 1;
				}
			}
		}
		else {
			lo(11) {
				if (tile[1][uni.pos1 - 1][i] == pos2) {
					return 1;
				}
			}
		}
		break;
	}
	cout << "0" << endl;
	return 0;
}

void Game::frames()
{
	//cout << "frames" << endl;
	int tim = timer.restart().asMilliseconds();
	if (tim < data[5][0] && data[5][1])
		sleep(milliseconds(data[5][0] - tim));
	if (data[5][2]) {
		fp.clear(Color(0, 0, 0, 0));
		int i = 1000 / (tim - 0.000000000001);
		string s = to_string(i);
		fpt.setString(s);
		fp.draw(fpt);
		fp.display();
		fps.setTexture(fp.getTexture());
	}
}

void Game::keyboard(Keyboard::Key key)
{
	//cout << "keyboard" << endl;
	switch (key) {
	case Keyboard::Escape:
		window->close();
		break;
	case Keyboard::A:
		adjudicate(); //temp
		break;
	case Keyboard::Space:
		unit[data[4][26] - 1].move = 1;
		break;
	case Keyboard::B:
		unit[data[4][26] - 1].move = 0;
		break;
	}
	drawArrows(data[4][26] - 1, data[4][4]);
}

void Game::drawArrows(int selUnit, int pos2)
{
	//cout << selUnit << " " << pos2 << endl;
	//cout << "drawarrows " << selUnit << " " << pos2 << endl;
	//gotta make it depending on year
	if (selUnit > 34)
		return;
	arrows.clear();
	arrows.resize(16 * 34);
	Color col;
	int tem = unit[selUnit].pos2;
	if (selUnit >= 0 && moveTile(unit[selUnit], pos2))
		unit[selUnit].pos2 = pos2;
	lo(34) {
		Vector2f a, b, c, bb, cc;
		if (!unit[i].pos1)
			continue;
		if (!unit[i].pos2)
			unit[i].pos2 = unit[i].pos1;
		if (unit[i].pos1 != unit[i].pos2) {
			a = Vector2f(unitPos[unit[i].pos1 - 1].x * 1.880 + data[4][20] / 3, unitPos[unit[i].pos1 - 1].y * 1.880 + data[4][20] / 3);
			switch (unit[i].move) {
			case 0:
				if (data[0][unit[i].pos2 - 1] && unit[i].type) {
					col = Color(0, 127, 255, 255);
				}
				else
					col = Color(0, 0, 0, 255);
				b = Vector2f(unitPos[unit[i].pos2 - 1].x * 1.880 + data[4][20] / 3, unitPos[unit[i].pos2 - 1].y * 1.880 + data[4][20] / 3);
				break;
			case 1:
				b = Vector2f((unitPos[unit[i].pos2 - 1].x + unitPos[unit[data[1][unit[i].pos2 - 1] - 1].pos2 - 1].x) / 2 * 1.880 + data[4][20] / 3, (unitPos[unit[i].pos2 - 1].y + unitPos[unit[data[1][unit[i].pos2 - 1] - 1].pos2 - 1].y) / 2 * 1.880 + data[4][20] / 3);
				col = Color(0, 127, 0, 255);
				break;
			case 2:
				b = Vector2f(unitPos[unit[i].pos2 - 1].x * 1.880 + data[4][20] / 3, unitPos[unit[i].pos2 - 1].y * 1.880 + data[4][20] / 3);
				col = Color(0, 127, 255, 255);
				break;
			case 3:
				b = Vector2f(unitPos[unit[i].pos2 - 1].x * 1.880 + data[4][20] / 3, unitPos[unit[i].pos2 - 1].y * 1.880 + data[4][20] / 3);
				col = Color(255, 0, 0, 255);
				break;
			case 4:
				b = Vector2f((unitPos[unit[i].pos2 - 1].x + unitPos[unit[data[1][unit[i].pos2 - 1] - 1].pos2 - 1].x) / 2 * 1.880 + data[4][20] / 3, (unitPos[unit[i].pos2 - 1].y + unitPos[unit[data[1][unit[i].pos2 - 1] - 1].pos2 - 1].y) / 2 * 1.880 + data[4][20] / 3);
				col = Color(255, 127, 0, 255);
				break;
			case 5:
				b = Vector2f(unitPos[unit[i].pos2 - 1].x * 1.880 + data[4][20] / 3, unitPos[unit[i].pos2 - 1].y * 1.880 + data[4][20] / 3);
				col = Color(0, 127, 255, 255);
				break;
			case 6:
				//we will see
				break;
			}
			Vector2f e = a - b;
			e = Vector2f(-e.y, e.x);
			e = Vector2f(e.x * data[4][23] / (2 * sqrt(e.x * e.x + e.y * e.y)), e.y * data[4][23] / (2 * sqrt(e.x * e.x + e.y * e.y)));
			Vector2f c = a - b;
			c = Vector2f(c.x * data[4][24] / (sqrt(c.x * c.x + c.y * c.y)), c.y * data[4][24] / (sqrt(c.x * c.x + c.y * c.y)));
			arrows[i * 16 + 0].position = a + e;
			arrows[i * 16 + 1].position = b + e + c;
			arrows[i * 16 + 2].position = b - e + c;
			arrows[i * 16 + 3].position = a - e;
			arrows[i * 16 + 4].position = b;
			arrows[i * 16 + 5].position = b;
			arrows[i * 16 + 6].position = b + c + Vector2f(c.y * data[4][25] / data[4][24], -c.x * data[4][25] / data[4][24]);;
			arrows[i * 16 + 7].position = b + c - Vector2f(c.y * data[4][25] / data[4][24], -c.x * data[4][25] / data[4][24]);;
			for (int j = 0; j < 8; j++) {
				arrows[i * 16 + j].color = col;
			}
		}
		//#00c5ff
		else {
			a = Vector2f(unitPos[unit[i].pos1 - 1].x * 1.880 + data[4][20] / 3, unitPos[unit[i].pos1 - 1].y * 1.880 + data[4][20] / 3);
			b = Vector2f(data[4][20] * 0.6, data[4][20] * 0.6);
			Vector2f bb = Vector2f(b.x, -b.y);
			Vector2f c = Vector2f(data[4][23], data[4][23]);
			Vector2f cc = Vector2f(c.x, -c.y);
			arrows[i * 16 + 0].position = a - b;
			arrows[i * 16 + 1].position = a - b + c;
			arrows[i * 16 + 2].position = a - bb + cc;
			arrows[i * 16 + 3].position = a - bb;
			arrows[i * 16 + 4].position = a + bb;
			arrows[i * 16 + 5].position = a + bb - cc;
			arrows[i * 16 + 6].position = a - b + c;
			arrows[i * 16 + 7].position = a - b;
			arrows[i * 16 + 8].position = a + b;
			arrows[i * 16 + 9].position = a + b - c;
			arrows[i * 16 + 10].position = a + bb - cc;
			arrows[i * 16 + 11].position = a + bb;
			arrows[i * 16 + 12].position = a - bb;
			arrows[i * 16 + 13].position = a - bb + cc;
			arrows[i * 16 + 14].position = a + b - c;
			arrows[i * 16 + 15].position = a + b;
			Color co;
			if (i != selUnit)
				unit[i].move = 0;
			switch (unit[i].move) {
			case 0:
				co = Color(63, 63, 63, 191);
				break;
			case 1:
				co = Color(0, 127, 0, 255);
				break;
			case 2:
				co = Color(0, 127, 255, 255);
				break;
			default:
				error(3, "");
				break;
			}
			if (!data[5][3])
				co = Color(0, 0, 0, 0);
			for (int j = 0; j < 16; j++)
				arrows[i * 16 + j].color = co;
		}
	}
	unit[selUnit].pos2 = tem;
	return;
}

void Game::hashUnits()
{
	lo(78)
		data[1][i] = 0;
	lo(34)
		if (unit[i].pos1)
			data[1][unit[i].pos1 - 1] = i + 1;
}

void Game::error(int n, string r)
{
	string st = "";
	switch (n) {
	case 1:
		st = "The " + r + " file was not found. Please add it.";
		break;
	case 2:
		st = "The " + r + " file is invalid. Please replace it.";
		break;
	case 3:
		st = "Runtime Error, please report as bug if it persists.";
		break;
	default:
		st = "Unknown Error";
		break;
	}
	string s = st + "\nPress Enter to save this text in the .error.txt report\nand anything else to close this window.";
	RenderTexture erro;
	Sprite err;
	if (!erro.create(data[4][28] * 100, data[4][28] * 4)) {
		return;
	}
	erro.clear(Color(0, 0, 0, 0));
	Text t;
	t.setString(s);
	t.setFont(verdana);
	t.setCharacterSize(data[4][28]);
	t.setFillColor(Color(0, 0, 0));
	erro.draw(t);
	erro.setSmooth(true);
	erro.display();
	err.setTexture(erro.getTexture());
	err.setPosition(Vector2f(750, 500));
	while (1) {
		frames();
		window->clear(Color(255, 255, 255));
		window->draw(err);
		window->display();
		while (window->pollEvent(ev)) {
			switch (ev.type) {
			case Event::Closed:
				window->close();
				return;
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Enter) {
					time_t now = time(0);
					tm* l = localtime(&now);
					ofstream file(".error.txt");
					file << "This is the error-report from " << l->tm_mday << "." << l->tm_mon + 1 << "." << l->tm_year + 1900 << ", " << l->tm_hour << ":" << l->tm_min << ":" << l->tm_sec << ":" << endl << "If the error(s) cannot be fixed by replacing the file you should update and replace the whole game-folder." << endl << st << endl;
					file.close();
				}
				window->close();
				return;
			case Event::MouseButtonPressed:
				window->close();
				return;
			}
		}
	}
	return;
}

int Game::getChecksum(ifstream file)
{
	return 0;
}

bool Game::checkResolved(int country)
{
	return false;
}

void Game::checkConvoy()
{
	int t[34];
	lo(34)
		t[i] = 0;
	lo(34) {
		if (unit[i].pos1 && unit[i].type && unit[i].move == 2) {
			int tt[34];
			ll(34) {
				tt[j] = 0;
			}
			tt[i] = 1;
			int a = i;
			ll(20) {
				int p = unit[a].pos2;
				if (!p)
					break;
				int u = data[1][p - 1];
				if (!u)
					break;
				tt[u - 1] = 1;
				if (unit[u - 1].move == 2 && !unit[u - 1].type) {
					if (!data[0][unit[u - 1].pos2 - 1]) {
						ll(34) {
							if(tt[j])
							t[j] = 1;
						}
						break;
					}
					if (data[1][unit[u - 1].pos2 - 1]) {
						a = u - 1;
					}
					else 
						break;
				}
				else
					break;
			}
		}
	}
	lo(34)
		if (unit[i].move == 2 && !t[i]) {
			unit[i].move = 0;
			unit[i].pos2 = unit[i].pos1;
		}
}

void Unit::initUnit()
{

}

Unit::Unit()
{
	initUnit();
}

Unit::~Unit()
{
	
}
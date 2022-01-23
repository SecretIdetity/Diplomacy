#include "Game.h"

void Game::initVar()
{
	this->window = nullptr;
	this->data[4][18] = 12;
	this->data[4][19] = 2;
	this->data[4][20] = 30;
	this->data[4][21] = 4;
	this->data[4][22] = 2;
	this->data[4][23] = 5;
	this->data[4][24] = 40;
	this->data[4][25] = 10;
	this->data[4][28] = 14;
}

void Game::initWin()
{
	this->videoMode.height = 1080;
	this->videoMode.width = 1920;
	//lul this->videoMode.bitsPerPixel = 32;
	this->window = new RenderWindow(this->videoMode, "Diplomacy", Style::Titlebar | Style::Close | Style::Resize, ContextSettings(0, 0, 1, 0, 0, 0, false));
}

void Game::initGame()
{
	/*ofstream fle(".error.txt");
	fle << "If this report is empty you encountered a runtime error." << endl;
	fle.close();*/
	int lineCount = 0;
	this->map.clear();
	this->map.setPrimitiveType(Triangles);
	this->map.resize(0);
	this->selector.clear();
	this->selector.setPrimitiveType(Triangles);
	this->selector.resize(0);
	this->border.clear();
	this->border.setPrimitiveType(Quads);
	this->border.resize(0);
	this->region.clear();
	this->region.setPrimitiveType(Quads);
	this->region.resize(0);
	this->units.clear();
	this->units.setPrimitiveType(Quads);
	this->units.resize(34 * 8);
	this->domBar.clear();
	this->domBar.setPrimitiveType(Quads);
	this->domBar.resize(8 * 4);
	this->arrows.clear();
	this->arrows.setPrimitiveType(Quads);
	this->arrows.resize(4 * 4 * 34);
	this->menu.clear();
	this->menu.setPrimitiveType(Quads);
	this->menu.resize(8);
	this->fp.create(this->data[4][28] * 2, this->data[4][28]);
	this->fp.setSmooth(true);
	this->fpt.setFont(verdana);
	this->fpt.setPosition(0, 0);
	this->fpt.setCharacterSize(this->data[4][28]);
	this->fpt.setFillColor(Color(0, 0, 0));
	string line;
	if (!this->verdana.loadFromFile("VERDANA.TTF")) {
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
			this->data[5][i] = vec[i];
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
					this->data[0][i] = vec[i];
				}
			}
			if (lineCount == 2) { //supplAreaPos
				for (size_t i = 0; i < vec.size(); i += 2) {
					this->region.resize(this->data[4][3] + 8);
					float a = (float)vec[i + 0] * 1.880;
					float b = (float)vec[i + 1] * 1.880;
					float l = (float)this->data[4][18];
					float s = (float)this->data[4][19];
					this->region[this->data[4][3] + 0].position = Vector2f(a, b);
					this->region[this->data[4][3] + 1].position = Vector2f(a + l, b);
					this->region[this->data[4][3] + 2].position = Vector2f(a + l, b + l);
					this->region[this->data[4][3] + 3].position = Vector2f(a, b + l);
					this->region[this->data[4][3] + 4].position = Vector2f(a + s, b + s);
					this->region[this->data[4][3] + 5].position = Vector2f(a + l - s, b + s);
					this->region[this->data[4][3] + 6].position = Vector2f(a + l - s, b + l - s);
					this->region[this->data[4][3] + 7].position = Vector2f(a + s, b + l - s);
					this->region[this->data[4][3] + 0].color = Color(0, 0, 0, 255);
					this->region[this->data[4][3] + 1].color = Color(0, 0, 0, 255);
					this->region[this->data[4][3] + 2].color = Color(0, 0, 0, 255);
					this->region[this->data[4][3] + 3].color = Color(0, 0, 0, 255);
					this->region[this->data[4][3] + 4].color = Color(255, 255, 255, 255);
					this->region[this->data[4][3] + 5].color = Color(255, 255, 255, 255);
					this->region[this->data[4][3] + 6].color = Color(255, 255, 255, 255);
					this->region[this->data[4][3] + 7].color = Color(255, 255, 255, 255);
					this->data[4][3] += 8;
				}
			}
			if (lineCount == 3) { //supplAreaLink
				for (size_t i = 0; i < vec.size(); i++) {
					this->data[3][i] = vec[i];
					this->data[4][2]++;
				}
			}
			if (lineCount == 4) { //unitPos
				for (size_t i = 0; i < vec.size(); i += 2) {
					this->unitPos[i / 2].x = (float)vec[i + 0];
					this->unitPos[i / 2].y = (float)vec[i + 1];
				}
			}
			if (lineCount == 5) { //areaText
				if (!this->tex.create(609 * 1.880, 575 * 1.880)) {
					return;
				}
				this->tex.clear(Color(0, 0, 0, 0));
				for (size_t i = 0; i < vec.size(); i += 5) {
					Text t;
					Vector2f a = Vector2f((int)(vec[i + 0] - this->data[4][28] / 2) * 1.880, (int)(vec[i + 1] - this->data[4][28] / 3) * 1.880);
					string s = "";
					for (int j = 0; j < 3; j++) {
						char c = (char)(vec[i + j + 2]);
						s += c;
					}
					t.setString(s);
					t.setFont(verdana);
					t.setCharacterSize(this->data[4][28]);
					t.setFillColor(Color(0, 0, 0));
					t.setPosition(a);
					this->tex.draw(t);
				}
				this->tex.setSmooth(true);
				this->tex.display();
				this->text.setTexture(this->tex.getTexture());
			}
			if (lineCount == 6) {
				float a = (float)vec[0] * 2;
				float b = (float)vec[1] * 2;
				float c = (float)vec[2] * 2;
				float d = (float)vec[3] * 2;
				this->menu[0].position = Vector2f(a, b);
				this->menu[1].position = Vector2f(c, b);
				this->menu[2].position = Vector2f(c, d);
				this->menu[3].position = Vector2f(a, d);
				this->menu[0].color = Color(222, 222, 222);
				this->menu[1].color = Color(222, 222, 222);
				this->menu[2].color = Color(222, 222, 222);
				this->menu[3].color = Color(222, 222, 222);
				for (size_t i = 4; i < vec.size(); i += 4) {
					this->menu.resize(i + 4);
					float e = (float)vec[i + 0] * 2;
					float f = (float)vec[i + 1] * 2;
					float g = (float)vec[i + 2] * 2;
					float h = (float)vec[i + 3] * 2;
					this->menu[i + 0].position = Vector2f(e, f);
					this->menu[i + 1].position = Vector2f(g, f);
					this->menu[i + 2].position = Vector2f(g, h);
					this->menu[i + 3].position = Vector2f(e, h);
					this->menu[i + 0].color = Color(255, 255, 255);
					this->menu[i + 1].color = Color(255, 255, 255);
					this->menu[i + 2].color = Color(255, 255, 255);
					this->menu[i + 3].color = Color(255, 255, 255);
				}
			}
			if (lineCount > 6 && lineCount < 85) { //mapPos + selector
				for (size_t i = 0; i < vec.size(); i += 6) {
					int color = (lineCount * 255) / 78;//debug
					this->map.resize(this->data[4][0] + 3);
					this->selector.resize(this->data[4][0] + 3);
					float a = (float)vec[i + 0] * 1.880;
					float b = (float)vec[i + 1] * 1.880;
					float c = (float)vec[i + 2] * 1.880;
					float d = (float)vec[i + 3] * 1.880;
					float e = (float)vec[i + 4] * 1.880;
					float f = (float)vec[i + 5] * 1.880;
					this->map[this->data[4][0] + 0].position = Vector2f(a, b);
					this->map[this->data[4][0] + 1].position = Vector2f(c, d);
					this->map[this->data[4][0] + 2].position = Vector2f(e, f);
					if (!data[0][lineCount - 7]) {//<---------------------------------------------- dont forget if changing line decoding
						this->map[this->data[4][0] + 0].color = Color(223, 221, 199, 255);
						this->map[this->data[4][0] + 1].color = Color(223, 221, 199, 255);
						this->map[this->data[4][0] + 2].color = Color(223, 221, 199, 255);
					}
					else {
						this->map[this->data[4][0] + 0].color = Color(207, 208, 243, 255);
						this->map[this->data[4][0] + 1].color = Color(207, 208, 243, 255);
						this->map[this->data[4][0] + 2].color = Color(207, 208, 243, 255);

					}
					this->selector[this->data[4][0] + 0].position = Vector2f(a, b);
					this->selector[this->data[4][0] + 1].position = Vector2f(c, d);
					this->selector[this->data[4][0] + 2].position = Vector2f(e, f);
					this->selector[this->data[4][0] + 0].color = Color(0, 0, 0, 0);
					this->selector[this->data[4][0] + 1].color = Color(0, 0, 0, 0);
					this->selector[this->data[4][0] + 2].color = Color(0, 0, 0, 0);
					/* //debug
					int clr = (int)((color + 70) * color) % 255;
					this->border.resize(data[4][0] * 2 + 6);
					this->border[data[4][0] * 2 + 0].position = Vector2f(a, b);
					this->border[data[4][0] * 2 + 1].position = Vector2f(c, d);
					this->border[data[4][0] * 2 + 2].position = Vector2f(c, d);
					this->border[data[4][0] * 2 + 3].position = Vector2f(e, f);
					this->border[data[4][0] * 2 + 4].position = Vector2f(e, f);
					this->border[data[4][0] * 2 + 5].position = Vector2f(a, b);
					this->border[data[4][0] * 2 + 0].color = Color(clr, 1 - clr, 0, 255);
					this->border[data[4][0] * 2 + 1].color = Color(clr, 1 - clr, 0, 255);
					this->border[data[4][0] * 2 + 2].color = Color(clr, 1 - clr, 0, 255);
					this->border[data[4][0] * 2 + 3].color = Color(clr, 1 - clr, 0, 255);
					this->border[data[4][0] * 2 + 4].color = Color(clr, 1 - clr, 0, 255)y
					this->border[data[4][0] * 2 + 5].color = Color(clr, 1 - clr, 0, 255);
					*/
					this->data[4][0] += 3;
					this->data[2][lineCount - 7] = this->data[4][0];//<---------------------------------------------- dont forget if changing line decoding
				}
			}
			if (lineCount > 84 && lineCount < 163) { //borderPos
				for (size_t i = 0; i < vec.size(); i += 2) {
					this->border.resize(data[4][1] + 4);
					Vector2f a = Vector2f((float)vec[i + 0] * 1.880, (float)vec[i + 1] * 1.880);
					Vector2f b = Vector2f((float)vec[(i + 2) % vec.size()] * 1.880, (float)vec[(i + 3) % vec.size()] * 1.880);
					Vector2f e = a - b;
					e = Vector2f(-e.y, e.x);
					e = Vector2f(e.x * this->data[4][22] / (2 * sqrt(e.x * e.x + e.y * e.y)), e.y * this->data[4][22] / (2 * sqrt(e.x * e.x + e.y * e.y)));
					this->border[this->data[4][1] + 0].position = a + e;
					this->border[this->data[4][1] + 1].position = b + e;
					this->border[this->data[4][1] + 2].position = b - e;
					this->border[this->data[4][1] + 3].position = a - e;
					this->border[this->data[4][1] + 0].color = Color(255, 255, 255, 255);
					this->border[this->data[4][1] + 1].color = Color(255, 255, 255, 255);
					this->border[this->data[4][1] + 2].color = Color(255, 255, 255, 255);
					this->border[this->data[4][1] + 3].color = Color(255, 255, 255, 255);
					this->data[4][1] += 4;
				}
			}
			if (lineCount > 162 && lineCount < 241) { //armyMovement
				for (size_t i = 0; i < vec.size() - 1; i++) {
					this->tile[0][lineCount - 163][i] = vec[i];//<---------------------------------------------- dont forget if changing line decoding
				}
			}
			if (lineCount > 240 && lineCount < 319) { //fleetMovement
				for (size_t i = 0; i < vec.size() - 1; i++) {
					this->tile[1][lineCount - 241][i] = vec[i];//<---------------------------------------------- dont forget if changing line decoding
				}
			}
			lineCount++;
		}
	}
	file.close();
	if (VideoMode::getDesktopMode().height == 1080 && VideoMode::getDesktopMode().width == 1920) {
		this->window->setSize(Vector2u(1920, 1001));
		this->window->setPosition(Vector2i(-9, -9));
	}
	else if (VideoMode::getDesktopMode().height == 144 && VideoMode::getDesktopMode().width == 2560) {
		this->window->setSize(Vector2u(2560, 1377));
		this->window->setPosition(Vector2i(-8, -8));
	}
}

Game::Game()
{
	this->initVar();
	this->initWin();
	this->initGame();
	this->loadGame();
	this->updateUnits();
}

Game::~Game()
{ 
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	//cout << "pollevents" << endl;
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case Event::Closed:
			window->close();
			break;
		case Event::KeyPressed:
			keyboard(this->ev.key.code);
			break;
		case Event::MouseButtonPressed:
			if (this->ev.mouseButton.button == Mouse::Right) {
				//right click stuffz
			}
			if (this->ev.mouseButton.button == Mouse::Left) {
				this->updatePos();
			}
			break;
		}
	}
}

void Game::update()
{
	this->frames();
	this->pollEvents();
	this->cursorInRegion();
	this->unitSelector();
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
	this->data[4][11] = this->data[4][12] = this->data[4][13] = this->data[4][14] = this->data[4][15] = this->data[4][16] = this->data[4][17] = 0;
	for (int i = 0; i < 34; i++) {
		Color c1, c2;
		if (this->unit[i].country) {
			switch (this->unit[i].country) {
			case 1: c1 = Color(156, 155, 139); c2 = Color(47, 47, 42); break;
			case 2: c1 = Color(217, 155, 139); c2 = Color(208, 47, 42); break;
			case 3: c1 = Color(212, 155, 195); c2 = Color(195, 47, 189); break;
			case 4: c1 = Color(201, 200, 215); c2 = Color(167, 167, 243); break;
			case 5: c1 = Color(156, 206, 139); c2 = Color(45, 179, 40); break;
			case 6: c1 = Color(212, 211, 139); c2 = Color(195, 194, 42); break;
			case 7: c1 = Color(155, 153, 188); c2 = Color(45, 45, 175); break;
			}
			if (!this->data[0][unit[i].pos1 - 1]) {
				if (this->unit[i].pos1 == 1) {
					for (int j = 0; j < this->data[2][0]; j += 3) {
						this->map[j + 0].color = c1;
						this->map[j + 1].color = c1;
						this->map[j + 2].color = c1;
					}
				}
				else {
					for (int j = this->data[2][unit[i].pos1 - 2]; j < this->data[2][unit[i].pos1 - 1]; j += 3) {
						this->map[j + 0].color = c1;
						this->map[j + 1].color = c1;
						this->map[j + 2].color = c1;
					}
				}
			}
			for (int j = 0; j < 34; j++) {
				if (this->unit[i].pos1 == this->data[3][j]) {
					this->region[j * 8 + 4].color = c2;
					this->region[j * 8 + 5].color = c2;
					this->region[j * 8 + 6].color = c2;
					this->region[j * 8 + 7].color = c2;
					this->data[3][j + 34] = this->unit[i].country;
				}
			}
		}
	}
	for (int i = 0; i < 34; i++) {
		if (this->data[3][i + 34])
			this->data[4][this->data[3][i + 34] + 10] += 1;
	}
	int count = 0;
	Color c1;
	for (int i = 0; i < 8; i++) {
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
		float a = (float)(1145 + this->data[4][22] * 0.94) * count / 34;
		float b = (float)(1145 + this->data[4][22] * 0.94) * (count + data[4][i + 11]) / 34;
		if (i == 7)
			b = (float)(1145 + this->data[4][22] * 0.94);
		float c = (float)(1051);
		float d = (float)(1080);
		this->domBar[i * 4 + 0].position = Vector2f(a, c);
		this->domBar[i * 4 + 1].position = Vector2f(b, c);
		this->domBar[i * 4 + 2].position = Vector2f(b, d);
		this->domBar[i * 4 + 3].position = Vector2f(a, d);
		this->domBar[i * 4 + 0].color = c1;
		this->domBar[i * 4 + 1].color = c1;
		this->domBar[i * 4 + 2].color = c1;
		this->domBar[i * 4 + 3].color = c1;
		count += this->data[4][i + 11];
	}
}

void Game::updateSelector()
{
	//cout << "updateselector" << endl;
	if (this->data[4][29]) {
		if (this->data[4][7]) {
			if (this->data[4][7] == 1) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(0, 0, 0, 0);
					this->selector[i + 1].color = Color(0, 0, 0, 0);
					this->selector[i + 2].color = Color(0, 0, 0, 0);

				}
			}
			else for (int i = this->data[2][this->data[4][7] - 2]; i < this->data[2][this->data[4][7] - 1]; i += 3) {
				this->selector[i + 0].color = Color(0, 0, 0, 0);
				this->selector[i + 1].color = Color(0, 0, 0, 0);
				this->selector[i + 2].color = Color(0, 0, 0, 0);

			}
		}
	}
	if (this->data[4][30]) {
		if (this->data[4][9]) {// && this->data[4][9] != this->data[4][6]) {
			if (this->data[4][9] == 1) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(0, 0, 0, 0);
					this->selector[i + 1].color = Color(0, 0, 0, 0);
					this->selector[i + 2].color = Color(0, 0, 0, 0);
				}
			}
			else for (int i = this->data[2][this->data[4][9] - 2]; i < this->data[2][this->data[4][9] - 1]; i += 3) {
				this->selector[i + 0].color = Color(0, 0, 0, 0);
				this->selector[i + 1].color = Color(0, 0, 0, 0);
				this->selector[i + 2].color = Color(0, 0, 0, 0);

			}
		}
	}
	if (this->data[4][4] != this->data[4][5]) {
		if (this->data[4][5] && this->data[4][5] != this->data[4][6] && this->data[4][5] != this->data[4][8]) {
			if (this->data[4][5] == 1) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(0, 0, 0, 0);
					this->selector[i + 1].color = Color(0, 0, 0, 0);
					this->selector[i + 2].color = Color(0, 0, 0, 0);
				}
			}
			else for (int i = this->data[2][this->data[4][5] - 2]; i < this->data[2][this->data[4][5] - 1]; i += 3) {
				this->selector[i + 0].color = Color(0, 0, 0, 0);
				this->selector[i + 1].color = Color(0, 0, 0, 0);
				this->selector[i + 2].color = Color(0, 0, 0, 0);

			}
		}
	}
	if (this->data[4][29]) {
		if (this->data[4][6]) {
			if (this->data[4][6] == 1) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(255, 127, 0, 63);
					this->selector[i + 1].color = Color(255, 127, 0, 63);
					this->selector[i + 2].color = Color(255, 127, 0, 63);
				}
			}
			else for (int i = this->data[2][this->data[4][6] - 2]; i < this->data[2][this->data[4][6] - 1]; i += 3) {
				this->selector[i + 0].color = Color(255, 127, 0, 63);
				this->selector[i + 1].color = Color(255, 127, 0, 63);
				this->selector[i + 2].color = Color(255, 127, 0, 63);
			}
		}
		this->data[4][7] = this->data[4][6];
		this->data[4][29] = 0;
	}
	if (this->data[4][30]) {
		if (this->data[4][8]){
			if (this->data[4][8] == 1) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(0, 127, 0, 63);
					this->selector[i + 1].color = Color(0, 127, 0, 63);
					this->selector[i + 2].color = Color(0, 127, 0, 63);
				}
			}
			else for (int i = this->data[2][this->data[4][8] - 2]; i < this->data[2][this->data[4][8] - 1]; i += 3) {
				this->selector[i + 0].color = Color(0, 127, 0, 63);
				this->selector[i + 1].color = Color(0, 127, 0, 63);
				this->selector[i + 2].color = Color(0, 127, 0, 63);
			}
		}
		this->data[4][9] = this->data[4][8];
		this->data[4][30] = 0;
	}
	if (this->data[4][4] != this->data[4][5]) {
		if (this->data[4][4] && this->data[4][4] != this->data[4][6] && this->data[4][4] != this->data[4][8]) {
			if (!this->data[4][4]) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(127, 127, 127, 63);
					this->selector[i + 1].color = Color(127, 127, 127, 63);
					this->selector[i + 2].color = Color(127, 127, 127, 63);
				}
			}
			else for (int i = this->data[2][this->data[4][4] - 2]; i < this->data[2][this->data[4][4] - 1]; i += 3) {
				this->selector[i + 0].color = Color(127, 127, 127, 63);
				this->selector[i + 1].color = Color(127, 127, 127, 63);
				this->selector[i + 2].color = Color(127, 127, 127, 63);
			}
		}
		this->data[4][5] = this->data[4][4];
	}
}

void Game::updatePos()
{
	//cout << "updatepos" << endl;
	if (!this->data[4][4]) {
		this->data[4][6] = this->data[4][8] = 0;
		this->data[4][29] = this->data[4][30] = 1;
		this->data[4][10] = 0;
	}
	else if (!this->data[4][10]) {
		this->data[4][6] = this->data[4][4];
		this->data[4][8] = 0;
		this->data[4][29] = this->data[4][30] = 1;
		this->data[4][10] = 1;
		this->drawArrows(this->data[1][this->data[4][6] - 1] - 1, this->data[4][6]);
	}
	else if (this->data[4][10] == 1) {
		this->data[4][8] = this->data[4][4];
		this->data[4][30] = 1;
		this->data[4][10] = 0;
	}
}

void Game::updateUnits()
{
	for (int i = 0; i < 34; i++) {
		if (!this->unit[i].pos1) {
			this->units[i * 8 + 0].position = Vector2f(0, 0);
			this->units[i * 8 + 1].position = Vector2f(0, 0);
			this->units[i * 8 + 2].position = Vector2f(0, 0);
			this->units[i * 8 + 3].position = Vector2f(0, 0);
			this->units[i * 8 + 4].position = Vector2f(0, 0);
			this->units[i * 8 + 5].position = Vector2f(0, 0);
			this->units[i * 8 + 6].position = Vector2f(0, 0);
			this->units[i * 8 + 7].position = Vector2f(0, 0);
		}
		else {
			Color c1, c2;
			float a = (float)this->unitPos[unit[i].pos1 - 1].x * 1.880;
			float b = (float)this->unitPos[unit[i].pos1 - 1].y * 1.880;
			float l = (float)this->data[4][20];
			float s = (float)this->data[4][21];
			if (this->unit[i].type) {
				this->units[i * 8 + 0].position = Vector2f(a, b);
				this->units[i * 8 + 1].position = Vector2f(a + l * 2 / 3, b);
				this->units[i * 8 + 2].position = Vector2f(a + l * 2 / 3, b + l * 2 / 3);
				this->units[i * 8 + 3].position = Vector2f(a, b + l * 2 / 3);
				this->units[i * 8 + 4].position = Vector2f(a + s, b + s);
				this->units[i * 8 + 5].position = Vector2f(a + l * 2 / 3 - s, b + s);
				this->units[i * 8 + 6].position = Vector2f(a + l * 2 / 3 - s, b + l * 2 / 3 - s);
				this->units[i * 8 + 7].position = Vector2f(a + s, b + l * 2 / 3 - s);
			}
			else {
				this->units[i * 8 + 0].position = Vector2f(a - l / 6, b);
				this->units[i * 8 + 1].position = Vector2f(a + l * 5 / 6, b);
				this->units[i * 8 + 2].position = Vector2f(a + l / 3, b + l * 2 / 3);
				this->units[i * 8 + 3].position = Vector2f(a + l / 3, b + l * 2 / 3);
				this->units[i * 8 + 4].position = Vector2f(a + s * 20 / 9 - l / 6, b + s);
				this->units[i * 8 + 5].position = Vector2f(a + l * 5 / 6 - s * 20 / 9, b + s);
				this->units[i * 8 + 6].position = Vector2f(a + l / 3, b + l * 2 / 3 - s * 5 / 3);
				this->units[i * 8 + 7].position = Vector2f(a + l / 3, b + l * 2 / 3 - s * 5 / 3);
			}
			switch (this->unit[i].country) {
			case 1: c1 = Color(47, 47, 42); c2 = Color(0, 0, 0); break;
			case 2:	c1 = Color(208, 47, 42); c2 = Color(204, 0, 0); break;
			case 3:	c1 = Color(195, 47, 189); c2 = Color(187, 0, 187); break;
			case 4:	c1 = Color(167, 167, 243); c2 = Color(153, 153, 255);  break;
			case 5:	c1 = Color(45, 179, 40); c2 = Color(0, 170, 0); break;
			case 6:	c1 = Color(195, 194, 42); c2 = Color(187, 187, 0); break;
			case 7:	c1 = Color(45, 45, 175); c2 = Color(0, 0, 170); break;
			}
			this->units[i * 8 + 0].color = c2;
			this->units[i * 8 + 1].color = c2;
			this->units[i * 8 + 2].color = c2;
			this->units[i * 8 + 3].color = c2;
			this->units[i * 8 + 4].color = c1;
			this->units[i * 8 + 5].color = c1;
			this->units[i * 8 + 6].color = c1;
			this->units[i * 8 + 7].color = c1;
		}
	}
}

/*void Game::moveUnit()
{
	if (this->data[4][6] != 0 && this->data[4][8] != 0) {
		for (int i = 0; i < 34; i++) {
			if (unit[i].pos1 == this->data[4][6]) {
				unit[i].pos2 = this->data[4][8];
			} // check if movement possible
		}
	}
} idk why this is here */

void Game::unitSelector()
{
	//cout << "unitselector" << endl;
	if (this->data[4][29]) {
		this->data[4][26] = 0;
		//this->data[4][26] = this->unit[this->data[1][this->data[4][6] - 2]].pos1 + 1;   idk what this did but ill leave it here; -2 presumably bc -1 init and -1 after hash readj
		for (int i = 0; i < 34; i++) {
			if (this->unit[i].pos1 == this->data[4][6]) {
				this->data[4][26] = i + 1;
				continue;
			}
		}
	}
	if (!this->data[4][6])
		this->data[4][26] = 0;
	if (this->data[4][4] != this->data[4][5]) {
		this->drawArrows(this->data[4][26] - 1, this->data[4][4]);
	}
	if (this->data[4][6] && this->data[4][29]) {
		for (int i = 0; i < 34; i++) {
			if (this->unit[i].pos1 == this->unit[i].pos2 && this->unit[i].move == 1)
				this->unit[i].move = 0;
			if (this->data[4][26] && this->unit[i].move == 1 && i != this->data[4][26] - 1 && unit[i].pos2 == unit[this->data[4][26] - 1].pos1) {
				this->unit[i].pos2 = this->unit[i].pos1;
				this->unit[i].move = 0;
			}
		}
		this->unit[this->data[1][this->data[4][6] - 1] - 1].pos2 = this->unit[this->data[1][this->data[4][6] - 1] - 1].pos1;
		if (this->unit[this->data[1][this->data[4][6] - 1] - 1].move == 2) {
			this->unit[this->data[1][this->data[4][6] - 1] - 1].move = 0;
			for (int i = 0; i < 34; i++) {
				if (this->unit[i].move == 2) {
					if (this->unit[i].pos2 != this->unit[i].pos1) {
						this->unit[i].pos2 = this->unit[i].pos1;
						this->unit[i].move = 0;
					}
				}
				else if (
					!moveTile(this->unit[i], this->unit[i].pos2)) {
					this->unit[i].pos2 = this->unit[i].pos1;
					this->unit[i].move = 0;
				}
			}
		}
		this->unit[this->data[1][this->data[4][6] - 1] - 1].move = 0;
		this->drawArrows(this->data[4][26] - 1, this->data[4][4]);
	}
	if (this->data[4][30] && this->data[4][8] && this->data[4][26]) {
		if (this->unit[this->data[4][26] - 1].country && moveTile(this->unit[this->data[4][26] - 1], this->data[4][4]) == 1)
			this->unit[this->data[4][26] - 1].pos2 = this->data[4][8];
		this->data[4][26] = 0;
	}
}
void Game::render()
{
	//cout << "render" << endl;
	if(this->data[5][4])
	this->window->clear(Color(255, 0, 255, 255));
	else
	this->window->clear(Color(255, 255, 255, 255));
	this->updateSelector();
	this->window->draw(this->map);
	this->window->draw(this->selector);
	this->window->draw(this->border);
	this->window->draw(this->region);
	this->window->draw(this->units);
	this->window->draw(this->domBar);
	this->window->draw(this->arrows);
	this->window->draw(this->text);
	this->window->draw(this->menu);
	if (this->data[5][2])
		this->window->draw(this->fps);
	this->window->display();
}

void Game::cursorInRegion()
{
	//cout << "cursorinregion" << endl;
	int v = -1;
	Vector2f m = (Vector2f)Vector2i(Mouse::getPosition(*this->window).x * 1920  / this->window->getSize().x, Mouse::getPosition(*this->window).y * 1080 / this->window->getSize().y);
	//cout << this->window->getSize().x << " " << this->window->getSize().y << " " << this->window->getPosition().x << " " << this->window->getPosition().y << endl;
	if (m.x > 1147 || m.y > 1053 || m.x < 0 || m.y < 0) {
		this->data[4][4] = 0;
		return;
	}
	if (m.x >= 0 && m.y >= 0)
		for (size_t i = 0; i < this->map.getVertexCount(); i += 3) {
			if (isInsideTriangle(map[i].position, map[i + 1].position, map[i + 2].position, m)) {
				v = i;
				continue;
			}
		}
	if (v == -1) {
		data[4][4] = 0;
		return;
	}
	if (this->data[2][0] > v) {
		this->data[4][4] = 1;
		return;
	}
	for (int i = 0; i < 78; i++) {
		if (this->data[2][i] > v && this->data[2][i - 1] <= v) {
			this->data[4][4] = i + 1;
			return;
		}
	}
}

void Game::loadGame()
{
	int lineCount = 0;
	int unitCount = 0;
	for (int i = 0; i < 34; i++) {
		unit[i].country = unit[i].pos1 = unit[i].pos2 = 0;
	}
	string line;
	ifstream save(".save.txt");
	if(save.fail())
		this->error(1, ".save.txt");
	if (save.is_open()) {
		while (getline(save, line)) {
			vector<int> vec;
			stringstream ss(line);
			for (int i; ss >> i;) {
				vec.push_back(i);
				if (ss.peek() == ' ')
					ss.ignore();
			}
			if (lineCount == 0) {
				for (size_t i = 0; i < vec.size(); i++) {
					if (vec[i]) {
						unit[unitCount].pos1 = i + 1;
						unit[unitCount].pos2 = i + 1;
						unit[unitCount].type = vec[i] % 2;
						unit[unitCount].country = (vec[i] + vec[i] % 2) / 2;
						unitCount++;
					}
				}
			}
			if (lineCount == 1) {
				for (size_t i = 0; i < vec.size(); i++) {
					switch (i) {
					case 0: this->data[4][27] = vec[i]; break;
					}
				}
			}
			lineCount++;
		}
	}
	save.close();
	this->hashUnits();
	this->updateColors();
	this->drawArrows(0, 0);
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
	/*
	//need year to adjudicate
	//need logic :/
	if (this->data[4][27] % 3 != 2) {
		for (int i = 0; i < 34; i++) { //unitAdjudicate
			for (int j = 0; j < 34; j++) { //reset array
				this->data[1][j] = 0;
			}
			for (int j = 0; j < 34; j++) { //set array
				if (this->unit[j].country != 0) {
					this->data[1][unit[j].pos1 - 1] = j + 1;
				}
			}
			for (int j = 0; j < 34; j++) { //check if same destination
				for (int k = 0; k < j; k++) {
					if (this->unit[j].pos2 == this->unit[k].pos2) {
						this->unit[j].move = this->unit[k].move = 1;
					}
				}
			}
			for (int j = 0; j < 34; j++) { //move if possible
				if (this->unit[j].move == 1) { //stay when flagged
					this->unit[j].pos2 = this->unit[j].move = 0;
				}
				else if (this->data[1][this->unit[j].pos2 - 1] != 0) { //when occupied
					if (this->unit[this->data[1][this->unit[j].pos2 - 1] - 1].pos2 == 0) { //stay when occupied
						this->unit[j].pos2 = 0;
					}
				}
				else { //move when free
					this->data[1][this->unit[j].pos1 - 1] = 0;
					this->unit[j].pos1 = this->unit[j].pos2;
					this->unit[j].pos2 = this->unit[j].move = 0;
				}
			}
		}
	}
	if (this->data[4][27] % 3 == 2) {
		//update based on region count
	}bunch of stuff idk what is how works
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			1 == 1;
		}
	}
	if (this->data[4][27] % 3 == 1) {
		updateColors();
	}
	*/

	//switch year (0 ord 1 | 1 adj 1 | 2 r&d 1 | 3 ord 2 | 4 adj 2 | 5 r&d 2 | 6 units)
	//(0 orders 1 | 1 resolution 1 | 2 retreat / disband 1 | 3 orders 2 | 4 resulution 2 | 5 retreat / disband 2 | 6 create / disband)
	//backend uhhh
	switch (this->data[4][27] % 7) {
	case 0: case 3:

		this->data[4][27]++;
		break;
	case 1: case 4:

		this->data[4][27]++;
		break;
	case 2: case 5:

		//2: no area 5: capture area
		this->data[4][27]++;
		break;
	case 6:

		this->data[4][27]++;
		break;
	}
	updateUnits();
	hashUnits();
	drawArrows(0, 0);
}

bool Game::moveTile(Unit uni, int pos2)
{
	//cout << "movetile " << uni.pos1 << " " << pos2 << endl;
	if (!pos2)
		return 0;
	bool t = 0;
	/*
	
	duh gotta actually name vars
	
	*/
	queue <int> queue;
	bool checked[78] = { false };
	switch (uni.move) {
	case 0:
		//if (this->unit[this->data[1][pos2] - 1].pos2 == uni.pos1 && this->data[1][pos2] != 0)
			//return 0;
		/*for (int i = 0; i < 34; i++) {
			if (unit[i].pos2 == pos2 && unit[i].pos1 != uni.pos1 && unit[i].pos1 != unit[i].pos2 && unit[i].move == 0)
				return 0;
		}*/
		if (uni.pos1 == pos2)
			return 1;
		for (int i = 0; i < 11; i++) {
			if (tile[(uni.type + 1) % 2][uni.pos1 - 1][i] == pos2)
				return 1;
		}
		if (!uni.type)
			return 0;
		for (int i = 0; i < 11; i++) {
			int target = this->tile[1][uni.pos1 - 1][i] - 1;
			if (target == -1)
				continue;
			if (this->data[1][target] > 0 && this->unit[this->data[1][target] - 1].move == 2) {
				checked[target] = 1;
				queue.push(target);
			}
		}
		while (!queue.empty()) {
			int popped = queue.front();
			queue.pop();
			for (int i = 0; i < 11; i++) {
				int target = this->tile[1][popped][i] - 1;
				if (target == -1)
					continue;
				if (pos2 == target + 1 && !this->data[0][pos2 - 1])
					return 1;
				if (this->data[1][target] > 0 && this->unit[this->data[1][target] - 1].move == 2 && !checked[target]) {
					checked[target] = 1;
					queue.push(target);
				}
			}
		}
		//dont know what i did lets redo it
		/*for (int i = 0; i < 11; i++) {
			int t = this->tile[(uni.type + 1) % 2][uni.pos1 - 1][i] - 1;
			if (t == -1)
				continue;
			t = this->data[1][t];
			if (this->unit[t].move == 2 && qu[t] == false) {
				q.push(t);
				qu[t] = true;
				cout << t << endl;
			}
		}*/
		//here once was a 45 line long fuuu bc of convoys
		/*idk whats going on here its gotta be rewritten
		while (!q.empty()) {
			int qq = q.front();
			q.pop();
			int 
			qu[this->unit[this->data[1][qq]].pos1] = true;
			for (int i = 0; i < 11; i++) {
				int t = this->tile[(this->unit[qq].type + 1) % 2][this->unit[qq].pos1 - 1][i] - 1;
				if (t == -1)
					continue;
				if (t == pos2 && this->data[0][t] == 0)
					return 1;
				if (this->unit[t].move == 2 && qu[t] == false) {
					qu[t] = true;
					q.push(t);
					cout << t << endl;
				}
			}
		}*/
		break;
	case 1:
		t = 0;
		if (!this->data[1][pos2 - 1] ||
			this->unit[this->data[1][pos2 - 1] - 1].pos1 == this->unit[this->data[1][pos2 - 1] - 1].pos2 ||
			this->unit[this->data[1][pos2 - 1] - 1].move ||
			this->unit[this->data[1][pos2 - 1] - 1].pos2 == uni.pos1 ||
			this->unit[this->data[1][pos2 - 1] - 1].pos1 == this->unit[this->data[1][pos2 - 1] - 1].pos2)
			return 0;
		for (int i = 0; i < 11; i++) {
			if (tile[(uni.type + 1) % 2][uni.pos1 - 1][i] == pos2)
				t = 1;
		}
		if (t)
			for (int i = 0; i < 11; i++) {
				if (tile[(uni.type + 1) % 2][uni.pos1 - 1][i] == this->unit[this->data[1][pos2 - 1] - 1].pos2)
					return 1;
			}
		break;
	}
	return 0;
}

void Game::frames()
{
	//cout << "frames" << endl;
	int tim = this->timer.restart().asMilliseconds();
	if (tim < this->data[5][0] && this->data[5][1])
		sleep(milliseconds(this->data[5][0] - tim));
	if (this->data[5][2]) {
		this->fp.clear(Color(0, 0, 0, 0));
		int i = 1000 / (tim - 0.000000000001);
		string s = to_string(i);
		this->fpt.setString(s);
		this->fp.draw(this->fpt);
		this->fp.display();
		this->fps.setTexture(this->fp.getTexture());
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
		this->unit[this->data[4][26] - 1].move = 1;
		break;
	case Keyboard::B:
		if (this->data[0][this->unit[this->data[4][26] - 1].pos1]) {
			this->unit[this->data[4][26] - 1].move = 2;
			this->data[4][10] = 0;
		}
		break;
	case Keyboard::N:
		this->unit[this->data[4][26] - 1].move = 0;
		break;
	}
	drawArrows(this->data[4][26] - 1, this->data[4][4]);
}

void Game::drawArrows(int selUnit, int pos2)
{
	//cout << selUnit << " " << pos2 << endl;
	//cout << "drawarrows " << selUnit << " " << pos2 << endl;
	//gotta make it depending on year
	if (selUnit > 34)
		return;
	this->arrows.clear();
	this->arrows.resize(16 * 34);
	Color col;
	int tem = this->unit[selUnit].pos2;
	if (selUnit >= 0 && moveTile(this->unit[selUnit], pos2))
		this->unit[selUnit].pos2 = pos2;
	for (int i = 0; i < 34; i++) {
		Vector2f a, b, c, bb, cc;
		if (!this->unit[i].pos1)
			continue;
		if (!this->unit[i].pos2)
			this->unit[i].pos2 = this->unit[i].pos1;
		if (this->unit[i].pos1 != this->unit[i].pos2) {
			a = Vector2f(unitPos[unit[i].pos1 - 1].x * 1.880 + this->data[4][20] / 3, unitPos[unit[i].pos1 - 1].y * 1.880 + this->data[4][20] / 3);
			switch (this->unit[i].move) {
			case 0:
				b = Vector2f(unitPos[unit[i].pos2 - 1].x * 1.880 + this->data[4][20] / 3, unitPos[unit[i].pos2 - 1].y * 1.880 + this->data[4][20] / 3);
				col = Color(0, 0, 0, 255);
				break;
			case 1:
				b = Vector2f((unitPos[unit[i].pos2 - 1].x + unitPos[unit[this->data[1][unit[i].pos2 - 1] - 1].pos2 - 1].x) / 2 * 1.880 + this->data[4][20] / 3, (unitPos[unit[i].pos2 - 1].y + unitPos[unit[this->data[1][unit[i].pos2 - 1] - 1].pos2 - 1].y) / 2 * 1.880 + this->data[4][20] / 3);
				col = Color(0, 127, 0, 255);
				break;
			case 2:
				this->unit[i].pos2 == this->unit[i].pos1;
				break;
			}
			Vector2f e = a - b;
			e = Vector2f(-e.y, e.x);
			e = Vector2f(e.x * this->data[4][23] / (2 * sqrt(e.x * e.x + e.y * e.y)), e.y * this->data[4][23] / (2 * sqrt(e.x * e.x + e.y * e.y)));
			Vector2f c = a - b;
			c = Vector2f(c.x * this->data[4][24] / (sqrt(c.x * c.x + c.y * c.y)), c.y * this->data[4][24] / (sqrt(c.x * c.x + c.y * c.y)));
			this->arrows[i * 16 + 0].position = a + e;
			this->arrows[i * 16 + 1].position = b + e + c;
			this->arrows[i * 16 + 2].position = b - e + c;
			this->arrows[i * 16 + 3].position = a - e;
			this->arrows[i * 16 + 4].position = b;
			this->arrows[i * 16 + 5].position = b;
			this->arrows[i * 16 + 6].position = b + c + Vector2f(c.y * this->data[4][25] / this->data[4][24], -c.x * this->data[4][25] / this->data[4][24]);;
			this->arrows[i * 16 + 7].position = b + c - Vector2f(c.y * this->data[4][25] / this->data[4][24], -c.x * this->data[4][25] / this->data[4][24]);;
			for (int j = 0; j < 8; j++) {
				this->arrows[i * 16 + j].color = col;
			}
		}
		//#00c5ff
		else {
			a = Vector2f(unitPos[unit[i].pos1 - 1].x * 1.880 + this->data[4][20] / 3, unitPos[unit[i].pos1 - 1].y * 1.880 + this->data[4][20] / 3);
			b = Vector2f(this->data[4][20] * 0.6, this->data[4][20] * 0.6);
			Vector2f bb = Vector2f(b.x, -b.y);
			Vector2f c = Vector2f(this->data[4][23], this->data[4][23]);
			Vector2f cc = Vector2f(c.x, -c.y);
			this->arrows[i * 16 + 0].position = a - b;
			this->arrows[i * 16 + 1].position = a - b + c;
			this->arrows[i * 16 + 2].position = a - bb + cc;
			this->arrows[i * 16 + 3].position = a - bb;
			this->arrows[i * 16 + 4].position = a + bb;
			this->arrows[i * 16 + 5].position = a + bb - cc;
			this->arrows[i * 16 + 6].position = a - b + c;
			this->arrows[i * 16 + 7].position = a - b;
			this->arrows[i * 16 + 8].position = a + b;
			this->arrows[i * 16 + 9].position = a + b - c;
			this->arrows[i * 16 + 10].position = a + bb - cc;
			this->arrows[i * 16 + 11].position = a + bb;
			this->arrows[i * 16 + 12].position = a - bb;
			this->arrows[i * 16 + 13].position = a - bb + cc;
			this->arrows[i * 16 + 14].position = a + b - c;
			this->arrows[i * 16 + 15].position = a + b;
			Color co;
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
				co = Color(255, 0, 255, 255);
				break;
			}
			if (!this->data[5][3])
				co = Color(0, 0, 0, 0);
			for (int j = 0; j < 16; j++)
				this->arrows[i * 16 + j].color = co;
		}
	}
	this->unit[selUnit].pos2 = tem;
	return;
}

void Game::hashUnits()
{
	for (int i = 0; i < 78; i++)
		this->data[1][i] = 0;
	for (int i = 0; i < 34; i++)
		if (unit[i].pos1)
			this->data[1][unit[i].pos1 - 1] = i + 1;
}

void Game::error(int t, string r)
{
	string s = "";
	switch (t){
	case 1:
		s = "The " + r + " file was not found. Please add it.";
		break;
	case 2:
		s = "The " + r + " file is invalid. Please replace it.";
		break;
	case 3:
		s = "Runtime Error, please report as bug if it persists.";
		break;
	default:
		s = "Unknown Error";
		break;
	}
	time_t now = time(0);
	tm *l = localtime(&now);
	ofstream file(".error.txt");
	file << "This is the error-report from " << l->tm_mday << "." << l->tm_mon + 1 << "." << l->tm_year + 1900 << ", " << l->tm_hour << ":" << l->tm_min << ":" << l->tm_sec << ":" << endl << "If the error(s) cannot be fixed by replacing the file you should update and replace the whole game-folder." << endl << s << endl;
	file.close();
	this->window->close();
}

int Game::getChecksum(ifstream file)
{
	return 0;
}

bool Game::checkResolved(int country)
{
	return false;
}

bool Game::checkDisbanded(int country)
{
	return false;
}

void Unit::initUnit()
{

}

Unit::Unit()
{
	this->initUnit();
}

Unit::~Unit()
{
	
}
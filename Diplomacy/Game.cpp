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
	this->window = new RenderWindow(this->videoMode, "Diplomacy", Style::Titlebar | Style::Close);
}

void Game::initGame()
{
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
	this->arrow.clear();
	this->arrow.setPrimitiveType(Quads);
	this->arrow.resize(8);
	this->menu.clear();
	this->menu.setPrimitiveType(Quads);
	this->menu.resize(8);
	if (!this->verdana.loadFromFile("VERDANA.TTF")) {
		cout << "No verdana\n";
		return;
	}
	string line;
	ifstream file(".data.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			vector<int> vec;
			stringstream ss(line);
			for (int i; ss >> i;) {
				vec.push_back(i);
				if (ss.peek() == ' ')
					ss.ignore();
			}
			if (lineCount == 0) { //dataExt //separate file?
				for (size_t i = 0; i < vec.size(); i++) {
					this->data[5][i] = vec[i];
				}
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
			if (lineCount == 5) {
				if (!this->tex.create(609 * 1.880, 575 * 1.880)) {
					return;
				}
				this->tex.clear(Color(0, 0, 0, 0));
				for (size_t i = 0; i < vec.size(); i += 5) {
					Text t;
					Vector2f a = Vector2f((float)(vec[i + 0] - this->data[4][28] / 2) * 1.880, (float)(vec[i + 1] - this->data[4][28] / 3) * 1.880);
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
					this->map.resize(data[4][0] + 3);
					this->selector.resize(data[4][0] + 3);
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
					this->border[data[4][0] * 2 + 4].color = Color(clr, 1 - clr, 0, 255);
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
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case Event::Closed:
			window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				window->close();
			if (this->ev.key.code == Keyboard::A)
				adjudicate();
			break;
		case Event::MouseButtonPressed:
			if (this->ev.mouseButton.button == Mouse::Right) {
				//right klick stuff
			}
			if (this->ev.mouseButton.button == Mouse::Left) {
				this->updatePos();
			}
		}
	}
}

void Game::update() 
{
	this->pollEvents();
	this->unitSelector();
	this->cursorInRegion();
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
		if (this->unit[i].country != 0) {
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
		if (this->data[3][i + 34] != 0)
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
		if(i == 7)
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
	if (this->data[4][6] != this->data[4][7]) {
		if (this->data[4][7] != 0) {
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
		if (this->data[4][6] != 0) {
			if (this->data[4][6] == 1) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(0, 255, 0, 255);
					this->selector[i + 1].color = Color(0, 255, 0, 255);
					this->selector[i + 2].color = Color(0, 255, 0, 255);
				}
			}
			else for (int i = this->data[2][this->data[4][6] - 2]; i < this->data[2][this->data[4][6] - 1]; i += 3) {
				this->selector[i + 0].color = Color(0, 255, 0, 255);
				this->selector[i + 1].color = Color(0, 255, 0, 255);
				this->selector[i + 2].color = Color(0, 255, 0, 255);
			}
		}
		this->data[4][7] = this->data[4][6];
	}
	if (this->data[4][8] != this->data[4][9]) {
		if (this->data[4][9] != 0 && this->data[4][9] != this->data[4][6]) {
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
		if (this->data[4][8] != 0 && this->data[4][22] != this->data[4][6]) {
			if (this->data[4][8] == 1) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(0, 0, 255, 255);
					this->selector[i + 1].color = Color(0, 0, 255, 255);
					this->selector[i + 2].color = Color(0, 0, 255, 255);
				}
			}
			else for (int i = this->data[2][this->data[4][8] - 2]; i < this->data[2][this->data[4][8] - 1]; i += 3) {
				this->selector[i + 0].color = Color(0, 0, 255, 255);
				this->selector[i + 1].color = Color(0, 0, 255, 255);
				this->selector[i + 2].color = Color(0, 0, 255, 255);
			}
		}
		this->data[4][9] = this->data[4][8];
	}
	if (this->data[4][4] != this->data[4][5]) {
		if (this->data[4][5] != 0 && this->data[4][5] != this->data[4][6] && this->data[4][5] != this->data[4][8]) {
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
		if (this->data[4][4] != 0 && this->data[4][4] != this->data[4][6] && this->data[4][4] != this->data[4][8]) {
			if (this->data[4][4] == 0) {
				for (int i = 0; i < this->data[2][0]; i += 3) {
					this->selector[i + 0].color = Color(255, 0, 0, 255);
					this->selector[i + 1].color = Color(255, 0, 0, 255);
					this->selector[i + 2].color = Color(255, 0, 0, 255);
				}
			}
			else for (int i = this->data[2][this->data[4][4] - 2]; i < this->data[2][this->data[4][4] - 1]; i += 3) {
				this->selector[i + 0].color = Color(255, 0, 0, 255);
				this->selector[i + 1].color = Color(255, 0, 0, 255);
				this->selector[i + 2].color = Color(255, 0, 0, 255);
			}
		}
		this->data[4][5] = this->data[4][4];
	}
}

void Game::updatePos()
{
	if (this->data[4][4] == 0) {
		this->data[4][6] = this->data[4][8] = 0;
		this->data[4][10] = 0;
	}
	else if (this->data[4][10] == 0) {
		this->data[4][6] = this->data[4][4];
		this->data[4][8] = 0;
		this->data[4][10] = 1;
	}
	else if (this->data[4][10] == 1) {
		this->data[4][8] = this->data[4][4];
		this->data[4][10] = 0;
	}
}

void Game::updateUnits()
{
	for (int i = 0; i < 34; i++) {
		if (this->unit[i].pos1 == 0) {
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
				this->units[i * 8 + 7].position = Vector2f(a + l / 3, b + l * 2 / 3 - s * 5 / 3 );
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

void Game::moveUnit()
{
	if (this->data[4][6] != 0 && this->data[4][8] != 0) {
		for (int i = 0; i < 34; i++) {
			if (unit[i].pos1 == this->data[4][6]) {
				unit[i].pos2 = this->data[4][8];
			} // check if movement possible
		}
	}
}

void Game::unitSelector()
{
	if (this->data[4][6] != this->data[4][7]) {
		this->data[4][26] = 0;
		for (int i = 0; i < 34; i++) {
			if (this->unit[i].pos1 == this->data[4][6]) {
				this->data[4][26] = i + 1;
				continue;
			}
		}
	}
	if (this->data[4][6] == 0) {
		this->data[4][26] = 0;
	}
	if (this->data[4][26] != 0) {// && this->data[4][4] != this->data[4][5]) {
		if (moveTile(this->unit[this->data[4][26] - 1].type, this->unit[this->data[4][26] - 1].pos1, this->data[4][4]) == 1 && this->data[4][4] != this->unit[this->data[4][26] - 1].pos1) {
			this->arrow.clear();
			this->arrow.resize(8);
			Vector2f a = Vector2f(unitPos[unit[this->data[4][26] - 1].pos1 - 1].x * 1.880 + this->data[4][20] / 3, unitPos[unit[this->data[4][26] - 1].pos1 - 1].y * 1.880 + this->data[4][20] / 3);
			Vector2f b = Vector2f(unitPos[this->data[4][4] - 1].x * 1.880 + this->data[4][20] / 3, unitPos[this->data[4][4] - 1].y * 1.880 + this->data[4][20] / 3);
			Vector2f e = a - b;
			e = Vector2f(-e.y, e.x);
			e = Vector2f(e.x * this->data[4][23] / (2 * sqrt(e.x * e.x + e.y * e.y)), e.y * this->data[4][23] / (2 * sqrt(e.x * e.x + e.y * e.y)));
			Vector2f c = a - b;
			c = Vector2f(c.x * this->data[4][24] / (sqrt(c.x * c.x + c.y * c.y)), c.y * this->data[4][24] / (sqrt(c.x * c.x + c.y * c.y)));
			this->arrow[0].position = a + e;
			this->arrow[1].position = b + e + c;
			this->arrow[2].position = b - e + c;
			this->arrow[3].position = a - e;
			this->arrow[4].position = b;
			this->arrow[5].position = b + c + Vector2f(c.y * this->data[4][25] / this->data[4][24], -c.x * this->data[4][25] / this->data[4][24]);
			this->arrow[6].position = b + c - Vector2f(c.y * this->data[4][25] / this->data[4][24], -c.x * this->data[4][25] / this->data[4][24]);
			this->arrow[7].position = this->arrow[6].position;
			this->arrow[0].color = Color(0, 0, 0);
			this->arrow[1].color = Color(0, 0, 0);
			this->arrow[2].color = Color(0, 0, 0);
			this->arrow[3].color = Color(0, 0, 0);
			this->arrow[4].color = Color(0, 0, 0);
			this->arrow[5].color = Color(0, 0, 0);
			this->arrow[6].color = Color(0, 0, 0);
			this->arrow[7].color = Color(0, 0, 0);
		}
		else {
			this->arrow.clear();
		}
	}
	else { 
		this->arrow.clear(); 
	}
	if (this->data[4][8] != this->data[4][9] && this->data[4][8] != 0 && this->data[4][26] != 0) {
		if (this->unit[this->data[4][26] - 1].country != 0 && moveTile(this->unit[this->data[4][26] - 1].type, this->unit[this->data[4][26] - 1].pos1, this->data[4][4]) == 1) {
			this->unit[this->data[4][26] - 1].pos2 = this->data[4][8];
			this->data[4][26] = 0;
		}
	}
}

void Game::render()
{
	this->window->clear(Color(255, 0, 255, 255));
	this->updateSelector();
	this->window->draw(this->map);
	this->window->draw(this->selector);
	this->window->draw(this->border);
	this->window->draw(this->region);
	this->window->draw(this->units);
	this->window->draw(this->domBar);
	this->window->draw(this->arrow);
	this->window->draw(this->text);
	this->window->draw(this->menu);
	this->window->display();
}

void Game::cursorInRegion()
{
	int v = -1;
	Vector2f m =(Vector2f) Vector2i(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y);
	if (m.x > 1147 && m.y > 1053) {
		this->data[4][4] = 0;
		return;
	}
	if(m.x >= 0 && m.y >= 0 )
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
					if (vec[i] != 0) {
						unit[unitCount].pos1 = i + 1;
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
	else {
		this->window->close();
	}
	save.close();
	this->updateColors();
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
	}
	updateUnits();
	if (this->data[4][27] % 3 == 1) {
		updateColors();
	}
	this->data[4][27]++;
}

bool Game::moveTile(int type, int pos1, int pos2)
{
	if (pos1 == pos2)
		return 1;
	for (int i = 0; i < 11; i++) {
		if (this->tile[(type + 1) % 2][pos1 - 1][i] == pos2 && pos2 != 0)
			return 1;
	}
	return 0;
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

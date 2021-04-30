#include "Game.h"
int main()
{
    Game game;
    while (game.running())
    {
        game.update();
        game.render();
    }
    return 0;
}
/*old coloring
    int c = 0;
    Color cc;
    this->data[4][11] = this->data[4][12] = this->data[4][13] = this->data[4][14] = this->data[4][15] = this->data[4][16] = this->data[4][17] = 0;
    for (size_t i = 0; i < this->map.getVertexCount(); i += 3) {
        while ((int)i >= this->data[2][c]) {
            c++;
        }
        if (this->data[0][c] != this->data[1][c]) {
            switch (this->data[0][c]) {//mapColor
            case 0: cc = Color(223, 221, 199, 255); break;
            case 1: cc = Color(156, 155, 139, 255); break;
            case 2: cc = Color(217, 155, 139, 255); break;
            case 3: cc = Color(212, 155, 195, 255); break;
            case 4: cc = Color(201, 200, 215, 255); break;
            case 5: cc = Color(156, 206, 139, 255); break;
            case 6: cc = Color(212, 211, 139, 255); break;
            case 7: cc = Color(155, 153, 188, 255); break;
            case 8: cc = Color(207, 208, 243, 255); break;
            }
            this->map[i + 0].color = cc;
            this->map[i + 1].color = cc;
            this->map[i + 2].color = cc;
        }
    }
    for (int i = 0; i < this->data[4][2]; i++) {//dotsColor
        if (this->data[0][this->data[3][i]] != this->data[1][this->data[3][i]]) {
            switch (this->data[0][this->data[3][i]]) {
            case 0: cc = Color(255, 255, 255, 255); break;
            case 1: cc = Color(0, 0, 0, 255); break;
            case 2: cc = Color(204, 0, 0, 255); break;
            case 3: cc = Color(187, 0, 187, 255); break;
            case 4: cc = Color(153, 153, 255, 255); break;
            case 5: cc = Color(0, 170, 0, 255); break;
            case 6: cc = Color(187, 187, 0, 255); break;
            case 7: cc = Color(0, 0, 170, 255); break;
            }
            this->region[i * 8 + 4].color = cc;
            this->region[i * 8 + 5].color = cc;
            this->region[i * 8 + 6].color = cc;
            this->region[i * 8 + 7].color = cc;
        }
    }
    for (int i = 0; i < 78; i++) {
        this->data[1][i] = this->data[0][i];
    }
    */

/*old coloring for cursor pos1 pos2
if (this->data[4][20] != this->data[4][21]) { //pos1
        if (this->data[4][21] < 78) {
            switch (this->data[0][this->data[4][21]]) {
            case 0: cc = Color(223, 221, 199, 255); break;
            case 1: cc = Color(156, 155, 139, 255); break;
            case 2: cc = Color(217, 155, 139, 255); break;
            case 3: cc = Color(212, 155, 195, 255); break;
            case 4: cc = Color(201, 200, 215, 255); break;
            case 5: cc = Color(156, 206, 139, 255); break;
            case 6: cc = Color(212, 211, 139, 255); break;
            case 7: cc = Color(155, 153, 188, 255); break;
            case 8: cc = Color(207, 208, 243, 255); break;
            }
            if (this->data[4][21] == 0) {
                for (int i = 0; i < this->data[2][this->data[4][21]]; i += 3) {
                    this->map[i + 0].color = cc;
                    this->map[i + 1].color = cc;
                    this->map[i + 2].color = cc;

                }
            }
            else for (int i = this->data[2][this->data[4][21] - 1]; i < this->data[2][this->data[4][21]]; i += 3) {
                this->map[i + 0].color = cc;
                this->map[i + 1].color = cc;
                this->map[i + 2].color = cc;

            }
        }
        if (this->data[4][20] < 78) {
            if (this->data[4][20] == 0) {
                for (int i = 0; i < this->data[2][(this->data[4][20])]; i += 3) {
                    this->map[i + 0].color = Color(0, 255, 0, 255);
                    this->map[i + 1].color = Color(0, 255, 0, 255);
                    this->map[i + 2].color = Color(0, 255, 0, 255);
                }
            }
            else for (int i = this->data[2][this->data[4][20] - 1]; i < this->data[2][this->data[4][20]]; i += 3) {
                this->map[i + 0].color = Color(0, 255, 0, 255);
                this->map[i + 1].color = Color(0, 255, 0, 255);
                this->map[i + 2].color = Color(0, 255, 0, 255);
            }
        }
        this->data[4][21] = this->data[4][20];
    }
    if (this->data[4][22] != this->data[4][23]) { //pos2
        if (this->data[4][23] < 78 && this->data[4][20] != this->data[4][23]) {
            switch (this->data[0][this->data[4][23]]) {
            case 0: cc = Color(223, 221, 199, 255); break;
            case 1: cc = Color(156, 155, 139, 255); break;
            case 2: cc = Color(217, 155, 139, 255); break;
            case 3: cc = Color(212, 155, 195, 255); break;
            case 4: cc = Color(201, 200, 215, 255); break;
            case 5: cc = Color(156, 206, 139, 255); break;
            case 6: cc = Color(212, 211, 139, 255); break;
            case 7: cc = Color(155, 153, 188, 255); break;
            case 8: cc = Color(207, 208, 243, 255); break;
            }
            if (this->data[4][23] == 0) {
                for (int i = 0; i < this->data[2][this->data[4][23]]; i += 3) {
                    this->map[i + 0].color = cc;
                    this->map[i + 1].color = cc;
                    this->map[i + 2].color = cc;

                }
            }
            else for (int i = this->data[2][this->data[4][23] - 1]; i < this->data[2][this->data[4][23]]; i += 3) {
                this->map[i + 0].color = cc;
                this->map[i + 1].color = cc;
                this->map[i + 2].color = cc;

            }
        }
        if (this->data[4][22] < 78) {
            if (this->data[4][22] == 0) {
                for (int i = 0; i < this->data[2][(this->data[4][22])]; i += 3) {
                    this->map[i + 0].color = Color(0, 0, 255, 255);
                    this->map[i + 1].color = Color(0, 0, 255, 255);
                    this->map[i + 2].color = Color(0, 0, 255, 255);
                }
            }
            else for (int i = this->data[2][this->data[4][22] - 1]; i < this->data[2][this->data[4][22]]; i += 3) {
                this->map[i + 0].color = Color(0, 0, 255, 255);
                this->map[i + 1].color = Color(0, 0, 255, 255);
                this->map[i + 2].color = Color(0, 0, 255, 255);
            }
        }
        this->data[4][23] = this->data[4][22];
    }
    if (this->data[4][4] != this->data[4][5]) { //regionHover
        if (this->data[4][5] < 78 && this->data[4][20] != this->data[4][5] && this->data[4][22] != this->data[4][5]) {
            switch (this->data[0][this->data[4][5]]) {
            case 0: cc = Color(223, 221, 199, 255); break;
            case 1: cc = Color(156, 155, 139, 255); break;
            case 2: cc = Color(217, 155, 139, 255); break;
            case 3: cc = Color(212, 155, 195, 255); break;
            case 4: cc = Color(201, 200, 215, 255); break;
            case 5: cc = Color(156, 206, 139, 255); break;
            case 6: cc = Color(212, 211, 139, 255); break;
            case 7: cc = Color(155, 153, 188, 255); break;
            case 8: cc = Color(207, 208, 243, 255); break;
            }
            if (this->data[4][5] == 0) {
                for (int i = 0; i < this->data[2][this->data[4][5]]; i += 3) {
                    this->map[i + 0].color = cc;
                    this->map[i + 1].color = cc;
                    this->map[i + 2].color = cc;

                }
            }
            else for (int i = this->data[2][this->data[4][5] - 1]; i < this->data[2][this->data[4][5]]; i += 3) {
                this->map[i + 0].color = cc;
                this->map[i + 1].color = cc;
                this->map[i + 2].color = cc;

            }
        }
        if (this->data[4][4] < 78 && this->data[4][20] != this->data[4][4] && this->data[4][22] != this->data[4][4]) {
            if (this->data[4][4] == 0) {
                for (int i = 0; i < this->data[2][(this->data[4][4])]; i += 3) {
                    this->map[i + 0].color = Color(255, 0, 0, 255);
                    this->map[i + 1].color = Color(255, 0, 0, 255);
                    this->map[i + 2].color = Color(255, 0, 0, 255);
                }
            }
            else for (int i = this->data[2][this->data[4][4] - 1]; i < this->data[2][this->data[4][4]]; i += 3) {
                this->map[i + 0].color = Color(255, 0, 0, 255);
                this->map[i + 1].color = Color(255, 0, 0, 255);
                this->map[i + 2].color = Color(255, 0, 0, 255);
            }
        }
        this->data[4][5] = this->data[4][4];
    }*/



/*class sfLine : public sf::Drawable
{
public:
    sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2):
        color(sf::Color::Yellow), thickness(5.f)
    {
        sf::Vector2f direction = point2 - point1;
        sf::Vector2f unitDirection = direction/std::sqrt(direction.x*direction.x+direction.y*direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

        sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

        vertices[0].position = point1 + offset;
        vertices[1].position = point2 + offset;
        vertices[2].position = point2 - offset;
        vertices[3].position = point1 - offset;

        for (int i=0; i<4; ++i)
            vertices[i].color = color;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(vertices,4,sf::Quads);
    }


private:
    sf::Vertex vertices[4];
    float thickness;
    sf::Color color;
};*/
    //#include <Thor/Shapes.hpp>
    //using namespace thor;
    //int* mapGenerate(int i);
    //int lineIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
    /*ConcaveShape* sea = new ConcaveShape;
    ConcaveShape* land = new ConcaveShape;
    ConcaveShape** alln = new ConcaveShape * [2]{ sea, land };
    int* quads = new int[312]; //1u 2r 3d 4l
    int quad = 0;
    //ConcaveShape aa, ab, ac, ad, ae, af, ag, ah, ai, aj, ak, al, am, an, ao, ap, aq, ar, as, at, au, av, aw, ax, ay, az, ba, bb, bc, bd, be, bf, bg, bh, bi, bj, bk, bl, bm, bn, bo, bp, bq, br, bs, bt, bu, bv, bw, bx, by, bz, ca, cb, cc, cd, ce, cf, cg, ch, ci, cj, ck, cl, cm, cn, co, cp, cq, cr, cs, ct, cu, cv, cw, cx, cy, cz;
    ConcaveShape* aa = new ConcaveShape, * ab = new ConcaveShape, * ac = new ConcaveShape, * ad = new ConcaveShape, * ae = new ConcaveShape, * af = new ConcaveShape, * ag = new ConcaveShape, * ah = new ConcaveShape, * ai = new ConcaveShape, * aj = new ConcaveShape, * ak = new ConcaveShape, * al = new ConcaveShape, * am = new ConcaveShape, * an = new ConcaveShape, * ao = new ConcaveShape, * ap = new ConcaveShape, * aq = new ConcaveShape, * ar = new ConcaveShape, * as = new ConcaveShape, * at = new ConcaveShape, * au = new ConcaveShape, * av = new ConcaveShape, * aw = new ConcaveShape, * ax = new ConcaveShape, * ay = new ConcaveShape, * az = new ConcaveShape,
                * ba = new ConcaveShape, * bb = new ConcaveShape, * bc = new ConcaveShape, * bd = new ConcaveShape, * be = new ConcaveShape, * bf = new ConcaveShape, * bg = new ConcaveShape, * bh = new ConcaveShape, * bi = new ConcaveShape, * bj = new ConcaveShape, * bk = new ConcaveShape, * bl = new ConcaveShape, * bm = new ConcaveShape, * bn = new ConcaveShape, * bo = new ConcaveShape, * bp = new ConcaveShape, * bq = new ConcaveShape, * br = new ConcaveShape, * bs = new ConcaveShape, * bt = new ConcaveShape, * bu = new ConcaveShape, * bv = new ConcaveShape, * bw = new ConcaveShape, * bx = new ConcaveShape, * by = new ConcaveShape, * bz = new ConcaveShape,
                * ca = new ConcaveShape, * cb = new ConcaveShape, * cc = new ConcaveShape, * cd = new ConcaveShape, * ce = new ConcaveShape, * cf = new ConcaveShape, * cg = new ConcaveShape, * ch = new ConcaveShape, * ci = new ConcaveShape, * cj = new ConcaveShape, * ck = new ConcaveShape, * cl = new ConcaveShape, * cm = new ConcaveShape, * cn = new ConcaveShape, * co = new ConcaveShape, * cp = new ConcaveShape, * cq = new ConcaveShape, * cr = new ConcaveShape, * cs = new ConcaveShape, * ct = new ConcaveShape, * cu = new ConcaveShape, * cv = new ConcaveShape, * cw = new ConcaveShape, * cx = new ConcaveShape, * cy = new ConcaveShape, * cz = new ConcaveShape;
    ConcaveShape** all = new ConcaveShape*[78]{ aa, ab, ac, ad, ae, af, ag, ah, ai, aj, ak, al, am, an, ao, ap, aq, ar, as, at, au, av, aw, ax, ay, az, ba, bb, bc, bd, be, bf, bg, bh, bi, bj, bk, bl, bm, bn, bo, bp, bq, br, bs, bt, bu, bv, bw, bx, by, bz, ca, cb, cc, cd, ce, cf, cg, ch, ci, cj, ck, cl, cm, cn, co, cp, cq, cr, cs, ct, cu, cv, cw, cx, cy, cz };
    RectangleShape* ra = new RectangleShape, * rb = new RectangleShape, * rc = new RectangleShape, * rd = new RectangleShape, * re = new RectangleShape, * rf = new RectangleShape, * rg = new RectangleShape, * rh = new RectangleShape, * ri = new RectangleShape, * rj = new RectangleShape, * rk = new RectangleShape, * rl = new RectangleShape, * rm = new RectangleShape, * rn = new RectangleShape, * ro = new RectangleShape, * rp = new RectangleShape, * rq = new RectangleShape, * rr = new RectangleShape, * rs = new RectangleShape, * rt = new RectangleShape, * ru = new RectangleShape, * rv = new RectangleShape;
    RectangleShape** allr = new RectangleShape * [22]{ ra, rb, rc, rd, re, rf, rg, rh, ri, rj, rk, rl, rm, rn, ro, rp, rq, rr, rs, rt, ru, rv };
    CircleShape* ka = new CircleShape, * kb = new CircleShape, * kc = new CircleShape, * kd = new CircleShape, * ke = new CircleShape, * kf = new CircleShape, * kg = new CircleShape, * kh = new CircleShape, * ki = new CircleShape, * kj = new CircleShape, * kk = new CircleShape, * kl = new CircleShape;
    CircleShape** allk = new CircleShape * [12]{ ka, kb, kc, kd, ke, kf, kg, kh, ki, kj, kk, kl };
    (*alln[0]).setPointCount(5);
    (*alln[0]).setPoint(0, Vector2f(200.f, 300.f));
    (*alln[0]).setPoint(1, Vector2f(400.f, 200.f));
    (*alln[0]).setPoint(2, Vector2f(500.f, 300.f));
    (*alln[0]).setPoint(3, Vector2f(600.f, 700.f));
    (*alln[0]).setPoint(4, Vector2f(500.f, 500.f));
    (*alln[0]).setFillColor(Color::Blue);
    (*alln[1]).setPointCount(5);
    (*alln[1]).setPoint(0, Vector2f(700.f, 300.f));
    (*alln[1]).setPoint(1, Vector2f(900.f, 200.f));
    (*alln[1]).setPoint(2, Vector2f(1000.f, 300.f));
    (*alln[1]).setPoint(3, Vector2f(1100.f, 700.f));
    (*alln[1]).setPoint(4, Vector2f(1000.f, 500.f));
    (*alln[1]).setFillColor(Color::Red);
    for (int i = 0; i < 78; ++i) {
        int* temp = mapGenerate(i);
        int z = temp[0] / 2;
        (*all[i]).setPointCount(z);
        (*all[i]).setFillColor(Color(223, 221, 199));
        (*all[i]).setOutlineThickness(2.f);
        (*all[i]).setOutlineColor(Color::White);
        for (int j = 0; j < z; ++j) {
            float x = (float) temp[(j * 2) + 1] * 1.9;
            float y = (float) temp[(j * 2) + 2] * 1.9;
            (*all[i]).setPoint(j, Vector2f(x, y));
            if (j == 0) {
                quads[i * 4 + 0] = quads[i * 4 + 2] = y;
                quads[i * 4 + 1] = quads[i * 4 + 3] = x;
            }
            else {
                if (quads[i * 4 + 0] > y)
                    quads[i * 4 + 0] = y;
                if (quads[i * 4 + 2] < y)
                    quads[i * 4 + 2] = y;
                if (quads[i * 4 + 1] < x)
                    quads[i * 4 + 1] = x;
                if (quads[i * 4 + 3] > x)
                    quads[i * 4 + 3] = x;
            }
        }
    }
    for (int i = 0; i < 22; ++i) {
        int* temp = mapGenerate(78);
        float x = (float)temp[i * 2] * 1.9;
        float y = (float)temp[i * 2 + 1] * 1.9;
        (*allr[i]).setPosition(Vector2f(x, y));
        (*allr[i]).setSize(Vector2f(10.f, 10.f));
        (*allr[i]).setOutlineThickness(2.f);
        (*allr[i]).setOutlineColor(Color::Black);
    }
    for (int i = 0; i < 12; ++i) {
        int* temp = mapGenerate(79);
        float x = (float)temp[i * 2] * 1.9 - 5;
        float y = (float)temp[i * 2 + 1] * 1.9 - 5;
        (*allk[i]).setPosition(Vector2f(x, y));
        (*allk[i]).setRadius(5);
        (*allk[i]).setOutlineThickness(2.f);
        (*allk[i]).setOutlineColor(Color::Black);
    }*/
//0 general: (223, 221, 199) 609, 559
//8 ocean: (207, 208, 243)
//1 de: (156, 155, 139) (47, 47, 42)    (0, 0, 0)
//2 oe: (217, 155, 139) (208, 47, 42)   (204, 0, 0)
//3 ru: (212, 155, 195) (195, 47, 189)  (187, 0, 187)
//4 fr: (201, 200, 215) (167, 167, 243) (153, 153, 255)
//5 it: (156, 206, 139) (45, 179, 40)   (0, 170, 0)
//6 tr: (212, 211, 139) (195, 194, 42)  (187, 187, 0)
//7 gb: (155, 153, 188) (45, 45, 175)   (0, 0, 170)
    //               0  1  2  3  4  5  6  7  8  9 10  1  2  3  4  5  6  7  8  9 20  1  2  3==4  5  6  7  8  9 30  1  2  3  4  5  6  7  8  9 40  1  2  3  4  5  6  7  8  9 50==1  2==3  4  5  6  7  8  9 60  1  2  3  4  5  6  7  8  9 70  1  2  3  4  5  6  7
  //int data[78] = { 0, 6, 5, 8, 8, 2, 0, 8, 4, 1, 8, 0, 8, 0, 0, 0, 6, 0, 2, 0, 5, 0, 0, 3, 3, 0, 4, 0, 8, 0, 1, 0, 8, 0, 0, 8, 8, 1, 8, 6, 8, 0, 0, 7, 0, 0, 0, 8, 3, 7, 0, 0, 0, 0, 8, 3, 8, 2, 0, 5, 0, 3, 8, 0, 8, 0, 0, 0, 4, 0, 0, 8, 7, 0, 8, 8, 0, 0 };
  //int data[78] = { 2, 3, 4, 8, 8, 5, 6, 8, 7, 1, 8, 1, 8, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 5, 7, 1, 2, 8, 3, 4, 5, 8, 6, 7, 8, 8, 1, 8, 2, 8, 3, 4, 5, 6, 7, 1, 8, 2, 3, 4, 4, 6, 6, 8, 1, 8, 2, 3, 4, 5, 6, 8, 7, 8, 1, 2, 3, 4, 5, 6, 8, 7, 1, 8, 8, 2, 3 };
  //int pro[34]  = { 1, 2, 5, 8, 9, 16, 18, 20, 23, 26, 30, 37, 39, 43, 48, 49, 55, 57, 59, 61, 68, 72, 6, 11, 14, 15, 25, 34, 45, 50, 52, 60, 73, 76 };
    /*RenderWindow window(VideoMode(1920, 1080), "Diplomacy");
    window.setVerticalSyncEnabled(false);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        Vector2i Pos = Mouse::getPosition(window);
        if (Pos.x <= 609 * 1.9 && Pos.y <= 559 * 1.9) {
            for (int i = 0; i < 78; ++i) {
                if (quads[i * 4 + 0] < Pos.y && quads[i * 4 + 1] > Pos.x && quads[i * 4 + 2] > Pos.y && quads[i * 4 + 3] < Pos.x) {
                    int* temp = mapGenerate(i);
                    int c = 0;
                    for (int j = 0; j < (temp[0] / 2) - 1; j++) {
                        if (lineIntersect(Pos.x, Pos.y, Pos.x + 700, Pos.y, temp[j * 2 + 1], temp[j * 2 + 2], temp[j * 2 + 3], temp[j * 2 + 4]) == 1) {
                            c++;
                        }
                    }
                    if (lineIntersect(Pos.x, Pos.y, Pos.x + 700, Pos.y + 1, temp[1], temp[2], temp[temp[0] - 2], temp[temp[0] - 1]) == 1)
                        c++;
                    if (c % 2 == 1 && c != 0)
                        quad = i;
                }
            }
        }
        for (int i = 0; i < 78; ++i) {
            if (quad == i && Pos.x <= 609 * 1.9 && Pos.y <= 559 * 1.9)
                (*all[i]).setFillColor(Color(255, 0, 0));
            else
            switch (data[i]) {
            case 0: (*all[i]).setFillColor(Color(223, 221, 199)); break;
            case 1: (*all[i]).setFillColor(Color(156, 155, 139)); break;
            case 2: (*all[i]).setFillColor(Color(217, 155, 139)); break;
            case 3: (*all[i]).setFillColor(Color(212, 155, 195)); break;
            case 4: (*all[i]).setFillColor(Color(201, 200, 215)); break;
            case 5: (*all[i]).setFillColor(Color(156, 206, 139)); break;
            case 6: (*all[i]).setFillColor(Color(212, 211, 139)); break;
            case 7: (*all[i]).setFillColor(Color(155, 153, 188)); break;
            case 8: (*all[i]).setFillColor(Color(207, 208, 243)); break;
            }
        }
        for (int i = 0; i < 22; i++) {
            switch (data[pro[i]]) {
            case 0: (*allr[i]).setFillColor(Color(255, 255, 255)); break;
            case 1: (*allr[i]).setFillColor(Color(0, 0, 0)); break;
            case 2: (*allr[i]).setFillColor(Color(204, 0, 0)); break;
            case 3: (*allr[i]).setFillColor(Color(187, 0, 187)); break;
            case 4: (*allr[i]).setFillColor(Color(153, 153, 255)); break;
            case 5: (*allr[i]).setFillColor(Color(0, 170, 0)); break;
            case 6: (*allr[i]).setFillColor(Color(187, 187, 0)); break;
            case 7: (*allr[i]).setFillColor(Color(0, 0, 170)); break;
            }
        }
        for (int i = 0; i < 12; i++) {
            switch (data[pro[i + 22]]) {
            case 0: (*allk[i]).setFillColor(Color(255, 255, 255)); break;
            case 1: (*allk[i]).setFillColor(Color(0, 0, 0)); break;
            case 2: (*allk[i]).setFillColor(Color(204, 0, 0)); break;
            case 3: (*allk[i]).setFillColor(Color(187, 0, 187)); break;
            case 4: (*allk[i]).setFillColor(Color(153, 153, 255)); break;
            case 5: (*allk[i]).setFillColor(Color(0, 170, 0)); break;
            case 6: (*allk[i]).setFillColor(Color(187, 187, 0)); break;
            case 7: (*allk[i]).setFillColor(Color(0, 0, 170)); break;
            }
        }
        window.clear(Color(255, 0, 255));
        int i = 0;
        while (i < 78) {
            window.draw(*all[i]);
            i++;
        }
        i = 0;
        while (i < 22) {
            window.draw(*allr[i]);
            i++;
        }
        i = 0;
        while (i < 12) {
            window.draw(*allk[i]);
            i++;
        }
        window.display();
    }
    return 0;
}
int lineIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    if ((((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1))) == 0)
        return 0;
    int x = ((((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3))) / (((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1))));
    int y = ((((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))) / (((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1))));
    if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
        return 1;
    else
        return 0;
}
int* mapGenerate(int i) {
    int* caa = new int[19]{ 18, 233, 415, 238, 431, 247, 442, 250, 438, 263, 434, 253, 418, 246, 416, 240, 415, 236, 411 };
    int* cab = new int[43]{ 42, 408, 470, 410, 473, 414, 475, 410, 482, 409, 487, 417, 486, 417, 489, 423, 487, 432, 493, 452, 495, 466, 491, 468, 479, 468, 461, 464, 457, 442, 460, 440, 458, 430, 455, 426, 450, 420, 451, 412, 454, 413, 464 };
    int* cac = new int[25]{ 24, 271, 464, 276, 474, 290, 487, 294, 502, 289, 511, 290, 514, 295, 515, 308, 500, 311, 491, 304, 484, 293, 481, 279, 458 };
    int* cad = new int[39]{ 38, 322, 480, 297, 456, 300, 453, 290, 453, 278, 443, 272, 424, 260, 417, 261, 401, 270, 398, 276, 399, 275, 403, 278, 410, 282, 401, 286, 402, 289, 418, 306, 436, 331, 454, 331, 477, 335, 480 };
    int* cae = new int[63]{ 62, 238, 431, 247, 442, 248, 447, 256, 458, 271, 464, 276, 474, 290, 487, 294, 502, 289, 511, 285, 511, 285, 508, 276, 510, 263, 510, 257, 507, 252, 508, 247, 513, 236, 524, 233, 523, 224, 527, 223, 518, 218, 516, 218, 490, 220, 490, 224, 468, 222, 458, 218, 458, 218, 454, 223, 450, 225, 444, 225, 436, 224, 431 };
    int* caf = new int[49]{ 48, 276, 399, 275, 403, 278, 410, 282, 401, 286, 402, 289, 418, 306, 436, 331, 454, 330, 445, 337, 446, 330, 437, 327, 429, 331, 424, 330, 416, 332, 410, 323, 408, 321, 398, 311, 394, 308, 383, 299, 385, 294, 380, 289, 385, 276, 386, 279, 389 };
    int* cag = new int[23]{ 22, 191, 299, 194, 303, 206, 306, 205, 311, 208, 315, 210, 326, 205, 331, 192, 323, 184, 315, 169, 311, 173, 301 };
    int* cah = new int[51]{ 50, 362, 33, 357, 39, 343, 44, 324, 54, 320, 64, 310, 75, 309, 84, 303, 86, 292, 111, 277, 132, 269, 134, 264, 142, 258, 141, 236, 154, 198, 154, 171, 181, 171, 197, 158, 193, 152, 194, 154, 188, 161, 185, 162, 181, 148, 177, 148, 0, 362, 0 };
    int* cai = new int[49]{ 48, 142, 417, 149, 403, 157, 397, 168, 395, 173, 396, 178, 390, 178, 381, 194, 382, 197, 385, 203, 379, 207, 386, 204, 390, 207, 396, 201, 399, 204, 402, 203, 410, 211, 416, 198, 421, 188, 422, 176, 417, 169, 412, 158, 418, 158, 425, 154, 427 };
    int* caj = new int[57]{ 56, 244, 254, 243, 257, 245, 263, 244, 270, 244, 273, 235, 277, 234, 274, 230, 273, 226, 275, 227, 280, 225, 292, 220, 298, 215, 297, 213, 302, 232, 308, 241, 316, 243, 322, 263, 310, 261, 296, 264, 293, 262, 287, 266, 283, 266, 275, 261, 274, 260, 269, 256, 266, 256, 263, 254, 255 };
    int* cak = new int[85]{ 84, 102, 317, 100, 322, 103, 328, 109, 329, 123, 344, 122, 350, 123, 357, 128, 363, 121, 382, 122, 384, 112, 399, 101, 396, 96, 397, 72, 384, 59, 381, 54, 375, 48, 374, 46, 378, 39, 375, 33, 381, 35, 384, 32, 396, 30, 406, 17, 427, 14, 427, 10, 433, 13, 440, 15, 441, 12, 450, 13, 454, 8, 462, 19, 469, 27, 468, 33, 475, 34, 484, 37, 490, 37, 495, 33, 496, 17, 518, 0, 520, 0, 273, 58, 273 };
    int* cal = new int[77]{ 76, 339, 487, 346, 498, 350, 498, 347, 500, 352, 508, 367, 507, 371, 511, 355, 510, 350, 514, 357, 521, 359, 533, 360, 528, 367, 536, 368, 531, 376, 537, 371, 520, 378, 521, 377, 513, 386, 516, 385, 509, 370, 494, 371, 491, 378, 494, 368, 483, 371, 477, 379, 484, 382, 483, 381, 477, 386, 478, 380, 472, 392, 472, 388, 460, 376, 464, 369, 464, 361, 467, 356, 471, 350, 471, 350, 477 };
    int* cam = new int[63]{ 62, 70, 261, 64, 250, 67, 242, 71, 245, 81, 234, 74, 228, 80, 225, 78, 218, 82, 217, 89, 220, 94, 220, 95, 218, 94, 216, 97, 216, 101, 212, 110, 212, 119, 217, 120, 227, 130, 227, 130, 223, 138, 217, 138, 214, 130, 208, 129, 197, 139, 189, 140, 182, 148, 177, 148, 0, 0, 0, 0, 273, 58, 273 };
    int* can = new int[25]{ 24, 138, 214, 130, 208, 129, 197, 139, 189, 140, 182, 148, 177, 162, 181, 161, 185, 154, 188, 152, 194, 146, 200, 144, 213 };
    int* cao = new int[35]{ 34, 226, 275, 227, 280, 225, 292, 220, 298, 215, 297, 213, 302, 210, 313, 208, 315, 205, 311, 206, 306, 194, 303, 191, 299, 198, 289, 205, 276, 205, 279, 207, 279, 211, 274 };
    int* cap = new int[85]{ 84, 275, 203, 277, 218, 276, 224, 282, 236, 279, 240, 279, 243, 282, 253, 289, 254, 294, 245, 305, 244, 312, 229, 311, 220, 314, 209, 322, 206, 328, 203, 331, 193, 326, 183, 320, 182, 321, 161, 330, 146, 343, 138, 351, 128, 347, 121, 349, 112, 355, 104, 362, 107, 356, 71, 342, 61, 341, 65, 330, 64, 332, 74, 324, 71, 311, 101, 308, 104, 309, 115, 300, 126, 301, 132, 292, 133, 290, 164, 285, 170, 287, 177, 279, 204 };
    int* caq = new int[41]{ 40, 555, 438, 551, 437, 520, 441, 514, 438, 511, 440, 502, 433, 481, 438, 470, 447, 464, 457, 468, 461, 468, 479, 466, 491, 473, 491, 490, 480, 501, 482, 508, 480, 531, 460, 546, 462, 555, 460, 557, 449 };
    int* car = new int[27]{ 26, 609, 493, 584, 478, 563, 479, 562, 471, 556, 467, 555, 460, 557, 449, 555, 438, 570, 427, 589, 442, 594, 439, 603, 441, 609, 440 };
    int* cas = new int[55]{ 54, 394, 376, 395, 382, 401, 385, 406, 396, 401, 402, 387, 402, 367, 406, 365, 412, 360, 413, 342, 410, 338, 412, 335, 410, 332, 410, 323, 408, 321, 398, 311, 394, 308, 383, 311, 375, 322, 370, 335, 354, 337, 350, 350, 347, 360, 351, 368, 353, 377, 360, 378, 363, 384, 365 };
    int* cat = new int[23]{ 22, 169, 311, 153, 315, 155, 320, 150, 319, 148, 329, 159, 331, 165, 331, 172, 328, 188, 332, 192, 323, 184, 315 };
    int* cau = new int[41]{ 40, 278, 443, 272, 424, 260, 417, 261, 401, 270, 398, 276, 399, 279, 389, 276, 386, 268, 385, 259, 388, 255, 394, 250, 397, 246, 392, 233, 404, 236, 411, 240, 415, 246, 416, 253, 418, 263, 434, 274, 447 };
    int* cav = new int[37]{ 36, 383, 327, 385, 332, 399, 338, 404, 354, 403, 360, 411, 361, 414, 372, 423, 376, 432, 372, 434, 360, 445, 350, 460, 345, 466, 307, 470, 303, 468, 295, 456, 292, 390, 306, 386, 309 };
    int* caw = new int[25]{ 24, 213, 302, 210, 313, 208, 315, 210, 326, 205, 331, 204, 338, 211, 346, 219, 344, 237, 322, 243, 322, 241, 316, 232, 308 };
    int* cax = new int[55]{ 54, 414, 147, 410, 152, 412, 161, 402, 177, 403, 183, 411, 184, 414, 187, 408, 187, 400, 192, 399, 197, 387, 196, 371, 198, 369, 202, 372, 205, 382, 206, 394, 205, 405, 217, 409, 228, 421, 229, 428, 225, 439, 211, 447, 209, 451, 213, 457, 210, 456, 207, 458, 194, 476, 183 };
    int* cay = new int[125]{ 124, 534, 164, 564, 159, 573, 143, 598, 132, 609, 117, 609, 0, 540, 0, 535, 9, 530, 6, 517, 19, 516, 33, 513, 38, 513, 23, 507, 20, 505, 26, 499, 33, 492, 48, 495, 58, 488, 60, 479, 57, 477, 55, 481, 50, 473, 43, 466, 45, 472, 62, 478, 66, 478, 74, 472, 72, 468, 74, 457, 91, 469, 100, 467, 106, 462, 109, 444, 101, 442, 110, 447, 115, 454, 119, 452, 122, 434, 118, 426, 103, 426, 94, 414, 88, 412, 83, 445, 84, 457, 79, 459, 66, 453, 61, 417, 47, 405, 49, 401, 45, 397, 48, 388, 61, 387, 68, 393, 73, 392, 92, 401, 110, 402, 118, 410, 130, 414, 147, 476, 183, 489, 184, 515, 169 };
    int* caz = new int[35]{ 34, 279, 243, 275, 242, 269, 243, 266, 240, 267, 234, 266, 221, 263, 223, 248, 224, 245, 237, 243, 247, 244, 254, 254, 255, 266, 255, 271, 260, 278, 254, 277, 250, 280, 248 };
    int* cba = new int[23]{ 22, 146, 365, 149, 372, 156, 374, 165, 365, 185, 344, 188, 332, 172, 328, 165, 331, 159, 331, 148, 329, 146, 337 };
    int* cbb = new int[67]{ 66, 362, 107, 368, 108, 372, 120, 366, 121, 359, 136, 345, 151, 347, 160, 350, 165, 348, 178, 349, 184, 357, 186, 365, 191, 384, 185, 402, 177, 412, 161, 410, 152, 414, 147, 410, 130, 402, 118, 401, 110, 392, 92, 393, 73, 387, 68, 388, 61, 386, 58, 388, 54, 379, 48, 370, 49, 369, 61, 355, 62, 346, 54, 342, 61, 356, 71 };
    int* cbc = new int[43]{ 42, 173, 301, 169, 311, 153, 315, 155, 320, 150, 319, 144, 318, 142, 312, 136, 310, 136, 326, 124, 323, 122, 318, 102, 317, 88, 303, 100, 291, 110, 292, 120, 295, 124, 291, 134, 294, 147, 295, 160, 298, 168, 296 };
    int* cbd = new int[23]{ 22, 163, 226, 163, 239, 168, 246, 170, 252, 169, 265, 166, 269, 153, 271, 150, 264, 151, 248, 155, 239, 155, 228 };
    int* cbe = new int[55]{ 54, 234, 366, 243, 370, 246, 369, 250, 371, 267, 368, 271, 370, 269, 362, 275, 362, 281, 356, 276, 346, 268, 343, 264, 329, 266, 325, 278, 326, 288, 321, 284, 314, 288, 305, 263, 310, 243, 322, 237, 322, 219, 344, 211, 346, 213, 352, 209, 363, 222, 365, 225, 362, 232, 363 };
    int* cbf = new int[39]{ 38, 100, 291, 112, 287, 122, 281, 130, 282, 127, 276, 119, 272, 116, 272, 115, 265, 128, 262, 143, 262, 150, 264, 153, 271, 150, 277, 145, 281, 147, 295, 134, 294, 124, 291, 120, 295, 110, 292 };
    int* cbg = new int[69]{ 68, 266, 255, 271, 260, 278, 254, 277, 250, 280, 248, 279, 243, 282, 253, 289, 254, 294, 245, 305, 244, 312, 229, 311, 220, 359, 220, 349, 229, 347, 243, 347, 248, 348, 254, 344, 262, 337, 264, 334, 273, 328, 274, 326, 265, 314, 266, 307, 273, 294, 275, 286, 274, 287, 267, 280, 266, 266, 275, 261, 274, 260, 269, 256, 266, 256, 263, 254, 255 };
    int* cbh = new int[35]{ 34, 207, 386, 204, 390, 207, 396, 201, 399, 204, 402, 203, 410, 211, 416, 222, 410, 233, 415, 236, 411, 233, 404, 246, 392, 243, 388, 229, 385, 227, 390, 221, 385, 213, 387 };
    int* cbi = new int[49]{ 48, 365, 412, 360, 413, 342, 410, 338, 412, 335, 410, 332, 410, 330, 416, 331, 424, 327, 429, 330, 437, 337, 446, 346, 452, 346, 466, 350, 471, 356, 471, 361, 467, 369, 464, 365, 461, 371, 456, 366, 439, 371, 438, 368, 433, 365, 425, 367, 421 };
    int* cbj = new int[37]{ 36, 241, 209, 246, 210, 266, 201, 270, 193, 275, 203, 277, 218, 276, 224, 282, 236, 279, 240, 279, 243, 275, 242, 269, 243, 266, 240, 267, 234, 266, 221, 263, 223, 248, 224, 241, 224 };
    int* cbk = new int[91]{ 90, 311, 220, 314, 209, 322, 206, 328, 203, 331, 193, 326, 183, 320, 182, 321, 161, 330, 146, 343, 138, 351, 128, 347, 121, 349, 112, 355, 104, 362, 107, 368, 108, 372, 120, 366, 121, 359, 136, 345, 151, 347, 160, 350, 165, 348, 178, 349, 184, 357, 186, 365, 191, 384, 185, 402, 177, 403, 183, 411, 184, 414, 187, 408, 187, 400, 192, 399, 197, 387, 196, 371, 198, 369, 202, 365, 204, 368, 210, 372, 213, 373, 221, 377, 227, 373, 229, 366, 228, 359, 220 };
    int* cbl = new int[29]{ 28, 294, 275, 286, 274, 287, 267, 280, 266, 266, 275, 266, 283, 262, 287, 264, 293, 261, 296, 263, 310, 288, 305, 296, 300, 297, 296, 292, 290 };
    int* cbm = new int[57]{ 56, 115, 469, 110, 461, 124, 444, 131, 439, 146, 438, 157, 432, 158, 425, 158, 418, 169, 412, 176, 417, 188, 422, 198, 421, 211, 416, 222, 410, 233, 415, 238, 431, 224, 431, 221, 434, 211, 436, 213, 451, 218, 454, 218, 458, 214, 461, 206, 462, 205, 466, 154, 466, 148, 463, 142, 469 };
    int* cbn = new int[77]{ 76, 417, 489, 420, 495, 417, 498, 417, 507, 423, 510, 427, 524, 435, 523, 435, 530, 441, 526, 447, 528, 453, 534, 464, 531, 466, 521, 475, 520, 485, 528, 491, 530, 505, 526, 511, 514, 520, 517, 527, 508, 530, 509, 536, 494, 545, 486, 555, 484, 563, 479, 562, 471, 556, 467, 555, 460, 546, 462, 531, 460, 508, 480, 501, 482, 490, 480, 473, 491, 466, 491, 452, 495, 432, 493, 423, 487 };
    int* cbo = new int[89]{ 88, 289, 511, 290, 514, 295, 515, 308, 500, 311, 491, 304, 484, 310, 480, 318, 485, 322, 485, 322, 480, 335, 480, 339, 487, 346, 498, 350, 498, 347, 500, 352, 508, 367, 507, 371, 511, 355, 510, 350, 514, 357, 521, 359, 533, 360, 528, 367, 536, 368, 531, 376, 537, 383, 544, 380, 547, 383, 550, 400, 554, 400, 559, 232, 559, 234, 551, 232, 544, 225, 535, 231, 531, 236, 524, 247, 513, 258, 519, 273, 531, 281, 532, 282, 521, 285, 513, 285, 511 };
    int* cbp = new int[51]{ 50, 347, 243, 347, 248, 348, 254, 344, 262, 337, 264, 334, 273, 328, 274, 326, 265, 314, 266, 307, 273, 294, 275, 292, 290, 297, 296, 296, 300, 320, 303, 324, 299, 326, 292, 341, 287, 345, 289, 359, 286, 365, 281, 367, 265, 362, 260, 356, 261, 354, 251 };
    int* cbq = new int[57]{ 56, 333, 330, 341, 330, 344, 332, 353, 327, 356, 323, 361, 324, 367, 329, 374, 327, 379, 324, 383, 327, 385, 332, 399, 338, 404, 354, 403, 360, 404, 371, 394, 376, 384, 365, 378, 363, 377, 360, 368, 353, 360, 351, 350, 347, 337, 350, 329, 346, 322, 347, 321, 339, 325, 340, 329, 338 };
    int* cbr = new int[29]{ 28, 166, 269, 168, 270, 171, 268, 177, 270, 178, 274, 176, 283, 165, 293, 172, 294, 168, 296, 160, 298, 147, 295, 145, 281, 150, 277, 153, 271 };
    int* cbs = new int[47]{ 46, 203, 520, 179, 515, 169, 518, 150, 511, 117, 509, 106, 511, 99, 515, 89, 512, 84, 518, 79, 520, 68, 516, 68, 511, 64, 514, 46, 509, 42, 502, 41, 494, 37, 495, 33, 496, 17, 518, 0, 520, 0, 559, 195, 559, 197, 527 };
    int* cbt = new int[57]{ 56, 403, 360, 404, 371, 394, 376, 395, 382, 401, 385, 406, 396, 401, 402, 387, 402, 367, 406, 365, 412, 367, 421, 370, 425, 375, 423, 382, 427, 390, 425, 398, 427, 404, 422, 410, 420, 422, 420, 430, 423, 432, 409, 439, 404, 438, 397, 427, 399, 422, 382, 423, 376, 414, 372, 411, 361 };
    int* cbu = new int[33]{ 32, 281, 356, 276, 346, 268, 343, 264, 329, 266, 325, 278, 326, 288, 321, 297, 322, 311, 334, 314, 332, 321, 339, 322, 347, 316, 348, 303, 346, 295, 349, 292, 357 };
    int* cbv = new int[27]{ 26, 245, 237, 243, 247, 244, 254, 243, 257, 245, 263, 244, 270, 244, 273, 235, 277, 234, 274, 230, 273, 226, 275, 211, 274, 211, 237 };
    int* cbw = new int[123]{ 122, 438, 397, 446, 378, 459, 375, 461, 377, 459, 379, 465, 383, 476, 381, 478, 383, 472, 385, 468, 392, 477, 396, 477, 401, 486, 404, 488, 397, 494, 396, 497, 392, 507, 389, 506, 384, 494, 387, 485, 378, 503, 364, 526, 351, 527, 354, 514, 365, 517, 371, 520, 371, 515, 384, 511, 383, 510, 386, 517, 393, 528, 394, 554, 406, 567, 408, 573, 417, 570, 427, 589, 442, 594, 439, 603, 441, 609, 440, 609, 330, 597, 330, 569, 321, 564, 305, 554, 304, 549, 284, 533, 283, 526, 287, 516, 286, 505, 280, 494, 295, 477, 289, 468, 295, 470, 303, 466, 307, 460, 345, 445, 350, 434, 360, 432, 372, 423, 376, 422, 382, 427, 399 };
    int* cbx = new int[29]{ 28, 152, 194, 158, 193, 171, 197, 170, 202, 165, 210, 158, 214, 151, 215, 157, 216, 161, 218, 163, 226, 155, 228, 145, 217, 144, 213, 146, 200 };
    int* cby = new int[57]{ 56, 134, 417, 40, 441, 34, 447, 36, 457, 27, 468, 33, 475, 34, 484, 37, 490, 47, 488, 52, 489, 60, 486, 78, 491, 83, 494, 86, 485, 90, 483, 98, 484, 107, 474, 113, 473, 115, 469, 110, 461, 124, 444, 131, 439, 146, 438, 157, 432, 158, 425, 154, 427, 142, 417, 135, 414 };
    int* cbz = new int[49]{ 48, 134, 417, 123, 412, 113, 407, 112, 399, 101, 396, 96, 397, 72, 384, 59, 381, 54, 375, 48, 374, 46, 378, 39, 375, 33, 381, 35, 384, 32, 396, 43, 395, 42, 399, 55, 400, 62, 407, 61, 411, 52, 412, 42, 432, 37, 431, 40, 441 };
    int* cca = new int[25]{ 24, 371, 438, 366, 439, 371, 456, 365, 461, 369, 464, 376, 464, 388, 460, 392, 472, 400, 468, 408, 470, 413, 464, 412, 454 };
    int* ccb = new int[39]{ 38, 412, 454, 420, 451, 426, 450, 422, 441, 425, 427, 429, 426, 430, 423, 422, 420, 410, 420, 404, 422, 398, 427, 390, 425, 382, 427, 375, 423, 370, 425, 367, 421, 365, 425, 368, 433, 371, 438 };
    int* ccc = new int[49]{ 48, 100, 291, 112, 287, 122, 281, 130, 282, 127, 276, 119, 272, 116, 272, 115, 265, 128, 262, 126, 256, 121, 257, 132, 250, 135, 250, 139, 240, 136, 229, 130, 227, 120, 227, 110, 232, 109, 246, 98, 259, 87, 257, 70, 261, 58, 273, 88, 303 };
    int* ccd = new int[45]{ 44, 333, 330, 326, 327, 323, 322, 320, 303, 324, 299, 326, 292, 341, 287, 345, 289, 359, 286, 365, 281, 372, 283, 379, 290, 386, 309, 383, 327, 379, 324, 374, 327, 367, 329, 361, 324, 356, 323, 353, 327, 344, 332, 341, 330 };
    int* cce = new int[117]{ 116, 540, 0, 535, 9, 530, 6, 517, 19, 516, 33, 513, 38, 513, 23, 507, 20, 505, 26, 499, 33, 492, 48, 495, 58, 488, 60, 479, 57, 477, 55, 481, 50, 473, 43, 466, 45, 472, 62, 478, 66, 478, 74, 472, 72, 468, 74, 457, 91, 469, 100, 467, 106, 462, 109, 444, 101, 442, 110, 447, 115, 454, 119, 452, 122, 434, 118, 426, 103, 426, 94, 414, 88, 412, 83, 445, 84, 457, 79, 459, 66, 453, 61, 417, 47, 405, 49, 401, 45, 397, 48, 391, 47, 395, 41, 394, 38, 384, 33, 382, 40, 380, 33, 377, 31, 374, 38, 371, 33, 366, 42, 366, 33, 362, 33, 362, 0 };
    int* ccf = new int[29]{ 28, 292, 357, 295, 349, 303, 346, 316, 348, 322, 347, 329, 346, 337, 350, 335, 354, 322, 370, 311, 375, 308, 383, 299, 385, 294, 380, 295, 362 };
    int* ccg = new int[29]{ 28, 304, 484, 310, 480, 318, 485, 322, 485, 322, 480, 297, 456, 300, 453, 290, 453, 278, 443, 274, 447, 279, 451, 280, 455, 279, 458, 293, 481 };
    int* cch = new int[21]{ 20, 247, 442, 248, 447, 256, 458, 271, 464, 279, 458, 280, 455, 279, 451, 274, 447, 263, 434, 250, 438 };
    int* cci = new int[31]{ 30, 232, 559, 234, 551, 232, 544, 225, 535, 231, 531, 236, 524, 233, 523, 224, 527, 223, 518, 218, 516, 212, 517, 208, 521, 203, 520, 197, 527, 195, 559 };
    int* ccj = new int[77]{ 76, 609, 117, 598, 132, 573, 143, 564, 159, 534, 164, 515, 169, 489, 184, 476, 183, 458, 194, 456, 207, 457, 210, 451, 213, 447, 209, 439, 211, 428, 225, 421, 229, 409, 228, 405, 239, 404, 275, 392, 278, 389, 285, 379, 290, 386, 309, 390, 306, 456, 292, 468, 295, 477, 289, 494, 295, 505, 280, 516, 286, 526, 287, 533, 283, 549, 284, 554, 304, 564, 305, 569, 321, 597, 330, 609, 330 };
    int* cck = new int[85]{ 84, 37, 490, 47, 488, 52, 489, 60, 486, 78, 491, 83, 494, 86, 485, 90, 483, 98, 484, 107, 474, 113, 473, 115, 469, 142, 469, 150, 471, 154, 466, 205, 466, 206, 476, 204, 485, 208, 492, 212, 492, 217, 489, 218, 490, 218, 516, 212, 517, 208, 521, 203, 520, 179, 515, 169, 518, 150, 511, 117, 509, 106, 511, 99, 515, 89, 512, 84, 518, 79, 520, 68, 516, 68, 511, 64, 514, 46, 509, 42, 502, 41, 494, 37, 495 };
    int* ccl = new int[55]{ 54, 369, 202, 365, 204, 368, 210, 372, 213, 373, 221, 377, 227, 373, 229, 366, 228, 359, 220, 349, 229, 347, 243, 354, 251, 356, 261, 362, 260, 367, 265, 365, 281, 372, 283, 379, 290, 389, 285, 392, 278, 404, 275, 405, 239, 409, 228, 405, 217, 394, 205, 382, 206, 372, 205 };
    int* ccm = new int[85]{ 84, 245, 237, 248, 224, 241, 224, 241, 209, 231, 201, 229, 192, 233, 186, 231, 180, 233, 167, 237, 160, 236, 154, 198, 154, 171, 181, 171, 197, 170, 202, 165, 210, 158, 214, 151, 215, 157, 216, 161, 218, 163, 226, 163, 239, 168, 246, 170, 252, 169, 265, 166, 269, 168, 270, 171, 268, 177, 270, 178, 274, 176, 283, 165, 293, 172, 294, 168, 296, 173, 301, 191, 299, 198, 289, 205, 276, 205, 279, 207, 279, 211, 274, 211, 237 };
    int* ccn = new int[21]{ 20, 331, 454, 331, 477, 335, 480, 339, 487, 350, 477, 350, 471, 346, 466, 346, 452, 337, 446, 330, 445 };
    int* cco = new int[25]{ 24, 530, 509, 536, 494, 545, 486, 555, 484, 563, 479, 584, 478, 609, 493, 609, 559, 528, 559, 532, 535, 526, 530, 525, 518 };
    int* ccp = new int[37]{ 36, 128, 363, 121, 382, 122, 384, 112, 399, 113, 407, 123, 412, 134, 417, 135, 414, 142, 417, 149, 403, 157, 397, 168, 395, 163, 387, 165, 383, 158, 380, 156, 374, 149, 372, 146, 365 };
    int* ccq = new int[37]{ 36, 150, 319, 144, 318, 142, 312, 136, 310, 136, 326, 124, 323, 122, 318, 102, 317, 100, 322, 103, 328, 109, 329, 123, 344, 122, 350, 123, 357, 128, 363, 146, 365, 146, 337, 148, 329 };
    int* ccr = new int[47]{ 46, 234, 366, 243, 370, 246, 369, 250, 371, 267, 368, 271, 370, 269, 362, 275, 362, 281, 356, 292, 357, 295, 362, 294, 380, 289, 385, 276, 386, 268, 385, 259, 388, 255, 394, 250, 397, 246, 392, 243, 388, 245, 384, 241, 378, 234, 374 };
    int* ccs = new int[29]{ 28, 288, 321, 297, 322, 311, 334, 314, 332, 321, 339, 325, 340, 329, 338, 333, 330, 326, 327, 323, 322, 320, 303, 296, 300, 288, 305, 284, 314 };
    int* cct = new int[45]{ 44, 435, 530, 441, 526, 447, 528, 453, 534, 464, 531, 466, 521, 475, 520, 485, 528, 491, 530, 505, 526, 511, 514, 520, 517, 527, 508, 530, 509, 525, 518, 526, 530, 532, 535, 528, 559, 400, 559, 400, 554, 414, 552, 416, 549 };
    int* ccu = new int[37]{ 36, 128, 262, 126, 256, 121, 257, 132, 250, 135, 250, 139, 240, 136, 229, 130, 227, 130, 223, 138, 217, 138, 214, 144, 213, 145, 217, 155, 228, 155, 239, 151, 248, 150, 264, 143, 262 };
    int* ccv = new int[47]{ 46, 32, 396, 30, 406, 17, 427, 14, 427, 10, 433, 13, 440, 15, 441, 12, 450, 13, 454, 8, 462, 19, 469, 27, 468, 36, 457, 34, 447, 40, 441, 37, 431, 42, 432, 52, 412, 61, 411, 62, 407, 55, 400, 42, 399, 43, 395 };
    int* ccw = new int[109]{ 108, 440, 458, 430, 455, 426, 450, 422, 441, 425, 427, 429, 426, 430, 423, 432, 409, 439, 404, 438, 397, 446, 378, 459, 375, 461, 377, 459, 379, 465, 383, 476, 381, 478, 383, 472, 385, 468, 392, 477, 396, 477, 401, 486, 404, 488, 397, 494, 396, 497, 392, 507, 389, 506, 384, 494, 387, 485, 378, 503, 364, 526, 351, 527, 354, 514, 365, 517, 371, 520, 371, 515, 384, 511, 383, 510, 386, 517, 393, 528, 394, 554, 406, 567, 408, 573, 417, 570, 427, 555, 438, 551, 437, 520, 441, 514, 438, 511, 440, 502, 433, 481, 438, 470, 447, 464, 457, 442, 460 };
    int* ccx = new int[73]{ 72, 376, 537, 371, 520, 378, 521, 377, 513, 386, 516, 385, 509, 370, 494, 371, 491, 378, 494, 368, 483, 371, 477, 379, 484, 382, 483, 381, 477, 386, 478, 380, 472, 392, 472, 400, 468, 408, 470, 410, 473, 414, 475, 410, 482, 409, 487, 417, 486, 417, 489, 420, 495, 417, 498, 417, 507, 423, 510, 427, 524, 435, 523, 435, 530, 416, 549, 412, 547, 387, 546, 383, 544 };
    int* ccy = new int[121]{ 120, 397, 48, 391, 47, 395, 41, 394, 38, 384, 33, 382, 40, 380, 33, 377, 31, 374, 38, 371, 33, 366, 42, 366, 33, 362, 33, 357, 39, 343, 44, 324, 54, 320, 64, 310, 75, 309, 84, 303, 86, 292, 111, 277, 132, 269, 134, 264, 142, 258, 141, 236, 154, 237, 160, 233, 167, 231, 180, 233, 186, 229, 192, 231, 201, 241, 209, 246, 210, 266, 201, 270, 193, 275, 203, 279, 204, 287, 177, 285, 170, 290, 164, 292, 133, 301, 132, 300, 126, 309, 115, 308, 104, 311, 101, 324, 71, 332, 74, 330, 64, 341, 65, 342, 61, 346, 54, 355, 62, 369, 61, 370, 49, 379, 48, 388, 54, 386, 58, 388, 61 };
    int* ccz = new int[39]{ 38, 192, 323, 205, 331, 204, 338, 211, 346, 213, 352, 209, 363, 208, 367, 194, 382, 178, 381, 178, 390, 173, 396, 168, 395, 163, 387, 165, 383, 158, 380, 156, 374, 165, 365, 185, 344, 188, 332 };
    int* cr = new int[44]{ 424, 475, 278, 469, 290, 396, 190, 412, 254, 278, 482, 469, 326, 376, 263, 390, 418, 187, 177, 338, 258, 359, 281, 298, 424, 502, 156, 289, 479, 393, 154, 219, 343, 302, 298, 363, 268, 448, 481, 234, 106, 322, 142, 253 };
    int* ck = new int[24]{ 186, 305, 378, 507, 205, 284, 323, 196, 272, 252, 343, 419, 402, 413, 80, 432, 377, 444, 220, 529, 15, 434, 270, 187 };
    int** poi = new int* [112]{ caa, cab, cac, cad, cae, caf, cag, cah, cai, caj, cak, cal, cam, can, cao, cap, caq, car, cas, cat, cau, cav, caw, cax, cay, caz, cba, cbb, cbc, cbd, cbe, cbf, cbg, cbh, cbi, cbj, cbk, cbl, cbm, cbn, cbo, cbp, cbq, cbr, cbs, cbt, cbu, cbv, cbw, cbx, cby, cbz, cca, ccb, ccc, ccd, cce, ccf, ccg, cch, cci, ccj, cck, ccl, ccm, ccn, cco, ccp, ccq, ccr, ccs, cct, ccu, ccv, ccw, ccx, ccy, ccz, cr, ck};
    return poi[i];
}*/
 
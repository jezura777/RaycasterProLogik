#include "Logic.hpp"
#include <iostream>

#include <math.h>

#define PI 3.14159265358
#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533 // one degree in radians

float px, py, pdx, pdy, pa; // Player Position

// void drawPlayer()
// {
//     glColor3f(1,1,0);
//     glPointSize(8);
//     glBegin(GL_POINTS);
//     glVertex2i(px, py);
//     glEnd();

//     glLineWidth(3);
//     glBegin(GL_LINES);
//     glVertex2i(px, py);
//     glVertex2i(px+pdx*5, py+pdy*5);
//     glEnd();
// }

int mapX = 8, mapY = 8, mapS = 64;
int map[] = {
    1,1,1,1,1,1,1,1,
    1,0,4,0,0,0,0,1,
    1,0,3,0,0,0,0,1,
    1,0,2,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,3,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

// void drawMap2D()
// {
//     int xo, yo;
//     for (int y = 0; y < mapY; y++)
//     {
//         for (int x = 0; x < mapX; x++)
//         {
//             if (map[y*mapX+x]>0) { setC(y*mapX+x, 0); } else { glColor3f(0,0,0); }
//             xo=x*mapS; yo=y*mapS;

//             glBegin(GL_QUADS);
//             glVertex2i(xo     +1, yo     +1);
//             glVertex2i(xo     +1, yo+mapS-1);
//             glVertex2i(xo+mapS-1, yo+mapS-1);
//             glVertex2i(xo+mapS-1, yo     +1);
//             glEnd();

//         }

//     }

// }

Rgb setC(int mapP, float offset) {

    if (map[mapP] == 1) {
        return Rgb(100+offset, 100+offset, 100+offset);
    } else if (map[mapP] == 2) {
        return Rgb(200 + offset, 0, 0);
    } else if (map[mapP] == 3) {
        return Rgb(0, 200 + offset, 0);
    } else if (map[mapP] == 4) {
        return Rgb(0, 0, 200 + offset);
    }

    return Rgb(200, 0, 200);
}

float dist(float ax, float ay, float bx, float by, float ang) {
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void drawRays2D() {
    int r=0, mx=0, my=0, mpH=0, mpV=0, dof=0;
    float rx=0, ry=0, ra=0, xo=0, yo=0, disT=0;
    Rgb color;
    ra = pa - DR * 30;
    if (ra < 0) {
        ra += 2 * PI;
    }
    if (ra > 2 * PI) {
        ra -= 2 * PI;
    }
    for (r = 0; r < 10; r++) {
        // ---Check Horizontal Lines---
        dof = 0;
        float disH = 1000000, hx = px, hy = py;
        float aTan = -1 / tan(ra);

        if (ra > PI) {
            ry = (((int)py >> 6) << 6) - 0.0001;
            rx = (py - ry) * aTan + px;
            yo = -64;
            xo = -yo * aTan;
        } // looking up
        if (ra < PI) {
            ry = (((int)py >> 6) << 6) + 64;
            rx = (py - ry) * aTan + px;
            yo = 64;
            xo = -yo * aTan;
        } // looking down
        if (ra == 0 || ra == PI) {
            rx = px;
            ry = py;
            dof = 8;
        } // looking straight left or right
        while (dof < 8) {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mpH = my * mapX + mx;
            if (mpH > 0 && mpH < mapX * mapY && map[mpH] > 0) {
                hx = rx;
                hy = ry;
                disH = dist(px, py, hx, hy, ra);
                dof = 8;
            } //hit wall
            else {
                rx += xo;
                ry += yo;
                dof += 1;
            } //next line
        }

        // ---Check Vertical Lines---
        dof = 0;
        float disV = 1000000, vx = px, vy = py;
        float nTan = -tan(ra);

        if (ra > P2 && ra < P3) {
            rx = (((int)px >> 6) << 6) - 0.0001;
            ry = (px - rx) * nTan + py;
            xo = -64;
            yo = -xo * nTan;
        } // looking left
        if (ra < P2 || ra > P3) {
            rx = (((int)px >> 6) << 6) + 64;
            ry = (px - rx) * nTan + py;
            xo = 64;
            yo = -xo * nTan;
        } // looking right
        if (ra == 0 || ra == PI) {
            rx = px;
            ry = py;
            dof = 8;
        } // looking straight up or down
        while (dof < 8) {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mpV = my * mapX + mx;
            if (mpV > 0 && mpV < mapX * mapY && map[mpV] > 0) {
                vx = rx;
                vy = ry;
                disV = dist(px, py, vx, vy, ra);
                dof = 8;
            } //hit wall
            else {
                rx += xo;
                ry += yo;
                dof += 1;
            } //next line
        }

        if (disV < disH) {
            rx = vx;
            ry = vy;
            disT = disV;
            color = setC(mpV, 50);
        } // vertical Hit
        if (disH < disV) {
            rx = hx;
            ry = hy;
            disT = disH;
            color = setC(mpH, -50);
        } // horizontal Hit

        // glLineWidth(5); glBegin(GL_LINES); glVertex2i(px, py); glVertex2i(rx, ry); glEnd();

        //---Draw 3D Walls---
        float ca = pa - ra;
        if (ca < 0) {
            ca += 2 * PI;
        }
        if (ca > 2 * PI) {
            ca -= 2 * PI;
        }
        disT = disT * cos(ca); // fix fisheye
        float lineH = (mapS * 320) / disT;
        if (lineH > 320) {
            lineH = 320;
        } //line height
        float lineO = 160 - lineH / 2; //line offset
        // glLineWidth(7); glBegin(GL_LINES);  glVertex2i(r*7+530,lineO); glVertex2i(r*7+530, lineH+lineO); glEnd();
        display.drawLine(r, lineO, r, lineH+lineO, color, 1);

        ra += DR*6;
        if (ra < 0) {
            ra += 2 * PI;
        }
        if (ra > 2 * PI) {
            ra -= 2 * PI;
        }
    }
}

void draw() {
    display.fill(Rgb(50, 50, 50));
    // drawMap2D();
    drawRays2D();
    // drawPlayer();
    display.show(255);
}

void input() {
    if (buttons.read(Left)) {
        pa -= 0.1;
        if (pa < 0) {
            pa += 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
    if (buttons.read(Right)) {
        pa += 0.1;
        if (pa > 2 * PI) {
            pa -= 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }

    if (buttons.read(Up)) {
        px += pdx;
        py += pdy;
    }
    if (buttons.read(Down)) {
        px -= pdx;
        py -= pdy;
    }

    draw();
}

void init() {
    // gluOrtho2D(0, 1024, 510, 0);
    px = 300;
    py = 300;
    pdx = cos(pa) * 5;
    pdy = sin(pa) * 5;

}

void logicMain() {
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // glutInitWindowSize(1024, 512);
    // glutCreateWindow("Raycaster");
    init();
    // glutDisplayFunc(display);
    // glutKeyboardFunc(buttons);
    // glutMainLoop();

    while (1)
    {
        input();
        draw();
    }
    
    // return 0;
}

#include "../inc/OpenGLGraph.hpp"
//using namespace std::;

SDLGraph::SDLGraph() {
    key = none;
    quit = false;
    snake1->direction = 'R';
    snake1->size = 1;
    init();
}

SDLGraph::SDLGraph(Snake *s1, Snake *s2) {
    std::cout << "SDLGraph" << std::endl;
    snake1 = s1;
    snake2 = s2;
    key = none;
    std::cout << "w = " << snake1->screenWidth << " h = " << snake1->screenHeiht << std::endl;
    quit = false;
    xrf = 0, yrf = 0, zrf = 0; // углы поворота
    // xrf -= 5;
    // yrf -= 3;
    //zrf -= 10;
    init();
}

SDLGraph::SDLGraph(SDLGraph &obj) {
    *this = obj;
}

SDLGraph::~SDLGraph() {
    // if (appleTexture)
    //     SDL_DestroyTexture(appleTexture);
    // if (snake1Texture)
    //     SDL_DestroyTexture(snake1Texture);
    // if (snake2Texture)
    //     SDL_DestroyTexture(snake2Texture);
    // TTF_CloseFont(textFont);
    // SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(window);
    // TTF_Quit();
    SDL_Quit();
}

void        SDLGraph::setMultiplayer(bool m) { multiplayer = m; }
eKeyType    SDLGraph::getKey() { return (key); }
void        SDLGraph::setKey(eKeyType k) { key = k; }


void        SDLGraph::init() {

    // Инициализация SDL

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        std::cout << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Включаем двойной буфер, настраиваем цвета

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

    // Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.

    window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, snake1->screenWidth, snake1->screenHeiht, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

    if(window == NULL){ // если не получилось создать окно, то выходим
        exit(1);
    }

    // Инициализация OpenGL

    glClearColor(0.0f, 0.5f, 0.5f, 0.0f); // устанавливаем фоновый цвет на черный
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST); // включаем тест глубины
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) snake1->screenWidth / (float) snake1->screenHeiht, 0.1f, 100.0f); // настраиваем трехмерную перспективу
    glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим

}

int         SDLGraph::close(std::string msg) {
    std::cout << msg << std::endl;
    this->~SDLGraph();
    exit(1);
    return (0);
}

void        SDLGraph::setKeyDownRotate() {
    switch( event.key.keysym.sym )
    {
        case SDLK_i:        { xrf += 0.3; break; }
        case SDLK_j:        { xrf -= 0.3; break; }
        case SDLK_o:        { yrf += 0.3; break; }
        case SDLK_k:        { yrf -= 0.3; break; }
        case SDLK_p:        { zrf += 0.3; break; }
        case SDLK_l:        { zrf -= 0.3; break; }
    }
}

void        SDLGraph::setKeyDown() {
    switch( event.key.keysym.sym )
    {
        case SDLK_w:        { key = w; break; }
        case SDLK_s:        { key = s; break; }
        case SDLK_a:        { key = a; break; }
        case SDLK_d:        { key = d; break; }
        case SDLK_UP:       { key = up; break; }
        case SDLK_DOWN:     { key = down; break; }
        case SDLK_LEFT:     { key = left; break; }
        case SDLK_RIGHT:    { key = right; break; }
        case SDLK_ESCAPE:   { key = escape; break; }
        case SDLK_RETURN:   { key = enter; break; }
        case SDLK_1:        { key = num1; break; }
        case SDLK_2:        { key = num2; break; }
        case SDLK_3:        { key = num3; break; }
        default:            { key = none; break; }
    }
}

void        SDLGraph::renderText(const char *text, int x, int y, bool selection) {

    // SDL_Surface *surface;
    // SDL_Texture *texture;

    // SDL_Color color = { 0, 0, 0, 255 };
    // surface = TTF_RenderText_Solid(textFont, text, color);
    // msgRECT.x = x;
    // msgRECT.y = y;
    // msgRECT.w = surface->w;
    // msgRECT.h = surface->h;
    // texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    // if (selection) {
    //     SDL_Rect outlineRect = { x, y, surface->w, surface->h };
    //     SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    //     SDL_RenderDrawRect( gRenderer, &outlineRect );
    // }

    // SDL_FreeSurface(surface);
    // SDL_RenderCopy(gRenderer, texture, NULL, &msgRECT);
    // SDL_DestroyTexture(texture);
}

void        SDLGraph::drawMenu(int buttonNum, bool start, int speed) {

    // SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );
    // SDL_RenderClear(gRenderer);

    // SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // if (start)
    //     renderText("CONTINUE", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 100, (buttonNum == 1) ? true : false);
    // renderText("NEW GAME", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 50, (buttonNum == 2) ? true : false);
    // renderText((std::string("MULTIPLAYER ") + (multiplayer ? "ON" : "OFF")).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2, (buttonNum == 3) ? true : false);
    // renderText("EXIT", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 + 50, (buttonNum == 4) ? true : false);
    // renderText(("SPEED  " + std::to_string(speed)).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 300, false);

    // SDL_RenderDrawLine(gRenderer, 50, 50, 50, snake1->screenHeiht - 50);
    // SDL_RenderDrawLine(gRenderer, 50, 50, snake1->screenWidth - 50, 50);
    // SDL_RenderDrawLine(gRenderer, snake1->screenWidth - 50, 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);
    // SDL_RenderDrawLine(gRenderer, 50, snake1->screenHeiht - 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);

    // SDL_RenderPresent(gRenderer);
}

void  SDLGraph::drawSnake3D() {
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (snake1->screenWidth > snake1->screenHeiht)
        k = (snake1->screenHeiht - 800) * 0.024;
    else
        k = (snake1->screenWidth - 800) * 0.024;
    glTranslatef(0.0f, 0.0f, 6 - k);    // Сдвинуть вглубь экрана

    // xrf = 0;
    // yrf = 0;
    // zrf = 0;
    // xrf -= 0.05;
    // yrf -= 0.05;
    // zrf -= 0.05;

    // glRotatef(xrf, 1.0f, 0.0f, 0.0f);    // Вращение куба по X, Y, Z
    // glRotatef(yrf, 0.0f, 1.0f, 0.0f);    // Вращение куба по X, Y, Z
    // glRotatef(zrf, 0.0f, 0.0f, 1.0f);    // Вращение куба по X, Y, Z
    

    for (int i = 0; i < snake1->snakeRect.size(); i++) {
        x = (snake1->snakeRect[i].x - snake1->screenWidth/2)/50;
        y = (snake1->screenHeiht - snake1->snakeRect[i].y - 50 - snake1->screenHeiht/2)/50; 
   
        glBegin(GL_QUADS); 
        glColor3f(0.4f, 0.0f, 0.0f);              // Синяя сторона (Верхняя)
        glVertex3f( x + 1,  y,   -26.0f);         // Верхний правый угол квадрата
        glVertex3f( x,      y,   -26.0f);         // Верхний левый
        glVertex3f( x,      y,   -25.0f);         // Нижний левый
        glVertex3f( x + 1,  y,   -25.0f);         // Нижний правый

        glColor3f(0.4f, 0.0f, 0.0f);              // Оранжевая сторона (Нижняя)
        glVertex3f( x + 1,  y + 1,   -25.0f);     // Верхний правый угол квадрата
        glVertex3f( x,      y + 1,   -25.0f);     // Верхний левый
        glVertex3f( x,      y + 1,   -26.0f);     // Нижний левый
        glVertex3f( x + 1,  y + 1,   -26.0f);     // Нижний правый
    
        glColor3f(1.0f, 0.0f, 0.0f);              // Красная сторона (Передняя) ///////////////////////////
        glVertex3f( x + 1,  y,       -25.0f);     // Верхний правый угол квадрата
        glVertex3f( x,      y,       -25.0f);     // Верхний левый
        glVertex3f( x,      y + 1,   -25.0f);     // Нижний левый
        glVertex3f( x + 1,  y + 1,   -25.0f);     // Нижний правый

        glColor3f(0.5f, 0.0f, 0.0f);              // Желтая сторона (Задняя)
        glVertex3f( x + 1,  y + 1,   -26.0f);     // Верхний правый угол квадрата
        glVertex3f( x,      y + 1,   -26.0f);     // Верхний левый
        glVertex3f( x,      y,       -26.0f);     // Нижний левый
        glVertex3f( x + 1,  y,       -26.0f);     // Нижний правый
        // тень
        glColor3f(0.2f, 0.2f, 0.2f);              // // тень
        glVertex3f( x + 1,  y + 1,   -27.0f);     // Верхний правый угол квадрата
        glVertex3f( x,      y + 1,   -27.0f);     // Верхний левый
        glVertex3f( x,      y,       -27.0f);     // Нижний левый
        glVertex3f( x + 1,  y,       -27.0f);     // Нижний правый

        glColor3f(0.6f, 0.0f, 0.0f);              // Синяя сторона (Левая)
        glVertex3f( x,      y,       -25.0f);     // Верхний правый угол квадрата
        glVertex3f( x,      y,       -26.0f);     // Верхний левый
        glVertex3f( x,      y + 1,   -26.0f);     // Нижний левый
        glVertex3f( x,      y + 1,   -25.0f);     // Нижний правый

        glColor3f(0.6f, 0.0f, 0.0f);               // Фиолетовая сторона (Правая)
        glVertex3f( x + 1,   y,       -26.0f);     // Верхний правый угол квадрата
        glVertex3f( x + 1,   y,       -25.0f);     // Верхний левый
        glVertex3f( x + 1,   y + 1,   -25.0f);     // Нижний левый
        glVertex3f( x + 1,   y + 1,   -26.0f);     // Нижний правый

        // golova romb 
        if (i == 0) {
            glColor3f(0.0f, 1.0f, 0.0f);              // Красная сторона (Передняя)
            glVertex3f( x + 0.5,  y,       -24.9f);     // Верхний правый угол квадрата
            glVertex3f( x,      y + 0.5,   -24.9f);     // Верхний левый
            glVertex3f( x + 0.5, y + 1,   -24.9f);     // Нижний левый
            glVertex3f( x + 1,  y + 0.5,   -24.9f);     // Нижний правый
        }

        glEnd();

        glBegin(GL_LINES);
            glColor3f(0.0f, 0.0f, 0.0f);
    
            //передняя
            glBegin(GL_LINES);
            glVertex3f( x + 1,  y,       -24.9f);     // Верхний правый угол квадрата
            glVertex3f( x,      y,       -24.9f);     // Верхний левый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x,      y + 1,   -24.9f);     // Нижний левый
            glVertex3f( x + 1,  y + 1,   -24.9f);     // Нижний правый
            glEnd();

            glBegin(GL_LINES);
            glVertex3f( x + 1,  y,       -24.9f);     // Верхний правый угол квадрата
            glVertex3f( x + 1,  y + 1,   -24.9f);     // Нижний правый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x,      y + 1,   -24.9f);     // Нижний левый
            glVertex3f( x,      y,       -24.9f);     // Верхний левый
            glEnd();

            //(Левая)
            glBegin(GL_LINES);
            glVertex3f( x,      y,       -24.9f);     // Верхний правый угол квадрата
            glVertex3f( x,      y,       -25.9f);     // Верхний левый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x,      y + 1,   -25.9f);     // Нижний левый
            glVertex3f( x,      y + 1,   -24.9f);     // Нижний правый
            glEnd();

            glBegin(GL_LINES);
            glVertex3f( x,      y,       -24.9f);     // Верхний правый угол квадрата
            glVertex3f( x,      y + 1,   -24.9f);     // Нижний правый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x,      y + 1,   -25.9f);     // Нижний левый
            glVertex3f( x,      y,       -25.9f);     // Верхний левый
            glEnd();

             //(Правая)
            glBegin(GL_LINES);
            glVertex3f( x + 1,   y,       -25.9f);     // Верхний правый угол квадрата
            glVertex3f( x + 1,   y,       -24.9f);     // Верхний левый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x + 1,   y + 1,   -24.9f);     // Нижний левый
            glVertex3f( x + 1,   y + 1,   -25.9f);     // Нижний правый
            glEnd();

            glBegin(GL_LINES);
            glVertex3f( x + 1,   y,       -25.9f);     // Верхний правый угол квадрата
            glVertex3f( x + 1,   y + 1,   -25.9f);     // Нижний правый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x + 1,   y,       -24.9f);     // Верхний левый
            glVertex3f( x + 1,   y + 1,   -24.9f);     // Нижний левый
            glEnd();

            //(Верхняя)
            glBegin(GL_LINES);
            glVertex3f( x + 1,  y,   -25.9f);         // Верхний правый угол квадрата
            glVertex3f( x,      y,   -25.9f);         // Верхний левый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x,      y,   -25.1f);         // Нижний левый
            glVertex3f( x + 1,  y,   -25.1f);         // Нижний правый
            glEnd();

            glBegin(GL_LINES);
            glVertex3f( x + 1,  y,   -25.9f);         // Верхний правый угол квадрата
            glVertex3f( x + 1,  y,   -25.1f);         // Нижний правый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x,      y,   -25.9f);         // Верхний левый
            glVertex3f( x,      y,   -25.1f);         // Нижний левый
            glEnd();

            //(Нижняя)
            glBegin(GL_LINES);
            glVertex3f( x + 1,  y + 1,   -25.1f);     // Верхний правый угол квадрата
            glVertex3f( x,      y + 1,   -25.1f);     // Верхний левый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x,      y + 1,   -25.9f);     // Нижний левый
            glVertex3f( x + 1,  y + 1,   -25.9f);     // Нижний правый
            glEnd();

            glBegin(GL_LINES);
            glVertex3f( x + 1,  y + 1,   -25.1f);     // Верхний правый угол квадрата
            glVertex3f( x + 1,  y + 1,   -25.9f);     // Нижний правый
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f( x,      y + 1,   -25.1f);     // Верхний левый
            glVertex3f( x,      y + 1,   -25.9f);     // Нижний левый
            glEnd();
        glEnd();


    }

}

void SDLGraph::drawSphere(double r, int lats, int longs, rect appleRect) {
    x = (appleRect.x - snake1->screenWidth/2)/50;
    y = (snake1->screenHeiht - appleRect.y - 50 - snake1->screenHeiht/2)/50; 
    x += 0.5;
    y += 0.5;
    std::cout << "APPLE x = " << x << " y = " << y << std::endl;
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0) * r;
        double zr0 =  cos(lat0) * r;
    
        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1) * r;
        double zr1 = cos(lat1) * r;
    
        glBegin(GL_LINE_STRIP); // GL_POLYGON
        for(j = 0; j <= longs; j++) {
              double lng = 2 * M_PI * (double) (j - 1) / longs;
              double x1 = cos(lng);
              double y1 = sin(lng);
    
              glNormal3f(x1 * zr0 + x, y1 * zr0 + y, z0);
              glVertex3f(x1 * zr0 + x, y1 * zr0 + y, z0);
              glNormal3f(x1 * zr1 + x, y1 * zr1 + y, z1);
              glVertex3f(x1 * zr1 + x, y1 * zr1 + y, z1);
           }
          glEnd();
      }
  }

void SDLGraph::drawApple3D(rect appleRect) {
    // x = (appleRect.x - snake1->screenWidth/2)/50;
    // y = (snake1->screenHeiht - appleRect.y - snake1->screenHeiht/2)/50; 
     //glTranslatef(0.0f, 0.0f, 0.0f);    // Сдвинуть вглубь экрана

       // glBegin(GL_QUADS); 
        // glColor3f(0.0f, 0.4f, 0.0f);              // Синяя сторона (Верхняя)
        // glVertex3f( x + 1,  y,   -26.0f);         // Верхний правый угол квадрата
        // glVertex3f( x,      y,   -26.0f);         // Верхний левый
        // glVertex3f( x,      y,   -25.0f);         // Нижний левый
        // glVertex3f( x + 1,  y,   -25.0f);         // Нижний правый

        // glColor3f(0.0f, 0.4f, 0.0f);              // Оранжевая сторона (Нижняя)
        // glVertex3f( x + 1,  y + 1,   -25.0f);     // Верхний правый угол квадрата
        // glVertex3f( x,      y + 1,   -25.0f);     // Верхний левый
        // glVertex3f( x,      y + 1,   -26.0f);     // Нижний левый
        // glVertex3f( x + 1,  y + 1,   -26.0f);     // Нижний правый
        
        // glColor3f(0.0f, 1.0f, 0.0f);              // Красная сторона (Передняя)
        // glVertex3f( x + 1,  y,       -25.0f);     // Верхний правый угол квадрата
        // glVertex3f( x,      y,       -25.0f);     // Верхний левый
        // glVertex3f( x,      y + 1,   -25.0f);     // Нижний левый
        // glVertex3f( x + 1,  y + 1,   -25.0f);     // Нижний правый

    // romb
        // glColor3f(0.0f, 1.0f, 0.0f);              // Красная сторона (Передняя)
        // glVertex3f( x + 0.5,  y,       -25.0f);     // Верхний правый угол квадрата
        // glVertex3f( x,      y + 0.5,       -25.0f);     // Верхний левый
        // glVertex3f( x + 0.5, y + 1,   -25.0f);     // Нижний левый
        // glVertex3f( x + 1,  y + 0.5,   -25.0f);     // Нижний правый

        // glColor3f(0.0f, 0.5f, 0.0f);              // Желтая сторона (Задняя)
        // glVertex3f( x + 1,  y + 1,   -26.0f);     // Верхний правый угол квадрата
        // glVertex3f( x,      y + 1,   -26.0f);     // Верхний левый
        // glVertex3f( x,      y,       -26.0f);     // Нижний левый
        // glVertex3f( x + 1,  y,       -26.0f);     // Нижний правый
        // // тень
        // glColor3f(0.0f, 0.2f, 0.2f);              // // тень
        // glVertex3f( x + 1,  y + 1,   -27.0f);     // Верхний правый угол квадрата
        // glVertex3f( x,      y + 1,   -27.0f);     // Верхний левый
        // glVertex3f( x,      y,       -27.0f);     // Нижний левый
        // glVertex3f( x + 1,  y,       -27.0f);     // Нижний правый

        // glColor3f(0.0f, 0.6f, 0.0f);              // Синяя сторона (Левая)
        // glVertex3f( x,      y,       -25.0f);     // Верхний правый угол квадрата
        // glVertex3f( x,      y,       -26.0f);     // Верхний левый
        // glVertex3f( x,      y + 1,   -26.0f);     // Нижний левый
        // glVertex3f( x,      y + 1,   -25.0f);     // Нижний правый

        // glColor3f(0.0f, 0.6f, 0.0f);               // Фиолетовая сторона (Правая)
        // glVertex3f( x + 1,   y,       -26.0f);     // Верхний правый угол квадрата
        // glVertex3f( x + 1,   y,       -25.0f);     // Верхний левый
        // glVertex3f( x + 1,   y + 1,   -25.0f);     // Нижний левый
        // glVertex3f( x + 1,   y + 1,   -26.0f);     // Нижний правый
        // glEnd();

    //sphera
    glShadeModel(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    // drawSphere(3, 25, 50);   // sphere
    glTranslatef(0, 0, -25.5f);
    drawSphere(0.5, 15, 15, appleRect);
    //shadow
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0, 0, -1.0f);
    drawSphere(0.5, 15, 15, appleRect);

}


void        SDLGraph::drawFrame() {
    
    x1 = (snake1->screenWidth/2 - 25)/50;
    y1 = (snake1->screenHeiht/2 - 25)/50;

    glBegin(GL_LINES);
    glVertex3f(  x1,  y1,  -0.5);     // Верхний правый угол квадрата  *----*
    glVertex3f( -x1,  y1,  -0.5);     // Верхний левый                 |    |
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3f( -x1,  y1,  -0.5);     // Верхний левый                 *-
    glVertex3f( -x1, -y1,  -0.5);     // Нижний левый                  | 
    glEnd();                               //                               *-

    glBegin(GL_LINES);
    glVertex3f( -x1, -y1,  -0.5);     // Нижний левый                  |    |
    glVertex3f(  x1, -y1,  -0.5);     // Нижний правый                 *----*
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(  x1, -y1,  -0.5);     // Верхний правый угол квадрата  -*
    glVertex3f(  x1,  y1,  -0.5);     // Нижний правый                  |
    glEnd();                               //                               -*
}

void        SDLGraph::draw(rect appleRect) {

    setKeyDownRotate();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // glTranslatef(0.0f, 0.0f, -50.0f);    // Сдвинуть вглубь экрана

    glColor3f(1.0f, 1.0f, 0.0f);        // Красная сторона (Передняя)


    // ramo4ka
    
    // SDL_RenderDrawLine(gRenderer, 50, 50, 50, snake1->screenHeiht - 50);
    // SDL_RenderDrawLine(gRenderer, 50, 50, snake1->screenWidth - 50, 50);
    // SDL_RenderDrawLine(gRenderer, snake1->screenWidth - 50, 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);
    // SDL_RenderDrawLine(gRenderer, 50, snake1->screenHeiht - 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);
    

    // SDL_RenderCopy(gRenderer, appleTexture, NULL, &rectForSDL);

    // renderText(("SCORE = " + std::to_string(snake1->size)).c_str(), 50, 10, false);

    // for (int i = 50 - 50/2 - 20/50; i < (50 - snake1->screenWidth/2)/50 - 20/50; i++ ) {
    //     glVertex2f(i, (50 - snake1->screenWidth/2)/50 - 20/50);
    // }

    drawSnake3D();
    drawApple3D(appleRect);
    drawFrame();






    //рамка

    



    // glBegin(GL_LINES);
    // glColor3f(1.0f, 1.0f, 1.0f);     // Красная сторона (Передняя)
    // glVertex3f( 1.0f,  1.0f, -7.0f);     // Верхний правый угол квадрата
    // glVertex3f(-1.0f,  1.0f, -7.0f);     // Верхний левый
    // glVertex3f(-1.0f, -1.0f, -7.0f);     // Нижний левый
    // glVertex3f( 1.0f, -1.0f, -7.0f);     // Нижний правый
    // glEnd();
        
        //drawFrame();
        // glVertex3f( (snake1->snakeRect[i].x + 50 -  snake1->screenWidth/2)/50 + 20/50, (snake1->screenHeiht - snake1->snakeRect[i].y -      snake1->screenHeiht/2)/50 + 20/50, -25.0f);     // Верхний правый угол квадрата
        // glVertex3f( (snake1->snakeRect[i].x -       snake1->screenWidth/2)/50 + 20/50, (snake1->screenHeiht - snake1->snakeRect[i].y -      snake1->screenHeiht/2)/50 + 20/50, -25.0f);     // Верхний левый
        // glVertex3f( (snake1->snakeRect[i].x -       snake1->screenWidth/2)/50 + 20/50, (snake1->screenHeiht - snake1->snakeRect[i].y + 50 - snake1->screenHeiht/2)/50 + 20/50, -25.0f);     // Нижний левый
        // glVertex3f( (snake1->snakeRect[i].x + 50 -  snake1->screenWidth/2)/50 + 20/50, (snake1->screenHeiht - snake1->snakeRect[i].y + 50 - snake1->screenHeiht/2)/50 + 20/50, -25.0f);     // Нижний правый

    // if (multiplayer) {
    //     for (int i = 0; i < snake2->snakeRect.size(); i++) {
    //         rectForSDL = toSDLRect(snake2->snakeRect[i]);
    //         SDL_RenderCopy(gRenderer, snake2Texture, NULL, &rectForSDL);
    //     }
    //     renderText(("SCORE = " + std::to_string(snake2->size)).c_str(), snake2->screenWidth - 250, 10, false);
    // }

    // glEnd();
    SDL_GL_SwapWindow(window);
}

void    SDLGraph::handleEvent() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                setKeyDown(); break ;
            case SDL_QUIT:
                close("exit");
        }
    }
}

bool        SDLGraph::windIsOpen() {
    return (!quit);
}

extern "C" IGraph *createGraph(Snake *s1, Snake *s2) {
    return (new SDLGraph(s1, s2));
}

extern "C"  void destroyGraph(IGraph *graph) {
    delete graph;
}

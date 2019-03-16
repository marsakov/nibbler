#include "OpenGLGraph.hpp"

OpenGLGraph::OpenGLGraph() {
	key = none;
	quit = false;
	snake1->direction = 'R';
	snake1->size = 1;
	iter = 0;
	init();
}

OpenGLGraph::OpenGLGraph(Snake *s1, Snake *s2) {
	std::cout << "OpenGLGraph" << std::endl;
	snake1 = s1;
	snake2 = s2;
	key = none;
	quit = false;
	xrf = 0, yrf = 0, zrf = 0; // углы поворота
	D3 = false;
	y3 = 0;
	iter = 0;
	init();
}

OpenGLGraph::OpenGLGraph(OpenGLGraph &obj) {
	*this = obj;
}

OpenGLGraph::~OpenGLGraph() {

	SDL_DestroyWindow(window);
	SDL_Quit();
}

eKeyType    OpenGLGraph::getKey() { return (key); }
void        OpenGLGraph::setKey(eKeyType k) { key = k; }


void        OpenGLGraph::init() {

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

	SDL_GL_CreateContext(window); // создаем контекст OpenGL

	if(window == NULL){ // если не получилось создать окно, то выходим
		exit(1);
	}

	// Инициализация OpenGL

	glClearColor(0.33f, 0.33f, 0.32f, 0.0f); // устанавливаем фоновый цвет на черный
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float) snake1->screenWidth / (float) snake1->screenHeiht, 0.1f, 100.0f); // настраиваем трехмерную перспективу
	glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим

}

int         OpenGLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~OpenGLGraph();
	exit(1);
	return (0);
}

void        OpenGLGraph::setKeyDown() {
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
		case SDLK_4:        { D3 ? D3 = false : D3 = true; break; }
		case SDLK_m:		{ key = mute; break; }
		default:            { key = none; break; }
	}
}

void        OpenGLGraph::renderText(const char *text, int x, int y, bool selection) {
	if (selection)
		glColor3f(0.97f, 0.14f, 0.45f);
	else 
		glColor3f(0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x,y);
	for(int i=0; i < (int)strlen(text); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void        OpenGLGraph::drawMenu(int buttonNum, bool start, bool network, int speed) {
	
	if (snake1->waiting)
		iter = (iter == 45) ? 1 : iter + 1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(5);

	glTranslatef(0.0f, 0.0f, -20.0f);

	if (start && !network && !snake1->waiting)
		renderText("CONTINUE", -20, 20, (buttonNum == 1) ? true : false);
	else if (snake1->waiting){
		renderText("********************", -20, 20, false);
		renderText("*", -20 + iter, 20, true);
	}
	if (snake1->muteVar)
		renderText(("MUTE"), -20, 90, false);
	renderText("NEW GAME", -20, 10, (buttonNum == 2) ? true : false);
	renderText((std::string("MULTIPLAYER ") + (snake1->multiplayer ? (snake1->network ? "NET" : "LOCAL") : "OFF")).c_str(), -20, 0, (buttonNum == 3) ? true : false);
	renderText("EXIT", -20, -10, (buttonNum == 4) ? true : false);
	renderText(("SPEED  " + std::to_string(speed)).c_str(), -20, 80, false);
	glutSwapBuffers();
	drawFrameMenu();
	SDL_GL_SwapWindow(window);
}

void		OpenGLGraph::drawGameOver(int winner, rect boomRect) {

	boomRect.x = 0;
	glPointSize(5);

	glTranslatef(0.0f, 0.0f, -20.0f);

	renderText("GAME OVER", -20, 10, false);
	if (snake1->multiplayer) {
		renderText(("Snake1 SCORE " + std::to_string(snake1->size)).c_str(), -20, 0, (winner == 1) ? true : false);
		renderText(("Snake2 SCORE " + std::to_string(snake2->size)).c_str(), -20, -10, (winner == 2) ? true : false);
	}
	else
		renderText(("Snake1 SCORE " + std::to_string(snake1->size)).c_str(), -20, 0, true);
	
	glutSwapBuffers();
	SDL_GL_SwapWindow(window);
}

void	OpenGLGraph::drawCube(rect snakeRect, rect snakeColor, int i) {
	x = (snakeRect.x - snake1->screenWidth/2)/50;
	y = (snake1->screenHeiht - snakeRect.y - 50 - snake1->screenHeiht/2 + y3)/50; 
   
	glBegin(GL_QUADS); 
	glColor3f((snakeColor.r + i*0.03)*0.6, (snakeColor.g + i*0.03)*0.6, (snakeColor.b + i*0.03)*0.6);              // Синяя сторона (Верхняя)
	glVertex3f( x - 0.08 + 1,  y + 0.08,   -26.0f);         // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,   -26.0f);         // Верхний левый
	glVertex3f( x + 0.08,      y + 0.08,   -25.0f);         // Нижний левый
	glVertex3f( x - 0.08 + 1,  y + 0.08,   -25.0f);         // Нижний правый

	glColor3f((snakeColor.r + i*0.03)*0.6, (snakeColor.g + i*0.03)*0.6, (snakeColor.b + i*0.03)*0.6);              // Оранжевая сторона (Нижняя)
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -26.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -26.0f);     // Нижний правый

	// (snakeColor.r + i*0.03), (snakeColor.g + i*0.03), (snakeColor.b + i*0.03)
	glColor3f((snakeColor.r + i*0.03), (snakeColor.g + i*0.03), (snakeColor.b + i*0.03));              // Красная сторона (Передняя) ///////////////////////////
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -25.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,       -25.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.0f);     // Нижний правый

	glColor3f((snakeColor.r + i*0.03)*0.4, (snakeColor.g + i*0.03)*0.4, (snakeColor.b + i*0.03)*0.4);              // Желтая сторона (Задняя)
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -26.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -26.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y + 0.08,       -26.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -26.0f);     // Нижний правый
	// тень
	glColor3f(0.2f, 0.2f, 0.2f);              // // тень
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -27.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -27.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y + 0.08,       -27.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -27.0f);     // Нижний правый

	glColor3f((snakeColor.r + i*0.03)*0.5, (snakeColor.g + i*0.03)*0.5, (snakeColor.b + i*0.03)*0.5);              // Синяя сторона (Левая)
	glVertex3f( x + 0.08,      y + 0.08,       -25.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,       -26.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -26.0f);     // Нижний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.0f);     // Нижний правый

	glColor3f((snakeColor.r + i*0.03)*0.5, (snakeColor.g + i*0.03)*0.5, (snakeColor.b + i*0.03)*0.5);               // Фиолетовая сторона (Правая)
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -26.0f);     // Верхний правый угол квадрата
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -25.0f);     // Верхний левый
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -26.0f);     // Нижний правый

	glEnd();
}

void	OpenGLGraph::drawCubeFrame(rect snakeRect) {
	x = (snakeRect.x - snake1->screenWidth/2)/50;
	y = (snake1->screenHeiht - snakeRect.y - 50 - snake1->screenHeiht/2 + y3)/50; 
   
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	//передняя
	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -24.9f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,       -24.9f);     // Верхний левый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -24.9f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -24.9f);     // Нижний правый
	glEnd();

	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -24.9f);     // Верхний правый угол квадрата
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -24.9f);     // Нижний правый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -24.9f);     // Нижний левый
	glVertex3f( x + 0.08,      y + 0.08,       -24.9f);     // Верхний левый
	glEnd();

	//(Левая)
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y + 0.08,       -24.9f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,       -25.9f);     // Верхний левый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.9f);     // Нижний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -24.9f);     // Нижний правый
	glEnd();

	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y + 0.08,       -24.9f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -24.9f);     // Нижний правый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.9f);     // Нижний левый
	glVertex3f( x + 0.08,      y + 0.08,       -25.9f);     // Верхний левый
	glEnd();

	 //(Правая)
	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,   y + 0.08,       -25.9f);     // Верхний правый угол квадрата
	glVertex3f( x - 0.08 + 1,   y + 0.08,       -24.9f);     // Верхний левый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,   y - 0.08 + 1,   -24.9f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,   y - 0.08 + 1,   -25.9f);     // Нижний правый
	glEnd();

	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,   y + 0.08,       -25.9f);     // Верхний правый угол квадрата
	glVertex3f( x - 0.08 + 1,   y - 0.08 + 1,   -25.9f);     // Нижний правый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,   y + 0.08,       -24.9f);     // Верхний левый
	glVertex3f( x - 0.08 + 1,   y - 0.08 + 1,   -24.9f);     // Нижний левый
	glEnd();

	//(Верхняя)
	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,  y + 0.08,   -25.9f);         // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,   -25.9f);         // Верхний левый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y + 0.08,   -25.1f);         // Нижний левый
	glVertex3f( x - 0.08 + 1,  y + 0.08,   -25.1f);         // Нижний правый
	glEnd();

	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,  y + 0.08,   -25.9f);         // Верхний правый угол квадрата
	glVertex3f( x - 0.08 + 1,  y + 0.08,   -25.1f);         // Нижний правый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y + 0.08,   -25.9f);         // Верхний левый
	glVertex3f( x + 0.08,      y + 0.08,   -25.1f);         // Нижний левый
	glEnd();

	//(Нижняя)
	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.1f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.1f);     // Верхний левый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.9f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.9f);     // Нижний правый
	glEnd();

	glBegin(GL_LINES);
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.1f);     // Верхний правый угол квадрата
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.9f);     // Нижний правый
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.1f);     // Верхний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.9f);     // Нижний левый
	glEnd();
	glEnd();
}


void  OpenGLGraph::drawSnake3D() {
   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	

	if (snake1->screenWidth > snake1->screenHeiht) {
		k = (snake1->screenHeiht - 800) * 0.024;
		glTranslatef(0.0f, 0.0f, 6 - k);
	}
	else {
		k = (snake1->screenHeiht - 1000) * 0.0245; 
		glTranslatef(0.0f, 0.0f, 2.86 - k);
	}

	glRotatef(xrf, 1.0f, 0.0f, 0.0f);    // Вращение map по X
	
	for (int i = 0; i < (int)snake1->snakeRect.size(); i++) {

		drawCube(snake1->snakeRect[i], snake1->snakeRect[0], i);
		drawCubeFrame(snake1->snakeRect[i]);
	}

	if (snake1->multiplayer) {
		for (int i = 0; i < (int)snake2->snakeRect.size(); i++) {
			drawCube(snake2->snakeRect[i], snake2->snakeRect[0], i);
			drawCubeFrame(snake2->snakeRect[i]);
		}
	}
}

void OpenGLGraph::drawSphere(double r, int lats, int longs, rect appleRect) {
	x = (appleRect.x - snake1->screenWidth/2)/50;
	y = (snake1->screenHeiht - appleRect.y - 50 - snake1->screenHeiht/2 + y3)/50; 
	x += 0.5;
	y += 0.5;

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

void 		OpenGLGraph::drawApple3DSphera(rect appleRect) {
	
	//sphera
	glShadeModel(GL_LINES);
	glColor3f(appleRect.r, appleRect.g, appleRect.b);
	glTranslatef(0, 0, -25.5f);
	drawSphere(0.5, 15, 15, appleRect);
	//shadow
	glColor3f(0.2f, 0.2f, 0.2f);
	glTranslatef(0, 0, -1.0f);
	drawSphere(0.4, 15, 15, appleRect);

}

void        OpenGLGraph::drawApple3DCube(rect appleRect) {

	x = (appleRect.x - snake1->screenWidth/2)/50;
	y = (snake1->screenHeiht - appleRect.y - 50 - snake1->screenHeiht/2 + y3)/50; 

	glBegin(GL_QUADS); 
	glColor3f(appleRect.r/1.4, appleRect.g/1.4, appleRect.b/1.4);              // Синяя сторона (Верхняя)
	glVertex3f( x - 0.08 + 1,  y + 0.08,   -26.0f);         // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,   -26.0f);         // Верхний левый
	glVertex3f( x + 0.08,      y + 0.08,   -25.0f);         // Нижний левый
	glVertex3f( x - 0.08 + 1,  y + 0.08,   -25.0f);         // Нижний правый

	glColor3f(appleRect.r/1.4, appleRect.g/1.4, appleRect.b/1.4);              // Оранжевая сторона (Нижняя)
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -26.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -26.0f);     // Нижний правый

	glColor3f(appleRect.r, appleRect.g, appleRect.b);              // Красная сторона (Передняя)
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -25.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,       -25.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -25.0f);     // Нижний правый

	glColor3f(appleRect.r/5, appleRect.g/5, appleRect.b/5);              // Желтая сторона (Задняя)
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -26.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -26.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y + 0.08,       -26.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -26.0f);     // Нижний правый
	// тень
	glColor3f(0.0f, 0.2f, 0.2f);              // // тень
	glVertex3f( x - 0.08 + 1,  y - 0.08 + 1,   -27.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -27.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y + 0.08,       -27.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,  y + 0.08,       -27.0f);     // Нижний правый

	glColor3f(appleRect.r*0.5, appleRect.g*0.5, appleRect.b*0.5);              // Синяя сторона (Левая)
	glVertex3f( x + 0.08,      y + 0.08,       -25.0f);     // Верхний правый угол квадрата
	glVertex3f( x + 0.08,      y + 0.08,       -26.0f);     // Верхний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -26.0f);     // Нижний левый
	glVertex3f( x + 0.08,      y - 0.08 + 1,   -25.0f);     // Нижний правый

	glColor3f(appleRect.r*0.5, appleRect.g*0.5, appleRect.b*0.5);               // Фиолетовая сторона (Правая)
	glVertex3f( x - 0.08 + 1,   y + 0.08,       -26.0f);     // Верхний правый угол квадрата
	glVertex3f( x - 0.08 + 1,   y + 0.08,       -25.0f);     // Верхний левый
	glVertex3f( x - 0.08 + 1,   y - 0.08 + 1,   -25.0f);     // Нижний левый
	glVertex3f( x - 0.08 + 1,   y - 0.08 + 1,   -26.0f);     // Нижний правый
	glEnd();
	glTranslatef(0, 0, -26.5f);


}

void        OpenGLGraph::drawFrameMenu() {
	
	x1 = (snake1->screenWidth/2 - 25)/50;
	y1 = (snake1->screenHeiht/2 - 25)/50;
	z1 = -19.35 - (snake1->screenHeiht - 800) * 0.0241;

	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex3f(  x1,  y1,  z1);     // Верхний правый угол квадрата  *----*
	glVertex3f( -x1,  y1,  z1);     // Верхний левый                 |    |
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( -x1,  y1,  z1);     // Верхний левый               *-
	glVertex3f( -x1, -y1,  z1);     // Нижний левый                | 
	glEnd();                        //                             *-

	glBegin(GL_LINES);
	glVertex3f( -x1, -y1,  z1);     // Нижний левый                  |    |
	glVertex3f(  x1, -y1,  z1);     // Нижний правый                 *----*
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(  x1, -y1,  z1);       // Верхний правый угол квадрата  -*
	glVertex3f(  x1,  y1,  z1);       // Нижний правый                  |
	glEnd();                          //                               -*
}

void        OpenGLGraph::drawFrame2D() {
	
	x1 = (snake1->screenWidth/2 - 25)/50;
	y1 = (snake1->screenHeiht/2 - 50 + y3)/50;

	// y = (snake1->screenHeiht - snakeRect.y - 50 - snake1->screenHeiht/2 + y3)/50;

	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex3f(  x1,  y1,  -0.5);     // Верхний правый угол квадрата  *----*
	glVertex3f( -x1,  y1,  -0.5);     // Верхний левый                 |    |
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( -x1,  y1,  -0.5);     // Верхний левый                 *-
	glVertex3f( -x1, -y1,  -0.5);     // Нижний левый                  | 
	glEnd();                          //                               *-

	glBegin(GL_LINES);
	glVertex3f( -x1, -y1,  -0.5);     // Нижний левый                  |    |
	glVertex3f(  x1, -y1,  -0.5);     // Нижний правый                 *----*
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(  x1, -y1,  -0.5);     // Верхний правый угол квадрата  -*
	glVertex3f(  x1,  y1,  -0.5);     // Нижний правый                  |
	glEnd();                          //                               -*
}

void        OpenGLGraph::drawFrame3D() {

	x1 = (snake1->screenWidth/2 - 25)/50; // 2500 
	y1 = (snake1->screenHeiht/2 - 25 + 1300)/50; // 1300 || 800

	y2 = (snake1->screenHeiht/2 + 550 - (snake1->screenHeiht - 800))/50;  // 1300

	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex3f(  x1,  y1,  -0.5);     // Верхний правый угол квадрата  *----*
	glVertex3f( -x1,  y1,  -0.5);     // Верхний левый                 |    |
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f( -x1,  y1,  -0.5);     // Верхний левый                 *-
	glVertex3f( -x1, y2,  -0.5);        // Нижний левый                | 
	glEnd();                          //                               *-

	glBegin(GL_LINES);
	glVertex3f( -x1, y2,  -0.5);     // Нижний левый                  |    |
	glVertex3f(  x1, y2,  -0.5);     // Нижний правый                 *----*
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(  x1, y2,  -0.5);   // Верхний правый угол квадрата  -*
	glVertex3f(  x1,  y1,  -0.5);     // Нижний правый                  |
	glEnd();                          //                               -*
}

void        OpenGLGraph::draw(rect appleRect) {

	// setKeyDownRotate();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 0.0f);        // Красная сторона (Передняя)


	drawSnake3D();
	if (appleRect.s == 1) {
		drawApple3DSphera(appleRect);
	}
	else {
		drawApple3DCube(appleRect);
	}
	if (!D3) {
		y3 = 0;
		xrf = 0;
		drawFrame2D();
	}
	else if (D3) {
		y3 = 1300;
		xrf = -50;
		drawFrame3D();
	}

	renderText(("SCORE " + std::to_string(snake1->size)).c_str(), -80, 90, false);
	if (snake1->multiplayer)
		renderText(("SCORE " + std::to_string(snake2->size)).c_str(), 60, 90, false);
	if (snake1->muteVar)
		renderText(("MUTE"), -20, 90, false);
	SDL_GL_SwapWindow(window);

}

void	OpenGLGraph::handleEvent() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				setKeyDown(); break ;
			case SDL_QUIT:
				close("exit");
		}
	}
}

bool        OpenGLGraph::windIsOpen() {
	return (!quit);
}

extern "C" IGraph *createGraph(Snake *s1, Snake *s2) {
	return (new OpenGLGraph(s1, s2));
}

extern "C"  void destroyGraph(IGraph *graph) {
	delete graph;
}

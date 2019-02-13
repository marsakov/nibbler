#include "../inc/OpenGLGraph.hpp"

GLfloat x = 0;
GLfloat y = 0;
GLfloat rsize = 10;

GLfloat xstep = 10; // Step size in x and y directions
GLfloat ystep = 10; // (number of pixels to move each time)

GLfloat windowWidth; // Keep track of windows changing width and height
GLfloat windowHeight;

OpenGLGraph::OpenGLGraph() {
	key = none;
	quit = false;
	snake1->direction = 'R';
	snake1->size = 1;
	init();
}

OpenGLGraph::OpenGLGraph(Snake *s1, Snake *s2) {
	std::cout << "OpenGLGraph" << std::endl;
	snake1 = s1;
	snake2 = s2;
	key = none;
	std::cout << "w = " << snake1->screenWidth << " h = " << snake1->screenHeiht << std::endl;
	quit = false;
	init();
}

OpenGLGraph::OpenGLGraph(OpenGLGraph &obj) {
	*this = obj;
}

OpenGLGraph::~OpenGLGraph() {

}

void		OpenGLGraph::setMultiplayer(bool m) { multiplayer = m; }
eKeyType	OpenGLGraph::getKey() { return (key); }
void		OpenGLGraph::setKey(eKeyType k) { key = k; }

void Keyboard(unsigned char key, int xx, int yy)
{
#define ESCAPE '\033'

    switch(key) {
        case ESCAPE: std::cout << "ESCAPE" << std::endl; exit(0); break ;
        case '1': std::cout << "case 1" << std::endl; break ;
        case '2': std::cout << "case 2" << std::endl; break ;
        case '3': std::cout << "case 3" << std::endl; break ;
    }
}

void keyboard(int key, int xx, int yy) {

     switch(key) {
        case GLUT_KEY_UP: y += ystep; std::cout << "y " << y << std::endl;  break ;
        case GLUT_KEY_DOWN: y -= ystep; std::cout << "y " << y << std::endl;  break ;
        case GLUT_KEY_LEFT: x -= xstep; std::cout << "x " << x << std::endl;  break ;
        case GLUT_KEY_RIGHT: x += xstep; std::cout << "x " << x << std::endl;  break ;
    }
}

int			OpenGLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~OpenGLGraph();
	exit(1);
	return (0);
}

void TimerFunction(int value)
{
    glutPostRedisplay();   // Redraw the scene with new coordinates
    glutTimerFunc(33,TimerFunction, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat aspectRatio;

    if (h == 0)  // Prevent a divide by zero
        h = 1;  
    glViewport(0, 0, w, h); // Set Viewport to window dimensions
    glMatrixMode(GL_PROJECTION); // Reset coordinate system
    glLoadIdentity();
    aspectRatio = (GLfloat)w / (GLfloat)h; // Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) {
      	windowWidth = 100;
       	windowHeight = 100 / aspectRatio;
        glOrtho (-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
    }
    else {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
        glOrtho (-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
    glLoadIdentity();
}

void		OpenGLGraph::setKeyDown() {
	// switch( event.key.keysym.sym )
	// {
	// 	case SDLK_w:		{ key = w; break; }
	// 	case SDLK_s:		{ key = s; break; }
	// 	case SDLK_a:		{ key = a; break; }
	// 	case SDLK_d:		{ key = d; break; }
	// 	case SDLK_UP:		{ key = up; break; }
	// 	case SDLK_DOWN:		{ key = down; break; }
	// 	case SDLK_LEFT:		{ key = left; break; }
	// 	case SDLK_RIGHT:	{ key = right; break; }
	// 	case SDLK_ESCAPE:	{ key = escape; break; }
	// 	case SDLK_RETURN:	{ key = enter; break; }
	// 	case SDLK_1:		{ key = num1; break; }
	// 	case SDLK_2:		{ key = num2; break; }
	// 	case SDLK_3:		{ key = num3; break; }
	// 	default:			{ key = none; break; }
	// }
}

// void		OpenGLGraph::renderText(const char *text, int x, int y, bool selection) {

   
// }

void		OpenGLGraph::drawMenu(int buttonNum, bool start, int speed) {

	
}

void	OpenGLGraph::draw(rect appleRect) {

}

void	OpenGLGraph::draw1() {
	
	glClear(GL_COLOR_BUFFER_BIT); // Clear the window with current clearing color
    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.0f, 1.0f, 1.0f); // Set snake color   R     G     B
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // Set background color

	for (int i = 0; i < snake1->snakeRect.size(); i++) {
		x = snake1->snakeRect[i].x;
		y = snake1->snakeRect[i].y;
		glRectf(x, y, x + rsize, y - rsize);
	}
	glRectf(x, y, x + rsize, y - rsize);
    glutSwapBuffers();  // Flush drawing commands and swap
}

void		OpenGLGraph::init() {

	 ac = 3;
    av[0] = (char*)"nibbler";
    av[1] =  (char*)std::to_string(snake1->screenWidth).c_str();
    av[2] =  (char*)std::to_string(snake1->screenHeiht).c_str();
    glutInit(&ac, av);//

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//
    glutInitWindowSize(snake1->screenWidth, snake1->screenHeiht);//
    glutCreateWindow("Snake");//
    std::cout << "snake1->snakeRect.size() = " << snake1->snakeRect.size() << std::endl;
    glutDisplayFunc(draw1);//


    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(33, TimerFunction, 1);
    glutMainLoop();
}


void	OpenGLGraph::handleEvent() {
	
}

bool		OpenGLGraph::windIsOpen() {
	return (!quit);
}

extern "C" IGraph *createGraph(Snake *s1, Snake *s2) {
	return (new OpenGLGraph(s1, s2));
}

extern "C"	void destroyGraph(IGraph *graph) {
	delete graph;
}

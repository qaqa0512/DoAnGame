#include "Dependencies\freeglut\glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include<time.h>
#include <sys/timeb.h>
#include <sys/utime.h>


#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 900

#define TIMER_PERIOD  50 // thởi gian cho bộ đếm thời gian
#define TIMER_ON         1 //0: tắt hẹn giờ, 1: bật hẹn giờ

#define D2R 0.0174532


typedef struct {
	int x; //giá trị x của các đối tượng chuyển động
	int y; //giá trị y của các đối tượng chuyển động
	bool initialized; //nó được sử dụng để cung cấp cho các vật thể chuyển động ngẫu nhiên khi chúng chạm đích hoặc trúng tên lửa

	bool countChecker = false; //để đếm tổng ufos
}ufo_t;

int carx = 0, v = 0;
int rev = 1;


int rocketx = carx; //giá trị x của đối tượng được bắn
int rockety = 0;//giá trị y của đối tượng được bắn
bool shooted = false;//để kiểm tra xem đối tượng
					 //có bị bắn hay không để di chuyển nó vì khi không bị bắn nó đi cùng chiều với ô tô nhưng khi bị bắn nó có giá trị x và y riêng
bool rocketFire = false; //lửa xuất hiện và biến mất


bool gameStart = false; //bắt đầu game với <F1>
ufo_t ufo[5];


int score = 0; // điểm đạt được bằng cách bắn ufos
int totalUfos = 0; // số lượng ufos hiển thị
int burstUfos = 0; // số lượng ufo bị bắn
int lastPoint = 0;//điểm cuối cùng đạt được bằng cách bắn ufos

int timer = 2000;//thời gian hẹn giờ để bắn tàu vũ trụ
bool gameStop = false;
/*Biến toàn cục */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // chiều rộng và chiều cao cửa sổ hiện tại

						  //
						  // để vẽ đường tròn, tâm tại (x, y)
						  // bán kính r
						  //
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}
void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}

void print(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}
// hiển thị văn bản với các biến.
void vprint(int x, int y, void *font, char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

//
//Để hiển thị trên cửa sổ bằng các lệnh OpenGL

//
//Vẽ UFO 

void drawUfo(int x, int y) {

	glColor3ub(72, 61, 139);
	circle(x, y - 10, 25);


	glBegin(GL_QUADS);
	glColor3ub(220, 220, 220);
	glVertex2f(-25 + x, y);
	glVertex2f(-75 + x, -35 + y);
	glColor3ub(105, 105, 105);
	glVertex2f(+75 + x, -35 + y);
	glVertex2f(+25 + x, y);
	glEnd();

	glColor3f(0, 0, 0);
	circle(-35 + x, -17.5 + y, 7);
	glColor3f(1, 0, 0);

	circle(-35 + x, -17.5 + y, 5);

	glColor3f(0, 0, 0);
	circle(-0 + x, -17.5 + y, 7);
	glColor3f(0, 1, 0);

	circle(-0 + x, -17.5 + y, 5);

	glColor3f(0, 0, 0);
	circle(+35 + x, -17.5 + y, 7);
	glColor3f(0, 0, 1);

	circle(+35 + x, -17.5 + y, 5);



}



void fire(int x) {
	glColor3ub(255, 69, 0);
	circle(x, -245 + rockety, 10);
	glColor4f(1, 1, 0, 0.5);
	circle(x, -245 + rockety, 15);
}
void displayRocket(int x) {
	glColor3f(1, 0, 0);
	circle(x, -190 + rockety, 15); // phần đầu


	if (rocketFire)
		fire(x);

	glColor3ub(47, 79, 79);
	glRectf(-15 + x, -190 + rockety, +15 + x, -240 + rockety); // phần thân tên lửa



	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);//cách
					  //tría 
	glVertex2f(-15 + x, -215 + rockety);
	glVertex2f(-25 + x, -221 + rockety);
	glVertex2f(-25 + x, -230 + rockety);
	glVertex2f(-15 + x, -230 + rockety);
	//phải
	glVertex2f(+15 + x, -215 + rockety);
	glVertex2f(+25 + x, -221 + rockety);
	glVertex2f(+25 + x, -230 + rockety);
	glVertex2f(+15 + x, -230 + rockety);
	glEnd();

	glColor3ub(112, 128, 144);
	glBegin(GL_QUADS);
	glVertex2f(-15 + x, -240 + rockety);
	glVertex2f(-10 + x, -245 + rockety);
	glVertex2f(+10 + x, -245 + rockety);
	glVertex2f(+15 + x, -240 + rockety);
	glEnd();
}


void displayCar() {
	glColor3ub(0, 0, 0); //lốp xe
	circle(-35 * rev + carx, -255, 20);
	circle(+35 * rev + carx, -255, 20);

	glColor3ub(248, 248, 255); //vật thể bên trong
	circle(-35 * rev + carx, -255, 10);
	circle(+35 * rev + carx, -255, 10);


	glColor3ub(27, 77, 62);
	glRectf(-70 * rev + carx, -220, +70 * rev + carx, -260); // thân hình
	glRectf(+60 * rev + carx, -225, +40 * rev + carx, -200); // cơ sở cửa sổ phía trước
	glColor3ub(138, 43, 226);
	glRectf(+56 * rev + carx, -220, +45 * rev + carx, -202); // cửa sỏ xe

	glColor3f(1, 1, 0);
	glRectf(+60 * rev + carx, -225 + v, +70 * rev + carx, -230 + v); // đèn trước

	glColor3f(1, 0, 0);
	glRectf(-60 * rev + carx, -225, -70 * rev + carx, -230); // đèn sau

	glColor3f(0, 0, 0);
	glRectf(-40 * rev + carx, -190, +40 * rev + carx, -240);

	glRectf(-20 * rev + carx, -170, +20 * rev + carx, -240);





}

//vẽ các đám mây
void displayCloud(int x, int y) {
	glColor3ub(240, 248, 255);
	circle(21 + x, -24 + y, 15);
	circle(25 + x, -7 + y, 25);
	circle(-25 + x, +5 + y, 25);
	circle(0 + x, 0 + y, 35);
}

//vẽ background 
void displayBackground() {

	//bầu trời
	glBegin(GL_QUADS);
	glColor3ub(0, 191, 255);
	glVertex2f(-600, 450);
	glVertex2f(600, 450);
	glColor3ub(240, 248, 255);
	glVertex2f(600, -450);
	glVertex2f(-600, -450);
	glEnd();

	//đất
	glBegin(GL_QUADS);
	glColor3ub(255, 222, 173);
	glVertex2f(-600, -210);
	glVertex2f(600, -210);
	glColor3ub(139, 69, 19);
	glVertex2f(600, -450);
	glVertex2f(-600, -450);
	glEnd();


	displayCloud(450, 340);
	displayCloud(250, 300);
	displayCloud(0, 340);


	displayCloud(-250, 300);
	displayCloud(-450, 340);

}


void menu() {
	glColor3f(0, 0, 0);
	glRectf(500, 600, 600, -600);

	glLineWidth(2);
	glColor3f(1, 1, 0);


	//bộ đếm thời gian tính giờ bắn
	if (timer > 0)
	{
		if (timer < 500)
		{
			glColor3f(1, 0, 0);//hiện chữ màu đỏ cho thời dưới 10 s
			if (timer % 5 != 0) {
				vprint(530, 350, GLUT_BITMAP_9_BY_15, "%02d", timer / 100/*, timer % 100*/);

			}


		}

		else
		{
			glColor3f(0, 1, 0);//hiện chữ màu xanh cho thời gian trên 10s
			vprint(530, 350, GLUT_BITMAP_9_BY_15, "%02d:%02d", timer / 100, timer % 100);

		}
	}
	else
	{
		glColor3f(1, 0, 0);
		vprint(530, 350, GLUT_BITMAP_9_BY_15, "00:00"); //bộ đếm thời gian
		vprint(2500, 200, GLUT_BITMAP_9_BY_15, "START"); //bộ đếm thời gian
		if (score >= 50 && timer / 100 == 0) {
			glColor3f(1, 0, 0);
			vprint(0, 100, GLUT_BITMAP_HELVETICA_18, "YOU WIN");
		}
		else if (score <50 && timer / 100 == 0) {
			glColor3f(1, 0, 0);
			vprint(-80, 100, GLUT_BITMAP_HELVETICA_18, "YOU LOSE");
		}

	}
	glColor3f(1, 1, 0);

	vprint(510, 200, GLUT_BITMAP_HELVETICA_18, "Total Ufos");//tổng số ufo đi qua

	vprint(540, 175, GLUT_BITMAP_9_BY_15, "%02d", totalUfos);


	vprint(510, 0, GLUT_BITMAP_HELVETICA_18, "Burst Ufos");//tổng số ufo bị bắn

	vprint(540, -25, GLUT_BITMAP_9_BY_15, "%02d", burstUfos);

	vprint(510, -100, GLUT_BITMAP_HELVETICA_18, "Last Points");//số ufo mà tên lửa đi qua trong lần đó

	vprint(540, -125, GLUT_BITMAP_9_BY_15, "%d", lastPoint);


	vprint(520, -250, GLUT_BITMAP_HELVETICA_18, "Diem");//số điếm tích lũy được
	vprint(525, -275, GLUT_BITMAP_9_BY_15, "%03d", score);


	if (!gameStart || gameStop)
		vprint(-550, -280, GLUT_BITMAP_HELVETICA_18, "Press <F1> to (re)start game");
	else
		vprint(-550, -280, GLUT_BITMAP_HELVETICA_18, "Press <F1> to stop game");
}

void display() {

	displayBackground();
	menu();

	if (!shooted)
		rocketx = carx;
	displayRocket(rocketx);


	//khoảng cách bay rocket
	if (rockety > 630) {
		shooted = false;
		rockety = 0;
		rocketFire = false;
	}

	displayCar();


	for (int i = 0; i < 5; i++)
		drawUfo(ufo[i].x, ufo[i].y);


	glutSwapBuffers();

}

void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	//để làm mới cửa sổ nó gọi hàm display ()

	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// thoát trò chơi.
	if (key == ' ' && gameStart)
		shooted = true;
	if (key == 's' || key == 'S')
		gameStart = !gameStart;

	//để làm mới cửa sổ nó gọi hàm display ()
	glutPostRedisplay();
}

int getMilliCount() {
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}
void sleep(int sleeptime)
{
	int count = 0;
	int beginsleep = getMilliCount();
	while (getMilliCount() - beginsleep < sleeptime)
	{
		count++;
	}
}

void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}

	if (key == GLUT_KEY_F1 && gameStop) {
		gameStop = false;
		for (int i = 0; i < 5; i++) {
			ufo[i].x = -675 - i * 300;
			ufo[i].initialized = false;
		}
		timer = 2000;
		totalUfos = 0;//tổng số ufo được chuong trình ra
		burstUfos = 0;//tổng số ufo bị bắn 
		score = 0;//điểm bắn hạ ufo 
		lastPoint = 0;//số ufo bị bắn trong 1 lần bắn
		rocketx = carx;//tốc độ rocket đi theo tọa độ của xe
		rockety = 0;
		shooted = false;
		gameStart = false;
	}


	if (key == GLUT_KEY_F1) {
		gameStart = !gameStart;
	}

	if (key == GLUT_KEY_RIGHT && carx < 430 && gameStart && !gameStop)
	{
		carx += 20;
		rev = 1; //chiều ngang của xe
	}
	if (key == GLUT_KEY_LEFT && carx > -530 && gameStart && !gameStop)
	{
		carx -= 20;//chiều dọc của xe
		rev = -1;
	}
	if (key == GLUT_KEY_UP && y <15 && gameStart && !gameStop)
	{
		v += 20;

	}
	if (key == GLUT_KEY_DOWN && y > 30 && gameStart && !gameStop)
	{
		v -= 20;
	}
	glutPostRedisplay();
	// to refresh the window it calls display() function

}

//
//Các phìm đặc biệt GLUT_KEY_F1, F2, F3,...
// phím mũi tên, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{

	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// sự kiện khi nhấp chuột
// Cung cấp nút
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y là tọa độ điểm đã nhấp chuột
//
void onClick(int button, int stat, int x, int y)
{



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// hàm được gọi khi kích thước của cửa sổ thay đổi
// w :chiều rộng của cửa sổ
// h : chiều dài của cửa sổ
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // gọi lại cửa sổ
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

void onMove(int x, int y) {
	glutPostRedisplay();
}

//tốc độ dayYYY
void rocketTimer() {
	if (shooted)
		rockety += 20;

	if (rockety % 20 == 0)
		rocketFire = !rocketFire;
}

#if TIMER_ON == 1
void onTimer(int v) {


	// Write your codes here.
	if (gameStart && !gameStop)
	{
		int m;
		timer -= 3;
		if (timer <= 0)
			gameStop = true;
		rocketTimer();


		for (int i = 0; i < 20; i++)
			if (!ufo[i].initialized)
			{
				ufo[i].y = rand() % 450;
				ufo[i].initialized = true;

			}

		for (int i = 0; i < 5; i++)
			if (ufo[i].initialized) {
				ufo[i].x += 20;

				if (ufo[i].x > -670 && !ufo[i].countChecker)
				{
					totalUfos++;
					ufo[i].countChecker = true;
				}
			}

		for (int i = 0; i < 5; i++)
			if (ufo[i].x > 430)
			{
				ufo[i].x = -675 - i * 400;
				ufo[i].initialized = false;
				ufo[i].countChecker = false;
			}


		for (int i = 0; i < 5; i++) {

			if (ufo[i].x == rocketx && ufo[i].x == rocketx && ufo[i].y + 70 >= rockety - 210 && ufo[i].y - 70 <= rockety - 210) {
				ufo[i].x = -675 - i * 400;
				ufo[i].initialized = false;
				ufo[i].countChecker = false;
				score += 5;
				burstUfos++;
				lastPoint = 5;
			}

			else if (ufo[i].x + 20 >= rocketx && ufo[i].x - 20 <= rocketx && ufo[i].y >= rockety - 210 && ufo[i].y - 70 <= rockety - 210)
			{
				ufo[i].x = -675 - i * 400;
				ufo[i].initialized = false;
				ufo[i].countChecker = false;
				score += 3;
				burstUfos++;
				lastPoint = 3;
			}
			else if (ufo[i].x + 30 >= rocketx && ufo[i].x - 30 <= rocketx && ufo[i].y + 70 >= rockety - 210 && ufo[i].y - 70 <= rockety - 210)
			{
				ufo[i].x = -675 - i * 400;
				ufo[i].initialized = false;
				ufo[i].countChecker = false;
				score += 2;
				burstUfos++;
				lastPoint = 2;
			}

			else if (ufo[i].x + 65 >= rocketx && ufo[i].x - 65
				<= rocketx && ufo[i].y + 70 >= rockety - 210 && ufo[i].y - 70 <= rockety - 210)
			{
				ufo[i].x = -675 - i * 400;
				ufo[i].initialized = false;
				ufo[i].countChecker = false;
				score += 1;
				burstUfos++;
				lastPoint = 1;
			}



		}
	}


	//để làm mới cửa sổ nó gọi hàm display ()

	glutPostRedisplay(); // thông báo cần vẽ lại hàm display()
	int timeDiff = 0;
	if (gameStart == true) {
		timeDiff++;

		if (timeDiff % 15 == 0 && gameStart == true)
		{
			int beginFrame = getMilliCount();
			int timeDiff = getMilliCount() - beginFrame;//thời gian thực hiện xong chu trình 
			if (timeDiff < 40)//sau 5 giây nếu khung hình xuất ra có thời gian mover<5 thì sẽ ngủ
			{
				sleep(40 - timeDiff);
			}
		}
	}
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);


}
#endif

void Init() {

	// làm min hình khối
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Blowing up baloons");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	//đăng ký hàm sử dụng bàn phím
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);


#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);//thời gian gọi lại hàm onTime
#endif

	Init();

	glutMainLoop();
}
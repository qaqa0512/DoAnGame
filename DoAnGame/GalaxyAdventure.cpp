#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include<windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

// Nguyen Quoc Anh - -1711061484 - 17DTHA6
// Nguyen Hoang Cong Duy - 1711061525 - 17DTHA6

// Tốc độ của game
int FPS = 50;

//Điều kiện game
int start = 0;
int gv = 0;
int level = 0;

//Bảng số
int score = 0;

//For Card Left / RIGHT
int lrIndex = 0;

//Chuong ngai vat tien toi
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;

// Thiết lập kiểu size font chữ
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24; // kiểu font chữ và size của font chữ
const int font2 = (int)GLUT_BITMAP_9_BY_15;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

char s[30];
void renderBitmapString(float x, float y, void *font, const char *string) {
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

// Bắt Đầu Trò Chơi
void startGame() {

	//Sảnh của ngôi nhà ma
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//Score Board
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(80, 97);
	glVertex2f(100, 97);
	glVertex2f(100, 98 - 8);
	glVertex2f(80, 98 - 8);
	glEnd();

	//Print Score
	char buffer[50];
	sprintf_s(buffer, "POINT: %d", score);
	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(80.5, 95, (void *)font3, buffer);

	//Increse Speed With level

	//Tau vu tru

		//Canh cua tau
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 22, 1);
	glVertex2f(lrIndex + 26, 3);
	glVertex2f(lrIndex + 30, 3);
	glVertex2f(lrIndex + 34, 1);
	glEnd();

		//Than cua tau
	glColor3f(1.0, 1.0, 1.0); // mau trang
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26, 1);
	glVertex2f(lrIndex + 24, 4);

	glColor3f(0.294, 0.000, 0.510);
	glVertex2f(lrIndex + 24, 8);
	glVertex2f(lrIndex + 28, 10);
	
	glVertex2f(lrIndex + 32, 8);
	glVertex2f(lrIndex + 32, 4);
	glVertex2f(lrIndex + 30, 1);
	
	glVertex2f(lrIndex + 28, 10);
	glVertex2f(lrIndex + 30, 8);
	glVertex2f(lrIndex + 30, 1);
	glEnd();


	//Ma quỷ

	// Ma quỷ 1
		//Than cua vat the la
	glColor3f(1.00, 0.500, 0.500);// mau huong
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26, car1 + 92);
	glVertex2f(lrIndex1 + 24, car1 + 94);

	glVertex2f(lrIndex1 + 24, car1 + 98);
	glVertex2f(lrIndex1 + 28, car1 + 96);

	glVertex2f(lrIndex1 + 32, car1 + 98);
	glVertex2f(lrIndex1 + 32, car1 + 94);

	glVertex2f(lrIndex1 + 30, car1 + 92);
	glEnd();

		// Duoi cua vat the la
	glColor3f(0.600, 0.400, 0.500);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 24, car1 + 100);
	glVertex2f(lrIndex1 + 24, car1 + 98);
	glVertex2f(lrIndex1 + 28, car1 + 96);
	glVertex2f(lrIndex1 + 32, car1 + 98);
	glVertex2f(lrIndex1 + 32, car1 + 100);
	glEnd();
	car1--;
	if (car1<-100) {
		car1 = 0;
		lrIndex1 = lrIndex;
		score++;
	}
	//KIll check car1
	if ((abs(lrIndex - lrIndex1)<8) && (car1 + 100<10)) {
		start = 0;
		gv = 1;
	}

	//Ma quỷ 2
	// Thân cua vat the 2
	glColor3f(0.294, 0.000, 0.510);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26, car2 + 92);
	glVertex2f(lrIndex2 + 24, car2 + 94);

	glVertex2f(lrIndex2 + 24, car2 + 96);
	glVertex2f(lrIndex2 + 26, car2 + 98);

	glVertex2f(lrIndex2 + 28, car2 + 96);
	glVertex2f(lrIndex2 + 30, car2 + 98);

	glVertex2f(lrIndex2 + 32, car2 + 96);
	glVertex2f(lrIndex2 + 32, car2 + 94);

	glVertex2f(lrIndex2 + 30, car2 + 92);
	glEnd();

	// Doi cua vat the 2
	glColor3f(1.000, 0.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 24, car2 + 100);
	glVertex2f(lrIndex2 + 24, car2 + 98);
	glVertex2f(lrIndex2 + 28, car2 + 96);
	glVertex2f(lrIndex2 + 32, car2 + 98);
	glVertex2f(lrIndex2 + 32, car2 + 100);
	glEnd();

	car2--;
	if (car2<-100) {
		car2 = 0;
		lrIndex2 = lrIndex;
		score++;
	}
	//KIll check car2
	if ((abs(lrIndex - lrIndex2)<8) && (car2 + 100<10)) {
		start = 0;
		gv = 1;
	}


	//Ma quỷ 3
	// Thân của vật thể
	glColor3f(1.000, 0.500, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 24, car3 + 98);
	glVertex2f(lrIndex3 + 25, car3 + 99);

	glVertex2f(lrIndex3 + 31, car3 + 99);
	glVertex2f(lrIndex3 + 32, car3 + 98);
	

	//Đuôi vật thể
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 24, car3 + 92);
	glVertex2f(lrIndex3 + 24, car3 + 94);

	glVertex2f(lrIndex3 + 26, car3 + 94);
	glVertex2f(lrIndex3 + 28, car3 + 93);
	glVertex2f(lrIndex3 + 30, car3 + 94);

	glVertex2f(lrIndex3 + 32, car3 + 94);
	glVertex2f(lrIndex3 + 32, car3 + 92);

	glEnd();
	car3--;
	if (car3<-100) {
		car3 = 0;
		lrIndex3 = lrIndex;
		score++;
	}
	//KIll check car3
	if ((abs(lrIndex - lrIndex3)<8) && (car3 + 100<10)) {
		start = 0;
		gv = 1;

	}

}

void fristDesign() {

	//Ảnh nền của ngôi nhà ma ám
	glColor3f(0.73, 0.16, 0.96); // medium purple
	glBegin(GL_POLYGON);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glColor3f(0.55, 0.09, 0.09); // Scarlet color
	glVertex2f(100, 50 - 50);
	glVertex2f(0, 50 - 50);
	glEnd();


	//Đường đi đến ngôi nhà của ma ám
	glColor3f(0.410, 0.410, 0.410);
	glBegin(GL_TRIANGLES);
	glVertex2f(50, 55);
	glVertex2f(90, 0);
	glVertex2f(10, 0);
	glEnd();

	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(22, 1);
	glVertex2f(26, 3);
	glVertex2f(30, 3);
	glVertex2f(34, 1);
	glEnd();

	//Nhân vật khám phá nhà ma
	glColor3f(1.0, 1.0, 1.0); // mau trang
	glBegin(GL_POLYGON);
	glVertex2f(26, 1);
	glVertex2f(24, 4);

	glColor3f(0.294, 0.000, 0.510);
	glVertex2f(24, 8);
	glVertex2f(28, 10);

	glVertex2f(32, 8);
	glVertex2f(32, 4);
	glVertex2f(30, 1);

	glVertex2f(28, 10);
	glVertex2f(30, 8);
	glVertex2f(30, 1);
	glEnd();

	////Road Midle
	//glColor3f(1, 1, 1);
	//glBegin(GL_TRIANGLES);
	//glVertex2f(32 ok- 2 + 21, 55);
	//glVertex2f(50 + 2, 50 - 50);
	//glVertex2f(50 - 2, 50 - 50);
	//glEnd();

	//Bầu trời u ám
	glColor3f(0.329, 0.329, 0.329); // DimGray color
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glColor3f(0.35, 0.16, 0.16); // Dark Brown Color
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glEnd();

		// Ngôi nhà ma ám
	// Đỉnh của ngôi nhà
	glColor3f(0.52, 0.37, 0.26); // Dark Orchid color
	glBegin(GL_POLYGON);
	glVertex2f(40, 90);
	glVertex2f(40, 95);
	glVertex2f(60, 95);
	glVertex2f(60, 90);
	glEnd();

	//Thân của Ngôi Nhà Ma Ám
	glColor3f(0.52, 0.37, 0.26); // Dark Orchid color
	glBegin(GL_POLYGON);
	glVertex2f(30, 80);
	glVertex2f(30, 90);
	glVertex2f(70, 90);
	glVertex2f(70, 80);
	glEnd();

	glColor3f(0.52, 0.37, 0.26); // Dark Orchid color
	glBegin(GL_POLYGON);
	glVertex2f(20, 70);
	glVertex2f(20, 80);
	glVertex2f(80, 80);
	glVertex2f(80, 70);
	glEnd();


	
	glColor3f(0.52, 0.37, 0.26); // Dark Orchid color
	glBegin(GL_POLYGON);
	glVertex2f(10, 55);
	glVertex2f(10, 70);
	glVertex2f(90, 70);
	glVertex2f(90, 55);
	glEnd();

	// Cửa của ngôi nhà
	glColor3f(1.0, 1.0, 1.0); // màu trắng
	glBegin(GL_POLYGON);
	glVertex2f(40, 65);
	glVertex2f(60, 65);
	glVertex2f(60, 55);
	glVertex2f(40, 55);
	glEnd();

	glColor3f(1.0, 0.0, 0.0); // màu trắng
	glBegin(GL_TRIANGLES);
	glVertex2f(40, 65);
	glVertex2f(60, 65);
	glVertex2f(60, 55);
	glVertex2f(40, 55);
	glEnd();

	//Mặt trăng máu
		//glColor3f(0.80, 0.80, 0.80); // DimGray color
	glBegin(GL_POLYGON);
	glVertex2f(7, 85);
	glVertex2f(7, 95);

	glVertex2f(20, 95);
	glVertex2f(20, 85);
	glEnd();

	// Biển báo cấm
	// Cây cột
	glColor3f(0.658824, 0.658824, 0.658824);
	glBegin(GL_POLYGON);
	glVertex2f(10,25);
	glVertex2f(10,45);
	glVertex2f(13, 45);
	glVertex2f(13, 25);
	glEnd();

	//Tấm bản
	glColor3f(0.91, 0.76, 0.65); // màu nâu sáng
    glBegin(GL_POLYGON);
    glVertex2f(3, 32);
    glVertex2f(3, 43);
	glVertex2f(20, 43);
	glVertex2f(20, 32);
    glEnd();




	//Menu Place Holder
	/*glColor3f(0.098, 0.098, 0.439);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();

	glColor3f(00, 0, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 4 + 10);
	glVertex2f(32 - 4, 50 + 4 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 + 45, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 + 45, 50 - 15 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 - 14 + 10);
	glVertex2f(32 + 46, 50 - 14 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 - 5, 50 + 5 + 10);
	glVertex2f(32 - 5, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();
*/


	////Text Information in Frist Page
	//if (gv == 1) {
	//	glColor3f(1.000, 0.000, 0.000);
	//	renderBitmapString(40, 75, (void *)font2, "YOU LOSE :((");
	//	glColor3f(1.000, 0.000, 0.000);
	//	char buffer2[50];
	//	sprintf_s(buffer2, "Your Score is : %d", score);
	//	renderBitmapString(33, 60 - 4 + 10, (void *)font1, buffer2);

	//}

	//// vị trí tiêu đề xuất hiện trên màn hình
	//glColor3f(1.000, 0.000, 0.500);
	//renderBitmapString(24, 80, (void *)font1, "The Haunted House 2020"); 

	//// vị trí thông báo hướng dẫn
	//glColor3f(0.000, 1.000, 0.000);
	//renderBitmapString(30, 50 + 10, (void *)font2, "Press SPACE to START"); 
	//renderBitmapString(30, 50 - 3 + 10, (void *)font2, "Press ESC to Exit");

	//// vị trí hướng dẫn di chuyển
	//glColor3f(1.000, 1.000, 1.000);
	//renderBitmapString(30, 50 - 6 + 10, (void *)font3, "Press UP to increase Speed");
	//renderBitmapString(30, 50 - 8 + 10, (void *)font3, "Press DOWN to decrease Speed");
	//renderBitmapString(30, 50 - 10 + 10, (void *)font3, "Press RIGHT to turn Right");
	//renderBitmapString(30, 50 - 12 + 10, (void *)font3, "Press LEFT to turn Left");

	// vi tri xuat hien tren bien bao cam
	glColor3f(0.0,0.0,0.0);
	renderBitmapString(3.5, 37, (void *)font2, "Dangerous"); 
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (start == 1) {
		// glClearColor(0.627, 0.322, 0.176,1);

		glClearColor(0.36, 0.25, 0.20, 0.0);
		startGame();
	}

	else {
		fristDesign();
		//glClearColor(0.184, 0.310, 0.310,1);
	}



	glFlush();
	glutSwapBuffers();
}



void spe_key(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:
		if (FPS>(50 + (level * 2)))
			FPS = FPS - 2;
		break;
	case GLUT_KEY_UP:
		FPS = FPS + 2;
		break;

	case GLUT_KEY_LEFT:
		if (lrIndex >= 0) {
			lrIndex = lrIndex - (FPS / 10);
			if (lrIndex<0) {
				lrIndex = -1;
			}
		}
		break;


	case GLUT_KEY_RIGHT:
		if (lrIndex <= 44) {
			lrIndex = lrIndex + (FPS / 10);
			if (lrIndex>44) {
				lrIndex = 45;
			}
		}
		break;

	default:
		break;
	}

}

void processKeys(unsigned char key, int x, int y) {

	switch (key)
	{
	case ' ':
		if (start == 0) {
			start = 1;
			gv = 0;
			FPS = 50;
			lrIndex = 0;
			car1 = 0;
			lrIndex1 = 0;
			car2 = +35;
			lrIndex2 = 0;
			car3 = +70;
			lrIndex3 = 0;
			score = 0;
			level = 0;
		}
		break;

	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void timer(int) {
	glutPostRedisplay(); // cập nhật lại màn hình
	glutTimerFunc(1000 / FPS, timer, 0);
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv); // 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 650);
	glutInitWindowPosition(200, 20);
	glutCreateWindow("The Haunted House 2020"); // tiêu đề hiện thị lên windows

	glutDisplayFunc(display); // 
	glutSpecialFunc(spe_key);
	glutKeyboardFunc(processKeys);

	glOrtho(0, 100, 0, 100, -1, 1);
	glClearColor(0.184, 0.310, 0.310, 1);

	glutTimerFunc(1000, timer, 0);
	glutMainLoop();

	return 0;
}
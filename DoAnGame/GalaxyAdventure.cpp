#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include<windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <mmsystem.h>


// Nguyen Quoc Anh - -1711061484 - 17DTHA6
// Nguyen Hoang Cong Duy - 1711061525 - 17DTHA6
// Cao Dang Quang - 1711061151 - 17DTHA5

// Tốc độ của game
int FPS = 50;

// Âm thanh cho game
int sound = 0;

//Điều kiện game
int begin = 0; // Begin

int gameover = 0; // gameOver
//Bảng số
int score = 0;

//Khoảng cách trái phải
int lefRight = 0;

//Chuong ngai vat tien toi
int ghost = 0;
int lefRight1 = 0;
int ghost2 = +33;
int lefRight2 = 0;
int ghost3 = +68;
int lefRight3 = 0;

// Thiết lập kiểu size font chữ
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_10; // kiểu font chữ và size của font chữ
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
void beginGame()
{
	//Sảnh của ngôi nhà ma
	glBegin(GL_POLYGON);
	glColor3f(0.556, 0.137, 0.137);
	glVertex2f(23, 0);
	glVertex2f(23, 100);

	glVertex2f(77, 100);
	glVertex2f(77, 0);
	glEnd();


	// Đèn trái
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(3, 65);
	glVertex2f(3, 80);

	glVertex2f(8, 85);
	glVertex2f(13, 85);

	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(18, 80);
	glVertex2f(18, 65);

	glVertex2f(13, 60);
	glVertex2f(8, 60);
	glEnd();

	// Đèn phải
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(81, 65);
	glVertex2f(81, 80);

	glVertex2f(86, 85);
	glVertex2f(91, 85);

	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(96, 80);
	glVertex2f(96, 65);

	glVertex2f(91, 60);
	glVertex2f(86, 60);
	glEnd();

		//Instructions
	// Vẽ bảng hướng dẫn
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(0, 10);
	glVertex2f(23, 10);
	glVertex2f(23, 30);
	glVertex2f(0, 30);
	glEnd();
	// Tiêu đề hương dẫn
	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(1.5, 27, (void *)font2, "INSTUCTIONS");// vị trí hiển thị hướng dẫn

	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(3, 23, (void *)font2, "<: LEFT");// vị trí hiện thị hướng dẫn sang trái

	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(3, 20, (void *)font2, ">: RIGHT");// vị trí hiển thị hướng dẫn sang phải

	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(3, 17, (void *)font2, "ESC: exit");// vị trí hiển thị hướng dẫn thoát

	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(3, 11, (void *)font2, "ENJOY IT!!!");// vị trí hiển thị chúc vui vẻ

	
	//Hiển thị điểm 
	char buffer[50];
	sprintf_s(buffer, "Ghost:%d", score);
	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(83, 93, (void *)font2, buffer);// vị trí hiện thị điểm 

	//Flycam
		//Cánh của flycam
	glColor3f(1.000, 0.000, 0.000);
	glBegin(GL_TRIANGLES);
	glVertex2f(lefRight + 22, 4);
	glVertex2f(lefRight + 28, 10);
	glVertex2f(lefRight + 34, 4);
	glEnd();

		//Than cua flycam
	glColor3f(1.0, 1.0, 1.0); // mau trang
	glBegin(GL_POLYGON);
	glVertex2f(lefRight + 26, 1);
	glVertex2f(lefRight + 24, 4);

	glVertex2f(lefRight + 24, 8);
	glVertex2f(lefRight + 28, 10);
	
	glVertex2f(lefRight + 32, 8);
	glVertex2f(lefRight + 32, 4);
	glVertex2f(lefRight + 30, 1);
	
	glVertex2f(lefRight + 28, 10);
	glVertex2f(lefRight + 30, 8);
	glVertex2f(lefRight + 30, 1);
	glEnd();


	//Ma quỷ

	// Ma quỷ 1
		//Than cua vat the la
	glColor3f(1.00, 0.500, 0.500);// mau huong
	glBegin(GL_POLYGON);
	glVertex2f(lefRight1 + 26, ghost + 92);
	glVertex2f(lefRight1 + 24, ghost + 94);

	glVertex2f(lefRight1 + 24, ghost + 98);
	glVertex2f(lefRight1 + 28, ghost + 96);

	glVertex2f(lefRight1 + 32, ghost + 98);
	glVertex2f(lefRight1 + 32, ghost + 94);

	glVertex2f(lefRight1 + 30, ghost + 92);
	glEnd();

		// Duoi cua vat the la
	glColor3f(0.600, 0.400, 0.500);
	glBegin(GL_POLYGON);
	glVertex2f(lefRight1 + 24, ghost + 100);
	glVertex2f(lefRight1 + 24, ghost + 98);
	glVertex2f(lefRight1 + 28, ghost + 96);
	glVertex2f(lefRight1 + 32, ghost + 98);
	glVertex2f(lefRight1 + 32, ghost + 100);
	glEnd();

	ghost--;

	if (ghost<-100) {
		ghost = 0;
		lefRight1 = lefRight;
		score++;
	}

	////Kiểm tra nếu flycam chạm trán phải ma thì sẽ bị phá hủy
	if ((abs(lefRight - lefRight1)<8) && (ghost + 100<10)) {
		begin = 0;
		gameover = 1;
	}

	//Ma quỷ 2
	// Thân cua vat the 2
	glColor3f(0.294, 0.000, 0.510);
	glBegin(GL_POLYGON);
	glVertex2f(lefRight2 + 26, ghost2 + 92);
	glVertex2f(lefRight2 + 24, ghost2 + 94);

	glVertex2f(lefRight2 + 24, ghost2 + 96);
	glVertex2f(lefRight2 + 26, ghost2 + 98);

	glVertex2f(lefRight2 + 28, ghost2 + 96);
	glVertex2f(lefRight2 + 30, ghost2 + 98);

	glVertex2f(lefRight2 + 32, ghost2 + 96);
	glVertex2f(lefRight2 + 32, ghost2 + 94);

	glVertex2f(lefRight2 + 30, ghost2 + 92);
	glEnd();

	// Duoi cua vat the 2
	glColor3f(1.000, 0.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(lefRight2 + 24, ghost2 + 100);
	glVertex2f(lefRight2 + 24, ghost2 + 98);
	glVertex2f(lefRight2 + 28, ghost2 + 96);
	glVertex2f(lefRight2 + 32, ghost2 + 98);
	glVertex2f(lefRight2 + 32, ghost2 + 100);
	glEnd();

	ghost2--;
	if (ghost2<-100) {
		ghost2 = 0;
		lefRight2 = lefRight;
		score++;
	}
	//Kiểm tra nếu flycam chạm trán phải ma thì sẽ bị phá hủy
	if ((abs(lefRight - lefRight2)<8) && (ghost2 + 100<10)) {
		begin = 0;
		gameover = 1;
	}
	 

	//Ma quỷ 3
	// Thân của vật thể
	glColor3f(1.000, 0.500, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lefRight3 + 24, ghost3 + 98);
	glVertex2f(lefRight3 + 25, ghost3 + 99);

	glVertex2f(lefRight3 + 31, ghost3 + 99);
	glVertex2f(lefRight3 + 32, ghost3 + 98);
	

	//Đuôi vật thể
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lefRight3 + 24, ghost3 + 92);
	glVertex2f(lefRight3 + 24, ghost3 + 94);

	glVertex2f(lefRight3 + 26, ghost3 + 94);
	glVertex2f(lefRight3 + 28, ghost3 + 93);
	glVertex2f(lefRight3 + 30, ghost3 + 94);

	glVertex2f(lefRight3 + 32, ghost3 + 94);
	glVertex2f(lefRight3 + 32, ghost3 + 92);

	glEnd();

	ghost3--;
	if (ghost3 < -100) {
		ghost3 = 0;
		lefRight3 = lefRight;
		score++;
	}
	//Kiểm tra nếu flycam chạm trán phải ma thì sẽ bị phá hủy
	if ((abs(lefRight - lefRight3) < 8) && (ghost3 + 100 < 10)) {
		begin = 0;
		gameover = 1;
	}
}

// Layout của The Haunted House
void layOut() {

	//Ảnh nền của ngôi nhà ma ám
	glColor3f(0.73, 0.16, 0.96); // medium purple
	glBegin(GL_POLYGON);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glColor3f(0.55, 0.09, 0.09); // Scarlet color
	glVertex2f(100, 0);
	glVertex2f(0, 0);
	glEnd();


	//Đường đi đến ngôi nhà của ma ám
	glColor3f(0.410, 0.410, 0.410);
	glBegin(GL_TRIANGLES);
	glVertex2f(50, 55);
	glVertex2f(80, 0);
	glVertex2f(20, 0);
	glEnd();

	////Flycam khám phá nhà ma
		//Cánh cua flycam
	glColor3f(1.000, 0.000, 0.000);
	glBegin(GL_TRIANGLES);
	glVertex2f(39, 21);
	glVertex2f(50, 30);
	glVertex2f(61, 21);
	glEnd();

		// Thân của flycam
	glColor3f(1.0, 1.0, 1.0); // mau trang
	glBegin(GL_POLYGON);
	glVertex2f(43, 20);
	glVertex2f(43,30);
	glVertex2f(50, 35);
	glVertex2f(57, 30);
	glVertex2f(57, 20);
	glVertex2f(53, 15);
	glVertex2f(47, 15);
	//glVertex2f(48, 20);
	//glVertex2f(50, 18);
	//glVertex2f(50, 11);
	glEnd();

	//Bầu trời u ám
	glColor3f(0.329, 0.329, 0.329); // DimGray color
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glColor3f(0.35, 0.16, 0.16); // Dark Brown Color
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glEnd();


	// Con dơi 2
	glColor3f(0.0, 0.0, 0.0); // Dark Orchid color
	glBegin(GL_POLYGON);
	glVertex2f(80, 90);
	glVertex2f(95, 90);

	glVertex2f(95, 85);
	glVertex2f(93, 87);

	glVertex2f(86.5, 87);
	glVertex2f(80, 85);

	glEnd();

		// Ngôi nhà ma ám
	// Đỉnh của ngôi nhà
	glColor3f(0.52, 0.37, 0.26); // Dark Orchid color
	glBegin(GL_POLYGON);
	glVertex2f(40, 90);
	glVertex2f(40, 95);
	glColor3f(0.0, 0.0, 0.0); // Dark Orchid color
	glVertex2f(60, 95);
	glVertex2f(60, 90);
	glEnd();

	//Thân của Ngôi Nhà Ma Ám
	glColor3f(0.52, 0.37, 0.26); // Dark Orchid color
	glBegin(GL_POLYGON);
	glVertex2f(30, 80);
	glVertex2f(30, 90);
	glColor3f(1.0, 1.0, 1.0); // Dark Orchid color
	glVertex2f(70, 90);
	glVertex2f(70, 80);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.52, 0.37, 0.26); // Dark Orchid color
	glVertex2f(20, 70);
	glVertex2f(20, 80);
	glColor3f(0.0, 0.0, 0.0); // Dark Orchid color
	glVertex2f(80, 80);
	glVertex2f(80, 70);
	glEnd();
	
	glColor3f(0.52, 0.37, 0.26); // Dark Orchid color
	glBegin(GL_POLYGON);
	glVertex2f(10, 55);
	glVertex2f(10, 70);
	glColor3f(0.0, 0.0, 0.0); // Dark Orchid color
	glVertex2f(90, 70);
	glVertex2f(90, 55);
	glEnd();

		// Cửa của ngôi nhà
	glColor3f(0.556, 0.137, 0.137); // red color
	glBegin(GL_POLYGON);
	glVertex2f(40, 65);
	glVertex2f(60, 65);

	glColor3f(0.0, 0.0, 0.0); // white color
	glVertex2f(60, 55);
	glVertex2f(40, 55);
	glEnd();

		// Hàng rào trái
	// Thanh trái hàng rào trái
	glColor3f(1.0, 0.5, 0.0); // red color
	glBegin(GL_POLYGON);
	glVertex2f(14, 54);
	glVertex2f(14, 62);

	glVertex2f(17, 62);
	glVertex2f(17, 54);
	glEnd();

	// Thanh giữa hàng rào trái
	glBegin(GL_POLYGON);
	glVertex2f(14+10, 54);
	glVertex2f(14+10, 62);

	glVertex2f(17+10, 62);
	glVertex2f(17+10, 54);
	glEnd();

	// Thanh phải hàng rào trái
	glBegin(GL_POLYGON);
	glVertex2f(14 + 20, 54);
	glVertex2f(14 + 20, 62);

	glVertex2f(17 + 20, 62);
	glVertex2f(17 + 20, 54);
	glEnd();

	// Thanh dưới hàng rào trái
	glBegin(GL_POLYGON);
	glVertex2f(14, 54);
	glVertex2f(36, 54);

	glVertex2f(36, 57);
	glVertex2f(14, 57);
	glEnd();

	//hàng rào phải
	// thanh phải của hàng rào phải
	glColor3f(1.0, 0.5, 0.0); // red color
	glBegin(GL_POLYGON);
	glVertex2f(64, 54);
	glVertex2f(64, 62);

	glVertex2f(67, 62);
	glVertex2f(67, 54);
	glEnd();

	// Thanh giữa hàng rào phải
	glBegin(GL_POLYGON);
	glVertex2f(64 + 10, 54);
	glVertex2f(64 + 10, 62);

	glVertex2f(67 + 10, 62);
	glVertex2f(67 + 10, 54);
	glEnd();

	// Thanh phải hàng rào phải
	glBegin(GL_POLYGON);
	glVertex2f(64 + 20, 54);
	glVertex2f(64 + 20, 62);

	glVertex2f(67 + 20, 62);
	glVertex2f(67 + 20, 54);
	glEnd();

	// Thanh dưới hàng rào phải
	glBegin(GL_POLYGON);
	glVertex2f(64, 54);
	glVertex2f(86, 54);

	glVertex2f(86, 57);
	glVertex2f(64, 57);
	glEnd();

		//Mặt trăng máu
	glColor3f(1.0,0.0,0.0); // red color
	glBegin(GL_POLYGON);
	glVertex2f(7, 85);
	glVertex2f(7, 95);
	glVertex2f(15, 97);

	glColor3f(0.410, 0.410, 0.410); // grey color
	glVertex2f(23,95);
	glVertex2f(23, 85);
	glVertex2f(15, 82);
	glEnd();

	// Bia mộ 2 
	glColor3f(0.80, 0.80, 0.80);  // dimgrey
	glBegin(GL_POLYGON);
	glVertex2f(23, 43);
	glVertex2f(38, 43);
	glVertex2f(38, 50);
	glVertex2f(36, 52);
	glVertex2f(25, 52);
	glVertex2f(23, 50);
	glEnd();

		// Biển báo cấm
	// Cây cột
	glColor3f(0.658824, 0.658824, 0.658824); // dimgrey
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


	// Bia mộ 1
	glColor3f(0.80, 0.80, 0.80); // màu nâu sáng
	glBegin(GL_POLYGON);
	glVertex2f(72, 45);
	glVertex2f(89, 45);
	glVertex2f(85, 50);
	glVertex2f(75, 50);
	glEnd();

	 // màu nâu sáng
	glBegin(GL_POLYGON);glColor3f(0.80, 0.80, 0.80);
	glVertex2f(72, 35);
	glVertex2f(89, 35);
	glVertex2f(89, 45);
	glVertex2f(72, 45);
	glEnd();
	
	// Bia mộ 3
	glColor3f(0.80, 0.80, 0.80); // màu nâu sáng
	glBegin(GL_POLYGON);
	glVertex2f(77,18);
	glVertex2f(77, 26);
	glVertex2f(80, 28);
	glVertex2f(92, 28);
	glVertex2f(95, 26);
	glVertex2f(95, 18);
	glEnd();

		// Bụi cỏ ven đường trái
	// Đỉnh cỏ trái
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_TRIANGLES);
	glVertex2f(81, 7);
	glVertex2f(83, 10);
	glVertex2f(86, 7);
	glEnd();

	// Đỉnh cỏ giữa trái
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_TRIANGLES);
	glVertex2f(81+5, 7);
	glVertex2f(83+7, 13);
	glVertex2f(86+5, 7);
	glEnd();

	// Đỉnh cỏ phải của trái
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_TRIANGLES);
	glVertex2f(81 + 10, 7);
	glVertex2f(83+13, 10);
	glVertex2f(86 + 11, 7);
	glEnd();

		// Thân của bụi cỏ ven đường phải
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_POLYGON);
	glVertex2f(81, 5);
	glVertex2f(97, 5);
	glVertex2f(97, 7);
	glVertex2f(81, 7);
	glEnd();

		// Bụi cỏ ven đường trái
	// Đỉnh cỏ trái của trái
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_TRIANGLES);
	glVertex2f(3, 5);
	glVertex2f(2, 10);
	glVertex2f(7, 7);
	glEnd();

	// Đỉnh cỏ giữa của trái
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_TRIANGLES);
	glVertex2f(3+5, 5);
	glVertex2f(5+3, 12);
	glVertex2f(7+5, 7);
	glEnd();

	//// Đỉnh cỏ giữa của trái
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_TRIANGLES);
	glVertex2f(3 + 7, 5);
	glVertex2f(10 + 3, 14);
	glVertex2f(7 + 7, 7);
	glEnd();

	//// Đỉnh cỏ phải của trái
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_TRIANGLES);
	glVertex2f(3 + 10, 5);
	glVertex2f(13 + 7, 14);
	glVertex2f(19, 7);
	glEnd();

	// Thân bụi cỏ ven đường trái
	glColor3f(0.0, 1.0, 0.0); // màu nâu sáng
	glBegin(GL_POLYGON);
	glVertex2f(3, 5);
	glVertex2f(19, 5);
	glVertex2f(19, 7);
	glVertex2f(3, 7);
	glEnd();


	

	// vị trí tiêu đề xuất hiện trên màn hình 
	glColor3f(0.0, 0.0, 0.0);
	renderBitmapString(35, 85, (void *)font2, "THE HAUNTED HOUSE"); 
	renderBitmapString(46.5, 81, (void *)font2, "2020");

	//// vị trí thông báo hướng dẫn
	glColor3f(1.000, 1.000, 0.000);
	renderBitmapString(14.5, 74.5, (void *)font2, "DO U WANT TO EXPLORE THE HAUNTED HOUSE???");


	glColor3f(1.0, 1.0, 0.0);
	renderBitmapString(22.5, 7, (void *)font2, "PRESS b TO BEGIN YOUR ADVENTURE"); 
	//renderBitmapString(30, 50 - 3 + 10, (void *)font2, "Press ESC to Exit");

	////vị trí hướng dẫn di chuyển
	//glColor3f(1.000, 1.000, 1.000);
	//renderBitmapString(30, 50 - 10 + 10, (void *)font3, "Press RIGHT to turn Right");
	//renderBitmapString(30, 50 - 12 + 10, (void *)font3, "Press LEFT to turn Left");

	// vi tri xuat hien tren bien bao cam
	glColor3f(0.0,0.0,0.0);
	renderBitmapString(3.5, 37, (void *)font2, "Dangerous"); 

	// điêu khác tên trên bia mộ 1
	glColor3f(0.0, 0.0, 0.0);
	renderBitmapString(76, 45, (void *)font2, "R.I.P");
	renderBitmapString(74, 39, (void *)font2, "A B C Z");

	// điêu khác tên trên bia mộ 2
	glColor3f(0.0, 0.0, 0.0);
	renderBitmapString(26.5, 47, (void *)font2, "R.I.P");

	// điêu khác tên trên bia mộ 3
	glColor3f(0.0, 0.0, 0.0);
	renderBitmapString(81.5, 22.5, (void *)font2, "R.I.P");

	// Tên flycam: FC-A56
	glColor3f(0.0, 0.0, 0.0);
	renderBitmapString(44.5, 27, (void *)font2, "FC-A56");
	renderBitmapString(44.5, 20, (void *)font2, "Flycam");

	
	

	////Hiện thị thông tin khi kết thúc game
	if (gameover == 1) {
		glBegin(GL_POLYGON);
		glColor3f(0.91, 0.76, 0.65); // màu nâu sáng
		glVertex2f(30, 20);
		glVertex2f(30, 40);
		glColor3f(0.36, 0.25, 0.20);
		glVertex2f(70, 40);
		glVertex2f(70, 20);
		glEnd();

		// Chú thích
		glColor3f(0.0, 0.0, 0.0);
		renderBitmapString(33, 35, (void *)font2, "FC-A56 IS DESTROYED");

		// Hiện thị số con ma mà flycam quay lại được
		glColor3f(0.0, 0.0, 0.0);
		char buffer2[50];
		renderBitmapString(33, 28, (void *)font2, "GHOSTS WERE FILMED:");
		sprintf(buffer2, "%d", score);
		renderBitmapString(48.5, 24, (void *)font2, buffer2);
	}
}


// Hiện thị màn hình lên windows
void display() {

	glClear(GL_COLOR_BUFFER_BIT);// xóa màu pixel trong buffer
	// kiểm tra nếu begin == 1 (bắt đầu thì sẽ vào trang chính để chơi)
	if (begin == 1) {
		glClearColor(0.36, 0.25, 0.20, 0.0);
		beginGame();
	}
	// kiểm tra nếu chưa thì sẽ ở trang layout 
	else {
		layOut();	
	}

	glFlush();
	glutSwapBuffers();
}


// Hàm sự kiện bàn phím
void speacialKey(int key, int x, int y) {
	switch (key) {
	// Nhấn phím Left để chuyển hướng sang trái
	case GLUT_KEY_LEFT:
		if (lefRight >= 0) {
			lefRight = lefRight - (FPS / 10);
			if (lefRight<0) {
				lefRight = -1;
			}
		}
		break;
	// Nhấn phím Right để chuyển hướng sang phải
	case GLUT_KEY_RIGHT:
		if (lefRight <= 44) {
			lefRight = lefRight + (FPS / 10);
			if (lefRight>44) {
				lefRight = 45;
			}
		}
		break;

	default:
		break;
	}
}

// Hàm sụ kiện bàn phím bằng các ký tự
void moveKey(unsigned char key, int x, int y) {

	switch (key)
	{
	// Nhấn nút 'b' để bắt đầu chơi
	case 'b':
		if (begin == 0) {
			begin = 1;
			gameover = 0;
			FPS = 50;
			lefRight = 0;
			ghost = 0;
			lefRight1 = 0;
			ghost2 = 32;
			lefRight2 = 0;
			ghost3 = 68;
			lefRight3 = 0;
			score = 0;
			sound = PlaySound(TEXT("Ghost.wav"),NULL, SND_FILENAME | SND_ASYNC);
		}
		break;

		// Nhấn ESC để thoát
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Xử lý tốc độ của game FPS
void timer(int) {
	glutPostRedisplay(); // cập nhật lại màn hình
	glutTimerFunc(1000 / FPS, timer, 0);
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 650);// kích thước của windows
	glutInitWindowPosition(200, 20); // vị trí màn hình xuất hiện
	glutCreateWindow("The Haunted House 2020 - Quoc Anh - Cong Duy - Quang Dang"); // tiêu đề hiện thị lên windows
	
	glutDisplayFunc(display); // hiện thị ảnh lên windows
	glutSpecialFunc(speacialKey); // sự kiện bàn phím
	glutKeyboardFunc(moveKey); // sự kiện bàn phím

	glOrtho(0, 100, 0, 100, -1, 1);
	glClearColor(0.184, 0.310, 0.310, 1); // xóa màu

	glutTimerFunc(1000, timer, 0); // xử lý tốc độ của game FPS
	glutMainLoop();

	return 0;
}
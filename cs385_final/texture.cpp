
/*  This is a little texture demo.					*/
/*	Run the program and you'll find two textured	*/
/*	mapped triangles.								*/
/*													*/
#include <iostream>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
//#include <windows.h>
#include "windows_sux.h"
#include "bmp.h"
#include "geometry.h"

using namespace std;

#define PI 3.14159

// function prototypes
void initializeTexture();
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);
void init(void);
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);

 // viewpoint
double theta=0, phi=0, distanceToViewpoint=200;
// window
int width=400;
int height=400;


// texture handle
GLuint topTexture;
GLuint baseTexture;

int 
main(int argc, char **argv)
{

  // set up window
  glutInitWindowSize(width,height);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Texture demo");

  // register callback functions
  glutDisplayFunc(display);
  glutReshapeFunc(reshape); 
  glutKeyboardFunc(keyboard);
  glutMotionFunc(motion);
  
  // initalize opengl parameters
  init();

  // loop until something happens
  glutMainLoop();
  return 0;           
}

void
init()
{
  // initialize viewing system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 1.0, 10.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
 

  // initialize background color to black
  glClearColor(0.0,0.0,0.0,0.0);

  // enable depth buffering
  glEnable(GL_DEPTH_TEST);

  // initialize graphics
  initializeTexture();
 
}


void
reshape(int newWidth, int newHeight)
{
  width=newWidth;
  height=newHeight;
  glViewport(0,0,width,height);
}

void
display()
{

	// check for openGL errors
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		cout << gluErrorString(errCode) << endl;

	// set up modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// compute eye position
	Tuple eye(0,0,0);
	eye[0] = (float) -distanceToViewpoint * cos(theta) * sin(phi);
	eye[1] = (float) distanceToViewpoint * sin(theta);
	eye[2] = (float) distanceToViewpoint * cos(theta) * cos(phi);

	// compute up vector
	// the is the vector orthogonal to eye that lies in the same
	// plane as eye and (0,1,0) and has a positive dot product with
	// (0,1,0)
	Tuple up = Tuple(0,1,0)-eye/eye.length();
	up.normalize();
	
	gluLookAt(eye[0],eye[1],eye[2], 0,0,0,up[0], up[1], up[2]);

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// enable texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, topTexture);
	
	// draw texture-mapped triangle
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, 1.5, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, 1.0, 2.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, 1.5, 2.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 2.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, topTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, 1.0, 2.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.5, 2.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.5, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-2.0, 1.0, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, topTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.5, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.5, 2.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 1.0, 2.0);
	glEnd();


	//START THE BASE


	glBindTexture(GL_TEXTURE_2D, baseTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, baseTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 2.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 2.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 2.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 2.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, baseTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 2.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 2.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, baseTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 2.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 2.0);
	glEnd();

	glutSwapBuffers();


}

void
keyboard(unsigned char key, int x, int y)
{

	switch (key) 
	{
	case 'Z': 
		distanceToViewpoint+=10;
		break;

	case 'z':
		if (distanceToViewpoint>10)
			distanceToViewpoint-=10;
		break;

	case 'h':
	case 'H':
	case '?':
		cout << "Use 'z'/'Z' to zoom in/out" << endl;
		break;

	default:
		break;
	}

	glutPostRedisplay();


}

/*******************************************************************
*	BMP reader from:  Program: Chapter 7 Bitmap Example 4
*	Author: Kevin Hawkins
*	
********************************************************************/



// LoadBitmapFile
// desc: Returns a pointer to the bitmap image of the bitmap specified
//       by filename. Also returns the bitmap header information.
//		 No support for 8-bit bitmaps.
unsigned char 
*LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;								// the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char		*bitmapImage;			// bitmap image data
	unsigned int		imageIdx = 0;			// image index counter
	unsigned char		tempRGB;				// swap variable

	// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	return bitmapImage;
}

void
motion(int x, int y)
{

	static int currX=-1;
	static int currY=-1;

	if (currX>0  && abs(x-currX) < width/6 && abs(y-currY) < height/6) {
		phi += (double) (x-currX)/ (double) width * 3.14159;
		theta += (double) (y-currY)/ (double) height * 3.14159;
	// limit theta to -4pi/9 and 4pi/9
	if (theta < -4*3.14159/9.0)
		theta = -4*3.14159/9.0;
	if (theta > 4*3.14159/9.0)
		theta = 4*3.14159/9.0;
	}
	currX = x;
	currY = y;
	glutPostRedisplay();
}

void
initializeTexture()
{	
	//  read in the texture
	//  the texture file name is hard coded as ball.bmp
	BITMAPINFOHEADER	bitmapInfoHeader;	// bitmap info header
	unsigned char*		bitmapData;		// the bitmap data
	bitmapData = LoadBitmapFile("texture.bmp", &bitmapInfoHeader);

	// generate texture object
	glGenTextures(1, &topTexture);

	// create texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, topTexture);

	// the following two commands tell openGL how to interpolate texture
	// values between the sampled values in your texture bitmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// the following two commands tell openGL how to extend the texture
	// when needed
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// now give it the texture map
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, 
		          bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
				  bitmapData);

	bitmapData = LoadBitmapFile("checkerboard.bmp", &bitmapInfoHeader);

	// generate texture object
	glGenTextures(2, &baseTexture);

	// create texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, baseTexture);

	// the following two commands tell openGL how to interpolate texture
	// values between the sampled values in your texture bitmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// the following two commands tell openGL how to extend the texture
	// when needed
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// now give it the texture map
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, 
		          bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
				  bitmapData);
	glDisable(GL_TEXTURE_2D);
}

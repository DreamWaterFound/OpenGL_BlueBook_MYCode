// Move.cpp
// Move a Block based on arrow key movements

#include <GLTools.h>	// OpenGL toolkit
#include <GLShaderManager.h>
#include <math3d.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch			squareBatch;	// 方块
GLShaderManager	shaderManager;	// Shader

GLfloat blockSize = 0.1f;
GLfloat vVerts[] = { -blockSize, -blockSize, 0.0f, 
	                  blockSize, -blockSize, 0.0f,
					  blockSize,  blockSize, 0.0f,
					 -blockSize,  blockSize, 0.0f};

GLfloat xPos = 0.0f;
GLfloat yPos = 0.0f;

///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context. 
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
{
	// Black background
	glClearColor(0.3f, 0.2f, 0.35f, 1.0f );
    
	shaderManager.InitializeStockShaders();

	// Load up a triangle
	squareBatch.Begin(GL_TRIANGLE_FAN, 4);
	squareBatch.CopyVertexData3f(vVerts);
	squareBatch.End();
}

// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
{
	GLfloat stepSize = 0.025f;


	if(key == GLUT_KEY_UP)
		yPos += stepSize;

	if(key == GLUT_KEY_DOWN)
		yPos -= stepSize;
	
	if(key == GLUT_KEY_LEFT)
		xPos -= stepSize;

	if(key == GLUT_KEY_RIGHT)
		xPos += stepSize;

	// Collision detection -- 这个碰撞检测其实是有 bug 的
	if(xPos < (-1.0f + blockSize)) 	xPos = -1.0f + blockSize;
    
	if(xPos > (1.0f - blockSize)) 	xPos = 1.0f - blockSize;
	
    if(yPos < (-1.0f + blockSize))  yPos = -1.0f + blockSize;
    
	if(yPos > (1.0f - blockSize)) 	yPos = 1.0f - blockSize;

	glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = { 0.75f, 0.5f, 0.23f, 1.0f };
    
	// 最终的变换矩阵, 平移变换矩阵, 旋转变换矩阵
    M3DMatrix44f mFinalTransform, mTranslationMatrix, mRotationMatrix;
    
    // Just Translate
    m3dTranslationMatrix44(mTranslationMatrix, xPos, yPos, 0.0f);
    
    // Rotate 5 degrees everytime we redraw
	// 每次都是绕着Y轴进行旋转
    static float yRot = 0.0f;
    yRot += 5.0f;
	// 好像着色器只会处理 沿着 Y 轴上的旋转, 并且这里..是放在x轴旋转角度上的位置
    m3dRotationMatrix44(mRotationMatrix, m3dDegToRad(yRot), 0.0f, 0.0f, 1.0f);

    
	// 将平移变换矩阵和旋转变换矩阵组合成为最终的变换矩阵
    m3dMatrixMultiply44(mFinalTransform, mTranslationMatrix, mRotationMatrix);
    
	shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransform, vRed);
	squareBatch.Draw();

	// Perform the buffer swap
	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Move Block with Arrow Keys");
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 1;
	}
	
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);

	SetupRC();

	glutMainLoop();
	return 0;
}

// Triangle.cpp
// Our first OpenGL program that will just draw a triangle on the screen.

#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class

#include <iostream>

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif

GLBatch	        triangleBatch;  // ?
GLShaderManager	shaderManager;  // Shader Manager

// HACK
void OnKey(unsigned char key, int x, int y)
{
    if(key == 'q' || key == 27)
    {
        ; //?
    }
}

///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
{
    // 重新设置视口
	glViewport(0, 0, w, h);
}


///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context. 
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
{
	// Blue background
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
    
	shaderManager.InitializeStockShaders();

	// Load up a triangle
	GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f, 
		                  0.5f, 0.0f, 0.0f,
						  0.0f, 0.5f, 0.0f };

	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();
}



///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	triangleBatch.Draw();

	// Perform the buffer swap to display back buffer
	glutSwapBuffers();
}


///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
{
    // 设置当前工作目录, 用于访问纹理信息 -- 不过现在好像没有什么用
	gltSetWorkingDirectory(argv[0]);
	
    // 初始化 GLUT
	glutInit(&argc, argv);
    // 设置窗口的工作模式
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    // 窗口大小
	glutInitWindowSize(800, 600);
    // 窗口标题
	glutCreateWindow("Triangle");
    // 注册窗口大小变化时的回调函数
    glutReshapeFunc(ChangeSize);
    // 注册显示更新时的回调函数
    glutDisplayFunc(RenderScene);
    // 注册键盘按键函数
    glutKeyboardFunc(OnKey);

    // 初始化 GLEW, 重定向所有 OpenGL 函数指针
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
    }
	
    // 设置渲染环境
	SetupRC();

    // 执行主循环, 由 GLUT 接管
	glutMainLoop();

	return 0;
}

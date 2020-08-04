// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstddef>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include"Model.h"
#include "Object.h"
#include"Texture.h"
#include "Camera.h"
#include"ScreenManager.h"
#include"ResourceManager.h"
#include "Singleton.h"
Camera camera1;

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

	
	
	Singleton<ResourceManager>::GetInstance()->loadResource("../Resources/RM/ResourcesManager.txt");
	Singleton<ScreenManager>::GetInstance()->loafObject("../Resources/RM/SceneManager.txt");
	Singleton<ScreenManager>::GetInstance()->init();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	Singleton<ScreenManager>::GetInstance()->Draw();
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	camera1.Update(deltaTime);
	Singleton<ScreenManager>::GetInstance()->update(camera1.getViewMatrix(), camera1.getProjection());
	Singleton<ScreenManager>::GetInstance()->update(deltaTime);
}
void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	camera1.keyBuffer(key, bIsPressed);
}

void CleanUp()
{
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}


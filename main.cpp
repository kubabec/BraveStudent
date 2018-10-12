#include <stdio.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include <vector>
#include "GL\freeglut.h"
#include "vec3.h"
#include "Cube.h"
#include "SceneObject.h"
#include "Model3D.h"
#include "Player.h"
#include "Tekstura.h"
#include "Building.h"
#include "Sphere.h"
#include "Roof.h"
#include "RewardSystem.h"
#include "Chodnik.h"
#include "Droga.h"
#include "Trawa.h"
#include "Gorka.h"
#include "Porsche.h"
#include "Tree.h"
#include "Skydome.h"
#include "Level1.h"
#include "Level2.h"
#include "Reward.h"
#include "Level3.h"
#include "Level4.h"
#include "InteractiveDoor.h"
#include "Fire.h"
#include "Scene.h"
#include "vec3.h"
#include <string>
#include <time.h>
#include "rotation.h"

void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void OnMouseMove(int, int);
int OpenInteractiveDoor(Player* player);
void LoadModels();
void LoadingText(char*, int);
void LoadingStatusBar(char*, int);
void SwitchLevelPortal();
void GoHigherLevel();
void GoLowerLevel();
void BackgroundUnderText();
void StatusBarBackground();
void RewardNameDecoder();


Player* player;
Scene scene;
Skydome* sky;

char countdownAsString[12];
char scoreAsString[12];
int finalCountdown = 350; 
int finalCountdownControl = 0;
bool CountdownStop = false;
int CountdownStopTime = 0; 
int completedCounter;
InteractiveDoor* TablicaDrzwi[6]; 


bool isGameStarted = false;
bool isGameOver = false;

bool texturesLoaded = false;
bool isFireOnLevel0Loaded = false;
bool printText = false; 

Reward* RewardHolder[7];
vec3 RewardPositions[10];
void preGameFunction();
void GameOverFunction();
Cube* preGameBackground = NULL;
clock_t previousUpdate;
double timeSum;
bool captureMouse;
Model3D* fire0[8]; 
Model3D* fire2[8];
RewardSystem* RewardManager;
int window_width, window_height;
char* rewardFound;
bool rewardFoundFlag;
int rewardFoundDisplayTime = 0;





//vec3 mousePosition;




int main(int argc, char* argv[])
{
	previousUpdate = clock() ;
	timeSum = 0; 
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 960);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Brave student the Game");

	

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);
	glutPassiveMotionFunc(OnMouseMove);
	glClearColor(0.1f, 0.2f, 0.3f, 0.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glutSetCursor(GLUT_CURSOR_NONE);
	captureMouse = true;
	glutWarpPointer(window_width / 2, window_height / 2);

	player = new Player();
	scene.AddPlayerObject(player);
	Cube* preGameBackground = new Cube(vec3(player->pos.x, player->pos.y - 0.5, player->pos.z), vec3(0.f, 0.f, 0.f), 0.5f);
	scene.AddpreGameBox(preGameBackground);

	
	RewardManager = new RewardSystem(&scene, player);


	LoadingText("Trwa wczytywanie gry...", 0);
	OnRender();

	LoadModels();

	glutFullScreen();

		glutMainLoop();

		return 0;
	}

bool keystate[256];

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		OnKeyDown(key, x, y);
	}
	keystate[key] = true;
}

void OnKeyDown(unsigned char key, int x, int y) {
	/*
	if (key == 'q' ) {
		std::cout << "x: " << player->pos.x << std::endl;
		std::cout << "y: " << player->pos.y << std::endl;
		std::cout << "z: " << player->pos.z << std::endl;
	}
	

	if (key == 'e') {
		if (player->speed == .063f)
			player->speed = 0.004;
		else
			player->speed = .063f;
	}
	

	if (key == 'r') {
		system("cls");
	}
	*/ 

	if (key == 'g') {
		if (player->isAlreadyCarryingReward) {
			RewardManager->RewardsHolder[player->HeldRewardID]->isHeldByPlayer = false;
			RewardManager->RewardsHolder[player->HeldRewardID]->pos.x += player->dir.x *0.5;
			RewardManager->RewardsHolder[player->HeldRewardID]->pos.y = player->pos.y - 0.2;
			RewardManager->RewardsHolder[player->HeldRewardID]->pos.z += player->dir.z *0.5;
			player->isAlreadyCarryingReward = false; 

		}
	}



	if (key == 13) {
		if(!isGameStarted && !isGameOver)
			isGameStarted = true;
		else if (isGameOver)
			glutLeaveMainLoop();
	}




	if (key == 27) {
		glutLeaveMainLoop();
	}
	
	/*
	if (key == 'f')
	{
		player->flyingMode = !player->flyingMode;
		player->ReactOnColisions = !player->ReactOnColisions;
	}
	*/
	

	if (key == 'm')
	{
		if (captureMouse)
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			captureMouse = false;
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(window_width / 2, window_height / 2);
			captureMouse = true;
		}
	}
}

void OnKeyUp(unsigned char key, int x, int y) {

	/*
	if (key == 'p')
	{
		GoHigherLevel();
	}
	if (key == 'o')
	{
		GoLowerLevel();
	}
	*/
	
 
	keystate[key] = false;
}

void OnMouseMove(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

void OnTimer(int id) {

	// Przelaczanie swiatla
	if (player->isOnLevel0) {
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);

	}
	else if (player->isOnLevel1) {
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);

	}
	else if (player->isOnLevel2) {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);

	}
	else if (player->isOnLevel3) {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glDisable(GL_LIGHT4);

	}
	else if (player->isOnLevel4) {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT4);

	}

	clock_t time = clock() ;
	double timeDiff = ((double)(time - previousUpdate)/CLOCKS_PER_SEC )*1000;
	previousUpdate = time; 
	timeSum = timeSum + timeDiff;
	int counter = 0;
	int countdownCopy = finalCountdown;

	while (timeSum >= 17) {
	
		counter += 1;

		if (isGameStarted) {
			if (player->isOnLevel4) OpenInteractiveDoor(player);

			if (RewardManager->CheckPlayerRewardColision()) {
				RewardNameDecoder();
				rewardFoundDisplayTime = 0;
				rewardFoundFlag = true;
			}


			if (player->isAlreadyCarryingReward)
				RewardManager->CheckIfRewardDelivered();

			finalCountdownControl += 1;

			if (finalCountdownControl >= 60) {
				finalCountdown -= 1;
				if (counter > 20) finalCountdown = countdownCopy;
				
				sprintf(countdownAsString, "%d", finalCountdown);
				finalCountdownControl = 0;
				if (finalCountdown == 0)
				{
					isGameOver = true;
				}
			}
		
		}


		SwitchLevelPortal();

		if (!isGameOver && isGameStarted) {
			if (keystate['w']) {
				player->velocity_vertical = 1;

			}
			if (keystate['s']) {
				player->velocity_vertical = -1;
			}
			if (keystate['a']) {
				player->velocity_horizontal = 1;
			}
			if (keystate['d']) {
				player->velocity_horizontal = -1;
			}


			if (captureMouse)
			{
				theta = atan2(player->dir.z, player->dir.x);
				phi = asin(player->dir.y);

				theta += (mousePosition.x - window_width / 2) * 0.005;
				phi -= (mousePosition.y - window_height / 2) * 0.005;

				player->dir.x = cos(theta) * cos(phi);
				player->dir.y = sin(phi);
				player->dir.z = sin(theta) * cos(phi);

				glutWarpPointer(window_width / 2, window_height / 2);
			}
		}

		scene.Update();

	
		timeSum = timeSum - 17;
	}
	glutTimerFunc(17, OnTimer, 0);
}

void OnRender() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(
		player->pos.x, player->pos.y, player->pos.z,
		player->pos.x + player->dir.x, player->pos.y + player->dir.y, player->pos.z + player->dir.z,
		0.0f, 1.0f, 0.0f
	);
	if (sky) {
		sky->pos = player->pos;
		sky->pos.y = sky->pos.y - 8;
	}

	scene.Render();

	if (!texturesLoaded) {
		BackgroundUnderText();
		LoadingText("Trwa ladowanie swiata gry...", 0);
	}
	else if (!isGameStarted) {
			BackgroundUnderText();
			preGameFunction();
		
		}
		else if (isGameStarted && !isGameOver) {
				StatusBarBackground();
				LoadingStatusBar("Pozostaly czas: ", 60);
				LoadingStatusBar(countdownAsString, 43);
				LoadingStatusBar("sekund", 37);

				sprintf(scoreAsString, "%d", player->score);
				LoadingStatusBar("Ocalone pieniadze polskich podatnikow: ", 5);
				LoadingStatusBar(scoreAsString, -30);
				LoadingStatusBar("PLN", -35);

				if (rewardFoundFlag &&  rewardFoundDisplayTime < 100) {
					rewardFoundDisplayTime += 1; 
					LoadingText(rewardFound, 0);

					if (rewardFoundDisplayTime > 300) {
						rewardFoundDisplayTime = 0;
						rewardFoundFlag = false;
					}
				}
				
		}
		else if (isGameOver) {
			glDisable(GL_LIGHTING);
			BackgroundUnderText();
			GameOverFunction();
		}
	
	

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void OnReshape(int width, int height) {

	window_width = width;
	window_height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, .01f, 100.0f);
}


int OpenInteractiveDoor(Player* player) {
	//portal 1 - 4,25   -15,7    -8,41
	//portal 2 - 4,36   -15,7   -3,06
	//portal 3 - 4,23    -15,7   -0,50
	float Por1Distance = sqrt(pow((player->pos.x - 4.25), 2) + pow((player->pos.y - -15.7), 2) + pow((player->pos.z - -8.41), 2) ); 
	float Por2Distance = sqrt(pow((player->pos.x - 4.36), 2) + pow((player->pos.y - -15.7), 2) + pow((player->pos.z -  -3.06), 2));
	float Por3Distance = sqrt(pow((player->pos.x - 4.23), 2) + pow((player->pos.y - -15.7), 2) + pow((player->pos.z - -0.5), 2));

	if (abs(Por1Distance) < 2.5) {
		TablicaDrzwi[0]->keepOpen = true;
	}else
		TablicaDrzwi[0]->keepOpen = false;

	if (TablicaDrzwi[0]->openAngle < -0.3) {
		//1 
		player->level_4[0][0] = 0;
		player->level_4[0][1] = 0;
		player->level_4[0][2] = 0;
		player->level_4[0][3] = 0;
	}
	else {
		player->level_4[0][0] = 3.47;
		player->level_4[0][1] = 5.05;
		player->level_4[0][2] = -8.49;
		player->level_4[0][3] = -8.35;
	}





	if (abs(Por2Distance) < 1.5 && TablicaDrzwi[4]->openAngle >= 0) {
		TablicaDrzwi[1]->keepOpen = true;
		TablicaDrzwi[2]->keepOpen = true;
		TablicaDrzwi[3]->keepOpen = true;
	}
	else {
		TablicaDrzwi[1]->keepOpen = false;
		TablicaDrzwi[2]->keepOpen = false;
		TablicaDrzwi[3]->keepOpen = false;
	}

	if (TablicaDrzwi[1]->openAngle < -0.3) {
		//1 
		player->level_4[1][0] = 0;
		player->level_4[1][1] = 0;
		player->level_4[1][2] = 0;
		player->level_4[1][3] = 0;
	}
	else {
		player->level_4[1][0] = 3.12;
		player->level_4[1][1] = 5.23;
		player->level_4[1][2] = -3.15;
		player->level_4[1][3] = -2.95;
	}







	if (abs(Por3Distance) < 1.5 && TablicaDrzwi[2]->openAngle >= 0) {
		TablicaDrzwi[4]->keepOpen = true;
		TablicaDrzwi[5]->keepOpen = true;
	}
	else {
		TablicaDrzwi[4]->keepOpen = false;
		TablicaDrzwi[5]->keepOpen = false;
	}

	if (TablicaDrzwi[4]->openAngle < -0.3) {
		//1 
		player->level_4[2][0] = 0;
		player->level_4[2][1] = 0;
		player->level_4[2][2] = 0;
		player->level_4[2][3] = 0;
	}
	else {
		player->level_4[2][0] = 3.12;
		player->level_4[2][1] = 5.32;
		player->level_4[2][2] = -0.63;
		player->level_4[2][3] = -0.46;
	}




	return 1; 
}


void LoadModels() {
		Model3D* budynek = new Model3D("../Resources/Maps/sciana.bmp"); // Zaimportowanie tekstury budynku
		budynek->load("../Resources/Models/budynek.obj");
		Model3D* budynekpum = new Model3D("../Resources/Maps/scianapum.bmp"); // Zaimportowanie tekstury budynku
		budynekpum->load("../Resources/Models/budynek.obj");
		Model3D* dach = new Model3D("../Resources/Maps/roof.bmp"); // Zaimportowanie tekstury budynku
		dach->load("../Resources/Models/dach.obj");
		Model3D* okna = new Model3D("../Resources/Maps/okno.bmp"); // Zaimportowanie tekstury budynku
		okna->load("../Resources/Models/okna.obj");
		Model3D* outGlassDoor = new Model3D("../Resources/Maps/blackglass.bmp"); // Zaimportowanie tekstury budynku
		outGlassDoor->load("../Resources/Models/OutGlassDoor.obj");




		fire0[0] = new Model3D("../Resources/Maps/fire/fire2.bmp"); // Zaimportowanie tekstury budynku
		fire0[1] = new Model3D("../Resources/Maps/fire/fire3.bmp"); // Zaimportowanie tekstury budynku
		fire0[2] = new Model3D("../Resources/Maps/fire/fire4.bmp"); // Zaimportowanie tekstury budynku
		fire0[3] = new Model3D("../Resources/Maps/fire/fire5.bmp"); // Zaimportowanie tekstury budynku
		fire0[4] = new Model3D("../Resources/Maps/fire/fire6.bmp"); // Zaimportowanie tekstury budynku
		fire0[5] = new Model3D("../Resources/Maps/fire/fire7.bmp"); // Zaimportowanie tekstury budynku
		fire0[6] = new Model3D("../Resources/Maps/fire/fire8.bmp"); // Zaimportowanie tekstury budynku
		fire0[7] = new Model3D("../Resources/Maps/fire/fire9.bmp"); // Zaimportowanie tekstury budynkus
		fire0[0]->load("../Resources/Models/fire.obj");
		fire0[1]->load("../Resources/Models/fire.obj");
		fire0[2]->load("../Resources/Models/fire.obj");
		fire0[3]->load("../Resources/Models/fire.obj");
		fire0[4]->load("../Resources/Models/fire.obj");
		fire0[5]->load("../Resources/Models/fire.obj");
		fire0[6]->load("../Resources/Models/fire.obj");
		fire0[7]->load("../Resources/Models/fire.obj");



		Model3D* Hummer = new Model3D("../Resources/Maps/hummer.bmp"); // Zaimportowanie tekstury budynku
		Hummer->load("../Resources/Models/hummer.obj");

		Model3D* chodnik = new Model3D("../Resources/Maps/chodnik.bmp"); // Zaimportowanie tekstury budynku
		chodnik->load("../Resources/Models/chodnik.obj");
		Model3D* droga = new Model3D("../Resources/Maps/road.bmp"); // Zaimportowanie tekstury budynku
		droga->load("../Resources/Models/droga.obj");
		Model3D* trawa = new Model3D("../Resources/Maps/grass.bmp"); // Zaimportowanie tekstury budynku
		trawa->load("../Resources/Models/trawa.obj");
		Model3D* gorka = new Model3D("../Resources/Maps/grass.bmp"); // Zaimportowanie tekstury budynku
		gorka->load("../Resources/Models/gorka.obj");
		Model3D* porsche = new Model3D("../Resources/Maps/porsche.bmp"); // Zaimportowanie tekstury budynku
		porsche->load("../Resources/Models/porsche.obj");
		Model3D* tree = new Model3D("../Resources/Maps/pienDrzewa.bmp"); // Zaimportowanie tekstury budynku
		tree->load("../Resources/Models/pienDrzewa.obj");
		Model3D* koronaDrzewa = new Model3D("../Resources/Maps/koronaDrzewa.bmp"); // Zaimportowanie tekstury budynku
		koronaDrzewa->load("../Resources/Models/koronaDrzewa.obj");
		Model3D* bloto = new Model3D("../Resources/Maps/bloto.bmp"); // Zaimportowanie tekstury budynku
		bloto->load("../Resources/Models/bloto.obj");
		Model3D* bush = new Model3D("../Resources/Maps/bush.bmp");
		bush->load("../Resources/Models/zywoplot.obj");
		Model3D* skydome = new Model3D("../Resources/Maps/skydome.bmp");
		skydome->load("../Resources/Models/sky.obj");
		Model3D* firetruck = new Model3D("../Resources/Maps/firetruck.bmp");
		firetruck->load("../Resources/Models/firetruck.obj");
		Model3D* trashbin = new Model3D("../Resources/Maps/trashbin.bmp");
		trashbin->load("../Resources/Models/trashbin.obj");
		Model3D* monitor = new Model3D("../Resources/Maps/monitor.bmp");
		monitor->load("../Resources/Models/monitor.obj");

		// chodnik przed budynkiem 
		Chodnik* sciezka_1 = new Chodnik(chodnik, vec3(9, 0, 0.5), vec3(0.2, 1, 0.1), 0);
		scene.AddObject(sciezka_1);
		Chodnik* sciezka_2 = new Chodnik(chodnik, vec3(5.9, 0, 0.5), vec3(0.2, 1, 0.1), 0);
		scene.AddObject(sciezka_2);
		Chodnik* sciezka_3 = new Chodnik(chodnik, vec3(2.8, 0, 0.5), vec3(0.2, 1, 0.1), 0);
		scene.AddObject(sciezka_3);
		Chodnik* sciezka_4 = new Chodnik(chodnik, vec3(-0.3, 0, 0.5), vec3(0.2, 1, 0.1), 0);
		scene.AddObject(sciezka_4);
		Chodnik* sciezka_5 = new Chodnik(chodnik, vec3(-3.4, 0, 0.5), vec3(0.2, 1, 0.1), 0);
		scene.AddObject(sciezka_5);
		Chodnik* sciezka_6 = new Chodnik(chodnik, vec3(-6.5, 0, 0.5), vec3(0.2, 1, 0.1), 0);
		scene.AddObject(sciezka_6);
		Chodnik* sciezka_7 = new Chodnik(chodnik, vec3(-8.17, 0, 3.44), vec3(0.1, 1, 0.2), 0);
		scene.AddObject(sciezka_7);
		Chodnik* sciezka_8 = new Chodnik(chodnik, vec3(-8.17, 0, 5.72), vec3(0.1, 1, 0.2), 0);
		scene.AddObject(sciezka_8);
		Chodnik* sciezka_9 = new Chodnik(chodnik, vec3(-8.17, -0.007, 7.9), vec3(0.1, 1, 0.2), 0);
		scene.AddObject(sciezka_9);

		// Droga
		Droga* hummer = new Droga(Hummer, vec3(-9.7, 0.57, -9), vec3(0.0008, 0.0008, 0.0008), 180);
		scene.AddObject(hummer);
		Droga* road0 = new Droga(droga, vec3(7.5, 0.008, 1.71), vec3(0.1, 1, 0.1), 0);
		scene.AddObject(road0);
		Droga* road = new Droga(droga, vec3(3, 0, 1.71), vec3(0.1, 1, 0.1), 0);
		scene.AddObject(road);
		Droga* road2 = new Droga(droga, vec3(-2.97, 0, 1.71), vec3(0.1, 1, 0.1), 0);
		scene.AddObject(road2);
		Droga* road3 = new Droga(droga, vec3(-8.94, 0, 1.71), vec3(0.1, 1, 0.1), 0);
		scene.AddObject(road3);
		Droga* road4 = new Droga(droga, vec3(-6.1, -0.01, 1.71), vec3(0.1, 1, 0.1), 90);
		scene.AddObject(road4);
		Droga* road5 = new Droga(droga, vec3(-6.1, -0.01, 7.65), vec3(0.1, 1, 0.1), 90);
		scene.AddObject(road5);
		Droga* road6 = new Droga(droga, vec3(-6.1, -0.012, -3), vec3(0.1, 1, 0.1), 90);
		scene.AddObject(road6);
		Droga* road7 = new Droga(droga, vec3(-6.1, -0.01, -7), vec3(0.1, 1, 0.1), 90);
		scene.AddObject(road7);
		Droga* road8 = new Droga(droga, vec3(17.3, -0.00, -1.7), vec3(0.1, 1, 0.1), 90);
		scene.AddObject(road8);
		Droga* road9 = new Droga(droga, vec3(17.3, -0.008, -7.3), vec3(0.1, 1, 0.1), 90);
		scene.AddObject(road9);
		Droga* road10 = new Droga(droga, vec3(-6, -0.011, -12.8), vec3(0.1, 1, 0.1), 90);
		scene.AddObject(road10);
		Droga* road11 = new Droga(droga, vec3(-6, -0.012, -16.3), vec3(0.1, 1, 0.1), 90);
		scene.AddObject(road11);

		Droga* Trashbin = new Droga(trashbin, vec3(-8, 0, -6.7), vec3(0.04, 0.03, 0.04), 0);
		scene.AddObject(Trashbin);
		Droga* Trashbin2 = new Droga(trashbin, vec3(-8, 0, -7), vec3(0.04, 0.03, 0.04), 0);
		scene.AddObject(Trashbin2);
		Droga* Trashbin3 = new Droga(trashbin, vec3(-8, 0, -7.3), vec3(0.04, 0.03, 0.04), 0);
		scene.AddObject(Trashbin3);
		Droga* Monitor = new Droga(monitor, vec3(-8, 0.27, -7.3), vec3(0.0096, 0.0096, 0.0096), 75);
		scene.AddObject(Monitor);
		Droga* Monitor2 = new Droga(monitor, vec3(-8, 0.24, -7.0), vec3(0.0096, 0.0096, 0.0096), 120);
		scene.AddObject(Monitor2);
		Droga* Monitor3 = new Droga(monitor, vec3(-8, 0.26, -6.7), vec3(0.0096, 0.0096, 0.0096), 100);
		scene.AddObject(Monitor3);


		// Bloto 
		Droga* bloto1 = new Droga(bloto, vec3(-21.5, 0.09, -4.8), vec3(0.07, 0.07, 0.07), 180);
		scene.AddObject(bloto1);

		Droga* bloto2 = new Droga(bloto, vec3(-18.7, 0.1, -4.8), vec3(0.07, 0.07, 0.07), 180);
		scene.AddObject(bloto2);


		// ulica

		Trawa* grass0 = new Trawa(trawa, vec3(6.5, 0.011, 0.3), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(grass0);
		Trawa* grass01 = new Trawa(trawa, vec3(6.5, 0.009, -3.3), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(grass01);
		Trawa* grass02 = new Trawa(trawa, vec3(6.5, 0.01, -7.1), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(grass02);
		Trawa* grass = new Trawa(trawa, vec3(-1.4, 0.005, 0.3), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(grass);
		Trawa* grass2 = new Trawa(trawa, vec3(-1.4, 0.008, -3.6), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(grass2);
		Trawa* grass3 = new Trawa(trawa, vec3(-7.5, 0.008, 4), vec3(0.1, 0.1, 0.1), 90);
		scene.AddObject(grass3);
		Trawa* grass4 = new Trawa(trawa, vec3(-7.5, 0, -8), vec3(0.1, 0.1, 0.1), 90);
		scene.AddObject(grass4);
		Trawa* grass5 = new Trawa(trawa, vec3(-7.5, -0.008, -15), vec3(0.1, 0.1, 0.1), 90);
		scene.AddObject(grass5);
		Trawa* grass6 = new Trawa(trawa, vec3(-7.5, -0.009, -18), vec3(0.1, 0.1, 0.1), 90);
		scene.AddObject(grass6);
		// Strona drogi za gorka
		Trawa* grass7 = new Trawa(trawa, vec3(-1.35, -0.01, -15), vec3(0.1, 0.1, 0.1), 90);
		grass7->Render();
		scene.AddObject(grass7);
		Trawa* grass8 = new Trawa(trawa, vec3(-1.35, -0.009, -18), vec3(0.1, 0.1, 0.1), 90);
		grass8->Render();
		scene.AddObject(grass8);
		Trawa* grass9 = new Trawa(trawa, vec3(10, -0.007, 4.5), vec3(0.1, 0.1, 0.1), 0);
		grass9->Render();
		scene.AddObject(grass9);

		Gorka* wzgorze = new Gorka(gorka, vec3(-8.4, -0.4, -4.8), vec3(0.1, 0.1, 0.1), -10);
		scene.AddObject(wzgorze);
		Gorka* wzgorze2 = new Gorka(gorka, vec3(-4, -0.7, -7.3), vec3(0.1, 0.1, 0.1), 90);
		scene.AddObject(wzgorze2);
		Gorka* wzgorze3 = new Gorka(gorka, vec3(-2, -0.5, -4), vec3(0.1, 0.1, 0.1), 10);
		scene.AddObject(wzgorze3);
		// Gorki


		sky = new Skydome(skydome, vec3(0, 0, 0), vec3(3, 1.5, 3), 0.f);
		scene.AddObject(sky);


		Droga* Firetruck = new Droga(firetruck, vec3(-13, 0.25, 2), vec3(0.4, 0.4, 0.4), -90);
		scene.AddObject(Firetruck);
		Droga* Firetruck2 = new Droga(firetruck, vec3(-12, 0.2, -2.5), vec3(0.4, 0.4, 0.4), 0);
		scene.AddObject(Firetruck2);


		// OGIEN 

		Fire* ogien = new Fire(fire0, vec3(-2.55, 5.5, 0.65), vec3(0.2, 0.13, 0.13), 1, 0);
		scene.AddObject(ogien);
		Fire* ogien2 = new Fire(fire0, vec3(0.38, 5.5, 0.65), vec3(0.2, 0.13, 0.13), 0, 0);
		scene.AddObject(ogien2);
		Fire* ogien3 = new Fire(fire0, vec3(3.23, 5.5, 0.65), vec3(0.2, 0.13, 0.13), 2, 0);
		scene.AddObject(ogien3);
		Fire* ogien4 = new Fire(fire0, vec3(6.02, 5.5, 0.65), vec3(0.2, 0.13, 0.13), 4, 0);
		scene.AddObject(ogien4);
		Fire* ogien5 = new Fire(fire0, vec3(-5.5, 5.5, 0.65), vec3(0.2, 0.13, 0.13), 5, 0);
		scene.AddObject(ogien5);

		// Budynki!


		Building* WI2 = new Building(budynek, vec3(0, 0, 0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject(WI2);
		Building* OutGlassDoor = new Building(outGlassDoor, vec3(-0.3, -0.05, 2.4), vec3(0.15, 0.13, 0.13), 0);
		scene.AddObject(OutGlassDoor);
		Building* OutGlassDoor2 = new Building(outGlassDoor, vec3(10.5, -0.05, 2.4), vec3(0.15, 0.13, 0.13), 0);
		scene.AddObject(OutGlassDoor2);
		Building* OutGlassDoor3 = new Building(outGlassDoor, vec3(16.8, -0.05, -11.7), vec3(0.15, 0.13, 0.13), 90);
		scene.AddObject(OutGlassDoor3);

		Roof* WI2_dach = new Roof(dach, vec3(0, 0, 0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject(WI2_dach);

		Roof* WI2_okna = new Roof(okna, vec3(0, 0, 0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject(WI2_okna);

		Building* PUM = new Building(budynekpum, vec3(14.3, 0, -12), vec3(0.13, 0.13, 0.13), 90);
		scene.AddObject(PUM);

		Roof* PUM_dach = new Roof(dach, vec3(14.3, 0, -12), vec3(0.13, 0.13, 0.13), 90);
		scene.AddObject(PUM_dach);

		Roof* PUM_okna = new Roof(okna, vec3(14.3, 0, -12), vec3(0.13, 0.13, 0.13), 90);
		scene.AddObject(PUM_okna);

		// Drzewa

		Tree* Drzewko = new Tree(tree, vec3(-13, 0, -15), vec3(0.2, 0.2, 0.2), 0);
		scene.AddObject(Drzewko);
		Tree* DrzewkoKorona = new Tree(koronaDrzewa, vec3(-13, 0, -15), vec3(0.2, 0.2, 0.2), 0);
		scene.AddObject(DrzewkoKorona);

		Tree* Drzewko2 = new Tree(tree, vec3(-13.2, 0, -13), vec3(0.2, 0.2, 0.2), 0);
		scene.AddObject(Drzewko2);
		Tree* DrzewkoKorona2 = new Tree(koronaDrzewa, vec3(-13.2, 0, -13), vec3(0.2, 0.2, 0.2), 0);
		scene.AddObject(DrzewkoKorona2);

		Tree* Drzewko3 = new Tree(tree, vec3(-12.8, -0.02, -10), vec3(0.3, 0.3, 0.3), 0);
		scene.AddObject(Drzewko3);
		Tree* DrzewkoKorona3 = new Tree(koronaDrzewa, vec3(-12.8, -0.02, -10), vec3(0.3, 0.3, 0.3), 0);
		scene.AddObject(DrzewkoKorona3);


		Tree* Drzewko4 = new Tree(tree, vec3(-13.2, 0, -7), vec3(0.3, 0.3, 0.3), 0);
		scene.AddObject(Drzewko4);
		Tree* DrzewkoKorona4 = new Tree(koronaDrzewa, vec3(-13.2, 0, -7), vec3(0.3, 0.3, 0.3), 0);
		scene.AddObject(DrzewkoKorona4);

		Tree* Drzewko5 = new Tree(tree, vec3(-13.0, -0.04, -5), vec3(0.3, 0.3, 0.3), 0);
		scene.AddObject(Drzewko5);
		Tree* DrzewkoKorona5 = new Tree(koronaDrzewa, vec3(-13.0, -0.04, -5), vec3(0.3, 0.3, 0.3), 0);
		scene.AddObject(DrzewkoKorona5);


		Tree* Drzewko6 = new Tree(tree, vec3(-13.0, -0.04, 0), vec3(0.3, 0.3, 0.3), 60);
		scene.AddObject(Drzewko6);
		Tree* DrzewkoKorona6 = new Tree(koronaDrzewa, vec3(-13.0, -0.04, 0), vec3(0.3, 0.3, 0.3), 60);
		scene.AddObject(DrzewkoKorona6);

		Tree* Drzewko7 = new Tree(tree, vec3(-12.5, -0.04, 3), vec3(0.2, 0.2, 0.2), 30);
		scene.AddObject(Drzewko7);
		Tree* DrzewkoKorona7 = new Tree(koronaDrzewa, vec3(-12.5, -0.04, 3), vec3(0.2, 0.2, 0.2), 30);
		scene.AddObject(DrzewkoKorona7);


		Tree* Drzewko8 = new Tree(tree, vec3(-12.0, -0.01, 5.4), vec3(0.2, 0.2, 0.2), 0);
		scene.AddObject(Drzewko8);
		Tree* DrzewkoKorona8 = new Tree(koronaDrzewa, vec3(-12.0, -0.01, 5.4), vec3(0.2, 0.2, 0.2), 0);
		scene.AddObject(DrzewkoKorona8);


		/// Lasek
		Tree* Drzewko9 = new Tree(tree, vec3(-2, -0.01, -8.5), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(Drzewko9);//
		Tree* DrzewkoKorona9 = new Tree(koronaDrzewa, vec3(-2, -0.01, -8.5), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(DrzewkoKorona9);//

		Tree* Drzewko11 = new Tree(tree, vec3(-5, 0.6, -8.4), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject(Drzewko11);//
		Tree* DrzewkoKorona11 = new Tree(koronaDrzewa, vec3(-5, 0.6, -8.4), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject(DrzewkoKorona11);//

		Tree* Drzewko12 = new Tree(tree, vec3(-4.3, 0.6, -6.8), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(Drzewko12);//
		Tree* DrzewkoKorona12 = new Tree(koronaDrzewa, vec3(-4.3, 0.6, -6.8), vec3(0.1, 0.1, 0.1), 0);
		scene.AddObject(DrzewkoKorona12);//

		Tree* Drzewko13 = new Tree(tree, vec3(-5.5, -0.01, -11.3), vec3(0.3, 0.3, 0.3), 0);
		scene.AddObject(Drzewko13);//
		Tree* DrzewkoKorona13 = new Tree(koronaDrzewa, vec3(-5.5, -0.01, -11.3), vec3(0.3, 0.3, 0.3), 0);
		scene.AddObject(DrzewkoKorona13);//

		Tree* zywoplot = new Tree(bush, vec3(-15.0, -0.01, 8.3), vec3(0.1, 0.1, 0.5), 0);
		scene.AddObject(zywoplot);
		Tree* zywoplot4 = new Tree(bush, vec3(-15.0, -0.01, 12.3), vec3(0.1, 0.1, 0.5), 0);
		scene.AddObject(zywoplot4);


		Tree* zywoplot2 = new Tree(bush, vec3(-15.0, -0.01, 0.1), vec3(0.1, 0.1, 0.5), 0);
		scene.AddObject(zywoplot2);
		Tree* zywoplot3 = new Tree(bush, vec3(-15.0, -0.01, -4.1), vec3(0.1, 0.1, 0.5), 0);
		scene.AddObject(zywoplot3);
		Tree* zywoplot5 = new Tree(bush, vec3(-15.0, -0.01, -8.1), vec3(0.1, 0.1, 0.5), 0);
		scene.AddObject(zywoplot5);
		Tree* zywoplot6 = new Tree(bush, vec3(-6, -0.01, -17.5), vec3(0.1, 0.1, 0.5), 90);
		scene.AddObject(zywoplot6);
		Tree* zywoplot7 = new Tree(bush, vec3(-2, -0.01, -17.5), vec3(0.1, 0.1, 0.5), 90);
		scene.AddObject(zywoplot7);
		Tree* zywoplot8 = new Tree(bush, vec3(-6.0, -0.01, -8.1), vec3(0.1, 0.1, 0.5), 0);
		scene.AddObject(zywoplot8);
		Tree* zywoplot9 = new Tree(bush, vec3(9.3, -0.01, -13.7), vec3(0.1, 0.1, 0.5), 130);
		scene.AddObject(zywoplot9);
		Tree* zywoplot10 = new Tree(bush, vec3(15, -0.01, -11.5), vec3(0.1, 0.1, 0.5), 90);
		scene.AddObject(zywoplot10);
		Tree* zywoplot11 = new Tree(bush, vec3(15, -0.01, 5.2), vec3(0.1, 0.1, 0.5), 0);
		scene.AddObject(zywoplot11);
		Tree* zywoplot12 = new Tree(bush, vec3(18, -0.01, 0.5), vec3(0.1, 0.1, 0.5), 90);
		scene.AddObject(zywoplot12);
		Tree* zywoplot13 = new Tree(bush, vec3(-3.9, -0.01, 6.7), vec3(0.1, 0.1, 0.6), 90);
		scene.AddObject(zywoplot13);

		Tree* zywoplot_przed_szkola = new Tree(bush, vec3(-3.0, -0.01, -6.0), vec3(0.04, 0.04, 0.09), 90);
		scene.AddObject(zywoplot_przed_szkola);

		Tree* zywoplot_przed_szkola2 = new Tree(bush, vec3(-4, -0.01, -6.0), vec3(0.04, 0.04, 0.09), 90);
		scene.AddObject(zywoplot_przed_szkola2);

		Porsche* porsche3 = new Porsche(porsche, vec3(11.0, 0.2, -5), vec3(0.008, 0.008, 0.008), 90);
		scene.AddObject(porsche3);

		Porsche* porsche4 = new Porsche(porsche, vec3(12.5, 0.2, -8), vec3(0.008, 0.008, 0.008), -90);
		scene.AddObject(porsche4);





		/// LEVEL 1
		Model3D* level1_floor = new Model3D("../Resources/Maps/Level1/floortexture.bmp");
		level1_floor->load("../Resources/Models/Level1/level1_floor.obj");
		Model3D* level1_walls = new Model3D("../Resources/Maps/Level1/walltexture.bmp");
		level1_walls->load("../Resources/Models/Level1/level1_walls.obj");
		Model3D* level1_windows = new Model3D("../Resources/Maps/okno.bmp");
		level1_windows->load("../Resources/Models/Level1/level1_windows.obj");
		Model3D* level1_doors = new Model3D("../Resources/Maps/Level1/doortexture.bmp");
		level1_doors->load("../Resources/Models/Level1/level1_doors.obj");
		Model3D* level1_insidedoors = new Model3D("../Resources/Maps/Level1/glassdoor.bmp");
		level1_insidedoors->load("../Resources/Models/Level1/level1_insidedoors.obj");
		Model3D* level1_ceiling = new Model3D("../Resources/Maps/Level1/ceilingtexture.bmp");
		level1_ceiling->load("../Resources/Models/Level1/level1_ceiling.obj");
		Model3D* level1_lift = new Model3D("../Resources/Maps/Level1/lifttexture.bmp");
		level1_lift->load("../Resources/Models/Level1/level1_lift.obj");
		Model3D* level1_desk_frame = new Model3D("../Resources/Maps/Level1/aluminium.bmp"); // lawki
		level1_desk_frame->load("../Resources/Models/Level1/level1_desk_frame.obj");
		Model3D* level1_desk_top = new Model3D("../Resources/Maps/Level1/Wood.bmp");
		level1_desk_top->load("../Resources/Models/Level1/level1_desk_top.obj");
		Model3D* level1_doorback = new Model3D("../Resources/Maps/Level1/doorback.bmp"); // Widok za drzwiami
		level1_doorback->load("../Resources/Models/Level1/level1_doorback.obj");
		Model3D* level1_sklepik = new Model3D("../Resources/Maps/Level1/sklepik.bmp"); // sklepik
		level1_sklepik->load("../Resources/Models/Level1/level1_sklepik.obj");
		Model3D* level1_pvr = new Model3D("../Resources/Maps/Level1/pvr.bmp"); // pvr
		level1_pvr->load("../Resources/Models/Level1/level1_pvr.obj");
		Model3D* level1_teacherdesk = new Model3D("../Resources/Maps/Level1/Wood.bmp"); //teacher desk
		level1_teacherdesk->load("../Resources/Models/Level1/level1_teacherdesk.obj");
		Model3D* level1_interactiveboard = new Model3D("../Resources/Maps/Level1/interactiveboard.bmp"); //tablica multimedialna
		level1_interactiveboard->load("../Resources/Models/Level1/level1_interactiveboard.obj");
		Model3D* level1_chairs = new Model3D("../Resources/Maps/Level1/chairs.bmp"); //krzesla
		level1_chairs->load("../Resources/Models/Level1/level1_chairs.obj");
		Model3D* level1_laptop = new Model3D("../Resources/Maps/Level1/laptop.bmp"); //krzesla
		level1_laptop->load("../Resources/Models/Level1/level1_laptop.obj");



	
			Level1* Level1_floor = new Level1(level1_floor, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_floor); // podloga
			Level1* Level1_walls = new Level1(level1_walls, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_walls); // sciany
			Level1* Level1_windows = new Level1(level1_windows, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_windows); // okna
			Level1* Level1_doors = new Level1(level1_doors, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_doors); // drzwi
			Level1* Level1_insidedoors = new Level1(level1_insidedoors, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_insidedoors); // drzwi korytarz
			Level1* Level1_ceiling = new Level1(level1_ceiling, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_ceiling); // sufit
			Level1* Level1_lift = new Level1(level1_lift, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_lift); // winda
			Level1* Level1_desk_frame = new Level1(level1_desk_frame, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_desk_frame); //lawki
			Level1* Level1_desk_top = new Level1(level1_desk_top, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_desk_top); //lawki
			Level1* Level1_doorback = new Level1(level1_doorback, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_doorback); //tlo za drzwiami
			Level1* Level1_sklepik = new Level1(level1_sklepik, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_sklepik); //sklepik
			Level1* Level1_pvr = new Level1(level1_pvr, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_pvr); //pvr
			Level1* Level1_teacherdesk = new Level1(level1_teacherdesk, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_teacherdesk); //teacher desk
			Level1* Level1_interactiveboard = new Level1(level1_interactiveboard, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_interactiveboard); //teacher desk
			Level1* Level1_chairs = new Level1(level1_chairs, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_chairs); //teacher desk
			Level1* Level1_laptop = new Level1(level1_laptop, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject1(Level1_laptop); //laptop
	


		Model3D* level2_floor = new Model3D("../Resources/Maps/Level1/floortexture.bmp");
		level2_floor->load("../Resources/Models/Level2/level2_floor.obj");
		Model3D* level2_walls = new Model3D("../Resources/Maps/Level1/walltexture.bmp");
		level2_walls->load("../Resources/Models/Level2/level2_walls.obj");
		Model3D* level2_windows = new Model3D("../Resources/Maps/okno.bmp");
		level2_windows->load("../Resources/Models/Level2/level2_windows.obj");
		Model3D* level2_insidedoors = new Model3D("../Resources/Maps/Level1/glassdoor.bmp");
		level2_insidedoors->load("../Resources/Models/Level2/level2_glassdoor.obj");
		Model3D* level2_ceiling = new Model3D("../Resources/Maps/Level1/ceilingtexture.bmp");
		level2_ceiling->load("../Resources/Models/Level2/level2_ceiling.obj");

		fire2[0] = new Model3D("../Resources/Maps/fire/fire2.bmp"); // Zaimportowanie tekstury budynku
		fire2[1] = new Model3D("../Resources/Maps/fire/fire3.bmp"); // Zaimportowanie tekstury budynku
		fire2[2] = new Model3D("../Resources/Maps/fire/fire4.bmp"); // Zaimportowanie tekstury budynku
		fire2[3] = new Model3D("../Resources/Maps/fire/fire5.bmp"); // Zaimportowanie tekstury budynku
		fire2[4] = new Model3D("../Resources/Maps/fire/fire6.bmp"); // Zaimportowanie tekstury budynku
		fire2[5] = new Model3D("../Resources/Maps/fire/fire7.bmp"); // Zaimportowanie tekstury budynku
		fire2[6] = new Model3D("../Resources/Maps/fire/fire8.bmp"); // Zaimportowanie tekstury budynku
		fire2[7] = new Model3D("../Resources/Maps/fire/fire9.bmp"); // Zaimportowanie tekstury budynkus
		fire2[0]->load("../Resources/Models/fire.obj");
		fire2[1]->load("../Resources/Models/fire.obj");
		fire2[2]->load("../Resources/Models/fire.obj");
		fire2[3]->load("../Resources/Models/fire.obj");
		fire2[4]->load("../Resources/Models/fire.obj");
		fire2[5]->load("../Resources/Models/fire.obj");
		fire2[6]->load("../Resources/Models/fire.obj");
		fire2[7]->load("../Resources/Models/fire.obj");


		Fire* ogien20 = new Fire(fire2, vec3(-3, -17.1, 50.9), vec3(0.5, 0.5, 0.13), 1, 70);
		scene.AddObject2(ogien20);
		Fire* ogien21 = new Fire(fire2, vec3(-3.7, -16.7, 51.2), vec3(0.5, 0.5, 0.13), 1, 10);
		scene.AddObject2(ogien21);
		Fire* ogien22 = new Fire(fire2, vec3(-5, -16.9, 51.2), vec3(0.5, 0.5, 0.13), 1, -10);
		scene.AddObject2(ogien22);
		Fire* ogien23 = new Fire(fire2, vec3(-5.7, -17.2, 50.8), vec3(0.5, 0.5, 0.13), 1, -70);
		scene.AddObject2(ogien23);

		 

		Level2* Level2_floor = new Level2(level2_floor, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject2(Level2_floor); // podloga
		Level2* Level2_walls = new Level2(level2_walls, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject2(Level2_walls); // sciany
		Level2* Level2_windows = new Level2(level2_windows, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject2(Level2_windows); // okna
		Level2* Level2_insidedoors = new Level2(level2_insidedoors, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject2(Level2_insidedoors); // drzwi korytarz
		Level2* Level2_ceiling = new Level2(level2_ceiling, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject2(Level2_ceiling); // sufit




		/// LEVEL 3
		Model3D* level3_floor = new Model3D("../Resources/Maps/Level1/floortexture.bmp");
		level3_floor->load("../Resources/Models/Level3/level3_floor.obj");
		Model3D* level3_walls = new Model3D("../Resources/Maps/Level1/walltexture.bmp");
		level3_walls->load("../Resources/Models/Level3/level3_walls.obj");
		Model3D* level3_windows = new Model3D("../Resources/Maps/okno.bmp");
		level3_windows->load("../Resources/Models/Level3/level3_windows.obj");
		Model3D* level3_doors = new Model3D("../Resources/Maps/Level1/doortexture.bmp");
		level3_doors->load("../Resources/Models/Level3/level3_doors.obj");
		Model3D* level3_insidedoors = new Model3D("../Resources/Maps/Level1/glassdoor.bmp");
		level3_insidedoors->load("../Resources/Models/Level3/level3_glassdoor.obj");
		Model3D* level3_ceiling = new Model3D("../Resources/Maps/Level1/ceilingtexture.bmp");
		level3_ceiling->load("../Resources/Models/Level3/level3_ceiling.obj");
		Model3D* level3_chairs = new Model3D("../Resources/Maps/Level1/chairs.bmp");
		level3_chairs->load("../Resources/Models/Level3/level3_chairs.obj");
		Model3D* level3_teacherdesk = new Model3D("../Resources/Maps/Level1/Wood.bmp");
		level3_teacherdesk->load("../Resources/Models/Level3/level3_teacherdesk.obj");
		Model3D* level3_deskframe = new Model3D("../Resources/Maps/Level1/aluminium.bmp");
		level3_deskframe->load("../Resources/Models/Level3/level3_deskframe.obj");
		Model3D* level3_desktop = new Model3D("../Resources/Maps/Level1/Wood.bmp");
		level3_desktop->load("../Resources/Models/Level3/level3_desktop.obj");
		Model3D* level3_computers = new Model3D("../Resources/Maps/computer.bmp");
		level3_computers->load("../Resources/Models/Level3/level3_computers.obj");
		Model3D* level3_elvis = new Model3D("../Resources/Maps/elvis.bmp");
		level3_elvis->load("../Resources/Models/Level3/level3_elvis.obj");


		// TRZECIE PIETRO BUDYNKU 

		Level3* Level3_floor = new Level3(level3_floor, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_floor); // podloga
		Level3* Level3_walls = new Level3(level3_walls, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_walls); // sciany
		Level3* Level3_windows = new Level3(level3_windows, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_windows); // okna
		Level3* Level3_doors = new Level3(level3_doors, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_doors); // drzwi
		Level3* Level3_insidedoors = new Level3(level3_insidedoors, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_insidedoors); // drzwi korytarz
		Level3* Level3_ceiling = new Level3(level3_ceiling, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_ceiling); // sufit
		Level3* Level3_chairs = new Level3(level3_chairs, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_chairs); // krzesla
		Level3* Level3_teacherdesk = new Level3(level3_teacherdesk, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_teacherdesk); // krzesla
		Level3* Level3_deskframe = new Level3(level3_deskframe, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_deskframe); // lawki nogi
		Level3* Level3_desktop = new Level3(level3_desktop, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_desktop); // lawki przykrycie
		Level3* Level3_computers = new Level3(level3_computers, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_computers); // komputery
		Level3* Level3_elvis = new Level3(level3_elvis, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
		scene.AddObject3(Level3_elvis); // komputery




		/// LEVEL 4
		Model3D* level4_floor = new Model3D("../Resources/Maps/Level1/floortexture.bmp");
		level4_floor->load("../Resources/Models/Level4/level4_floor.obj");
		Model3D* level4_walls = new Model3D("../Resources/Maps/Level1/walltexture.bmp");
		level4_walls->load("../Resources/Models/Level4/level4_walls.obj");
		Model3D* level4_windows = new Model3D("../Resources/Maps/okno.bmp");
		level4_windows->load("../Resources/Models/Level4/level4_windows.obj");
		Model3D* level4_doors = new Model3D("../Resources/Maps/Level1/doortexture.bmp");
		level4_doors->load("../Resources/Models/Level4/level4_doors.obj");
		Model3D* level4_insidedoors = new Model3D("../Resources/Maps/Level1/glassdoor.bmp");
		level4_insidedoors->load("../Resources/Models/Level4/level4_glassdoor.obj");
		Model3D* level4_ceiling = new Model3D("../Resources/Maps/Level1/ceilingtexture.bmp");
		level4_ceiling->load("../Resources/Models/Level4/level4_ceiling.obj");
		Model3D* level4_InteractiveDoor1 = new Model3D("../Resources/Maps/Level1/walltexture.bmp");
		level4_InteractiveDoor1->load("../Resources/Models/Level4/InteractiveDoor1.obj");
		Model3D* level4_InteractiveDoor2 = new Model3D("../Resources/Maps/Level1/walltexture.bmp");
		level4_InteractiveDoor2->load("../Resources/Models/Level4/InteractiveDoor2.obj");
		Model3D* level4_InteractiveDoor3 = new Model3D("../Resources/Maps/Level1/walltexture.bmp");
		level4_InteractiveDoor3->load("../Resources/Models/Level4/InteractiveDoor3.obj");
		Model3D* level4_InteractiveDoor4 = new Model3D("../Resources/Maps/Level1/walltexture.bmp");
		level4_InteractiveDoor4->load("../Resources/Models/Level4/InteractiveDoor4.obj");
		Model3D* level4_InteractiveDoor5 = new Model3D("../Resources/Maps/Level4/SafeDoor.bmp");
		level4_InteractiveDoor5->load("../Resources/Models/Level4/InteractiveDoor5.obj");
		Model3D* level4_InteractiveDoor6 = new Model3D("../Resources/Maps/Level4/SafeDoor.bmp");
		level4_InteractiveDoor6->load("../Resources/Models/Level4/InteractiveDoor6.obj");
		Model3D* level4_widescreen = new Model3D("../Resources/Maps/Level4/widescreen.bmp");
		level4_widescreen->load("../Resources/Models/Level4/widescreen.obj");
		Model3D* level4_widescreen2 = new Model3D("../Resources/Maps/Level4/widescreen2.bmp");
		level4_widescreen2->load("../Resources/Models/Level4/widescreen2.obj");
		Model3D* level4_widescreen3 = new Model3D("../Resources/Maps/Level4/widescreen3.bmp");
		level4_widescreen3->load("../Resources/Models/Level4/widescreen3.obj");
		Model3D* level4_widescreen4 = new Model3D("../Resources/Maps/Level4/widescreen4.bmp");
		level4_widescreen4->load("../Resources/Models/Level4/widescreen4.obj");
		Model3D* level4_widescreen5 = new Model3D("../Resources/Maps/Level4/widescreen5.bmp");
		level4_widescreen5->load("../Resources/Models/Level4/widescreen5.obj");
		Model3D* level4_widedesks = new Model3D("../Resources/Maps/Level4/wideDesks.bmp");
		level4_widedesks->load("../Resources/Models/Level4/wideDesks.obj");
		Model3D* level4_widewalls = new Model3D("../Resources/Maps/Level4/wideWalls.bmp");
		level4_widewalls->load("../Resources/Models/Level4/wideWalls.obj");
		Model3D* level4_Macbook = new Model3D("../Resources/Maps/Level4/Macbook/macbookTexture.bmp");
		level4_Macbook->load("../Resources/Models/Level4/Macbook/Macbook.obj");
		Model3D* level4_officeChair = new Model3D("../Resources/Maps/Level4/deskChair.bmp");
		level4_officeChair->load("../Resources/Models/Level4/OfficeChairs.obj");
		Model3D* level4_LuxuryCouch = new Model3D("../Resources/Maps/Level4/LuxuryCouch.bmp");
		level4_LuxuryCouch->load("../Resources/Models/Level4/LuxuryCouch.obj");
		Model3D* level4_LuxuryTable = new Model3D("../Resources/Maps/Level4/GoldTable.bmp");
		level4_LuxuryTable->load("../Resources/Models/Level4/LuxuryTable.obj");
		Model3D* level4_LuxuryTV = new Model3D("../Resources/Maps/Level4/LuxuryTV.bmp");
		level4_LuxuryTV->load("../Resources/Models/Level4/LuxuryTV.obj");
		Model3D* level4_Shelf = new Model3D("../Resources/Maps/Level1/Wood.bmp");
		level4_Shelf->load("../Resources/Models/Level4/Shelf.obj");
		Model3D* level4_Books = new Model3D("../Resources/Maps/Level4/BOOKS_TEXTURE.bmp");
		level4_Books->load("../Resources/Models/Level4/Books.obj");
		Model3D* level4_Bar = new Model3D("../Resources/Maps/Level4/BarTexture.bmp");
		level4_Bar->load("../Resources/Models/Level4/Bar.obj");
		Model3D* level4_littleShelf = new Model3D("../Resources/Maps/Level1/doorTexture.bmp");
		level4_littleShelf->load("../Resources/Models/Level4/littleShelf.obj");
		Model3D* level4_panele = new Model3D("../Resources/Maps/Level4/panele.bmp");
		level4_panele->load("../Resources/Models/Level4/panele.obj");
		Model3D* level4_roundTable = new Model3D("../Resources/Maps/Level4/roundTable.bmp");
		level4_roundTable->load("../Resources/Models/Level4/roundTable.obj");
		Model3D* level4_iPhoneX = new Model3D("../Resources/Maps/Level4/iPhoneX.bmp");
		level4_iPhoneX->load("../Resources/Models/Level4/iPhoneX.obj");
		Model3D* level4_camera = new Model3D("../Resources/Maps/Level4/level4_camera.bmp");
		level4_camera->load("../Resources/Models/Level4/level4_camera.obj");
		Model3D* level4_krzesla = new Model3D("../Resources/Maps/Level1/chairs.bmp");
		level4_krzesla->load("../Resources/Models/Level4/level4_krzesla.obj");
		Model3D* level4_fingerScanner = new Model3D("../Resources/Maps/Level4/fingerscanner.bmp");
		level4_fingerScanner->load("../Resources/Models/Level4/level4_fingerScanner.obj");


		//// CZWARTE PIETRO 


			Level4* Level4_floor = new Level4(level4_floor, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_floor); // podloga
			Level4* Level4_walls = new Level4(level4_walls, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_walls); // sciany
			Level4* Level4_windows = new Level4(level4_windows, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_windows); // okna
			Level4* Level4_doors = new Level4(level4_doors, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_doors); // drzwi
			Level4* Level4_insidedoors = new Level4(level4_insidedoors, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_insidedoors); // drzwi korytarz
			Level4* Level4_ceiling = new Level4(level4_ceiling, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_ceiling); // sufit
			InteractiveDoor* Level4_InteractiveDoor1 = new InteractiveDoor(level4_InteractiveDoor1, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0, 2);
			scene.AddObject4(Level4_InteractiveDoor1); // sdrzwi otwierane  1
			TablicaDrzwi[0] = Level4_InteractiveDoor1;

			InteractiveDoor* Level4_InteractiveDoor2 = new InteractiveDoor(level4_InteractiveDoor2, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0, 3);
			scene.AddObject4(Level4_InteractiveDoor2); // 2
			TablicaDrzwi[1] = Level4_InteractiveDoor2;

			InteractiveDoor* Level4_InteractiveDoor3 = new InteractiveDoor(level4_InteractiveDoor3, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0, 4);
			scene.AddObject4(Level4_InteractiveDoor3); // 3
			TablicaDrzwi[2] = Level4_InteractiveDoor3;

			InteractiveDoor* Level4_InteractiveDoor4 = new InteractiveDoor(level4_InteractiveDoor4, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0, 2);
			scene.AddObject4(Level4_InteractiveDoor4); // 4 
			TablicaDrzwi[3] = Level4_InteractiveDoor4;

			InteractiveDoor* Level4_InteractiveDoor5 = new InteractiveDoor(level4_InteractiveDoor5, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0, 3);
			scene.AddObject4(Level4_InteractiveDoor5); // 5
			TablicaDrzwi[4] = Level4_InteractiveDoor5;

			InteractiveDoor* Level4_InteractiveDoor6 = new InteractiveDoor(level4_InteractiveDoor6, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0, 4);
			scene.AddObject4(Level4_InteractiveDoor6); // 6 
			TablicaDrzwi[5] = Level4_InteractiveDoor6;

			Level4* Level4_widescreen = new Level4(level4_widescreen, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_widescreen); // Widescreen1
			Level4* Level4_widescreen2 = new Level4(level4_widescreen2, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_widescreen2); // Widescreen2
			Level4* Level4_widescreen3 = new Level4(level4_widescreen3, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_widescreen3); // Widescreen3
			Level4* Level4_widescreen4 = new Level4(level4_widescreen4, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_widescreen4); // Widescreen4
			Level4* Level4_widescreen5 = new Level4(level4_widescreen5, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_widescreen5); // Widescreen5
			Level4* Level4_widedesks = new Level4(level4_widedesks, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_widedesks); // Widedesks
			Level4* Level4_widewalls = new Level4(level4_widewalls, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_widewalls); // Widewalls
			Level4* Level4_macbook = new Level4(level4_Macbook, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_macbook); // MAcbook
			Level4* Level4_officeChair = new Level4(level4_officeChair, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_officeChair); //OfficeChairs
			Level4* Level4_LuxuryCouch = new Level4(level4_LuxuryCouch, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_LuxuryCouch); //LuxuryCouch
			Level4* Level4_LuxuryTable = new Level4(level4_LuxuryTable, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_LuxuryTable); //LuxuryTable
			Level4* Level4_LuxuryTV = new Level4(level4_LuxuryTV, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_LuxuryTV); //LuxuryTable
			Level4* Level4_Shelf = new Level4(level4_Shelf, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_Shelf); //Ksiazki
			Level4* Level4_Books = new Level4(level4_Books, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_Books); //Ksiazki
			Level4* Level4_Bar = new Level4(level4_Bar, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_Bar); //bar
			Level4* Level4_littleShelf = new Level4(level4_littleShelf, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_littleShelf); //littleShelf
			Level4* Level4_panele = new Level4(level4_panele, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_panele); //panele
			Level4* Level4_roundTable = new Level4(level4_roundTable, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_roundTable); //roundTable
			Level4* Level4_iPhoneX = new Level4(level4_iPhoneX, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_iPhoneX); //roundTable
			Level4* Level4_camera = new Level4(level4_camera, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_camera); //roundTable
			Level4* Level4_krzesla = new Level4(level4_krzesla, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_krzesla); //krzesla
			Level4* Level4_fingerScanner = new Level4(level4_fingerScanner, vec3(0.0, -7, 0.0), vec3(0.13, 0.13, 0.13), 0);
			scene.AddObject4(Level4_fingerScanner); //fingerscanner


			texturesLoaded = true;

}

void LoadingText(char* text, int a)
{


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.f, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 10.0); 

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	int moveRatio;
	if (rewardFoundFlag && !isGameOver) {
		glColor3f(0.f, 0.f, 0.2f);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
		
	}

	int b = 0;
	if (a != 0) b = 350;
	glRasterPos2f(600 - b, 600 - 10* a);
	int textLen = strlen(text);
	for (int i = 0; i < textLen; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}

	glPopMatrix();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}


void LoadingStatusBar(char* text, int a)
{

	     
	 /// 

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.f, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 10.0);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	if(finalCountdown> 50)
		glColor3f(0, 150, 0);
	else
		glColor3f(1.0f, 0.f, 0.f);


	int b = 0;
	if (a != 0) b = 350;
	glRasterPos2f((window_width/2) -10*a , window_height-25);
	int textLen = strlen(text);
	for (int i = 0; i < textLen; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}

	
	glPopMatrix();

	glPopMatrix();

	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();



}

void preGameFunction() {

	char* line0 = "WPROWADZENIE DO GRY ... ";
	char* line1 = "Nieposluszny student zlekcewazyl slowa prowadzacego i wbrew ostrzezeniom, po zajeciach pozostawil";
	char* line2 = "kabel zasilajacy wpiety do urzadzenia typu National Instruments Elvis II.";
	char* line3 = "Wtedy dosz³o do tragedii ... Ogien rozprzestrzenil sie bardzo szybko, lecz nie zajal jeszcze wszystkich pieter.";
	char* line4 = "Wciel sie w role odwaznego studenta, wynies z budynku do samochodu jak najwiecej";
	char* line13 = "cennego dla uczelni sprzetu i ocal pieniadze polskich podatnikow ...";
	char* line5 = "Patrz na czas! Kiedy minie, ogien przedostanie sie do serwerowni i doprowadzi do wybuchu poteznych stacji typu BLADE";
	char* line6 = "Wcisnij klawisz 'ENTER', aby rozpoczac rozgrywke...";
	char* line7 = " __ Sterowanie ____________________________________________________________________";
	char* line8 = "|  Poruszanie sie: W,S,A,D";
	char* line9 = "|  Wejdz w przedmiot, aby go podniesc";
	char* line10 ="|  G - Wyrzuc niesiony przedmiot";
	char* line11 ="|____Wyjscie z gry - ESC___________________________________________________________";

	LoadingText(line0, -10);
	LoadingText(line1, 1 );
	LoadingText(line2, 4);
	LoadingText(line3, 7);

	LoadingText(line4, 12);
	LoadingText(line13, 15);

	LoadingText(line5, 20);

	LoadingText(line6, 25);

	LoadingText(line7, 30);
	LoadingText(line8, 32);
	LoadingText(line9, 34);
	LoadingText(line10, 36);
	LoadingText(line11, 38);


}


void SwitchLevelPortal() {
	if (player->isOnLevel0 && player->pos.x >= -4.63 && player->pos.x <= -3.80 && player->pos.z >= -0.1 && player->pos.z <= 0.51)
		GoHigherLevel();
	if (player->isOnLevel1 && player->pos.x >= -5.12 && player->pos.x <= -4.13 && player->pos.z >= 2.69 && player->pos.z <= 2.73)
		GoHigherLevel();
	if (player->isOnLevel2 && player->pos.x >= -5.22 && player->pos.x <= -4.10 && player->pos.z >= 48.13 && player->pos.z <= 48.27)
		GoHigherLevel();
	if (player->isOnLevel3 && player->pos.x >= -5.13 && player->pos.x <= -4.00 && player->pos.z >= 23.15 && player->pos.z <= 23.19)
		GoHigherLevel();


	/// -------- Na dol 

	if (player->isOnLevel1 && player->pos.x >= -4.03 && player->pos.x <= -3.15 && player->pos.z >= 2.69 && player->pos.z <= 2.73)
		GoLowerLevel();
	if (player->isOnLevel2 && player->pos.x >= -4.06 && player->pos.x <= -3.01 && player->pos.z >= 48.13 && player->pos.z <= 48.27)
		GoLowerLevel();
	if (player->isOnLevel3 && player->pos.x >= -4.06 && player->pos.x <= -3.04 && player->pos.z >=23.15 && player->pos.z <= 23.19)
		GoLowerLevel();
	if (player->isOnLevel4 && player->pos.x >= -4.06 && player->pos.x <= -3.04 && player->pos.z >= -12.46 && player->pos.z <= -12.35)
		GoLowerLevel();
}


void GoHigherLevel() {
//	scene.SceneSwitch(player->CurrentLevel);

	player->LevelSwitch(1);
	//printf("Is on Level : ");
	//printf(" %d ", player->CurrentLevel);
}

void GoLowerLevel() {
//	scene.SceneSwitch(player->CurrentLevel);

	player->LevelSwitch(0);
	//printf("Is on Level : ");
	//printf(" %d ", player->CurrentLevel);
}

void BackgroundUnderText() {
	scene.preGameBox->pos.x = player->pos.x;
	scene.preGameBox->pos.y = player->pos.y ;
	scene.preGameBox->pos.z = player->pos.z;
	scene.TextBackground = true;
}

void GameOverFunction() {

	char* line0 = "KONIEC GRY ... ";
	char* line1 = "_______________________________________________________";
	char* line2 = "Udalo ci sie ocalic przed pozarem: ";
	char* line3 = scoreAsString;
	char* line6 = "             PLN"; 
	char* line4 = "pieniedzy polskich podatnikow. Gratulacje! ";

	char elvisCount[12];
	char htcCount[12];
	char projectorCount[12]; 
	char microphoneCount[12];

	sprintf(elvisCount, "%d", player->CollectedRewards[1]);
	sprintf(htcCount, "%d", player->CollectedRewards[2]);
	sprintf(projectorCount, "%d", player->CollectedRewards[3]);
	sprintf(microphoneCount, "%d", player->CollectedRewards[4]);


	char* line7 = elvisCount;
	char* line8 = "     x National Instruments ELVIS II";


	char* line9 = htcCount;
	char* line10 = "     x gogli VR HTC Vive";

	char* line11 = projectorCount;
	char* line12  = "     x w pelni sprawnych projektorow";

	char* line13 = microphoneCount;
	char* line14 = "      x nadal dzialajacych mikrofonow";

	char* line5 = "_______________________________________________________";


	LoadingText(line0, -10);
	LoadingText(line1, 1);
	LoadingText(line2, 4);
	LoadingText(line3, 7);
	LoadingText(line6, 7);
	LoadingText(line4, 10);
	LoadingText(line5, 13);

	LoadingText(line7, 17);
	LoadingText(line8, 17);

	LoadingText(line9, 20);
	LoadingText(line10, 20);

	LoadingText(line11, 23);
	LoadingText(line12, 23);

	LoadingText(line13, 26);
	LoadingText(line14, 26);


}

void StatusBarBackground() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.f, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 10.0);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
	glColor3f(0.1, 0.0f, 0.3f); // Red
	glVertex2f(0, window_height-40);    // x, y
	glVertex2f(window_width, window_height-40);
	glVertex2f(window_width, window_height);
	glVertex2f(0, window_height);
	glEnd();

	glFlush();
	glPopMatrix();

	glPopMatrix();

	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}

void RewardNameDecoder() {
	int typeID = player->HeldRewardID;
	int type = RewardManager->RewardsHolder[typeID]->RewardType;

	
	switch (type) {
	case 1:
		rewardFound = "Podniosles NI Elvis II - 1250 PLN";
		break;
	case 2:
		rewardFound = "Podniosles gogle VR HTC Vive - 2599 PLN";
		break;
	case 3:
		rewardFound = "Podniosles w pelni sprawny projektor - 499 PLN";
		break;
	case 4:
		rewardFound = "Podniosles jeszcze dzialajacy mikrofon - 735 PLN";
		break;
	}

}


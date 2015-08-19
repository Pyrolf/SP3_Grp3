#include "SceneBase.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	// Blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	
	glEnable(GL_CULL_FACE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
	
	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	
	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_DIRECTIONAL;
	lights[1].position.Set(1, 1, 0);
	lights[1].color.Set(1, 1, 0.5f);
	lights[1].power = 0.4f;
	//lights[1].kC = 1.f;
	//lights[1].kL = 0.01f;
	//lights[1].kQ = 0.001f;
	//lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	//lights[1].cosInner = cos(Math::DegreeToRadian(30));
	//lights[1].exponent = 3.f;
	//lights[1].spotDirection.Set(0.f, 1.f, 0.f);
	
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);
	
	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 18, 36, 1.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 10.f);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);
	//meshList[GEO_TORUS] = MeshBuilder::GenerateCylinder("torus", 36, 36, 5, 1);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);

	// Load the ground mesh and texture
	meshList[GEO_GROUND_BACKGROUND] = MeshBuilder::Generate2DMesh("GEO_GROUND_BACKGROUND", Color(1, 1, 1), 0.0f, 0.0f, 1024.0f, 800.0f);
	meshList[GEO_GROUND_BACKGROUND]->textureID = LoadTGA("Image//ground_background.tga");
	meshList[GEO_ICECAVE_BACKGROUND] = MeshBuilder::Generate2DMesh("GEO_ICECAVE_BACKGROUND", Color(1, 1, 1), 0.0f, 0.0f, 1024.0f, 800.0f);
	meshList[GEO_ICECAVE_BACKGROUND]->textureID = LoadTGA("Image//icecave_background.tga");
	//Assignment
	meshList[GEO_TILEHERO_FRAME0] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME0", 32.0f, 32.0f, 4, 6, 0, 3);
	meshList[GEO_TILEHERO_FRAME0]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME1] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME1", 32.0f, 32.0f, 4, 6, 1, 3);
	meshList[GEO_TILEHERO_FRAME1]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME2] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME2", 32.0f, 32.0f, 4, 6, 2, 3);
	meshList[GEO_TILEHERO_FRAME2]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME3] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME3", 32.0f, 32.0f, 4, 6, 3, 3);
	meshList[GEO_TILEHERO_FRAME3]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME4] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME4", 32.0f, 32.0f, 4, 6, 4, 3);
	meshList[GEO_TILEHERO_FRAME4]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME5] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME5", 32.0f, 32.0f, 4, 6, 5, 3);
	meshList[GEO_TILEHERO_FRAME5]->textureID = LoadTGA("Image//tile_hero.tga");
	
	meshList[GEO_TILEHERO_FRAME0_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME0_FRONT", 32.0f, 32.0f, 4, 6, 0, 0);
	meshList[GEO_TILEHERO_FRAME0_FRONT]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME1_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME1_FRONT", 32.0f, 32.0f, 4, 6, 1, 0);
	meshList[GEO_TILEHERO_FRAME1_FRONT]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME2_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME2_FRONT", 32.0f, 32.0f, 4, 6, 2, 0);
	meshList[GEO_TILEHERO_FRAME2_FRONT]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME3_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME3_FRONT", 32.0f, 32.0f, 4, 6, 3, 0);
	meshList[GEO_TILEHERO_FRAME3_FRONT]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME4_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME4_FRONT", 32.0f, 32.0f, 4, 6, 4, 0);
	meshList[GEO_TILEHERO_FRAME4_FRONT]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME5_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME5_FRONT", 32.0f, 32.0f, 4, 6, 5, 0);
	meshList[GEO_TILEHERO_FRAME5_FRONT]->textureID = LoadTGA("Image//tile_hero.tga");

	meshList[GEO_TILEHERO_FRAME0_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME0_BACK", 32.0f, 32.0f, 4, 6, 0, 2);
	meshList[GEO_TILEHERO_FRAME0_BACK]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME1_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME1_BACK", 32.0f, 32.0f, 4, 6, 1, 2);
	meshList[GEO_TILEHERO_FRAME1_BACK]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME2_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME2_BACK", 32.0f, 32.0f, 4, 6, 2, 2);
	meshList[GEO_TILEHERO_FRAME2_BACK]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME3_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME3_BACK", 32.0f, 32.0f, 4, 6, 3, 2);
	meshList[GEO_TILEHERO_FRAME3_BACK]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME4_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME4_BACK", 32.0f, 32.0f, 4, 6, 4, 2);
	meshList[GEO_TILEHERO_FRAME4_BACK]->textureID = LoadTGA("Image//tile_hero.tga");
	meshList[GEO_TILEHERO_FRAME5_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEHERO_FRAME5_BACK", 32.0f, 32.0f, 4, 6, 5, 2);
	meshList[GEO_TILEHERO_FRAME5_BACK]->textureID = LoadTGA("Image//tile_hero.tga");
	
	meshList[GEO_TILEENEMY_FRAME0] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME0", 32.0f, 32.0f, 4, 4, 0, 3);
	meshList[GEO_TILEENEMY_FRAME0]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME1] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME1", 32.0f, 32.0f, 4, 4, 1, 3);
	meshList[GEO_TILEENEMY_FRAME1]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME2] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME2", 32.0f, 32.0f, 4, 4, 2, 3);
	meshList[GEO_TILEENEMY_FRAME2]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME3] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME3", 32.0f, 32.0f, 4, 4, 3, 3);
	meshList[GEO_TILEENEMY_FRAME3]->textureID = LoadTGA("Image//tile_zombie.tga");
	
	meshList[GEO_TILEENEMY_FRAME0_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME0_FRONT", 32.0f, 32.0f, 4, 4, 0, 1);
	meshList[GEO_TILEENEMY_FRAME0_FRONT]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME1_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME1_FRONT", 32.0f, 32.0f, 4, 4, 1, 1);
	meshList[GEO_TILEENEMY_FRAME1_FRONT]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME2_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME2_FRONT", 32.0f, 32.0f, 4, 4, 2, 1);
	meshList[GEO_TILEENEMY_FRAME2_FRONT]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME3_FRONT] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME3_FRONT", 32.0f, 32.0f, 4, 4, 3, 1);
	meshList[GEO_TILEENEMY_FRAME3_FRONT]->textureID = LoadTGA("Image//tile_zombie.tga");
	
	meshList[GEO_TILEENEMY_FRAME0_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME0_BACK", 32.0f, 32.0f, 4, 4, 0, 0);
	meshList[GEO_TILEENEMY_FRAME0_BACK]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME1_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME1_BACK", 32.0f, 32.0f, 4, 4, 1, 0);
	meshList[GEO_TILEENEMY_FRAME1_BACK]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME2_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME2_BACK", 32.0f, 32.0f, 4, 4, 2, 0);
	meshList[GEO_TILEENEMY_FRAME2_BACK]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_TILEENEMY_FRAME3_BACK] = MeshBuilder::GeneratePartOfSpriteSheet2D("GEO_TILEENEMY_FRAME3_BACK", 32.0f, 32.0f, 4, 4, 3, 0);
	meshList[GEO_TILEENEMY_FRAME3_BACK]->textureID = LoadTGA("Image//tile_zombie.tga");
	meshList[GEO_ALERT] = MeshBuilder::Generate2DMesh("GEO_ALERT", Color(1, 1, 1), 0.0f, 0.0f, 32.0f, 32.0f);
	meshList[GEO_ALERT]->textureID = LoadTGA("Image//alert_sign.tga");
	
	meshList[GEO_TILEGROUND] = MeshBuilder::Generate2DMesh("GEO_TILEGROUND", Color(1, 1, 1), 0.0f, 0.0f, 32.0f, 32.0f);
	meshList[GEO_TILEGROUND]->textureID = LoadTGA("Image//tile1_ground.tga");
	meshList[GEO_MAGMA] = MeshBuilder::Generate2DMesh("GEO_MAGMA", Color(1, 1, 1), 0.0f, 0.0f, 32.0f, 32.0f);
	meshList[GEO_MAGMA]->textureID = LoadTGA("Image//tile2_magma.tga");
	meshList[GEO_DOOR] = MeshBuilder::Generate2DMesh("GEO_DOOR", Color(1, 1, 1), 0.0f, 0.0f, 32.0f, 32.0f);
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//tile3_door.tga");
	meshList[GEO_LIVE_1] = MeshBuilder::Generate2DMesh("GEO_LIVE_red", Color(5, 0, 0), 0.0f, 0.0f, 5.0f, 5.0f);
	meshList[GEO_LIVE_2] = MeshBuilder::Generate2DMesh("GEO_LIVE_orange", Color(3, 3, 0), 0.0f, 0.0f, 5.0f, 5.0f);
	meshList[GEO_LIVE_3] = MeshBuilder::Generate2DMesh("GEO_LIVE_green", Color(0, 5, 0), 0.0f, 0.0f, 5.0f, 5.0f);
	//meshList[GEO_LIVE]->textureID = LoadTGA("Image//health.tga");
	meshList[GEO_HEALTH_BAR] = MeshBuilder::Generate2DMesh("GEO_HEALTH_BAR", Color(1, 1, 1), 0.0f, 0.0f, 18.f, 6.f);
	meshList[GEO_HEALTH_BAR]->textureID = LoadTGA("Image//healthbar.tga");
	

	meshList[GEO_MAINMENU] = MeshBuilder::Generate2DMesh("GEO_MAINMENU", Color(1, 1, 1), 0.0f, 0.0f, 1024.0f, 800.0f);
	meshList[GEO_MAINMENU]->textureID = LoadTGA("Image//mainmenu.tga");
	meshList[GEO_PAUSE] = MeshBuilder::Generate2DMesh("GEO_PAUSE", Color(1, 1, 1), 0.0f, 0.0f, 1024.0f, 800.0f);
	meshList[GEO_PAUSE]->textureID = LoadTGA("Image//pause.tga");
	meshList[GEO_GAMEOVER] = MeshBuilder::Generate2DMesh("GEO_GAMEOVER", Color(1, 1, 1), 0.0f, 0.0f, 1024.0f, 800.0f);
	meshList[GEO_GAMEOVER]->textureID = LoadTGA("Image//gameover.tga");
	
	meshList[GEO_TILE_KILLZONE] = MeshBuilder::Generate2DMesh("GEO_TILE_KILLZONE", Color(1, 1, 1), 0.0f, 0.0f, 32.0f, 32.0f);
	meshList[GEO_TILE_KILLZONE]->textureID = LoadTGA("Image//tile10_killzone.tga");
	meshList[GEO_TILE_SAFEZONE] = MeshBuilder::Generate2DMesh("GEO_TILE_SAFEZONE", Color(1, 1, 1), 0.0f, 0.0f, 32.0f, 32.0f);
	meshList[GEO_TILE_SAFEZONE]->textureID = LoadTGA("Image//tile11_safezone.tga");

	meshList[GEO_LADDER] = MeshBuilder::Generate2DMesh("GEO_LADDER", Color(1, 1, 1), 0.0f, 0.0f, 32.0f, 32.0f);
	meshList[GEO_LADDER]->textureID = LoadTGA("Image//tile1_ladder_rear.tga");


	
	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	bLightEnabled = true;
}

void SceneBase::Update(double dt)
{
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if(Application::IsKeyPressed('5'))
	{
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('6'))
	{
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('7'))
	{
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('8'))
	{
		bLightEnabled = true;
	}
	else if(Application::IsKeyPressed('9'))
	{
		bLightEnabled = false;
	}

	if(Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(10.f * dt);
	if(Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(10.f * dt);
	if(Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(10.f * dt);
	if(Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(10.f * dt);
	if(Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(10.f * dt);
	if(Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(10.f * dt);

	camera.Update(dt);

	fps = (float)(1.f / dt);
}

static const float SKYBOXSIZE = 1000.f;

void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
				modelStack.LoadIdentity();
				modelStack.Translate(x, y, 0);
				modelStack.Scale(size, size, size);
				glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
				glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
				glUniform1i(m_parameters[U_LIGHTENABLED], 0);
				glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mesh->textureID);
				glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
				for(unsigned i = 0; i < text.length(); ++i)
				{
					Mtx44 characterSpacing;
					characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
					Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
					glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
					mesh->Render((unsigned)text[i] * 6, 6);
				}
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
			modelStack.PopMatrix();
		viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderMeshIn2D(Mesh *mesh, const bool enableLight, const float size, const float x, const float y, const bool rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -80, 80, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();

}

void SceneBase::Render2DMesh(Mesh *mesh, bool enableLight, float size, float x, float y, bool rotate)
{
	if (rotate)
		glDisable(GL_CULL_FACE);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 1024, 0, 800, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	//modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	if (rotate)
	{
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Translate(-32, 0, 0);
	}
	modelStack.Scale(size, size, size);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();

	if(rotate)
		glEnable(GL_CULL_FACE);
}

void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneBase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
}

void SceneBase::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
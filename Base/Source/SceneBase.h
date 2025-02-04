#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Minimap.h"

class SceneBase : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		GEO_SPHERE5,
		GEO_SPHERE6,
		GEO_SPHERE7,
		GEO_SPHERE8,
		GEO_SPHERE9,
		GEO_QUAD,
		GEO_CUBE,
		GEO_RING,
		GEO_CONE,

		// Background
		GEO_GROUND_BACKGROUND,
		GEO_ICECAVE_BACKGROUND,
		

		// SP3
		// Normal zombie
		// Front
		GEO_NORMAL_ZOMBIE_FRONT_0,
		GEO_NORMAL_ZOMBIE_FRONT_1,
		GEO_NORMAL_ZOMBIE_FRONT_2,
		// Back
		GEO_NORMAL_ZOMBIE_BACK_0,
		GEO_NORMAL_ZOMBIE_BACK_1,
		GEO_NORMAL_ZOMBIE_BACK_2,
		// Side
		GEO_NORMAL_ZOMBIE_SIDE_0,
		GEO_NORMAL_ZOMBIE_SIDE_1,
		GEO_NORMAL_ZOMBIE_SIDE_2,

		// Smart zombie
		// Front
		GEO_SMART_ZOMBIE_FRONT_0,
		GEO_SMART_ZOMBIE_FRONT_1,
		GEO_SMART_ZOMBIE_FRONT_2,
		// Back
		GEO_SMART_ZOMBIE_BACK_0,
		GEO_SMART_ZOMBIE_BACK_1,
		GEO_SMART_ZOMBIE_BACK_2,
		// Side
		GEO_SMART_ZOMBIE_SIDE_0,
		GEO_SMART_ZOMBIE_SIDE_1,
		GEO_SMART_ZOMBIE_SIDE_2,
		
		// Tank zombie
		// Front
		GEO_TANK_ZOMBIE_FRONT_0,
		GEO_TANK_ZOMBIE_FRONT_1,
		GEO_TANK_ZOMBIE_FRONT_2,
		// Back
		GEO_TANK_ZOMBIE_BACK_0,
		GEO_TANK_ZOMBIE_BACK_1,
		GEO_TANK_ZOMBIE_BACK_2,
		// Side
		GEO_TANK_ZOMBIE_SIDE_0,
		GEO_TANK_ZOMBIE_SIDE_1,
		GEO_TANK_ZOMBIE_SIDE_2,

		// Hunter zombie
		// Front
		GEO_HUNTER_ZOMBIE_FRONT_0,
		GEO_HUNTER_ZOMBIE_FRONT_1,
		GEO_HUNTER_ZOMBIE_FRONT_2,
		// Back
		GEO_HUNTER_ZOMBIE_BACK_0,
		GEO_HUNTER_ZOMBIE_BACK_1,
		GEO_HUNTER_ZOMBIE_BACK_2,
		// Side
		GEO_HUNTER_ZOMBIE_SIDE_0,
		GEO_HUNTER_ZOMBIE_SIDE_1,
		GEO_HUNTER_ZOMBIE_SIDE_2,

		// Alert Sign
		GEO_ZOMBIE_ALERT_SIGN,
		
		// Range
		GEO_NORMAL_ZOMBIE_ATTACK_RANGE,
		GEO_NORMAL_ZOMBIE_REPEL_RANGE,

		GEO_SMART_ZOMBIE_ATTACK_RANGE,
		GEO_SMART_ZOMBIE_REPEL_RANGE,

		GEO_TANK_ZOMBIE_ATTACK_RANGE,
		GEO_TANK_ZOMBIE_REPEL_RANGE,

		GEO_HUNTER_ZOMBIE_ATTACK_RANGE,
		GEO_HUNTER_ZOMBIE_REPEL_RANGE,


		// Tiles
		GEO_TILEGROUND,
		GEO_MAGMA,
		GEO_DOOR,
		GEO_LIVE_1,
		GEO_LIVE_2,
		GEO_LIVE_3,
		GEO_HEALTH_BAR,

		// Rear Tiles
		GEO_LADDER,

		// Screen
		GEO_MAINMENU,
		GEO_PAUSE,
		GEO_GAMEOVER,
		GEO_HIGHSCORE,
		GEO_INSTRUCTIONS1,
		GEO_INSTRUCTIONS2,
		GEO_TILE_KILLZONE,
		GEO_TILE_SAFEZONE,

		GEO_TEXT,
		
		GEO_HACK_WINDOW,
		GEO_HACK_RED_BAR,
		GEO_HACK_WHITE_BAR,
		GEO_HACK_YELLOW_BAR,

		GEO_BLACK,
		GEO_BLACK_HOLE,

		GEO_FLASHLIGHT,
		GEO_FLASH,
		NUM_GEOMETRY,
	};

public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size=1.0f, float x=0.0f, float y=0.0f, bool rotate=false);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void Render2DMesh(Mesh *mesh, const bool enableLight, const float size=1.0f, const float x=0.0f, const float y=0.0f, const bool rotateY=false, const float rotateZ = 0.0f);


	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Mesh* meshList[NUM_GEOMETRY];
private:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;

	Light lights[2];

	bool bLightEnabled;

	float fps;
};

#endif
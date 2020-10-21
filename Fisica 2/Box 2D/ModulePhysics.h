#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"
#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class b2World;
class b2Body;

// TODO 6: Create a small class that keeps a pointer to the b2Body
// and has a method to request the position
// then write the implementation in the .cpp
// Then make your circle creation function to return a pointer to that class
class Physicbody {
public:
	Physicbody()
	{
		body = NULL;
	}
	~Physicbody() {
	}
	void GetPosition(int& x, int& y) const;
	float GetRotation()const;
private:
	int width, height;
	b2Body *body;
};


class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	void CreateCircle(float x, float y, float rad) {
		b2BodyDef body;
		body.type = b2_dynamicBody;
		float radius = PIXEL_TO_METERS(rad);
		body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

		b2Body* b = world->CreateBody(&body);

		b2CircleShape shape;
		shape.m_radius = radius;
		b2FixtureDef fixture;
		fixture.shape = &shape;

		b->CreateFixture(&fixture);
	};
	void CreateSquare(float x, float y) {
		b2BodyDef square;
		square.type = b2_dynamicBody;
		b2Vec2 vertices[4];
		vertices[0].Set(0.0f, 0.0f);
		vertices[1].Set(2.0f, 0.0f);
		vertices[2].Set(0.0f, 1.0f);
		vertices[3].Set(2.0f, 1.0f);

		square.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
		b2Body* b = world->CreateBody(&square);

		int32 count = 4;
		b2PolygonShape polygon;
		polygon.Set(vertices, count);

		b2FixtureDef fixture;
		fixture.shape = &polygon;
		fixture.density = 1.0f;

		b->CreateFixture(&fixture);
	}
	void CreateChain(float x, float y) {
		b2BodyDef chain;
		chain.type = b2_dynamicBody;
		int points[24] = {
			-38, 80,
			-44, -54,
			-16, -60,
			-16, -17,
			19, -19,
			19, -79,
			61, -77,
			57, 73,
			17, 78,
			20, 16,
			-25, 13,
			-9, 72
		};
		b2Vec2 vec[12];
		int h = 0;

		for (int i = 0; i < 24; i += 2)
		{
			vec[h].Set(PIXEL_TO_METERS(points[i]), PIXEL_TO_METERS(points[i + 1]));
			h++;
		}

		chain.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
		b2Body* b = world->CreateBody(&chain);


		b2ChainShape chains;
		chains.CreateLoop(vec, 12);

		b2FixtureDef fixture;
		fixture.shape = &chains;


		b->CreateFixture(&fixture);
	}
	// TODO 4: Move body creation to 3 functions to create circles, rectangles and chains

private:

	bool debug;
	b2World* world;
};
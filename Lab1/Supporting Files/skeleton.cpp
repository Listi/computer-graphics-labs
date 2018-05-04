#include <iostream>
#include "glm/glm.hpp"
#include "SDL.h"
#include "SDLauxiliary.h"
#include "TestModel.h"

using namespace std;
using glm::vec3;
using glm::mat3;

struct Intersection
{
    vec3 position;
    float distance;
    int triangleIndex;
};

// ----------------------------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 100;
const int SCREEN_HEIGHT = 100;
float focalLength = 100;
mat3 R;
vec3 cameraPos(0, 0, - 3);
vector<Triangle> triangles;
SDL_Surface* screen;
int t;

// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();

//Initializing ClosestIntersection
bool ClosestIntersection(vec3 start, vec3 dir, const vector<Triangle>& triangles, Intersection& closestIntersection);

bool ClosestIntersection(vec3 start, vec3 dir, const vector<Triangle>& triangles, Intersection& closestIntersection) {
    
    //Tip from the lab:
    closestIntersection.distance = std::numeric_limits<float>::max();
    bool foundIntersection = false;
    
    for (size_t i = 0; i < triangles.size(); ++i) {
        Triangle triangle = triangles[i];
        
        //Given calculations
        vec3 v0 = triangle.v0*R;
        vec3 v1 = triangle.v1*R;
        vec3 v2 = triangle.v2*R;
        vec3 e1 = v1 - v0;
        vec3 e2 = v2 - v0;
        vec3 b = start - v0;
        mat3 A(-dir, e1, e2);
        vec3 x = glm::inverse(A) * b;
        //
        
        float xx = x.x;
        float xy = x.y;
        float xz = x.z;
        
        if (0 <= xy && 0 <= xz && xy + xz <= 1 && xx >= 0) {
            if (xx < closestIntersection.distance) {
                closestIntersection.distance = xx;
                closestIntersection.position = x;
                closestIntersection.triangleIndex = i;
            }
            foundIntersection = true;
        }
    }
    return foundIntersection;
}

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.
    LoadTestModel(triangles);

	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
	}

	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Update()
{
	// Compute frame time:
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
	cout << "Render time: " << dt << " ms." << endl;
}

void Draw()
{
	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);
    
    vec3 base_color(0,0,0);
	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{
		for( int x=0; x<SCREEN_WIDTH; ++x )
		{
            vec3 dir(x - SCREEN_WIDTH / 2, y - SCREEN_HEIGHT / 2, focalLength);
            Intersection inter;
            if (ClosestIntersection(cameraPos, dir, triangles, inter)) {
                PutPixelSDL(screen, x, y, triangles[inter.triangleIndex].color);
            }
            else {
                PutPixelSDL(screen, x, y, base_color);
            }
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

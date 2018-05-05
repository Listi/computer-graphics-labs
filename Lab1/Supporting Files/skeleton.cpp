#include <iostream>
#include "glm/glm.hpp"
#include "SDL.h"
#include "SDLauxiliary.h"
#include "TestModel.h" //Including the triangle struct and LoadTestModel()

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
mat3 R; //Rotation matrix
float yaw; //Camera rotation around the y-axis
vec3 cameraPos(0, 0, - 3);
vector<Triangle> triangles;
SDL_Surface* screen;
int t;
vec3 lightPos(0, -0.5, -0.7);
vec3 lightColor = 14.f * vec3(1,1,1);

// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();

//init
//vec3 DirectLight(const Intersection& i);
bool ClosestIntersection(vec3 start, vec3 dir, const vector<Triangle>& triangles, Intersection& closestIntersection, int triangleIndex);

bool ClosestIntersection(vec3 start, vec3 dir, const vector<Triangle>& triangles, Intersection& closestIntersection, int triangleIndex) {
    
    //Tip from the lab:
    closestIntersection.distance = std::numeric_limits<float>::max();
    bool intersection = false;
    
    //Loop over all given triangles
    for (size_t i = 0; i < triangles.size(); ++i) {
        Triangle triangle = triangles[i];
        
        vec3 v0 = triangle.v0*R;
        vec3 v1 = triangle.v1*R;
        vec3 v2 = triangle.v2*R;
        vec3 e1 = v1 - v0; //Vector that is parallel to the edge of the triangle between v0 and v1
        vec3 e2 = v2 - v0; //Vector that is parallel to the edge of the triangle between v0 and v2
        //The following is just the solving of the equation for the intersection point x
        vec3 b = start - v0;
        mat3 A(-dir, e1, e2);
        vec3 x = glm::inverse(A) * b;
        
        //The coordinates of the intersection point x
        float xx = x.x;
        float xy = x.y;
        float xz = x.z;
        
        //Check if the point is on the border or inside the triangle,
        //in that case we have a hit
        if (0 <= xy && 0 <= xz && xy + xz <= 1 && xx >= 0) {
            if (xx < closestIntersection.distance) {
                closestIntersection.distance = xx;
                closestIntersection.position = x;
                closestIntersection.triangleIndex = i;
            }
            intersection = true;
        }
    }
    return intersection;
}

vec3 DirectLight(const Intersection& i){
    vec3 normal = triangles[i.triangleIndex].normal;
    float dist = glm::distance(lightPos, i.position);
    vec3 base_color(0,0,0);

    vec3 distLight;
    distLight.x = lightPos.x - i.position.x;
    distLight.y = lightPos.y - i.position.y;
    distLight.z = lightPos.z - i.position.z;

    vec3 r = glm::normalize(distLight);
    float rDotNorm = glm::dot(r, normal);

    //Because too lazy to #import M_PI
    vec3 B = lightColor/(4*3.14159265359f*dist*dist);

    if (rDotNorm<0){
        rDotNorm = 0;
    }

    vec3 D = B * rDotNorm;
    Intersection inter;
    if (ClosestIntersection(i.position, r, triangles, inter, i.triangleIndex)){
        float newObjectDist = glm::distance(inter.position, i.position);
        if (newObjectDist < dist){
            return base_color;
        }
    }
    return D;
}

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.
    LoadTestModel(triangles); //Load the room

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
    
    //Works slowly, why?
    float pan = 0.2;
    Uint8* keystate = SDL_GetKeyState(0);
    if (keystate[SDLK_UP]){
        cameraPos.z += pan;
    }
    if (keystate[SDLK_DOWN]){
        cameraPos.z -= pan;
    }
    if (keystate[SDLK_LEFT]){
        yaw += pan;
    }
    if (keystate[SDLK_RIGHT]){
        yaw -= pan;
    }
    
    //Update the Rotation matrix depending on the (potential) new angle
    R[0][0] = cos(yaw);  R[0][1] = 0; R[0][2] = sin(yaw);
    R[1][0] = 0; R[1][1] = 1;  R[1][2] = 0;
    R[2][0] = -sin(yaw);  R[2][1] = 0;  R[2][2] = cos(yaw);
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
            vec3 direction(x-SCREEN_WIDTH/2, y-SCREEN_HEIGHT/2, focalLength);
            Intersection inter;
            if (ClosestIntersection(cameraPos, direction, triangles, inter, -1)) {
                vec3 color = triangles[inter.triangleIndex].color; //The triangle's own color
                vec3 colorWithDirLighting = color * DirectLight(inter); //The triangle's own color with direct lighting
                
                PutPixelSDL(screen, x, y, DirectLight(inter));
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

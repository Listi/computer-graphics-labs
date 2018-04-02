// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include "glm/glm.hpp"
#include <vector>
#include "SDLauxiliary.h"

//Task 3
#include <random>
#include <iostream>

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;


//vector<float> result( 10 );


//Task 2.3
//
//vec3 red(1,0,0); // topLeft
//vec3 blue(0,0,1); // topRight
//vec3 green(0,1,0); // bottomLeft
//vec3 yellow(1,1,0); // bottomRight
//vector<vec3> leftSide( SCREEN_HEIGHT );
//vector<vec3> rightSide( SCREEN_HEIGHT );
//vector<vec3> horizontal ( SCREEN_WIDTH );


//Task 3

vector<vec3> stars( 1000 );
int t;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Update();
void Draw();

// Task 2.2 a)
//
//std::vector<float> Interpolate( float a, float b, vector<float>& result ) {
//    for (int i=0; i<result.size(); ++i) {
//        result[i] = a+i;
//    }
//    return result;
//}


//Task 2.2 b)
//std::vector<vec3> Interpolate( vec3 a, vec3 b, vector<vec3>& result ) {
//
//    float xValue = (b.x - a.x)/(result.size()-1);
//    float yValue = (b.y - a.y)/(result.size()-1);
//    float zValue = (b.z - a.z)/(result.size()-1);
//
//    result[0].x = a.x;
//    result[0].y = a.y;
//    result[0].z = a.z;
//
//    for(int i=1; i<result.size(); ++i){
//        result[i].x = result[i-1].x+xValue;
//        result[i].y = result[i-1].y+yValue;
//        result[i].z = result[i-1].z+zValue;
//    }
//    return result;
//}

//Task 2.3
//
//std::vector<vec3> Interpolate( vec3 a, vec3 b, vector<vec3>& result ) {
//
//    float xValue = (b.x - a.x)/(result.size()-1);
//    float yValue = (b.y - a.y)/(result.size()-1);
//    float zValue = (b.z - a.z)/(result.size()-1);
//
//    result[0].x = a.x;
//    result[0].y = a.y;
//    result[0].z = a.z;
//
//    for(int i=1; i<result.size(); ++i){
//        result[i].x = result[i-1].x+xValue;
//        result[i].y = result[i-1].y+yValue;
//        result[i].z = result[i-1].z+zValue;
//    }
//    return result;
//}



// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> xyrand(-1.0, 1.0);
    std::uniform_real_distribution<> zrand(0.0000001, 1.0);
    
    for(int star = 0; star<stars.size(); ++star){
        
        float randX = xyrand(gen);
        float randY = xyrand(gen);
        float randZ = zrand(gen);
        
        stars[star].x = randX;
        stars[star].y = randY;
        stars[star].z = randZ;
    }
    
    
    // Task 2.2 a)
    //
    //    vector<float> result( 10 ); // Create a vector width 10 floats
    //    Interpolate( 5, 14, result ); // Fill it with interpolated values
    //
    //    for( int i=0; i<result.size(); ++i )
    //        cout << result[i] << " "; // Print the result to the terminal
    
    
    //Task 2.2 b)
    
    //    vector<vec3> result( 4 );
    //    vec3 a(1,4,9.2);
    //    vec3 b(4,1,9.8);
    //    Interpolate( a, b, result );
    //    for( int i=0; i<result.size(); ++i )
    //    {
    //        cout << "( "
    //        << result[i].x << ", "
    //        << result[i].y << ", "
    //        << result[i].z << " ) ";
    //    }
    
    screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
    t = SDL_GetTicks();
    
    while( NoQuitMessageSDL() )
    {
        Update();
        Draw();
    }
    SDL_SaveBMP( screen, "screenshot.bmp" );
    return 0;
}


// Task 2
//void Draw()
//{
//
////    Task 2.3
////
////    vector<vec3> downLeft = Interpolate( red, yellow, leftSide );
////    vector<vec3> downRight = Interpolate( blue, green, rightSide );
//
//
//    if( SDL_MUSTLOCK(screen) )
//        SDL_LockSurface(screen);
//    for( int y=0; y<SCREEN_HEIGHT; ++y )
//    {
////        Task 2.3
////
////        vector<vec3> right = Interpolate( downLeft[y], downRight[y], horizontal );
//        for( int x=0; x<SCREEN_WIDTH; ++x )
//        {
////            Task 2.3
////
////            PutPixelSDL( screen, x, y, right[x] );
//
//            vec3 color(0,0,1);
//            PutPixelSDL(screen, x, y, color);
//        }
//
//    }
//    if( SDL_MUSTLOCK(screen) )
//        SDL_UnlockSurface(screen);
//    SDL_UpdateRect( screen, 0, 0, 0, 0 );
//}

void Update()
{
    int t2 = SDL_GetTicks();
    float dt = float(t2-t);
    t = t2;
    
    for( int s=0; s<stars.size(); ++s ) {
        
    stars[s].z = stars[s].z - 0.0002*dt;
        
    if( stars[s].z <= 0 )
        stars[s].z += 1;
    }
    
}

void Draw()
{
    
    SDL_FillRect( screen, 0, 0 );
    if( SDL_MUSTLOCK(screen) )
        SDL_LockSurface(screen);
    float halfHeight = SCREEN_HEIGHT / 2;
    float halfWidth = SCREEN_WIDTH / 2;
    for( size_t s=0; s<stars.size(); ++s )
    {
        int u = halfHeight * (stars[s].x / stars[s].z) + halfWidth;
        int v = halfHeight * (stars[s].y / stars[s].z) + halfHeight;
        
        vec3 color(1,1,1);
        PutPixelSDL(screen, u, v, color);
    }
    if( SDL_MUSTLOCK(screen) )
        SDL_UnlockSurface(screen);
    SDL_UpdateRect( screen, 0, 0, 0, 0 );
}



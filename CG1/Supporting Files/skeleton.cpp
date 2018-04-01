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

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;

vector<float> result( 10 );

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
std::vector<float> Interpolate( float a, float b, vector<float>& result ) {
    for (int i=0; i<result.size(); ++i) {
        result[i] = a+i;
    }
    return result;
}

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
    
    vector<float> result( 10 ); // Create a vector width 10 floats
    Interpolate( 5, 14, result ); // Fill it with interpolated values
    
    for( int i=0; i<result.size(); ++i )
        cout << result[i] << " "; // Print the result to the terminal
    
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	while( NoQuitMessageSDL() )
	{
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Draw()
{
    if( SDL_MUSTLOCK(screen) )
        SDL_LockSurface(screen);
    for( int y=0; y<SCREEN_HEIGHT; ++y )
    {
        for( int x=0; x<SCREEN_WIDTH; ++x )
        {
            vec3 color(0,0,1);
            PutPixelSDL( screen, x, y, color );
        }
        
    }
    if( SDL_MUSTLOCK(screen) )
        SDL_UnlockSurface(screen);
    SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

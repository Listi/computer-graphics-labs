#include <iostream>
#include "glm/glm.hpp"
#include "SDL.h"
#include "SDLauxiliary.h"
#include "TestModel.h"

using namespace std;
using glm::vec3;
using glm::ivec2;
using glm::mat3;

using glm::vec2;

// ----------------------------------------------------------------------------
// GLOBAL VARIABLES
float focalLength = 100;
const int SCREEN_WIDTH = 110;
const int SCREEN_HEIGHT = 110;
SDL_Surface* screen;
int t;
vector<Triangle> triangles;
vec3 cameraPos( 0, 0, -3.001 );
mat3 R;
float yaw = 0; // Yaw angle controlling camera rotation around y-axis
vec3 currentColor;


// ----------------------------------------------------------------------------
// STRUCTS

struct Pixel {
    int x;
    int y;
    float zinv;
};


// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();

void VertexShader( const vec3& v, ivec2& p ) {
    //P'=(P-C)*R
    //where {P'= projected3D = Position of the point in a coordinate system centered at the camera}
    //      {P = v = Position of the point}
    //      {C = cameraPos = Position of the camera}
    vec3 projected3D = (v - cameraPos)*R;
    // x = f*X/Z+W2 (here instead W/2 because of origin of the image)
    // y = f*Y/Z+H2 (here instead H/2 because of origin of the image)
    float projected2Dx = (focalLength*projected3D.x / projected3D.z+SCREEN_WIDTH/2);
    float projected2Dy = (focalLength*projected3D.y / projected3D.z+SCREEN_HEIGHT/2);
    p.x = projected2Dx;
    p.y = projected2Dy;
}

void Interpolate( ivec2 a, ivec2 b, vector<ivec2>& result) {
    int N = result.size();
    vec2 step = vec2(b-a) / float(max(N-1,1));
    vec2 current( a );
    for (int i=0; i<N; ++i){
        result[i] = current;
        current += step;
    }
}

void DrawLineSDL(SDL_Surface* surface, ivec2 a, ivec2 b, vec3 color) {
    ivec2 delta = glm::abs(a-b);
    int pixels = glm::max(delta.x, delta.y) + 1;
    vector<ivec2> line(pixels);
    Interpolate(a, b, line);
    for (int i= 0; i<pixels; ++i){
        float LinePixelX = line[i].x;
        float LinePixelY = line[i].y;
        PutPixelSDL(surface, LinePixelX, LinePixelY, color);
    }
}

void DrawPolygonEdges(const vector<vec3>& vertices){
    int V = vertices.size();
    
    // Transform each vertex from 3D world position to 2D image position:
    vector<ivec2> projectedVertices(V);
    for (int i=0; i<V; ++i){
        VertexShader(vertices[i], projectedVertices[i]);
    }
    
    // Loop over all vertices and draw the edge from it to the next vertex:
    for (int i=0; i<V; ++i){
        int j = (i+1)%V; //  The next vertex
        vec3 color(1,1,1);
        DrawLineSDL(screen, projectedVertices[i], projectedVertices[j], color);
    }
}

void ComputePolygonRows(const vector<ivec2>& vertexPixels, vector<ivec2>& leftPixels, vector<ivec2>& rightPixels) {
    
    // Find max and min y-value of the polygon
    // and compute the number of rows it occupies.
    int min = numeric_limits<int>::max();
    int max = numeric_limits<int>::min();
    for (int i = 0; i < vertexPixels.size(); ++i){
        if (vertexPixels[i].y<min){
            min = vertexPixels[i].y;
        }
        if (vertexPixels[i].y>max){
            max = vertexPixels[i].y;
        }
    }
    int numberOfRows = max-min+1;
    
    // Resize leftPixels and rightPixels
    // so that they have an element for each row.
    leftPixels.resize(numberOfRows);
    rightPixels.resize(numberOfRows);
    
    // Initialize the x-coordinates in leftPixels
    // to some really large value and the x-coordinates
    // in rightPixels to some really small value.
    for (int i = 0; i < numberOfRows; ++i){
        leftPixels[i].x = +numeric_limits<int>::max();
        rightPixels[i].x = -numeric_limits<int>::max();
        leftPixels[i].y = min + i;
        rightPixels[i].y = min + i;
    }
    
    // Loop through all edges of the polygon and use
    // linear interpolation to find the x-coordinate for
    // each row it occupies. Update the corresponding
    // values in rightPixels and leftPixels.
    for (int i = 0; i < vertexPixels.size(); ++i){
        int k = (i + 1) % vertexPixels.size();
        
        int firstX = vertexPixels[i].x;
        int firstY = vertexPixels[i].y;
        ivec2 first(firstX, firstY);
        
        int lastX = vertexPixels[k].x;
        int lastY = vertexPixels[k].y;
        ivec2 last(lastX, lastY);
        
        int deltaX = glm::abs(lastX-firstX);
        int deltaY = glm::abs(lastY-firstY);
        int numberOfPixels = glm::max(deltaX, deltaY) + 1;
        vec2 delta(deltaX, deltaY);
        
        vector<ivec2> line(numberOfPixels);
        Interpolate(first, last, line);
        
        for (int line_segment = 0; line_segment < line.size(); ++line_segment){
            int limitRow = line[line_segment].y - min;
            int currLineX = line[line_segment].x;
            if (currLineX < leftPixels[limitRow].x){
                leftPixels[limitRow].x = currLineX;
            }
            if (currLineX > rightPixels[limitRow].x){
                rightPixels[limitRow].x = currLineX;
            }
        }
    }
}

void DrawRows(const vector<ivec2>& leftPixels, const vector<ivec2>& rightPixels){
    for (int i = 0; i < leftPixels.size(); ++i){
        //        PutPixelSDL(screen, leftPixels[i], rightPixels[i], currentColor);
        DrawLineSDL(screen, leftPixels[i], rightPixels[i], currentColor);
    }
}

void DrawPolygon(const vector<vec3>& vertices){
    int V = vertices.size();
    vector<ivec2> vertexPixels(V);
    for(int i = 0; i < V; ++i){
        VertexShader(vertices[i], vertexPixels[i]);
    }
    vector<ivec2> leftPixels;
    vector<ivec2> rightPixels;
    ComputePolygonRows(vertexPixels, leftPixels, rightPixels);
    DrawRows(leftPixels, rightPixels);
}

int main( int argc, char* argv[] )
{
    // Test case for ComputePolygonRows()
    
    //    vector<ivec2> vertexPixels(3);
    //    vertexPixels[0] = ivec2(10, 5);
    //    vertexPixels[1] = ivec2(5, 10);
    //    vertexPixels[2] = ivec2(15, 15);
    //    vector<ivec2> leftPixels;
    //    vector<ivec2> rightPixels;
    //    ComputePolygonRows(vertexPixels, leftPixels, rightPixels);
    //    for (size_t row = 0; row < leftPixels.size(); ++row) {
    //        cout << "Start: ("
    //            << leftPixels[row].x << ","
    //            << leftPixels[row].y << "). "
    //            << "End: ("
    //            << rightPixels[row].x << ","
    //            << rightPixels[row].y << "). " << endl;
    //    }
    
    LoadTestModel( triangles );
    screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
    t = SDL_GetTicks();    // Set start value for timer.
    
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
    
    Uint8* keystate = SDL_GetKeyState(0);
    
    R[0][0] = cos(yaw);
    R[0][1] = 0;
    R[0][2] = sin(yaw);
    
    //down
    R[1][0] = 0;
    R[1][1] = 1;
    R[1][2] = 0;
    
    //forward
    R[2][0] = -sin(yaw);
    R[2][1] = 0;
    R[2][2] = cos(yaw);
    
    float pan = 0.02;
    
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
    
    if( keystate[SDLK_RSHIFT] )
        ;
    
    if( keystate[SDLK_RCTRL] )
        ;
    
    if( keystate[SDLK_w] )
        ;
    
    if( keystate[SDLK_s] )
        ;
    
    if( keystate[SDLK_d] )
        ;
    
    if( keystate[SDLK_a] )
        ;
    
    if( keystate[SDLK_e] )
        ;
    
    if( keystate[SDLK_q] )
        ;
}

void Draw()
{
    SDL_FillRect( screen, 0, 0 );
    
    if( SDL_MUSTLOCK(screen) )
        SDL_LockSurface(screen);
    
    for( int i=0; i<triangles.size(); ++i )
    {
        currentColor = triangles[i].color;
        vector<vec3> vertices(3);
        
        vertices[0] = triangles[i].v0;
        vertices[1] = triangles[i].v1;
        vertices[2] = triangles[i].v2;
        //        DrawPolygonEdges(vertices);
        DrawPolygon(vertices);
        
        //        for (int v=0; v<3; ++v){
        //            ivec2 projPos;
        //            VertexShader(vertices[v], projPos);
        //            vec3 color(1,1,1);
        //            PutPixelSDL(screen, projPos.x, projPos.y, color);
        //        }
    }
    
    if ( SDL_MUSTLOCK(screen) )
        SDL_UnlockSurface(screen);
    
    SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

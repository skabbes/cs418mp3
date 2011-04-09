#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "gfx/vec3.h"
#include <GL/glut.h>

using namespace std;
using namespace gfx;

class Model{
    private:
        vector<Vec3f> verticies;
        vector<Vec3f> normals;
        vector<Vec3i> faces;
        GLuint texture;
    public:
        Model(string filename);
        void computeNormals();
        void addTexture(string filename, bool wrap);
        void render();
};

#endif

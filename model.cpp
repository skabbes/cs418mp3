#include "model.h"
#include "textureloader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include <cmath>

Model::Model(string filename){

    ifstream in;
    in.open(filename.c_str(), ios::in);

    string command;
    float f1, f2, f3;


    while( in ){
        in >> command;
        if( in.eof() ) continue;
        
        if( command == "v" ){
            Vec3f v;
            in >> v[0];
            in >> v[1];
            in >> v[2];
            verticies.push_back(v);
        } else if (command == "f" ){
            Vec3i f;
            in >> f[0];
            in >> f[1];
            in >> f[2];

            // obj file format actually uses 1-indexed faces
            f[0] -= 1;
            f[1] -= 1;
            f[2] -= 1;
            faces.push_back(f);
        } 

        getline(in, command);
    }

    Vec3f zero(0, 0, 0);
    for(int i=0;i<verticies.size();i++){
        normals.push_back( zero );
    }

}

void Model::addTexture(string filename, bool wrap){
    texture = loadTexture(filename.c_str(), wrap ? 1: 0);
}

void Model::computeNormals(){
    for(int i=0;i<faces.size();i++){
        Vec3f one = verticies[ faces[i][0] ];
        Vec3f two = verticies[ faces[i][1] ];
        Vec3f three = verticies[ faces[i][2] ];
        
        Vec3f x = two - one;
        Vec3f y = three - one;
        Vec3f normal = cross(x, y);

        normals[ faces[i][0] ] += normal;
        normals[ faces[i][1] ] += normal;
        normals[ faces[i][2] ] += normal;
    }

    for(int i=0;i<normals.size();i++){
        unitize( normals[i] );
    }
}

void Model::render(){

    float x, y, z, theta;
    float nx, ny, nz;
    float ymax = .5;

    for(int i=0;i<faces.size();i++){
        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 1.0, 1.0);
            for(int j=0;j<3;j++){
                x = verticies[ faces[i][j] ][0];
                y = verticies[ faces[i][j] ][1];
                z = verticies[ faces[i][j] ][2];
                theta = atan2(x, z);

                nx = normals[ faces[i][j] ][0];
                ny = normals[ faces[i][j] ][1];
                nz = normals[ faces[i][j] ][2];

                glNormal3f(nx, ny, nz);
                glTexCoord2d( (20.0 *  theta ) / (2 * M_PI), y / ymax);
                glVertex3f(x, y, z);
            }
        glEnd();

/*
        glBegin(GL_LINES);
            glColor3f(1.0, 0, 0);
            Vec3f v = verticies[ faces[i][0] ];
            Vec3f n = v + (normals[ faces[i][0] ] * .5);

            glVertex3f(v[0], v[1], v[2]);
            glVertex3f(n[0], n[1], n[2]);

            v = verticies[ faces[i][1] ];
            n = v + (normals[ faces[i][1] ] * .5);

            glVertex3f(v[0], v[1], v[2]);
            glVertex3f(n[0], n[1], n[2]);

            v = verticies[ faces[i][2] ];
            n = v + (normals[ faces[i][2] ] * .5);

            glVertex3f(v[0], v[1], v[2]);
            glVertex3f(n[0], n[1], n[2]);

        glEnd();
*/
    }
}

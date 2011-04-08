#include "model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <GL/glut.h>

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

    for(int i=0;i<faces.size();i++){
        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 1.0, 1.0);

            glNormal3f( normals[ faces[i][0] ][0], normals[faces[i][0]][1], normals[faces[i][0]][2] );

            glVertex3f( verticies[ faces[i][0] ][0], verticies[faces[i][0]][1], verticies[faces[i][0]][2] );

            glNormal3f( normals[faces[i][1]][0], normals[faces[i][1]][1], normals[faces[i][1]][2] );
            glVertex3f( verticies[faces[i][1]][0], verticies[faces[i][1]][1], verticies[faces[i][1]][2] );

            glNormal3f( normals[faces[i][2]][0], normals[faces[i][2]][1], normals[faces[i][2]][2] );
            glVertex3f( verticies[faces[i][2]][0], verticies[faces[i][2]][1], verticies[faces[i][2]][2] );
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

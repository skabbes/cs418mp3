varying vec3 V;
varying vec3 N;
varying float dist;

uniform vec3 velocity;
uniform vec3 eye;

void main(void)
{  

  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

  // Set up the normals for the vertex shader
  V = vec3(gl_ModelViewMatrix * gl_Vertex);
  N = normalize(gl_NormalMatrix * gl_Normal);

  // calculate distance so I can calculate fog later
  dist = distance(eye, vec3(gl_Vertex) );
}

#version 330 core
//in vec3 position; // input vertex position from mesh
//in vec2 texcoord; // input vertex texture coordinate from mesh
//in vec3 normal;   // input vertex normal from mesh
//
//// uniform variables are exposed as node slots
//uniform mat4 projection; //description="camera projection matrix"
//uniform mat4 modelview; // description="modelview transformation"
//
//// transposed inverse modelview transformation
//// (not exposed as slot but computed from "modelview")
//uniform mat4 modelviewTransposedInverse;
//
//out vec2 tc; // output texture coordinate of vertex
//out vec3 fn; // output fragment normal of vertex
//
//uniform mat4 rotationMatrix;


// IMplemetar rotacao de objeto na cena


void main(){
//  tc = texcoord;
//  fn = normalize( vec3( modelviewTransposedInverse * vec4(normal, 0.0) ) );
//  gl_Position = projection * modelview * vec4(position, 1.0) * rotationMatrix;
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);

  //Implemetar rotacao de objeto na cena
}

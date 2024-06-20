#version 330 core
precision highp float;
precision highp int;
out vec4 outColor;
//in vec2 tc; // texture coordinate of pixel (interpolated)
//in vec3 fn; // fragment normal of pixel (interpolated)
//
//uniform sampler2D myTexture; // wrap_s="REPEAT" wrap_t="REPEAT"
//uniform float texScale;  // description="texture scaling" defaultval="2.0"
//uniform int gsnMeshGroup; // not exposed as slot

void main() {

  //Implementar luz ambiente
//  vec3 normal = normalize(fn);
//  vec4 texColor  = texture(myTexture, texScale * tc);
//  vec4 col = vec4(0.0, 0.0, 0.0, 1.0);
//  if(gsnMeshGroup == 0) col = vec4(1.0, 0.0, 0.0, 1.0);
//  if(gsnMeshGroup == 1) col = vec4(0.0, 1.0, 0.0, 1.0);
//  if(gsnMeshGroup == 2) col = vec4(0.0, 0.0, 1.0, 1.0);
//  if(gsnMeshGroup == 3) col = vec4(1.0, 1.0, 0.0, 1.0);
//  outColor = col * texColor;
  outColor = vec4(0.0, 0.0, 0.0, 1.0);
}

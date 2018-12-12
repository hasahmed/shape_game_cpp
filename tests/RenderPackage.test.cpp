#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include "../shapegame"

using namespace shapegame;
int main(){
	Shape s(100, 12, ShapeType::Triangle, Color::BLACK);
  GLRenderObject g;
  g.vao = 10;
  g.vbo = 1;
  g.vertexAttribIndex = 5;
  float verts[] = {
    1, 2, 3
  };
  g.verts.assign(verts, verts + 3);
  assert(g.verts[0] == 1);
  assert(g.verts[1] == 2);
  assert(g.verts[2] == 3);

  RenderPackage r(&s, &g);
  assert(r.glRenderObject->vao == 10);
  assert(r.glRenderObject->vbo == 1);
  assert(r.glRenderObject->vertexAttribIndex = 5);
  assert(r.glRenderObject->verts[0] == 1);
  assert(r.glRenderObject->verts[1] == 2);
  assert(r.glRenderObject->verts[2] == 3);
  assert(r.shape->getHeight() == 100);
  assert(r.shape->getWidth() == 12);
  assert(r.shape->pos.getX() == 0);
  assert(r.shape->pos.getY() == 0);
  assert(r.shape->type == ShapeType::Triangle);
  std::cout << "RenderPackage.test.cpp Tests Passed" << std::endl;
}
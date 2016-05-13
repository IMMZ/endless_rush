// TODO: license text

#include "debugdraw.hpp"

#include <iostream>

namespace ibrengine
{

DebugDraw::DebugDraw():
  b2Draw(),
  sf::RenderWindow(sf::VideoMode(800, 600), "Debug Draw")
{
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
  sf::VertexArray arr(sf::LinesStrip, vertexCount + 1);
  for (int i = 0; i < vertexCount; ++i)
  {
    arr[i].position = sf::Vector2f(vertices[i].x * 32.0f, vertices[i].y * 32.0f);
    arr[i].color = sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
  }
  // Повторяем первую точку как последнюю, чтобы фигура рисовалась замкнутой
  arr[vertexCount] = arr[0];
  draw(arr);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
  sf::ConvexShape shape;
  shape.setPointCount(vertexCount);
  shape.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
  shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
  for (int i = 0; i < vertexCount; ++i)
  {
    shape.setPoint(i, sf::Vector2f(vertices[i].x * 32.0f, vertices[i].y * 32.0f));
  }
  draw(shape);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
  sf::CircleShape circle(radius * 32.0f);
  circle.setPosition(sf::Vector2f(center.x * 32.0f - radius * 32.0f, center.y * 32.0f - radius * 32.0f));
  circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
  draw(circle);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis,
    const b2Color& color)
{
  DrawCircle(center, radius, color);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
  sf::Vertex v1(sf::Vector2f(p1.x * 32.0f, p1.y * 32.0f));
  sf::Vertex v2(sf::Vector2f(p2.x * 32.0f, p2.y * 32.0f));
  v1.color = v2.color = sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
  sf::Vertex line[2] = { v1, v2 };
  draw(line, 2, sf::Lines);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{

}

} // namespace ibrengine

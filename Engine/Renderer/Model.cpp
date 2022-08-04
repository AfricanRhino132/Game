#include "Model.h"
#include "../Core/File.h"
#include <sstream>
#include <iostream>

namespace neu
{
    Model::Model(const std::string& filename)
    {
        Load(filename);
        m_radius = CalculateRadius();
    }

    void Model::Draw(Renderer& renderer, Vector2& position, float angle, const Vector2& scale)
    {
        //crae::Color color;
        //color.r = crae::random(256);
        //color.g = crae::random(256);
        //color.b = crae::random(256);
        //color.a = 255;

        //draw model
        for (unsigned int i = 0; i < m_points.size() - 1; i++)
        {
            neu::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
            neu::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

            renderer.DrawLine(p1, p2, m_color);
        }
    }

    void Model::Load(const std::string& filename)
    {
        std::string buffer;

        neu::ReadFile(filename, buffer);

        //read color
        std::istringstream stream(buffer);
        stream >> m_color;

        
        std::string line;
        std::getline(stream, line);

        size_t numPoints = std::stoi(line);

        for (size_t i = 0; i < numPoints; i++)
        {

            Vector2 point;

            stream >> point;

            m_points.push_back(point);
        }
    }

    float Model::CalculateRadius()
    {
        float radius = 0;

        for (auto& point : m_points)
        {
            if (point.Length() > radius)
            {
                radius = point.Length();
            }
        }

        return radius;
    }
}
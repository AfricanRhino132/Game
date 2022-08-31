#include "CameraComponent.h" 
#include "Framework/Actor.h" 
#include "Engine.h" 

namespace neu
{
    void CameraComponent::Initialize()
    {
        SetViewport(viewport_size);
    }

    void CameraComponent::Update()
    {
        // create camera view matrix 
        Matrix3x3 mxTranslation = Matrix3x3::CreateTranslation(-m_owner->m_transform.position);
        Matrix3x3 mxRotation = Matrix3x3::CreateRotation(-math::DegToRad(m_owner->m_transform.rotation));

        m_view = mxTranslation * mxRotation;

        if ((g_inputSystem.GetMousePosition().x >= 0 && g_inputSystem.GetMousePosition().x <= 50) || (g_inputSystem.GetMousePosition().x > 750 && g_inputSystem.GetMousePosition().x <= 810))
        {
            Vector2 origin{ g_renderer.getScreenWidth() / 2, g_renderer.getScreenHeight() / 2 };

            Vector2 dirVec =  g_inputSystem.GetMousePosition() - origin;

            dirVec.Normalize();

            m_owner->m_transform.position += dirVec * camera_speed * g_time.deltaTime;
        }

        if ((g_inputSystem.GetMousePosition().y >= 0 && g_inputSystem.GetMousePosition().y <= 35) || (g_inputSystem.GetMousePosition().y > 565 && g_inputSystem.GetMousePosition().y <= 610))
        {

            Vector2 origin{ g_renderer.getScreenWidth() / 2, g_renderer.getScreenHeight() / 2 };

            Vector2 dirVec = g_inputSystem.GetMousePosition() - origin;

            dirVec.Normalize();

            m_owner->m_transform.position += dirVec * camera_speed * g_time.deltaTime;
        }

        g_renderer.SetViewMatrix(m_view);
    }

    void CameraComponent::SetViewport(const Vector2& size)
    {
        Matrix3x3 mxTranslation = Matrix3x3::CreateTranslation(size * 0.5f);

        m_viewport = mxTranslation;
        g_renderer.SetViewportMatrix(m_viewport);
    }

    bool CameraComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CameraComponent::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, viewport_size);
        READ_DATA(value, camera_speed);

        return true;
    }

}
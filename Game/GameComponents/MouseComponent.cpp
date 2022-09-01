#include "MouseComponent.h"
#include "Engine.h"
#include <iostream>

void MouseComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void MouseComponent::Update()
{
    m_owner->m_transform.position = neu::g_inputSystem.GetMousePosition();
}

void MouseComponent::OnCollisionEnter(neu::Actor* other)
{
    std::cout << "Mouse Collided with " << other->GetName() << std::endl;
    ////Hover
    //if (other->GetName() == "StartText")
    //{
    //    auto text = other->GetComponent<neu::TextComponent>();
    //    text->color = { 255,0,0,255 };
    //}
    //if (other->GetName() == "ExitText")
    //{
    //    auto text = other->GetComponent<neu::TextComponent>();
    //    text->color = { 255,0,0,255 };
    //}

    //Clicked
    if (other->GetName() == "StartText" && neu::g_inputSystem.GetButtonState(neu::mouse_left) == neu::InputSystem::Pressed)
    {
        neu::Event event;
        event.name = "EVENT_START_GAME";
        neu::g_eventManager.Notify(event);
    }
    if (other->GetName() == "QuitText" && neu::g_inputSystem.GetButtonState(neu::mouse_left) == neu::InputSystem::Pressed)
    {
        neu::Event event;
        event.name = "EVENT_QUIT_GAME";
        neu::g_eventManager.Notify(event);
    }
}

void MouseComponent::OnCollisionExit(neu::Actor* other)
{
    //Hover Exit
    std::cout << "Collision Exited from " << other->GetName() << std::endl;
    //if (other->GetName() == "StartText")
    //{
    //    auto text = other->GetComponent<neu::TextComponent>();
    //    text->color = { 0,0,0,255 };
    //}
    //if (other->GetName() == "ExitText")
    //{
    //    auto text = other->GetComponent<neu::TextComponent>();
    //    text->color = { 0,0,0,255 };
    //}
}

void MouseComponent::OnNotify(const neu::Event& event)
{
    //if (event.name == "EVENT_DAMAGE")
    //{
    //    health -= std::get<float>(event.data);
    //    if (health <= 0)
    //    {
    //        m_owner->SetDestroy();
    //    }
    //}

}

bool MouseComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool MouseComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);

    return true;
}
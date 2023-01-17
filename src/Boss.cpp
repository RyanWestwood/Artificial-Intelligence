#include "Boss.h"

Boss::Boss() : Entity()
{
	m_Collider.Dimensions = { 6,4,50,56 };
	m_Collider.PixelOffset = { 6,4 };
	m_Transform.Position = { 736,512 };
	m_Transform.Velocity = { 32.f,32.f };
	m_Image.NoOfAnims = 7;
	m_Health = 100;
}


void Boss::Initialize()
{
	Entity::Initialize();
	m_Image.Texture.Initialize("ad.png");
	m_Image.Texture.m_Source = { 0,0,32,32 };
	m_Image.Texture.m_Destination = { 128,128,64,64 };

	m_HealthBar.Initialize({ 468,30,600,24 }, 4);
	m_AbilityBar.Initialize({ 764,70,300,12 }, 2, "TACTICAL DESTROYER");

	m_DisplayName.Initalize("PAUL, DESTROYER OF PLANETS");
	m_DisplayName.m_Dimensions.x = 590;
	m_DisplayName.m_Dimensions.y = 10;
}

void Boss::Input()
{
	Entity::Input();
}

void Boss::Update(const float delta_time)
{
	m_Collider.Dimensions.x = m_Transform.Position.x + m_Collider.PixelOffset.x;
	m_Collider.Dimensions.y = m_Transform.Position.y + m_Collider.PixelOffset.y;
	m_Image.Texture.m_Destination.x = m_Transform.Position.x;
	m_Image.Texture.m_Destination.y = m_Transform.Position.y;
}

void Boss::UpdateAnimation()
{
	Entity::UpdateAnimation();
}

void Boss::UpdateAi(Vector2 goal)
{

}

void Boss::Draw()
{
	Entity::Draw();

	m_Image.Texture.Draw();

	m_HealthBar.Draw();
	m_AbilityBar.Draw();
	m_DisplayName.Draw();
}

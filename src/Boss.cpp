#include "Boss.h"
#include "engine/Globals.h"

Boss::Boss() : Entity()
{
	m_Collider.Dimensions = { 6,4,50,56 };
	m_Collider.PixelOffset = { 6,4 };
	m_Transform.Position = { 736,512 };
	m_Transform.Velocity = { 32.f,32.f };
	m_Image.NoOfAnims = 7;
	m_Health = 100;


	ai::bt::Sequence* seq = new ai::bt::Sequence();
	ai::bt::Node* act = new ai::bt::Node();
	ai::bt::Node* action = new ai::bt::Node();
	ai::bt::Node* action1 = new ai::bt::Node();

	act->Initialize([&](const float delta_time) {
		if (m_Health <= 0) {
			Death();
#ifdef LOGGING
			std::cout << "Died in the behavior tree!\n";
#endif
			return ai::bt::Status::Success;
		}

		return ai::bt::Status::Running;
		});

	action->Initialize([&](const float delta_time) {
		if (*m_Timer >= 1.f && *m_MeleeTimer <= 0.f) {
			std::cout << "Melee Attack!\n";
			*m_Timer = 0.f;
			*m_MeleeTimer = 2.f;
			return ai::bt::Status::Success;
		}

		return ai::bt::Status::Running;
		});

	action1->Initialize([&](const float delta_time) {
		if (*m_Timer >= 1.f && *m_RangedTimer <= 0.f) {
			std::cout << "Ranged Attack!\n";
			*m_Timer = 0.f;
			*m_RangedTimer = 2.f;
			return ai::bt::Status::Success;
		}

	return ai::bt::Status::Running;
		});

	seq->AddChild(*action);
	seq->AddChild(*action1);

	m_Tree.Initialize(*seq);
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

	m_Blackboard = ai::CreateBlackboard(globals::GetAssetDirectory() + "blackboards/boss.csv");
	m_Timer = m_Blackboard->GetFloat("update_timer", 1.f);
	m_MeleeTimer = m_Blackboard->GetFloat("melee_timer", 2.f);
	m_RangedTimer = m_Blackboard->GetFloat("ranged_timer", 2.f);	
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

	m_Tree.Update(delta_time);
	*m_Timer += delta_time;
	*m_RangedTimer -= delta_time;
	*m_MeleeTimer -= delta_time;
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

void Boss::TakeDamage(unsigned short damage_amount)
{
	m_Health -= damage_amount;
	if (m_Health <= 0) {
		Death();
	}
	m_HealthBar.ChangeHealth(m_Health);
}
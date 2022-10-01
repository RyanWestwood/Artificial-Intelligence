#include "StateManager.h"
#include <memory>
#include <functional>
#include <Windows.h>
#include <iostream>
#include "../Dll.h"

namespace AI {
	namespace FSM {
		State::State(std::shared_ptr<StateManager> manager, std::function<void()> function)
		{
			m_Manager = manager;
			m_Func = function;
		}

		AttackState::AttackState(std::shared_ptr<StateManager> manager, std::function<void()> function) : State(manager, function)
		{
			m_Ammo = 0;
		}

		AttackState::AttackState()
		{

		}

		void AttackState::Update()
		{
			m_Func();
		}

		StateManager::StateManager()
		{
			m_CurrentState = std::make_unique<State>();
		}

		void StateManager::SetState(std::shared_ptr<State> state)
		{
			m_CurrentState = state;
		}

		StatePtr StateManager::GetState()
		{
			return m_CurrentState;
		}

		void StateManager::Update()
		{
			if (m_CurrentState) {
				m_CurrentState->Update();
			}
		}

		std::shared_ptr<StateManager> GetStateManager()
		{
			return std::make_shared<StateManager>();
		}

		std::shared_ptr<AttackState> CreateAttackState(ManagerPtr m, Function f)
		{
			std::cout << "Attack State!\n";
			return std::make_shared<AttackState>(m,f);
		}

	} // namespace FSM
} // namespace AI
#include "StateManager.h"
#include <memory>
#include <functional>
#include <Windows.h>
#include <iostream>
#include "../Dll.h"

namespace AI {
	namespace FSM {
		State::State(ManagerPtr manager, std::function<void()> function)
		{
			m_Manager = manager;
			m_Func = function;
		}

		AttackState::AttackState(ManagerPtr manager, Function function) : State(manager, function)
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

		void StateManager::SetState(StatePtr state)
		{
			m_CurrentState = std::move(state);
		}

		StatePtr StateManager::GetState()
		{
			return std::move(m_CurrentState);
		}

		void StateManager::Update()
		{
			if (m_CurrentState) {
				m_CurrentState->Update();
			}
		}

		ManagerPtr GetStateManager()
		{
			return std::make_shared<StateManager>();
		}

		StatePtr CreateAttackState(ManagerPtr m, Function f)
		{
			return std::move(std::make_unique<AttackState>(m,f));
		}

	} // namespace FSM
} // namespace AI
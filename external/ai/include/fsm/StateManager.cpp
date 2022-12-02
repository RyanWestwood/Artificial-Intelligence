#include "StateManager.h"
#include <memory>
#include <functional>
#include <Windows.h>
#include <iostream>
#include "../Dll.h"

namespace ai {
	namespace fsm {
		State::State(ManagerPtr manager, Function function)
		{
			m_Manager = manager;
			m_Func = function;
		}

		void State::Update()
		{
			m_Func();
		}

		StateManager::StateManager()
		{
			m_CurrentState = std::make_unique<State>();
		}

		void StateManager::SetState(StatePtr& state)
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

		ManagerPtr GetStateManager()
		{
			return std::make_shared<StateManager>();
		}

		StatePtr CreateState(ManagerPtr manager, Function function)
		{
			return std::make_shared<State>(manager, function);
		}

	} // namespace FSM
} // namespace AI
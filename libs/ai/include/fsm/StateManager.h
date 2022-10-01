#include "../Dll.h"
#include <memory>
#include <functional>

namespace AI {
	namespace FSM {

		class StateManager;
		class State;

		typedef std::shared_ptr<StateManager> ManagerPtr;
		typedef std::shared_ptr<State> StatePtr;
		typedef std::function<void()> Function;


		class IState {
			virtual void Update() = 0;
		};

		class State : public IState {
		public:
			State() {};
			State(ManagerPtr manager, Function function);
			virtual ~State() {};

			void Update() { m_Func(); };
		protected:
			ManagerPtr m_Manager;
			Function m_Func;
		};

		class AttackState : public State
		{
		public:
			AttackState();
			AttackState(ManagerPtr manager, Function function);
			void Update();
		private:
			int m_Ammo;
		};

		class IStateManager {
		public:
			virtual void SetState(StatePtr state) = 0;
			virtual StatePtr GetState() = 0;
			virtual void Update() = 0;
		};

		class StateManager : public IStateManager
		{
		public:
			StateManager();

			void SetState(StatePtr state);
			StatePtr GetState();
			void Update();

		private:
			StatePtr m_CurrentState;
		};

		extern "C++" AI_API std::shared_ptr<StateManager> GetStateManager();
		extern "C++" AI_API std::shared_ptr<AttackState> CreateAttackState(ManagerPtr, Function);

	} // namespace FSM
} // namespace AI
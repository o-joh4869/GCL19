#pragma once
#include"../Base.h"

namespace Scene { namespace Game { 
	class State;
namespace StageSelect {

	class Manager : public Scene::Game::Base {
	public:
		Manager(Scene::Game::State *state);
		virtual Scene::Base *update() override;
		virtual ~Manager() = default;
	private:
		Scene::Game::State *mState;

		int mStageid;

	};
}}}
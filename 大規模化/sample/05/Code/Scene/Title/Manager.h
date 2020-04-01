#pragma once
#include"../Base.h"

namespace Scene { 
	class State;
namespace Title {
	class Manager : public Scene::Base {
	public:
		Manager(Scene::State *state);
		virtual Scene::Base *update() override;
		virtual ~Manager() = default;
	private:
		Scene::State *mState;
	};
}}
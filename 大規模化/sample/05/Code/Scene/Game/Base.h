#pragma once
#include"../Base.h"

namespace Scene { namespace Game {
	class Base : public Scene::Base {
	protected:
		Base() : 
			Scene::Base()
		{}
		virtual Scene::Base *update() override { return nullptr; }
		virtual ~Base() = default;
	};
}}
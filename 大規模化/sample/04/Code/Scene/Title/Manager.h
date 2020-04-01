#pragma once
#include"../Base.h"

namespace Scene { namespace Title {
	class Manager : public Scene::Base {
	public:
		Manager();
		virtual Scene::Base *update() override;
		virtual ~Manager() = default;
	};
}}
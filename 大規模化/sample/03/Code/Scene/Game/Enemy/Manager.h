#pragma once
#include<memory>
#include<vector>
namespace Scene { namespace Game {
	class Player;
namespace Enemy {
	class Base;

	class Manager {
	public:
		Manager();
	private:
		std::vector<std::unique_ptr<Base>> mEnemy;
	public:
		void update(Player *const &player);
		void draw() const;
	};
}}}
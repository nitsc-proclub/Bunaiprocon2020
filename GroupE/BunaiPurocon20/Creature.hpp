#include  <Siv3D.hpp>
#include "Constant.hpp"


class Creature : public CollisionObject {


public:
	using CollisionObject::CollisionObject;

	void update() override {
		CollisionObject::update();
		if (run == true) {
			x -= Constant::creatureSpeed;
		}
		else {
			x -= Constant::scrollSpeed;
		}
		
	}

	void draw() const override {
		tex.resized(Constant::creatureWidth,Constant::creatureHeight).draw(x, Constant::windowHeight - (Constant::groundHeight + Constant::creatureHeight));
	}

};


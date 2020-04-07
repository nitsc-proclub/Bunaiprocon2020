#include  <Siv3D.hpp>
#include "Constant.hpp"


class Money : public CollisionObject {

private:
	int Speed;
	int fallPoint;

public:
	using CollisionObject::CollisionObject;

	Money(Texture tex, int x) :CollisionObject(tex, x) {
		y =  0 - tex.height();
		Speed = Random(2, 7);
		fallPoint = Random(0, Constant::windowWidth);
	}

	void update() override {
		CollisionObject::update();
		if (x<=fallPoint) {
			y += Speed;
		}
		else {
			x -= Constant::scrollSpeed;
		}
	}

	void draw() const override {
		tex.draw(x, y);
	}

};
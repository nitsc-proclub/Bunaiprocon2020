#include  <Siv3D.hpp>
#include "Constant.hpp"


class Bar : public CollisionObject {

public:
	using CollisionObject::CollisionObject;


	void update() override {
		collider = Line(x+tex.width()* 2/5, Constant::windowHeight - Constant::groundHeight, x + tex.width()* 3/5, Constant::windowHeight - Constant::groundHeight);
		x -= Constant::scrollSpeed;
	}

	void draw() const override {
		tex.resized(Constant::windowWidth / 5).draw(x, Constant::windowHeight - (Constant::groundHeight + Constant::humanHeight));
	}

};


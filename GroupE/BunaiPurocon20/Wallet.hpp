#include  <Siv3D.hpp>
#include "Constant.hpp"


class Wallet : public CollisionObject {

public:
	using CollisionObject::CollisionObject;

	void update() override {
		CollisionObject::update();
		x -= Constant::scrollSpeed;
	}

	void draw() const override {
		tex.resized(Constant::walletWidth,Constant::walletHeight).draw(x, Constant::windowHeight - (Constant::groundHeight + Constant::walletHeight));
	}

};


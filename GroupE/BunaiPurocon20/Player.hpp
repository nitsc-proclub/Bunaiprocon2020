#include  <Siv3D.hpp>
#include "Constant.hpp"

enum Direction {
	right = 0,
	Left = 1
};

class Player {

private:
	Texture tex;
	int x;
	Direction dir;
	Rect collider;

public:

	Player(Texture tex) {
		this->tex = tex;
		x = Constant::windowWidth / 10;
		dir = right;
	}

	void update() {
		if (KeyRight.pressed() && x <= Constant::windowWidth - Constant::humanWidth) {
			x += Constant::playerSpeed;
			dir = right;
		}
		if (KeyLeft.pressed() && x >= 0) {
			x -= Constant::playerSpeed;
			dir = Left;
		}
		updateCollider();
	}


	void updateCollider() {
		collider = Rect(x, Constant::windowHeight - (Constant::groundHeight + Constant::humanHeight), Constant::humanWidth, Constant::humanHeight);
	}

	void draw() const {
		tex(0+85*dir, 0, 85, 170).resized(Constant::humanWidth, Constant::humanHeight).draw(x, Constant::windowHeight - (Constant::groundHeight + Constant::humanHeight));
	}

	Rect getCollider() {
		return collider;
	}

	void setX(int x) {
		this->x = x;
	}
	
	int getX() {
		return x;
	}
};


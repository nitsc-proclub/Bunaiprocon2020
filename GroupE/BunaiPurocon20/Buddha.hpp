#include <Siv3D.hpp>
#include "Constant.hpp"

class Buddha {

private:
	Texture tex;
	int x, y;
	int destination;
	bool moving;
	Polygon view;
	int count;
	bool adding;

public:
	Buddha(Texture tex) {
		this->tex = tex;
		x = Constant::windowWidth / 2;
		moving = false;
		count = 0;
	}

	void update() {
		if (moving == false) {
			destination = Random(Constant::windowWidth );
			moving = true;
		}
		else {
			if (x != destination) {
				if (x > destination) {
					x -= 1;
				}
				if (x < destination) {
					x += 1;
				}
			}
			else {
				moving = false;
			}
		}
		y = (tex.height() / 2) + 10 * sin(x / 3 / 3.1415926);
		if (count < 100) {
			adding = true;
		}
		else if(count > 500){
			adding = false;
		}

		if (adding) {
			count+=3;
		}
		else {
			count-=3;
		}


		view = Polygon{ Vec2(x ,y-30),Vec2(x + count, Constant::windowHeight - Constant::groundHeight),Vec2(x - count, Constant::windowHeight - Constant::groundHeight) };
	}

	void draw() const {
		tex.drawAt(x, y);
		view.draw(ColorF(1.0, 0.0, 0.0, 0.25));
	}

	Polygon getCollider() {
		return view;
	}

};
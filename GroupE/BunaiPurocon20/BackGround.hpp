#include  <Siv3D.hpp>
#include "Constant.hpp"


class BackGround {

private:
	Texture tex1, tex2;
	int x1, x2;

public:

	BackGround(Texture tex) {
		tex1 = tex;
		tex2 = tex;
		x1 = 0;
		x2 = Constant::windowWidth;
	}

	 void update() {
		 x1 -= Constant::scrollSpeed;
		 x2 -= Constant::scrollSpeed;

		 if(x1 <= -Constant::windowWidth) {
			 x1 = x2 + Constant::windowWidth;
		 }

		 if (x2 <= -Constant::windowWidth) {
			 x2 = x1 + Constant::windowWidth;
		 }
	}

	 void draw() const {
		tex1.resized(Constant::windowWidth, Constant::windowHeight).draw(x1, 0);
		tex2.resized(Constant::windowWidth, Constant::windowHeight).draw(x2, 0);
	 }
};


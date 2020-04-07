#include  <Siv3D.hpp>
#include "Constant.hpp"

class CollisionObject {

protected:
	Texture tex;
	int x, y;
	Line collider;
	bool intersectFlag;
	bool actionFlag;
	bool run;

public:

	CollisionObject(Texture tex ,int x) {
		this->tex = tex;
		this->x = x;
		y = Constant::windowHeight - Constant::groundHeight;
		intersectFlag = false;
		actionFlag = false;
		run = false;
	}

	virtual void update() {
		collider = Line(x, y, x + tex.width(), y);
	}

	virtual void draw() const {}



	Line getCollider() {
		return collider;
	}

	int getX() const {
		return x;
	}

	void setRun(bool n) {
		run = n;
	}

	 void setIntersectFlag(bool a) {
		intersectFlag = a;
	}

	 bool getIntersectFlag() const {
		 return intersectFlag;
	 }

	 void setActionFlag(bool a)  {
		 actionFlag = a;
	 }

	 bool getActionFlag() const {
		 return actionFlag;
	 }
};


#include "stdafx.h"
#include "AllHead.h"

namespace PlayerClasses {
	void PlayerClass::MoveUpdate(){
		position += movingVector;
		movingVector = Vector2(0, 0);
		return;
	}
}
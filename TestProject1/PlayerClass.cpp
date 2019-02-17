#include "stdafx.h"
#include "AllHead.h"



namespace PlayerClasses {
	void PlayerClass::MoveUpdate(){
		//à⁄ìÆîÕàÕÇÃêßå¿
		if (gamePosition.x + movingVector.x < 50)gamePosition.x = 50;
		else if (gamePosition.x + movingVector.x > stageEnd)gamePosition.x = stageEnd;
		else gamePosition.x += movingVector.x;
		movingVector.x = 0;


		if (gamePosition.y + movingVector.y < 0) {
			gamePosition.y = 0;
			movingVector.y = 0;
			onGround = true;
		}
		else {
			gamePosition.y += movingVector.y;
			movingVector.y -= AccelGrav;
		}
		return;
	}

	void PlayerClass::DushCheck() {
		if (dushCounter > 20) {
			dushRightKey = false;
			dushLeftKey = false;
		}
		else dushCounter++;

		dushInput = false;
		if (B_RIGHT.GetKeyDown()) {
			dushLeftKey = false;
			dushCounter = 0;
			if (dushRightKey) {
				dushInput = true;
			}
			dushRightKey = true;
		}
		if (B_LEFT.GetKeyDown()) {
			dushRightKey = false;
			dushCounter = 0;
			if (dushLeftKey) {
				dushInput = true;
			}
			dushLeftKey = true;
		}

	}

	void PlayerClass::TranceGraphicPosition() {
		drawPosition = Vector2(gamePosition.x - size.x / 2, WindowScaleY - (gamePosition.y + size.y + floorHight));
	}
}
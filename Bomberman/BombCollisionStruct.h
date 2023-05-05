#pragma once
#include <SFML/Graphics.hpp>

struct BombCollisionStruct
{
public:
	BombCollisionStruct() {}

	BombCollisionStruct(int leftTip_, int RightTip_, int bottomTip_, int topTip_, int centerStartX_, int centerEndX_, int centerStartY_, int centerEndY_)
		: leftTip(leftTip_), RightTip(RightTip_), bottomTip(bottomTip_), topTip(topTip_), centerStartX(centerStartX_), centerEndX(centerEndX_), centerStartY(centerStartY_), centerEndY(centerEndY_)
	{}

	BombCollisionStruct GetBombCollisionStruct() {
		return { leftTip, RightTip, bottomTip, topTip, centerStartX, centerEndX, centerStartY, centerEndY };
	}

	int leftTip;
	int RightTip;
	int bottomTip;
	int topTip;
	int centerStartX;
	int centerEndX;
	int centerStartY;
	int centerEndY;
};
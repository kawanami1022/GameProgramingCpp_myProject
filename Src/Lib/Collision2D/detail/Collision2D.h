#pragma once
#include <cmath>
#include <algorithm>
#include "../Collision2D.h"

template<typename T>
bool Collision2D::IsHitAABB(RectTmp<T>& rect1, RectTmp<T>& rect2)
{
	return ((std::max(rect1.Position2().x, rect2.Position2().x) < std::min(rect1.Right(), rect2.Right()))
		&& std::max(rect1.Position2().y, rect2.Position2().y) < std::min(rect1.Buttom(), rect2.Buttom()));
}

template<typename T>
bool Collision2D::IsHitCircle(CircleTmp<T>& circle1, CircleTmp<T>& circle2)
{
	return (circle1.radious_ + circle2.radious_ > std::hypot(circle1.pos_.x - circle2.pos_.x, circle1.pos_.y - circle2.pos_.y));
}





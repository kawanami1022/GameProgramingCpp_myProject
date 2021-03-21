#pragma once
#include "../Geometry2D/Geometry2D.h"

namespace Collision2D
{

template<typename T>
bool IsHitAABB(RectTmp<T>&, RectTmp<T>&);		// check hit rectangle to each other

template<typename T>
bool IsHitCircle(CircleTmp<T>&, CircleTmp<T>&);	// check hit circle to each other

}




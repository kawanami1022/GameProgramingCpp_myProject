#pragma once
#include <cmath>
#include <iostream>
#include <typeinfo>
#include "../../Vector2/Vector2.h"
#include "../../SDL_gfx/SDL2_gfxPrimitives.h"
#include "../Geometry2D.h"
#include "../../Constraint/cast.h"
#include "../../Color/Color.h"


template<class T>
RectTmp<T>::RectTmp()
{
	pos_ = Vector2(0, 0);
	width_ = 0;
	hight_ = 0;
	color_ = {0xff,0xff,0xff,0xff};
	fillFlag_ = false;
}

template<class T>
RectTmp<T>::RectTmp(Vector2Tmp<T> vec, T hight, T width)
{
	pos_=Vector2Tmp<T>(vec.x,vec.y);
	width_ = hight;
	hight_ = width;
	color_ = { 0xff,0xff,0xff,0xff };
	fillFlag_ = false;
}



template<class T>
inline RectTmp<T>::RectTmp(Vector2Tmp<T> vec, T hight, T width, RGBA color)
{
	pos_ = Vector2Tmp<T>(vec.x, vec.y);
	width_ = hight;
	hight_ = width;
	color_ = color;
	fillFlag_ = false;
}

template<class T>
RectTmp<T>::RectTmp(Vector2Tmp<T> vec, T hight, T width, RGBA color,bool FillFlag)
{
	pos_ = Vector2Tmp<T>(vec.x, vec.y);
	width_ = hight;
	hight_ = width;
	color_ = color;
	fillFlag_ = FillFlag;
}

template<class T>
RectTmp<T>& RectTmp<T>::operator=(const RectTmp& rect)
{
	return rect;
}



// this function can Draw a rectangle
template<class T>
void RectTmp<T>::Draw(SDL_Renderer* renderer)
{
	fillFlag_ == true ? FillDraw(renderer) : OutlineDraw(renderer);
}

// this function can Draw a rectangle
//bool FillFlag :true fill false outline
template<class T>
void RectTmp<T>::Draw(SDL_Renderer* renderer, bool FillFlag)
{
	FillFlag == true ? FillDraw(renderer) : OutlineDraw(renderer);
}

//  a rectangle Draw FillBox
// SDL_Renderer: 
template<class T>
void RectTmp<T>::FillDraw(SDL_Renderer* renderer)
{
	if (typeid(T) == typeid(int))
	{
		SDL_Rect fillRect = { pos_.x,pos_.y,hight_,width_ };
		SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
		SDL_RenderFillRect(renderer, &fillRect);
	}

	if (typeid(T) == typeid(float))
	{
		SDL_FRect fillRect = { STCF(pos_.x),STCF(pos_.y),STCF(hight_),STCF(width_) };
		SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
		SDL_RenderFillRectF(renderer, &fillRect);
	}
}

// a rectangle Draw outline
template<class T>
void RectTmp<T>::OutlineDraw(SDL_Renderer* renderer)
{
	if (typeid(T) == typeid(int))
	{
		SDL_Rect fillRect = { pos_.x,pos_.y,hight_,width_ };
		SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
		SDL_RenderDrawRect(renderer, &fillRect);
	}

	if (typeid(T) == typeid(float))
	{
		SDL_FRect fillRect = { STCF(pos_.x), STCF(pos_.y), STCF(hight_), STCF(width_) };
		SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
		SDL_RenderDrawRectF(renderer, &fillRect);
	}
}




template<class T>
inline CircleTmp<T> CircleTmp<T>::operator=(const CircleTmp<T>& circleTmp)
{
	this->pos_ = circleTmp.pos_;
	this->radious_ = circleTmp.radious_;
	this->fillColor_ = circleTmp.fillColor_;
	this->fillVisible_ = circleTmp.fillVisible_;
	this->outlineID_= circleTmp.outlineID_;
	this->outlineColor_ = circleTmp.outlineColor_;
	this->outlineSize_ = circleTmp.outlineSize_;
	this->outlineVisible_ = circleTmp.outlineVisible_;
	return (*this);
}

template<class T>
CircleTmp<T>::CircleTmp() :pos_(Vector2(0, 0)),
						radious_(0),
						fillColor_({0xff,0xff,0xff,0xff}),
						fillVisible_(true),
						outlineID_(OUTLINE_ID::CENTER),
						outlineColor_(RGBA{0xff,0xff,0xff,0xff}),
						outlineSize_(0),
						outlineVisible_(true)
{
	Init();
}

template<class T>
inline CircleTmp<T>::CircleTmp(Vector2Tmp<T> pos, T radious) :pos_(Vector2(0, 0)),
											radious_(0),
											fillColor_({ 0xff,0xff,0xff,0xff }),
											fillVisible_(true),
											outlineID_(OUTLINE_ID::CENTER),
											outlineColor_(RGBA{ 0x00,0x00,0x00,0xff }),
											outlineSize_(1),
											outlineVisible_(true)
{
	Init();
}

template<class T>
inline CircleTmp<T>::CircleTmp(Vector2Tmp<T> pos, T radious, RGBA fillcolor, bool fillVisible) 
														:pos_(pos),
														radious_(radious),
														fillColor_(fillcolor),
														fillVisible_(fillVisible),
														outlineID_(OUTLINE_ID::CENTER),
														outlineColor_(RGBA{ 0x00,0x00,0x00,0xff }),
														outlineSize_(1),
														outlineVisible_(true)
{
	Init();
}

template<class T>
inline CircleTmp<T>::CircleTmp(Vector2Tmp<T> pos, T radious,RGBA fillcolor,bool fillVisible, 
							OUTLINE_ID outlineID, RGBA outlineColor, unsigned int outlineSize, bool outlineVisible)
							:pos_(pos),
							radious_(radious),
							fillColor_(fillcolor),
							fillVisible_(fillVisible),
							outlineID_(outlineID),
							outlineColor_(outlineColor),
							outlineSize_(outlineSize),
							outlineVisible_(outlineVisible)
{
	Init();
}

template<class T>
inline void CircleTmp<T>::Init()
{
	drawFunc[0] = &CircleTmp<T>::outSideDraw;
	drawFunc[1] = &CircleTmp<T>::centerDraw;
	drawFunc[2] = &CircleTmp<T>::InnerDraw;
}

template<class T>
inline void CircleTmp<T>::Draw(SDL_Renderer* renderer)
{

	if (fillVisible_) { fillDraw(renderer); }

	if (outlineVisible_){outlineDraw(renderer);}
}

template<class T>
inline void CircleTmp<T>::fillDraw(SDL_Renderer* renderer)
{
	filledCircleRGBA(renderer, STCI(pos_.x), STCI(pos_.y), STCI(radious_), fillColor_.r, fillColor_.g, fillColor_.b, fillColor_.a);
	aacircleRGBA(renderer, STCI(pos_.x), STCI(pos_.y), STCI(radious_), fillColor_.r, fillColor_.g, fillColor_.b, fillColor_.a);

	for(unsigned int idx=0;idx<3;idx++)
		aacircleRGBA(renderer, STCI(pos_.x), STCI(pos_.y), STCI(radious_)+1, fillColor_.r, fillColor_.g, fillColor_.b, fillColor_.a);
}


// outline draw specified outlineID
// 
template<class T>
inline void CircleTmp<T>::outlineDraw(SDL_Renderer* renderer)
{
	for (auto ID : OUTLINE_ID())
	{
		auto func = this->drawFunc[STCI(ID)];
		if (outlineID_ == ID)
		for (unsigned int dst = 0; dst < outlineSize_; dst++)
		{
			for (unsigned int idx = 0; idx < 2; idx++)
			{
				(this->*func)(renderer, dst);
			}
		}
	}
}

// outline draw outside
template<class T>
inline void CircleTmp<T>::outSideDraw(SDL_Renderer* renderer, int dst)
{
	aacircleRGBA(renderer, STCI(pos_.x), STCI(pos_.y), STCI(radious_) + dst + 1, outlineColor_.r, outlineColor_.g, outlineColor_.b, outlineColor_.a);
}

template<class T>
inline void CircleTmp<T>::centerDraw(SDL_Renderer* renderer, int dst)
{
	aacircleRGBA(renderer, STCI(pos_.x), STCI(pos_.y),
		STCI(radious_) - STCI(outlineSize_ / 2) + dst, STCI(outlineColor_.r),
		outlineColor_.g, outlineColor_.b, outlineColor_.a);
}

template<class T>
inline void CircleTmp<T>::InnerDraw(SDL_Renderer* renderer, int dst)
{
	aacircleRGBA(renderer, STCI(pos_.x), STCI(pos_.y), STCI(radious_) - dst + 1, outlineColor_.r, outlineColor_.g, outlineColor_.b, outlineColor_.a);
}


template<class T>
inline CapsuleTmp<T>::CapsuleTmp()
	:pos_(Vector2Tmp<T>(STCT(0.f), STCT(0.f))), height_(STCT(0.f)), radious_(STCT(0.f)), fillColor_(RGBA{ 0xff,0xff,0xff,0xff }), fillVisible_(false),
	outlineID_(OUTLINE_ID::CENTER), outlineColor_(RGBA{0xff,0xff,0xff,0xff}),outlineSize_(0),outlineVisible_(false)
{
	Init();
}

template<class T>
inline CapsuleTmp<T>::CapsuleTmp(Vector2T pos, T height, T radious)
	:pos_(Vector2(0, 0)), height_(0), radious_(0), fillColor_(RGBA{ 0xff,0xff,0xff,0xff }), fillVisible_(false),
	outlineID_(OUTLINE_ID::CENTER), outlineColor_(RGBA{ 0xff,0xff,0xff,0xff }), outlineSize_(0), outlineVisible_(false)
{
	//Init();
}

template<class T>
inline CapsuleTmp<T>::CapsuleTmp(Vector2T pos, T height, T radious, RGBA fillColor)
	:pos_(Vector2(0, 0)), height_(0), radious_(0), fillColor_(RGBA{ 0xff,0xff,0xff,0xff }), fillVisible_(false),
	outlineID_(OUTLINE_ID::CENTER), outlineColor_(RGBA{ 0xff,0xff,0xff,0xff }), outlineSize_(0), outlineVisible_(false)
{
	//Init();
}

template<class T>
inline CapsuleTmp<T>::CapsuleTmp(Vector2T pos, T height, T radious, RGBA fillColor,
 bool fillVisible,
	OUTLINE_ID outlineID, RGBA outlineColor, unsigned int outlineSize, bool outlineVisible)
	: pos_(pos), height_(height), radious_(radious), fillColor_(fillColor), fillVisible_(fillVisible),
	outlineID_(outlineID), outlineColor_(outlineColor), outlineSize_(outlineSize), outlineVisible_(outlineVisible)
{
	//Init();
}

template<class T>
inline void CapsuleTmp<T>::Draw(SDL_Renderer* renderer)
{
	if (fillVisible_) { fillDraw(renderer); }

	if (outlineVisible_) { outlineDraw(renderer); }
}

template<class T>
inline void CapsuleTmp<T>::fillDraw(SDL_Renderer* renderer)
{
	const Sint16 vx[] = { 0,100,100,0 };
	const Sint16 vy[] = { 0,0,100,100 };


	aapolygonRGBA(renderer,
		vx,
		vy,
		4,
		fillColor_.r,
		fillColor_.g,
		fillColor_.b,
		fillColor_.a);
}

template<class T>
inline void CapsuleTmp<T>::outlineDraw(SDL_Renderer* renderer)
{
}

template<class T>
inline void CapsuleTmp<T>::Init()
{
	posTl_ = Vector2T(pos_.x - height_ / 2, pos_.y - radious_);
	posTr_ = Vector2T(pos_.x + height_ / 2, pos_.y - radious_);
	posDr_ = Vector2T(pos_.x + height_ / 2, pos_.y + radious_);
	posDl_ = Vector2T(pos_.x - height_ / 2, pos_.y + radious_);

	posL_ = Vector2T(pos_.x - height_ / 2, pos_.y);
	posR_= Vector2T(pos_.x + height_ / 2, pos_.y);

	drawFunc[0] = &CapsuleTmp<T>::outSideDraw;
	drawFunc[1] = &CapsuleTmp<T>::centerDraw;
	drawFunc[2] = &CapsuleTmp<T>::InnerDraw;


}

template<class T>
inline void CapsuleTmp<T>::outSideDraw(SDL_Renderer* renderer, int)
{
}

template<class T>
inline void CapsuleTmp<T>::centerDraw(SDL_Renderer* renderer, int)
{
}

template<class T>
inline void CapsuleTmp<T>::InnerDraw(SDL_Renderer* renderer, int)
{
}

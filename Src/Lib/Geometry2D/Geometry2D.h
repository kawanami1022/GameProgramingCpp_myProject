#pragma once
#include <array>
#include <type_traits>
#include <SDL.h>

enum class OUTLINE_ID
{
	INNER,		// inside line
	CENTER,		// center line
	OUTSIDE,		// outside line
	Max,
};

struct RGB;
struct RGBA;

template<class T>
class Vector2Tmp;

template <class T >
struct RectTmp
{
	Vector2Tmp<T> pos_;
	T width_;
	T hight_;
	RGBA color_;
	bool fillFlag_;		//bool FillFlag :true fill false outline
	
	// constractor
	RectTmp();
	RectTmp(Vector2Tmp<T>,T,T);
	RectTmp(Vector2Tmp<T>,T,T,RGBA);
	RectTmp(Vector2Tmp<T>, T, T, RGBA,bool);

	// operater
	RectTmp& operator=(const RectTmp&);

	// Getter
	Vector2Tmp<T> Position2()const
	{
		return pos_;
	}

	T Right()const
	{
		return pos_.x + width_;
	}

	T Buttom()const
	{
		return pos_.y + hight_;
	}

	// draw Function
	void Draw(SDL_Renderer*);
	void Draw(SDL_Renderer*, bool FillFlag);
	void FillDraw(SDL_Renderer*);
	void OutlineDraw(SDL_Renderer*);

};


template <class T >
struct CircleTmp
{
	// variables
	Vector2Tmp<T> pos_;		// circle's center position
	T radious_;				// circle's radious

	RGBA fillColor_;			// specify fillcolor
	bool fillVisible_;		//bool FillFlag :true fill false outline

	/// <summary>
	/// specify outlineID
	/// OUTLINE_ID::INNER		innerline
	/// OUTLINE_ID::CENTER	centerline
	/// OUTLINE_ID::OUTSIDE	outside
	/// </summary>
	OUTLINE_ID outlineID_;		
	RGBA outlineColor_;			// specify outlineColor
	unsigned int outlineSize_;		// specify outlinesize
	bool outlineVisible_;			// true:draw outline  false:This flag doesn't draw outline
	// operater
	CircleTmp<T> operator=(const CircleTmp<T>&);
	// Getter
	

	// constractor
	CircleTmp();
	CircleTmp(Vector2Tmp<T>,T);
	CircleTmp(Vector2Tmp<T> pos, T radious, RGBA fillcolor, bool fillVisible);
	CircleTmp(Vector2Tmp<T> pos, T radious, RGBA fillcolor, bool fillVisible,
		OUTLINE_ID outlineID, RGBA outlineColor, unsigned int outlineSize, bool outlineVisible);

	// functions
	void Draw(SDL_Renderer*);				// draw circle	outlineVisible_:true outline draw	fillVisible_:true draw fillcircle
	void fillDraw(SDL_Renderer*);			// draw fillcircle
	void outlineDraw(SDL_Renderer*);		// outline draw specified outlineID


private:
	void Init();
	void outSideDraw(SDL_Renderer*, int);
	void centerDraw(SDL_Renderer*, int);
	void InnerDraw(SDL_Renderer*, int);
	typedef void (CircleTmp<T>::*outlineDrawFunc)(SDL_Renderer*, int);
	std::array<outlineDrawFunc,3> drawFunc;
};

template<class T>
class CapsuleTmp
{
	using Vector2T = Vector2Tmp<T>;
	using CircleT = CircleTmp<T>;
public:

	Vector2T pos_;		// capsule's center position

	T height_;			// capsule's height
	T radious_;			// capsule's radious

	RGBA fillColor_;			// specify fillcolor
	bool fillVisible_;		//bool FillFlag :true fill false outline

	/// <summary>
	/// specify outlineID
	/// OUTLINE_ID::INNER		innerline
	/// OUTLINE_ID::CENTER	centerline
	/// OUTLINE_ID::OUTSIDE	outside
	/// </summary>
	OUTLINE_ID outlineID_;
	RGBA outlineColor_;			// specify outlineColor
	unsigned int outlineSize_;		// specify outlinesize
	bool outlineVisible_;			// true:draw outline  false:This flag doesn't draw outline
	SDL_Surface* surface_;		// 
	// constractor
	CapsuleTmp();
	CapsuleTmp(Vector2T pos, T height, T radious);
	CapsuleTmp(Vector2T pos, T height, T radious,RGBA fillColor);
	CapsuleTmp(Vector2T pos, T height, T radious,RGBA fillColor,
		bool fillVisible,OUTLINE_ID outlineID,RGBA outlineColor,unsigned int outlineSize,bool outlineVisible);

	// functions
	void Draw(SDL_Renderer*);				// draw circle	outlineVisible_:true outline draw	fillVisible_:true draw fillcircle
	void fillDraw(SDL_Renderer*);			// draw fillcircle
	void outlineDraw(SDL_Renderer*);		// outline draw specified outlineID

	// Getter Setter


private:


	Vector2T posTl_;		// capsule's top left(when the cupsule angle 0)
	Vector2T posTr_;		// capsule's top right(when the cupsule angle 0)
	Vector2T posDr_;	// capsule's down right(when the cupsule angle 0)
	Vector2T posDl_;	// capsule's down left(when the cupsule angle 0)

	Vector2T posL_;	// Left position(When this angle's 0)
	Vector2T posR_;	// Right position(When this angle's 0)

	void Init();
	void outSideDraw(SDL_Renderer*, int);
	void centerDraw(SDL_Renderer*, int);
	void InnerDraw(SDL_Renderer*, int);

	typedef void (CapsuleTmp<T>::* outlineDrawFunc)(SDL_Renderer*, int);
	std::array<outlineDrawFunc, 3> drawFunc;
};

#include "detail/Geometry2D.h"


using Rect = RectTmp<int>;
using RectS = RectTmp<short>;
using RectL = RectTmp<long>;
using RectF = RectTmp<float>;
using RectD = RectTmp<double>;

using Circle = CircleTmp<int>;
using CircleS = CircleTmp<short>;
using CircleL = CircleTmp<long>;
using CircleF = CircleTmp<float>;
using CircleD = CircleTmp<double>;


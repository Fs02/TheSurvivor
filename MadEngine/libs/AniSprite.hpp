#ifndef ANISPRITE_HPP_INCLUDED
#define ANISPRITE_HPP_INCLUDED

#include "../stdafx.hpp"

/*
 * AniSprite Class with little modification
 * Original version of AniSprite can be found here: http://www.sfml-dev.org/wiki/en/sources/anisprite
 */

class AniSprite //public sf::Sprite
{
public:
	AniSprite();
		//initialtion list

	AniSprite(sf::Sprite* Sprite, int frameWidth, int frameHeight);
	~AniSprite(void);
	//Get
	sf::IntRect GetFramePosition(int frame);
	int GetFrameCount();
	int GetCurrentFrame();
	//set
	void SetFrameSize(int frameWidth, int frameHeight);
	//Sets current frame
	void SetFrame(int frame);
	//sets loop speed in fps
	void SetLoopSpeed(float fps);
	void SetInvert(bool invert = false);
	//start looping
	void Play();
	void Play(int start, int end);
	//stop
	void Stop();
	//update functions
	void Update();
	//set Position
	void setPosition(float x, float y);
	//set Rotation
	void setRotation(float angle);
	//Set Custom Origin
	void setOrigin(float x, float y);
	//draw
	void Draw(sf::RenderWindow* Window);
private:
    sf::Sprite* m_Sprite;

	sf::Clock clock;
	float fps;
	bool isPlaying;
	bool isInvert;
	int loopStart;
	int loopEnd;
	int currentFrame;
	int frameWidth;
	int frameHeight;
};

#endif // ANISPRITE_HPP_INCLUDED

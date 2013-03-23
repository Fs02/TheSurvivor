/*
 * AniSprite Class with little modification
 * Original version of AniSprite can be found here: http://www.sfml-dev.org/wiki/en/sources/anisprite
 */

#include "AniSprite.hpp"

AniSprite::AniSprite(void)
//	: sf::Sprite()
{
	fps=1;
	currentFrame=0;
	isPlaying = false;
	loopStart = 0;
	SetFrameSize(0, 0);
}

AniSprite::AniSprite(sf::Sprite* Sprite, int frameW, int frameH)
//		: sf::Sprite(Texture)
{
    m_Sprite        = Sprite;
	fps             = 1;
	currentFrame    = 0;
	isPlaying       = false;
	loopStart       = 0;
	SetFrameSize(frameW, frameH);
	//now calculate stuff
}

AniSprite::~AniSprite(void)
{
}

int AniSprite::GetFrameCount()
{
	unsigned int across     = m_Sprite->getTexture()->getSize().x / frameWidth;
	unsigned int down       = m_Sprite->getTexture()->getSize().y / frameHeight;
	return across*down;
}

int AniSprite::GetCurrentFrame()
{
    return currentFrame;
}
//first frame is frame ZERO
sf::IntRect AniSprite::GetFramePosition(int frame)
{
	//get number across and down
	unsigned int across     = m_Sprite->getTexture()->getSize().x / frameWidth;
	unsigned int down       = m_Sprite->getTexture()->getSize().y / frameHeight;

    int tileY = frame / across ; //get Y on grid
    int tileX = frame % across ; //get X on grid

	sf::IntRect result(
		tileX * frameWidth,
		tileY * frameHeight,
		frameWidth,
		frameHeight);

	//end
	return result;

}
//
void
AniSprite::SetFrameSize(int frameW, int frameH)
{
	frameWidth      = frameW;
	frameHeight     = frameH;
	m_Sprite->setTextureRect(sf::IntRect(0,0,frameW,frameH));
	m_Sprite->setOrigin(frameWidth / 2, frameHeight / 2);
}
//Sets current frame
void
AniSprite::SetFrame(int frame)
{
	this->currentFrame = frame;
}
//sets loop speed in fps
void
AniSprite::SetLoopSpeed(float newfps)
{
	this->fps = newfps;
}
//start looping
void
AniSprite::Play()
{
	this->Play(0,GetFrameCount());
}
void
AniSprite::Play(int start, int end)
{
	loopStart = start;
	loopEnd = end;
	currentFrame = start;
	isPlaying = true;
	clock.restart();
}
//stop
void
AniSprite::Stop()
{
	isPlaying = false;
}
//update function
void
AniSprite::Update()
{
	if(isPlaying)
	{
		int frameCount = (loopEnd+1) - loopStart;

 		float timePosition = (clock.getElapsedTime().asSeconds() * fps);
		currentFrame = loopStart +
			(int)timePosition % frameCount;

		m_Sprite->setTextureRect(GetFramePosition(currentFrame));
	}
}

void AniSprite::setPosition(float x, float y)
{
    m_Sprite->setPosition(x, y);
}

void AniSprite::setRotation(float angle)
{
    m_Sprite->setRotation(angle);
}

void AniSprite::setOrigin(float x, float y)
{
    m_Sprite->setOrigin(x,y);
}

void AniSprite::SetInvert(bool invert)
{
    isInvert    = invert;
}

void AniSprite::Draw(sf::RenderWindow* Window)
{
    if (isInvert)   m_Sprite->setRotation(m_Sprite->getRotation()+180);
    Window->draw(*m_Sprite);
}

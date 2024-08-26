#include "GameAudio.hpp"

#include <SFML/Audio.hpp>

GameAudio::GameAudio()
{

}

bool GameAudio::loadMusic(const std::string& filename)
{
	if (!music.openFromFile(filename))
	{
		return false;
	}

	return true;
}

void GameAudio::playMusic()
{
	music.play();
}

void GameAudio::stopMusic()
{
	music.stop();
}

void GameAudio::setLoop(bool loop)
{
	music.setLoop(loop);
}

void GameAudio::setMusicVolume(float volume)
{
	music.setVolume(volume);
}

bool GameAudio::loadSound(const std::string &filename)
{
	if (!buffer.loadFromFile(filename))
	{
		return false;
	}

	sound.setBuffer(buffer);
	return true;
}

void GameAudio::playSound()
{
	sound.play();
}

void GameAudio::pauseSound()
{
	sound.pause();
}

void GameAudio::stopSound()
{
	sound.stop();
}

void GameAudio::setSoundVolume(float volume)
{
	sound.setVolume(volume);
}
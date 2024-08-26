#pragma once

#ifndef GAMEAUDIO_HPP
#define GAMEAUDIO_HPP

#include <SFML/Audio.hpp>

class GameAudio
{
	public:
		GameAudio();

		bool loadMusic(const std::string &filename);
		void playMusic();
		void stopMusic();
		void setLoop(bool loop);
		void setMusicVolume(float volune);

		bool loadSound(const std::string& filename);
		void playSound();
		void pauseSound();
		void stopSound();
		void setSoundVolume(float volume);

	private:
		sf::Music music;
		sf::SoundBuffer buffer;
		sf::Sound sound;

};

#endif

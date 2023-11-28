
#include <algorithm>
#include "AudioManager.h"
#include "pch.h"



AudioManager::AudioManager()
{

}

bool AudioManager::Init()
{

	if (Mix_Init(MIX_INIT_MP3) == 0)
	{
		cout << "Mixer init failed\n";
		return false;
	}
	else
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_AllocateChannels(16);
		return true;
	}
}

void AudioManager::SetMusicVolume(int volLevel)
{
	int clampedVolume =
		std::clamp(volLevel, 0, 128);

	Mix_VolumeMusic(clampedVolume);

}

void AudioManager::PlayMusic(int id, int loops)
{
	Mix_PlayMusic(m_vMusicTracks[id], loops);

}

void AudioManager::PlaySound(int id, int channel, int loops)
{
	Mix_PlayChannel(channel, m_vSounds[id], loops);
}

void AudioManager::LoadMusic(const char* path)
{
	//check if it is loadable first...
	Mix_Music* t = Mix_LoadMUS(path);
	if (t != nullptr)
	{
		m_vMusicTracks.push_back(t);
	}
	else
	{
		//error
		cout << "Music load failed. \n";
	}
}

void AudioManager::LoadSound(const char* path)
{
	Mix_Chunk* t = Mix_LoadWAV(path);
	if (t != nullptr)
		m_vSounds.push_back(t);
	else
		cout << "Sound load failed. \n";
}

void AudioManager::LoadMusicGlobal(const char* path, std::string label)
{
	Mix_Music* t = Mix_LoadMUS(path);
	if (t != nullptr)
		m_vMusicGlobal.push_back(make_pair(t, label));
	else
		cout << "Global music load failed. \n";
}
void AudioManager::LoadMusicLocal(const char* path, string label)
{
	Mix_Music* t = Mix_LoadMUS(path);
	if (t != nullptr)
		m_vMusicLocal.push_back(make_pair(t, label));
	else
		cout << "Local music load failed. \n";
}

void AudioManager::PlayMusicGlobal(string label)
{
	for (size_t i = 0; i < m_vMusicGlobal.size(); i++)
	{
		if (m_vMusicGlobal[i].second == label)
		{
			Mix_PlayMusic(m_vMusicGlobal[i].first, 1);
		}
	}
}

void AudioManager::PlayMusicLocal(string label)
{
	for (size_t i = 0; i < m_vMusicLocal.size(); i++)
	{
		if (m_vMusicLocal[i].second == label)
		{
			Mix_PlayMusic(m_vMusicLocal[i].first, 1);
		}
	}
}

void AudioManager::ToggleMusic()
{
	//Mix_PausedMusic() returns 1 if paused.
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();

}

void AudioManager::UnloadMusic()
{
	for (size_t i = 0; i < m_vMusicTracks.size(); i++)
	{
		Mix_FreeMusic(m_vMusicTracks[i]);
		m_vMusicTracks.erase(std::next(m_vMusicTracks.begin()));
		m_vMusicTracks[i] = nullptr;
	}
	m_vMusicTracks.clear();
	m_vMusicTracks.shrink_to_fit();


	//how do you unload the entire vector?
	//iterate through the vector,
	//unload each index, and set its index to nullptr
	//after your do the above, 
	//clear the vector & shrink to fit

}

void AudioManager::UnloadSound()
{
	//how to unload a single audio chunk from memory:
	//Mix_FreeChunk(    )
	for (size_t i = 0; i < m_vSounds.size(); i++)
	{
		Mix_FreeChunk(m_vSounds[i]);

	}
}

AudioManager::~AudioManager()
{
	UnloadMusic();
	UnloadSound();

	Mix_CloseAudio();
	Mix_Quit();
}
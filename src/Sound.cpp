#include "Sound.hpp"

void Sound::loadEffects(void)
{
    this->effects = new Mix_Chunk*[NUM_EFFECTS];
    (this->effects)[EFFECT_CHIME] = Mix_LoadWAV("sounds/chime.wav");
    (this->effects)[EFFECT_WALK] = Mix_LoadWAV("sounds/walk_e.wav");
}

void Sound::loadMusic(void)
{
    this->music = new Mix_Music*[NUM_MUSIC];
    (this->music)[MUSIC_BEAR] = Mix_LoadMUS("sounds/background.wav");
}

Sound::Sound(void)
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, SOUND_CHANNELS, SOUND_CHUNK_SIZE);
    loadEffects();
    loadMusic();
}

Sound::~Sound(void)
{
    int loop;

    loop = 0;
    while (loop < NUM_EFFECTS)
        Mix_FreeChunk((this->effects)[loop++]);
    delete[] this->effects;
    loop = 0;
    while (loop < NUM_MUSIC)
        Mix_FreeMusic((this->music)[loop++]);
    delete[] this->music;
    Mix_CloseAudio();
}

void Sound::playEffectOnce(int effect, int channel)
{
    
    Mix_PlayChannel(channel, (this->effects)[effect], 0);
}

void Sound::playEffectLoop(int effect, int loop)
{
    Mix_PlayChannel(DEFAULT_CHANNEL, (this->effects)[effect], loop);
}

void Sound::playEffectForvever(int effect)
{
    Mix_PlayChannel(DEFAULT_CHANNEL, (this->effects)[effect], -1);
}

void Sound::playMusicOnce(int music)
{
    Mix_PlayMusic((this->music)[music], 1);
}

void Sound::playMusicLoop(int music, int loop)
{
    Mix_PlayMusic((this->music)[music], loop);
}

void Sound::playMusicForvever(int music)
{
    Mix_PlayMusic((this->music)[music], -1);
}

void Sound::stopEffect(int channel)
{
    Mix_HaltChannel(channel);
}

Mix_Chunk **Sound::getEffects(void)
{
    return (this->effects);
}

Mix_Music **Sound::getMusic(void)
{
    return (this->music);
}

void Sound::operator=(Sound *rhs)
{
    this->effects = rhs->getEffects();
    this->music = rhs->getMusic();
}
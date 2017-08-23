#ifndef SOUND_CLASS_HPP
#define SOUND_CLASS_HPP

#include "Bomberman.hpp"

#define SOUND_CHANNELS 2
#define SOUND_CHUNK_SIZE 4096

/* Channels */
#define WALK_CHANNEL 1
#define DEFAULT_CHANNEL -1

/* Effects */
#define NUM_EFFECTS 2
#define EFFECT_CHIME 0
#define EFFECT_WALK 1

/* Music */
#define NUM_MUSIC 1
#define MUSIC_BEAR 0

class Sound
{
    private:
        Mix_Chunk **effects;
        Mix_Music **music;
        
        void loadEffects(void);
        void loadMusic(void);

    public:
        Sound(void);
        ~Sound(void);

        void playEffectOnce(int effect, int channel);
        void playEffectLoop(int effect, int loop);
        void playEffectForvever(int effect);

        void playMusicOnce(int music);
        void playMusicLoop(int music, int loop);
        void playMusicForvever(int music);

        void stopEffect(int channel);        

        Mix_Chunk **getEffects(void);
        Mix_Music **getMusic(void);

        void operator=(Sound *rhs);
};

#endif
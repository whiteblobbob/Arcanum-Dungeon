#ifndef SOUND_H
#define SOUND_H


// Cross platform audio functions
void init_audio();
void cleanup_audio();

// BGM

void play_bgm(const char *filepath);
void stop_bgm();

// Volume
void set_bgm_volume(float volume);     // 0.0 – 1.0 (Indicate percentage)
void set_sfx_volume(float volume);     // 0.0 – 1.0 (Indicate percentage)

// SFX
void play_sfx(const char *filepath);
void stop_all_sfx();


#endif

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "sound.h"

ma_engine engine;
ma_sound bgm;         // BGM will Loop
int bgm_initialized = 0;

ma_engine engine;
ma_sound sfx_list[32];
int sfx_count = 0;

float sfx_volume = 1.0f; // default 100%


void init_audio() {
    ma_engine_init(NULL, &engine);
}

void play_sfx(const char* filename) {
    if (sfx_count >= 32) return;

    if (ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sfx_list[sfx_count]) == MA_SUCCESS) {
        ma_sound_set_volume(&sfx_list[sfx_count], sfx_volume); // << HERE
        ma_sound_start(&sfx_list[sfx_count]);
        sfx_count++;
    }
}

void set_sfx_volume(float volume) {
    sfx_volume = volume;

    // update volume semua sfx yang sedang aktif
    for (int i = 0; i < sfx_count; i++) {
        ma_sound_set_volume(&sfx_list[i], sfx_volume);
    }
}


void play_bgm(const char *file) {
    if (!bgm_initialized) {
        ma_sound_init_from_file(&engine, file, 0, NULL, NULL, &bgm);
        bgm_initialized = 1;
    } else {
        ma_sound_uninit(&bgm);
        ma_sound_init_from_file(&engine, file, 0, NULL, NULL, &bgm);
    }
    ma_sound_set_looping(&bgm, MA_TRUE);
    ma_sound_set_volume(&bgm, 1.0f);
    ma_sound_start(&bgm);

}

void set_bgm_volume(float volume) {
    ma_sound_set_volume(&bgm, volume);
}


void stop_bgm() {
    if (bgm_initialized) {
        ma_sound_stop(&bgm);
    }
}

void stop_all_sfx() {
    ma_engine_stop(&engine);
}


void cleanup_audio() {
    if (bgm_initialized) {
        ma_sound_uninit(&bgm);
    }
    ma_engine_uninit(&engine);
}

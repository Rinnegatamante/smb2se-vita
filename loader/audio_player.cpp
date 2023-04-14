#include <vitasdk.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

SoLoud::Soloud soloud;
SoLoud::WavStream music;
int music_handle = -1;

extern "C" {

void audio_player_init() {
	soloud.init();
}

void *audio_load_sound(char *fname) {
	auto *w = new SoLoud::Wav;
	w->load(fname);
	return w;
}

void audio_queue_music(char *fname, int loopcount) {
	music.load(fname);
	music.setLooping(loopcount == -1 ? true : false);
	music_handle = soloud.playBackground(music);
}

void audio_stop_music() {
	if (music_handle != -1)
		soloud.stop(music_handle);
	music_handle = -1;
}

void audio_set_music_volume(float volume) {
	music.setVolume(volume);
	if (music_handle != -1)
		soloud.setVolume(music_handle, volume);
}

int audio_play_sound(int id, float volume, float pitch, int loopcount) {
	auto *w = (SoLoud::Wav *)-id;
	w->setLooping(loopcount ? true : false);
	return soloud.play(*w, volume);
}

int last_removed_id = -1;
void audio_remove_sound(int id) {
	if (id != last_removed_id) {
		auto *w = (SoLoud::Wav *)-id;
		w->stop();
		delete w;
	}
	last_removed_id = id;
}

void audio_stop_sound(int id) {
	soloud.stop(id);
}

void audio_set_volume(int id, float volume) {
	soloud.setVolume(id, volume);
}

void audio_set_pitch(int id, float pitch) {
	soloud.setRelativePlaySpeed(id, pitch);
}

};

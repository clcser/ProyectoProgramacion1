#ifndef AUDIO_H
#define AUDIO_H

enum audio {
    JUMP,
    WIN,
    LOSE
};

void play_audio(enum audio type);

#endif

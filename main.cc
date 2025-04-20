#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <string>
#include <climits> 

struct playback_data {
    double freq;
    double ampl;
    double smoothing;
    double phase;
    double prev;
};

static void play_audio(void* userdata, unsigned char* stream, int len) {
    playback_data* data = (playback_data*)userdata;
    short* buffer = (short*)stream;
    size_t num_samples = len / sizeof (short);


    for (size_t i = 0; i < num_samples; ++i) {
        double total = 0.0;
        for (size_t j = 0; j < 4; ++j) {
            playback_data* v = &data[j];
            if (v->freq > 0.0 && v->ampl > 0.0) {
            v->phase += v->freq / 44100.0;
            if (v->phase >= 1.0) v->phase -= 1.0;
            double x = (v->phase < 0.5 ? v->ampl : -v->ampl);
            v->prev = (1.0 - v->smoothing) * x + v->smoothing * v->prev;
            total += v->prev;
            }
        }
        if (total >  1.0) total =  1.0;
        if (total < -1.0) total = -1.0;
        buffer[i] = (short)(total * SHRT_MAX);
    }
}




int main (){
    using namespace std;
    if(SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr<<"SDL could not initialize! SDL Error"<< SDL_GetError()<<endl;
    return 1;
    }

    playback_data data[4] = {};
    SDL_AudioSpec audio_spec = {
        .freq = 44100, .format = AUDIO_S16SYS, .channels = 1,
        .samples = 2048, .callback = play_audio, .userdata = &data
    };
    
    if (SDL_OpenAudio(&audio_spec, nullptr) < 0) {
        cerr<<"SDL_OpenAudio failed"<< SDL_GetError()<<endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_PauseAudio(false); 

    while (true) {
        string s;
        cin >> s;        
        if (s == "quit") 
            break;               
        else if (s == "freq") {
            int v; double f;
            cin >> v >> f;
            if (v >= 0 && v < 4) {
                SDL_LockAudio(); 
                data[v].freq = f;
                SDL_UnlockAudio(); 
            }
        }
        else if (s == "ampl") {
            int v; double a;
            cin >> v >> a;
            if (v >= 0 && v < 4) {
                SDL_LockAudio();
                data[v].ampl = a;
                if (a == 0.0) 
                    data[v].prev = 0.0;
                SDL_UnlockAudio();
            }
        }
        else if (s == "lowpass") {
            int v; double sp;
            cin >> v >> sp;
            if (v >= 0 && v < 4) {
                SDL_LockAudio();
                data[v].smoothing = sp;
                SDL_UnlockAudio();
            }
        }
        else if (s == "delay") {
            long ms;
            cin >> ms;
            SDL_Delay(ms);
        }
        else break;
    }

    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}

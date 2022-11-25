/*
** EPITECH PROJECT, 2022
** Hoppy
** File description:
** direct_sound_audio
*/

#include "audio/audio.h"

#include "foundation/dynamic_library.h"
#include "foundation/log.h"

#include <dsound.h>

namespace hoppy {
    typedef HRESULT (*PFN_DIRECT_SOUND_CREATE_8)(LPCGUID lpcGuidDevice, LPDIRECTSOUND8 *ppDS8, LPUNKNOWN pUnkOuter);

    struct dsound_state {
        dynamic_library dsound_library;
        IDirectSound8* dsound_device;
        DSCAPS device_caps;
        IDirectSoundBuffer* primary_buffer;
    };

    PFN_DIRECT_SOUND_CREATE_8 DSCreate8;
    static dsound_state ds_state;

    void audio_init(window *w)
    {
        dynamic_library_load(&ds_state.dsound_library, "dsound.dll");
        DSCreate8 = (PFN_DIRECT_SOUND_CREATE_8)dynamic_library_get_proc_addr(&ds_state.dsound_library, "DirectSoundCreate8");

        if (DSCreate8(NULL, &ds_state.dsound_device, NULL) != DS_OK) {
            log_err("[ERROR] Failed to create Direct Sound device!");
        }
        HRESULT result = IDirectSound8_SetCooperativeLevel(ds_state.dsound_device, (HWND)w->platform_handle, DSSCL_PRIORITY);
        if (FAILED(result)) {
            log_err("[ERROR] Failed to set cooperative level!");
        }
        ds_state.device_caps.dwSize = sizeof(DSCAPS);
        IDirectSound8_GetCaps(ds_state.dsound_device, &ds_state.device_caps);

        // NOTE(milo.h): Create primary buffer
        WAVEFORMATEX wave_format = {};
        wave_format.wFormatTag = WAVE_FORMAT_PCM;
        wave_format.nChannels = 2;
        wave_format.nSamplesPerSec = 48000;
        wave_format.nBlockAlign = 4;
        wave_format.nAvgBytesPerSec = wave_format.nSamplesPerSec * wave_format.nBlockAlign;
        wave_format.wBitsPerSample = 16;

        GUID guid_null;
        memset(&guid_null, 0, sizeof(GUID));

        DSBUFFERDESC buffer_desc = {};
        buffer_desc.dwSize = sizeof(DSBUFFERDESC);
        buffer_desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
        buffer_desc.dwBufferBytes = 0;
        buffer_desc.lpwfxFormat = NULL;
        buffer_desc.guid3DAlgorithm = guid_null;

        result = IDirectSound8_CreateSoundBuffer(ds_state.dsound_device, &buffer_desc, &ds_state.primary_buffer, NULL);
        if (FAILED(result)) {
            log_err("[ERROR] Failed to create primary sound buffer!");
        }
        IDirectSoundBuffer8_SetFormat(ds_state.primary_buffer, &wave_format);
    }

    void audio_exit()
    {
        IDirectSoundBuffer_Release(ds_state.primary_buffer);
        IDirectSound8_Release(ds_state.dsound_device);
        dynamic_library_free(&ds_state.dsound_library);
    }
}

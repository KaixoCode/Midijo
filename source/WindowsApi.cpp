#ifdef _WIN32
#include "Midijo/WindowsApi.hpp"

namespace Midijo
{
#define CHECK(x, msg, type) if (x != MMSYSERR_NOERROR) { LOGL(msg); type; }

    WindowsInApi::WindowsInApi(bool loadDevices)
    {
        if (loadDevices) {
            // Load devices
            Devices(true);
        }
    }

    const std::vector<DeviceInfo<Windows>>& WindowsInApi::Devices(bool reload)
    {
        if (!reload)
            return m_Devices;

        m_Devices.clear();

        auto _count = midiInGetNumDevs();
        for (auto i = 0; i < _count; i++)
        {
            MIDIINCAPS info;
            midiInGetDevCapsA(i, &info, sizeof info);

            std::string _name = info.szPname;

            m_Devices.push_back(DeviceInfo<Windows>{ { i, _name, Windows } });
        }

        return m_Devices;
    }

    Error WindowsInApi::Open(const MidiParameters& settings) 
    {
        if (m_Information.state != Closed)
            return AlreadyOpen;

        m_Information = settings;

        MMRESULT _res = midiInOpen(&m_Midi, settings.device, (DWORD_PTR)&MidiInProc, (DWORD_PTR)this, CALLBACK_FUNCTION);
        CHECK(_res, "Failed to open midi device", return 
              _res == MMSYSERR_ALLOCATED ? InUse
            : _res == MMSYSERR_BADDEVICEID ? InvalidDevice 
            : _res == MMSYSERR_NOMEM ? NoMemory : Fail);

        _res = midiInStart(m_Midi);
        CHECK(_res, "Failed to close midi device", return _res == MMSYSERR_INVALHANDLE ? InvalidDevice : Fail);

        m_Information.state = Opened;

        return NoError;
    }

    Error WindowsInApi::Close() 
    {
        if (m_Information.state == Closed)
            return NotOpen;

        MMRESULT _res = midiInStop(m_Midi);
        CHECK(_res, "Failed to close midi device", return _res == MMSYSERR_INVALHANDLE ? InvalidDevice : Fail);

        _res = midiInClose(m_Midi);
        CHECK(_res, "Failed to close midi device", return _res == MMSYSERR_INVALHANDLE ? InvalidDevice : Fail);

        m_Information.state = Closed;

        return NoError;
    }

    void WindowsInApi::MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) 
    {
        WindowsInApi* _api = (WindowsInApi*)dwInstance;

        uint8_t _b1 = (dwParam1 & 0x000000FF) >> 0;
        uint8_t _b2 = (dwParam1 & 0x0000FF00) >> 8;
        uint8_t _b3 = (dwParam1 & 0x00FF0000) >> 16;
        uint8_t _b4 = (dwParam1 & 0xFF000000) >> 24;
         
        switch (_b1)
        {
        case 0x90: _api->HandleEvent(NoteOn{ _b1, _b2, _b3, _b4 }); break;
        case 0x80: _api->HandleEvent(NoteOff{ _b1, _b2, _b3, _b4 }); break;
        case 0xA0: _api->HandleEvent(Aftertouch{ _b1, _b2, _b3, _b4 }); break;
        case 0xB0: _api->HandleEvent(CC{ _b1, _b2, _b3, _b4 }); break;
        case 0xC0: _api->HandleEvent(ProgramChange{ _b1, _b2, _b3, _b4 }); break;
        case 0xD0: _api->HandleEvent(ChannelAftertouch{ _b1, _b2, _b3, _b4 }); break;
        case 0xE0: _api->HandleEvent(PitchBend{ _b1, _b2, _b3, _b4 }); break;
        }
    }

    WindowsOutApi::WindowsOutApi(bool loadDevices)
    {
        if (loadDevices) {
            // Load devices
            Devices(true);
        }
    }

    const std::vector<DeviceInfo<Windows>>& WindowsOutApi::Devices(bool reload)
    {
        if (!reload) // No reload, just return devices.
            return m_Devices;

        m_Devices.clear();

        auto _count = midiOutGetNumDevs();
        for (auto i = 0; i < _count; i++)
        {
            MIDIOUTCAPS info;
            midiOutGetDevCapsA(i, &info, sizeof info);

            std::string _name = info.szPname;

            m_Devices.push_back(DeviceInfo<Windows>{ { i, _name, Windows } });
        }

        return m_Devices;
    }

    void WindowsOutApi::Message(const Event& e) 
    {
        midiOutShortMsg(m_Midi, (
            (static_cast<uint32_t>(e.byte1) << 0) |
            (static_cast<uint32_t>(e.byte2) << 8) |
            (static_cast<uint32_t>(e.byte3) << 16) |
            (static_cast<uint32_t>(e.byte4) << 24)));
    }

    Error WindowsOutApi::Open(const MidiParameters& settings) 
    {
        if (m_Information.state != Closed)
            return AlreadyOpen;

        m_Information = settings;

        MMRESULT _res = midiOutOpen(&m_Midi, settings.device, (DWORD_PTR)&MidiOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION);
        CHECK(_res, "Failed to open midi device", return
            _res == MMSYSERR_ALLOCATED ? InUse
            : _res == MMSYSERR_BADDEVICEID ? InvalidDevice
            : _res == MMSYSERR_NOMEM ? NoMemory : Fail);

        m_Information.state = Opened;

        return NoError;
    }

    Error WindowsOutApi::Close() 
    {
        if (m_Information.state == Closed)
            return NotOpen;

        MMRESULT _res = midiOutClose(m_Midi);
        CHECK(_res, "Failed to close midi device", return _res == MMSYSERR_INVALHANDLE ? InvalidDevice : Fail);

        m_Information.state = Closed;

        return NoError; 
    }

    void WindowsOutApi::MidiOutProc(HMIDIOUT hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
    {
        WindowsOutApi* _api = (WindowsOutApi*)dwInstance;
    }
}
#endif
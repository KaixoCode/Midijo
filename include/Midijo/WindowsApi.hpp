#ifdef _WIN32
#pragma once
#include "Midijo/pch.hpp"
#include "Midijo/ApiBase.hpp"

namespace Midijo
{
    template<>
    struct DeviceInfo<Windows> : public DeviceInfo<>
    {

    private:
        DeviceInfo(DeviceInfo<>&& d)
            : DeviceInfo<>{ std::forward<DeviceInfo<>>(d) }
        {}

        friend class WindowsApi;
        friend class WindowsInApi;
        friend class WindowsOutApi;
    };

    class WindowsApi : public ApiBase
    {
    public:
        virtual const std::vector<DeviceInfo<Windows>>& Devices(bool reload = false) = 0;

        const DeviceInfo<>& Device(int id) const override { for (auto& i : m_Devices) if (i.id == id) return (DeviceInfo<>&)i; };
        int DeviceCount() const override { return m_Devices.size(); }
        const DeviceInfo<Windows>& ApiDevice(int id) const { for (auto& i : m_Devices) if (i.id == id) return i; };

    protected:
        std::vector<DeviceInfo<Windows>> m_Devices;
    };

    class WindowsInApi : public WindowsApi
    {
    public:
        WindowsInApi(bool loadDevices = true);
        ~WindowsInApi() { Close(); }

        const std::vector<DeviceInfo<Windows>>& Devices(bool reload = false) override;

        Error Open(const MidiParameters& settings = MidiParameters{}) override;
        Error Close() override;

    private:
        HMIDIIN m_Midi;

        static void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, 
            DWORD_PTR dwParam1, DWORD_PTR dwParam2);
    };

    class WindowsOutApi : public WindowsApi
    {
    public:
        WindowsOutApi(bool loadDevices = true);
        ~WindowsOutApi() { Close(); }

        const std::vector<DeviceInfo<Windows>>& Devices(bool reload = false) override;
        void Message(const Event&) override;

        Error Open(const MidiParameters& settings = MidiParameters{}) override;
        Error Close() override;

    private:
        HMIDIOUT m_Midi;

        static void CALLBACK MidiOutProc(HMIDIOUT hMidiOut, UINT wMsg, DWORD_PTR dwInstance,
            DWORD_PTR dwParam1, DWORD_PTR dwParam2);
    };
}
#endif
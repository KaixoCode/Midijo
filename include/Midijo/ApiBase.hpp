#pragma once
#include "Midijo/pch.hpp"
#include "Midijo/Callback.hpp"

namespace Midijo 
{
#ifdef _WIN32
#define DEFAULT_MIDIJO_API Windows
#else
#define DEFAULT_MIDIJO_API // There has to be a default api, this won't compile!
#endif

    enum Api
    {
        Unspecified,
        Windows,
        DefaultApi = DEFAULT_MIDIJO_API,
    };

    template<Api api = Unspecified>
    struct DeviceInfo
    {
        /**
         * Device id
         */
        int id;

        /**
         * Device name
         */
        std::string name;

        /**
         * Device api
         */
        Api api;
    };

    template<typename ...Args> DeviceInfo(Args...)->DeviceInfo<Unspecified>;

    struct MidiParameters
    {
        /**
         * Midi device id.
         */
        int device = 0;

        /**
         * Asynchronously receive the midi messages.
         */
        int async = true;
    };

    enum MidiState
    {
        Closed, Opened
    };

    struct MidiInformation
    {
        MidiState state = Closed;
        int device = 0;
        bool async = true;

        MidiInformation& operator=(const MidiParameters& s)
        {
            device = s.device;
            async = s.async;
            return *this;
        }
    };

    enum Error
    {
        NoError = 0,

        NoMemory,      // Failed to allocate memory
        InUse,         // Midi device is already in use
        InvalidDevice, // The provided device id is invalid
        
        NotOpen,        // Midi is not open
        AlreadyOpen,    // Midi is already open
        Fail,           // General fail, either hardware or other. (Api specific fail)
    };

    class ApiBase
    {
    public:
        virtual ~ApiBase() { }
        virtual const DeviceInfo<>& Device(int id) const = 0;
        virtual int DeviceCount() const = 0;
        virtual const MidiInformation& Information() const { return m_Information; }

        virtual Error Open(const MidiParameters & = {}) = 0;
        virtual Error Close() = 0;

        EventListener listener;

        template<typename T>
        void HandleEvent(const T& e)
        {
            if (m_Information.async)
                listener.HandleEvent(e);
            else
            {
                std::lock_guard _{ m_Lock };
                m_EventQueue.push(std::make_unique<T>(e));
            }
        }

        void HandleEvents();
        bool HandleEvent();

        virtual void Message(const Event&) {};

    protected:
        MidiInformation m_Information;
        std::queue<std::unique_ptr<Event>> m_EventQueue;
        std::mutex m_Lock;
    };
}
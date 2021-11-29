#pragma once
#include "Midijo/pch.hpp"
#include "Midijo/ApiBase.hpp"
#include "Midijo/WindowsApi.hpp"

namespace Midijo
{
    template<Api api = Unspecified>
    class Midi
    {
    public:
        /**
         * Returns device with the given id.
         * @param id device id
         * @return device with id
         */
        const DeviceInfo<>& Device(int id) const { return m_Api->Device(id); }

        /**
         * Get the device count.
         * @return device count
         */
        int DeviceCount() const { return m_Api->DeviceCount(); }

        /**
         * Get midi information. This call only returns useful information after a device has been opened.
         * @return midi information
         */
        const MidiInformation& Information() const { return m_Api->Information(); }

        /**
         * Open the midi device.
         * @param settings <code>MidiParameters</code>
         * @return
         * AlreadyOpen - If the stream is already opened<br>
         * InUse - If the midi device is already in use<br>
         * InvalidDevice - If the provided device id is invalid<br>
         * Fail - If the device failed to open<br>
         * NoError - If stream opened successfully
         */
        Error Open(const MidiParameters& settings = MidiParameters{}) { return m_Api->Open(settings); };
        
        /**
         * Start the midi device.
         * @return
         * NotOpen - If the stream wasn't opened<br>
		 * AlreadyRunning - If the stream is already running<br>
		 * InvalidDevice - If the opened device id has become invalid<br>
         * Fail - If the device failed to start<br>
         * NoError - If stream started successfully
         */
        Error Start() { return m_Api->Start(); };

        /**
         * Stop the midi device.
         * @return
		 * NotOpen - If the stream wasn't opened<br>
		 * NotRunning - If the stream is not running<br>
         * InvalidDevice - If the opened device id has become invalid<br>
         * Fail - If the device failed to stop<br>
         * NoError - If stream stopped successfully
         */
        Error Stop() { return m_Api->Stop(); };

        /**
         * Close the midi device.
         * @return
		 * NotOpen - If the stream wasn't opened<br>
         * InvalidDevice - If the opened device id has become invalid<br>
         * Fail - If the device failed to close<br>
         * NoError - If stream closed successfully
         */
        Error Close() { return m_Api->Close(); };

    protected:
        std::unique_ptr<ApiBase> m_Api = nullptr;
        Midijo::Api m_Type = api;
    };

    template<>
    class Midi<Windows> : public Midi<>
    {
    public:
        /**
         * Search for all available devices. When called more than once, the list will be updated.
         * @return all available devices given the chosen api.
         */
        const std::vector<DeviceInfo<Windows>>& Devices(bool reload = false) const { return ((WindowsInApi*)m_Api.get())->Devices(reload); }

        /**
         * Returns device with the given id.
         * @param id device id
         * @return device with id
         */
        const DeviceInfo<Windows>& Device(int id) const { return ((WindowsInApi*)m_Api.get())->ApiDevice(id); }
    };

    template<Api api = Unspecified>
    class MidiIn : public Midi<api>
    {
    public:
        /**
         * Constructor
         * @param a api
         */
        MidiIn() requires (api != Unspecified) { Api(api); }
        MidiIn(Api a) requires (api == Unspecified) { Api(a); }

        /**
         * Get this MidiIn object as a specific api, to expose api specific functions.
         * @return this as a midi object for a specific api
         */
        template<Api a>
        MidiIn<a>& Get() requires (api == Unspecified) { return *(MidiIn<a>*)this; }

        /**
         * Set the api.
         * @param api api
         */
        void Api(Midijo::Api a)
        {
            this->m_Type = a;
            switch (a)
            {
#ifdef _WIN32
            case Windows: this->m_Api = std::make_unique<WindowsInApi>(); break;
#endif
            default: throw std::exception("Incompatible api");
            }
        }

        /**
         * Get the current api of this midi.
         * @return api
         */
        Midijo::Api Api() const { return m_Type; }

        /**
         * Add a midi event callback. The returned Callback object will
         * remove the callback from when its destructor is called. 
         * This behaviour is useful when registering a callback inside an object,
         * because this will automatically remove the callback when the object is destroyed.
         * @param callback callback
         * @return callback object
         */
        template<ValidCallback T>
        Callback ScopedCallback(T&& callback) 
        {
            return this->m_Api->listener.ScopedCallback(std::forward<T>(callback));
        }

        /**
         * Add a midi event callback. 
         * @param callback callback
         */
        template<ValidCallback T>
        void Callback(T&& callback)
        {
            return this->m_Api->listener.Callback(std::forward<T>(callback));
        }

        /**
         * Only use this when async is set to false. 
         * Handles all the events in the queue.
         */
        void HandleEvents() { this->m_Api->HandleEvents(); }

        /**
         * Only use this when async is set to false.
         * Handles a single event, returns true when an event was handled.
         * @return true if there was an event to handle.
         */
        bool HandleEvent() { return this->m_Api->HandleEvent(); }
    };

    template<Api api = Unspecified>
    class MidiOut : public Midi<api>
    {
    public:
        /**
         * Constructor
         * @param a api
         */
        MidiOut() requires (api != Unspecified) { Api(api); }
        MidiOut(Api a) requires (api == Unspecified) { Api(a); }

        /**
         * Get this MidiIn object as a specific api, to expose api specific functions.
         * @return this as a midi object for a specific api
         */
        template<Api a>
        MidiOut<a>& Get() requires (api == Unspecified) { return *(MidiOut<a>*)this; }

        /**
         * Set the api.
         * @param api api
         */
        void Api(Midijo::Api api)
        {
            this->m_Type = api;
            switch (api)
            {
#ifdef _WIN32
            case Windows: this->m_Api = std::make_unique<WindowsOutApi>(); break;
#endif
            default: throw std::exception("Incompatible api");
            }
        }

        /**
         * Get the current api of this midi.
         * @return api
         */
        Midijo::Api Api() const { return m_Type; }
    };

    MidiIn(Api)->MidiIn<Unspecified>;
    MidiIn()->MidiIn<DefaultApi>;
    MidiOut(Api)->MidiOut<Unspecified>;
    MidiOut()->MidiOut<DefaultApi>;
}


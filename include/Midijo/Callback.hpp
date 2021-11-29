#pragma once
#include "Midijo/pch.hpp"

namespace Midijo
{    
    // Get the signature of a member function
    template<typename T>
    struct MemberSignature {};
    template<typename Ret, typename Type, typename... Args>
    struct MemberSignature<Ret(Type::*)(Args...) const>
    {
        using type = Ret(Args...);
    };
    template<typename Ret, typename Type, typename... Args>
    struct MemberSignature<Ret(Type::*)(Args...)>
    {
        using type = Ret(Args...);
    };

    // Get the signature of a lambda's operator()
    template<typename _Fx, typename = void>
    struct LambdaSignature {};
    template<typename _Fx>
    struct LambdaSignature<_Fx, std::void_t<decltype(&_Fx::operator())>>
    {
        using type = typename MemberSignature<decltype(&_Fx::operator())>::type;
    };

    template<typename _Fx>
    using LambdaSignatureT = typename LambdaSignature<_Fx>::type;

    /**
     * All notes that can be generated from a midi message.
     */
    enum Note
    {
         C = 0,   C0 = C  | 0x0,  C1 = C  | 0x10,  C2 = C  | 0x20,  C3 = C  | 0x30,  
        CS = 1,  CS0 = CS | 0x0, CS1 = CS | 0x10, CS2 = CS | 0x20, CS3 = CS | 0x30,  
         D = 2,   D0 = D  | 0x0,  D1 = D  | 0x10,  D2 = D  | 0x20,  D3 = D  | 0x30,  
        DS = 3,  DS0 = DS | 0x0, DS1 = DS | 0x10, DS2 = DS | 0x20, DS3 = DS | 0x30,  
         E = 4,   E0 = E  | 0x0,  E1 = E  | 0x10,  E2 = E  | 0x20,  E3 = E  | 0x30,  
         F = 5,   F0 = F  | 0x0,  F1 = F  | 0x10,  F2 = F  | 0x20,  F3 = F  | 0x30,  
        FS = 6,  FS0 = FS | 0x0, FS1 = FS | 0x10, FS2 = FS | 0x20, FS3 = FS | 0x30,  
         G = 7,   G0 = G  | 0x0,  G1 = G  | 0x10,  G2 = G  | 0x20,  G3 = G  | 0x30,  
        GS = 8,  GS0 = GS | 0x0, GS1 = GS | 0x10, GS2 = GS | 0x20, GS3 = GS | 0x30,  
         A = 9,   A0 = A  | 0x0,  A1 = A  | 0x10,  A2 = A  | 0x20,  A3 = A  | 0x30,  
        AS = 10, AS0 = AS | 0x0, AS1 = AS | 0x10, AS2 = AS | 0x20, AS3 = AS | 0x30, 
         B = 11,  B0 = B  | 0x0,  B1 = B  | 0x10,  B2 = B  | 0x20,  B3 = B  | 0x30, 

         C4 = C  | 0x40,  C5 = C  | 0x50,  C6 = C  | 0x60,  C7 = C  | 0x70,  C8 = C  | 0x80, 
        CS4 = CS | 0x40, CS5 = CS | 0x50, CS6 = CS | 0x60, CS7 = CS | 0x70, CS8 = CS | 0x80, 
         D4 = D  | 0x40,  D5 = D  | 0x50,  D6 = D  | 0x60,  D7 = D  | 0x70,  D8 = D  | 0x80, 
        DS4 = DS | 0x40, DS5 = DS | 0x50, DS6 = DS | 0x60, DS7 = DS | 0x70, DS8 = DS | 0x80, 
         E4 = E  | 0x40,  E5 = E  | 0x50,  E6 = E  | 0x60,  E7 = E  | 0x70,  E8 = E  | 0x80, 
         F4 = F  | 0x40,  F5 = F  | 0x50,  F6 = F  | 0x60,  F7 = F  | 0x70,  F8 = F  | 0x80, 
        FS4 = FS | 0x40, FS5 = FS | 0x50, FS6 = FS | 0x60, FS7 = FS | 0x70, FS8 = FS | 0x80, 
         G4 = G  | 0x40,  G5 = G  | 0x50,  G6 = G  | 0x60,  G7 = G  | 0x70,  G8 = G  | 0x80, 
        GS4 = GS | 0x40, GS5 = GS | 0x50, GS6 = GS | 0x60, GS7 = GS | 0x70, GS8 = GS | 0x80, 
         A4 = A  | 0x40,  A5 = A  | 0x50,  A6 = A  | 0x60,  A7 = A  | 0x70,  A8 = A  | 0x80, 
        AS4 = AS | 0x40, AS5 = AS | 0x50, AS6 = AS | 0x60, AS7 = AS | 0x70, AS8 = AS | 0x80, 
         B4 = B  | 0x40,  B5 = B  | 0x50,  B6 = B  | 0x60,  B7 = B  | 0x70,  B8 = B  | 0x80, 

         C9 = C  | 0x90,  C10 = C  | 0xA0,  C11 = C  | 0xB0, 
        CS9 = CS | 0x90, CS10 = CS | 0xA0, CS11 = CS | 0xB0, 
         D9 = D  | 0x90,  D10 = D  | 0xA0,  D11 = D  | 0xB0, 
        DS9 = DS | 0x90, DS10 = DS | 0xA0, DS11 = DS | 0xB0, 
         E9 = E  | 0x90,  E10 = E  | 0xA0,  E11 = E  | 0xB0, 
         F9 = F  | 0x90,  F10 = F  | 0xA0,  F11 = F  | 0xB0, 
        FS9 = FS | 0x90, FS10 = FS | 0xA0, FS11 = FS | 0xB0, 
         G9 = G  | 0x90,  G10 = G  | 0xA0,  G11 = G  | 0xB0, 
        GS9 = GS | 0x90, GS10 = GS | 0xA0, GS11 = GS | 0xB0, 
         A9 = A  | 0x90,  A10 = A  | 0xA0,  A11 = A  | 0xB0, 
        AS9 = AS | 0x90, AS10 = AS | 0xA0, AS11 = AS | 0xB0, 
         B9 = B  | 0x90,  B10 = B  | 0xA0,  B11 = B  | 0xB0, 
    };
    
    struct Event 
    {
        Event(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
            : byte1(a), byte2(b), byte3(c), byte4(d)
        {}

        uint8_t byte1, byte2, byte3, byte4;

        /**
         * Signal that this event has been handled.
         */
        void Handle() const { handled = true; }

        /**
         * Check if this event has been handled.
         * @return true when Handle has been called
         */
        bool Handled() const { return handled; }

    private:
        mutable bool handled = false;
        virtual void DynamicLink() = 0;
    };

    /**
     * Event that fires when you press a midi key. 
     */
    struct NoteOn : public Event
    {
        using Event::Event;

        /**
         * Create note on event.
         * @param note note
         * @param velocity velocity
         */
        NoteOn(Midijo::Note note, uint8_t velocity) 
            : Event(0x90, note & 0xF + (12 * (note >> 4)), velocity, 0)
        {}

        /**
         * Create note on event.
         * @param raw raw note number
         * @param velocity velocity
         */
        NoteOn(uint8_t raw, uint8_t velocity)
            : Event(0x90, raw, velocity, 0)
        {}
        
        /**
         * Get the midi note that was pressed.
         * @return midi note
         */
        Midijo::Note Note() const { return static_cast<Midijo::Note>(((byte2 / 12) << 4) | (byte2 % 12)); };

        /**
         * Get the raw note number.
         * @return raw note number
         */
        uint8_t RawNote() const { return byte2; }

        /**
         * Get the velocity.
         * @return velocity
         */
        uint8_t Velocity() const { return byte3; };

    private:
        void DynamicLink() override {};
    };

    /**
     * Event that fires when you release a midi key.
     */
    struct NoteOff : public Event
    {
        using Event::Event;

        /**
         * Create note off event.
         * @param note note
         * @param velocity velocity
         */
        NoteOff(Midijo::Note note, uint8_t velocity)
            : Event(0x80, note & 0xF + (12 * (note >> 4)), velocity, 0)
        {}

        /**
         * Create note off event.
         * @param raw raw note number
         * @param velocity velocity
         */
        NoteOff(uint8_t raw, uint8_t velocity)
            : Event(0x80, raw, velocity, 0)
        {}

        /**
         * Get the midi note that was pressed.
         * @return midi note
         */
        Midijo::Note Note() const { return static_cast<Midijo::Note>(((byte2 / 12) << 4) | (byte2 % 12)); };

        /**
         * Get the raw note number.
         * @return raw note number
         */
        uint8_t RawNote() const { return byte2; }

        /**
         * Get the velocity.
         * @return velocity
         */
        uint8_t Velocity() const { return byte3; };

    private:
        void DynamicLink() override {};
    };

    /**
     * Event that fires when there is a pressure change press 
     * on one of the currently pressed midi keys.
     */
    struct Aftertouch : public Event
    {
        using Event::Event;

        /**
         * Create aftertouch event.
         * @param note note
         * @param amount amount
         */
        Aftertouch(Midijo::Note note, uint8_t amount)
            : Event(0xA0, note & 0xF + (12 * (note >> 4)), amount, 0)
        {}

        /**
         * Create aftertouch event.
         * @param raw raw note number
         * @param amount amount
         */
        Aftertouch(uint8_t raw, uint8_t amount)
            : Event(0xA0, raw, amount, 0)
        {}

        /**
         * Get the midi note that was pressed.
         * @return midi note
         */
        Midijo::Note Note() const { return static_cast<Midijo::Note>(((byte2 / 12) << 4) | (byte2 % 12)); };        

        /**
         * Get the raw note number.
         * @return raw note number
         */
        uint8_t RawNote() const { return byte2; }

        /**
         * Get the aftertouch amount.
         * @return amount
         */
        uint8_t Amount() const { return byte3; }

    private:
        void DynamicLink() override {};
    };

    /**
     * Event that fires when there is a change in state
     * of one of the controllers.
     */
    struct CC : public Event
    {
        using Event::Event;

        /**
         * Create cc event.
         * @param number number
         * @param value value
         */
        CC(uint8_t number, uint8_t value)
            : Event(0xB0, number, value, 0)
        {}

        /**
         * Get the cc number that was updated.
         * @return cc number
         */
        uint8_t Number() const { return byte2; }

        /**
         * Get the value of the cc that was updated.
         * @return value
         */
        uint8_t Value() const { return byte3; }

    private:
        void DynamicLink() override {};
    };

    /**
     * Event that fires when a program change is requested.
     */
    struct ProgramChange : public Event
    {
        using Event::Event;

        /**
         * Create program change event.
         * @param program program
         */
        ProgramChange(uint8_t program)
            : Event(0xC0, program, 0, 0)
        {}

        /**
         * Get the program.
         * @return program
         */
        uint8_t Program() const { return byte2; }

    private:
        void DynamicLink() override {};
    };

    /**
     * Event that fired when the channel aftertouch has been changed.
     */
    struct ChannelAftertouch : public Event
    {
        using Event::Event;

        /**
         * Create channel aftertouch event.
         * @param amount amount
         */
        ChannelAftertouch(uint8_t amount)
            : Event(0xD0, amount, 0, 0)
        {}

        /**
         * Get the aftertouch amount.
         * @return amount
         */
        uint8_t Amount() const { return byte2; }

    private:
        void DynamicLink() override {};
    };

    /**
     * Event that fires when the pitch bend changes.
     */
    struct PitchBend : public Event
    {
        using Event::Event;

        /**
         * Create pitch bend event.
         * @param amount amount
         */
        PitchBend(uint8_t amount)
            : Event(0xE0, amount, 0, 0)
        {}

        /**
         * Get the pitch bend value.
         * @return value
         */
        uint16_t Value() const { return static_cast<uint16_t>(byte2) | (static_cast<uint16_t>(byte3) << 7); }

    private:
        void DynamicLink() override {};
    };

    struct EventFunctionBase
    {
        virtual void Call(const Event&) = 0;
    };

    template<typename, typename>
    struct EventFunction;
    template<typename Func, std::derived_from<Event> Type>
    struct EventFunction<Func, void(const Type&)> : EventFunctionBase
    {
        EventFunction(Func f) : fun(f) {}

        void Call(const Event& e) override
        {
            // Try casting
            const Type* _e = dynamic_cast<const Type*>(&e);
            if (_e) // if successfull, call callback
                fun(*_e);
        }

        Func fun;
    };

    struct Callback
    {
        ~Callback() { if (m_Deleter) m_Deleter(); };
        std::function<void(void)> m_Deleter;
    };

    struct EventListener
    {
        template<typename T>
        Callback ScopedCallback(T&& t) 
        {
            auto& _ptr = m_Listeners.emplace_back(std::make_unique<EventFunction<T, LambdaSignatureT<T>>>(std::forward<T>(std::forward<T>(t))));
            auto _raw = _ptr.get();
            auto& _l = m_Listeners;
            return { [_raw, &_l]() {
                _l.erase(std::remove_if(_l.begin(), _l.end(), [&](auto& _p) { return _p.get() == _raw; }));
            } };
        }

        template<typename T>
        void Callback(T&& t)
        {
            m_Listeners.emplace_back(std::make_unique<EventFunction<T, LambdaSignatureT<T>>>(std::forward<T>(std::forward<T>(t))));
        }

        void HandleEvent(const Event& e)
        {
            // Call all event listeners
            for (auto& l : m_Listeners)
                l->Call(e);
        }

    private:
        std::vector<std::unique_ptr<EventFunctionBase>> m_Listeners;
    };

    template<typename T>
    struct ValidCallbackType;

    template<typename Ret, typename Arg> requires (std::is_const_v<std::remove_reference_t<Arg>> && std::is_reference_v<Arg>) 
    struct ValidCallbackType<Ret(Arg)>
    {
        using type = std::decay_t<Arg>;
    };

    template<typename T>
    concept ValidCallback = std::derived_from<typename ValidCallbackType<LambdaSignatureT<T>>::type, Event>;

}
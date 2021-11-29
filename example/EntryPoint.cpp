#include "Midijo/Midijo.hpp"

using namespace Midijo;

int main()
{
    MidiIn in;
    
    // Register a callback for any event type.
    in.Callback([](const Event& e)
    {
        std::cout << 
            (int)e.byte1 << ", " << (int)e.byte2 << ", " << 
            (int)e.byte3 << ", " << (int)e.byte4 << '\n';
    });
    
    // Register a callback for a specific event type.
    in.Callback([](const NoteOn& e)
    {
        std::cout << e.Note() << ", " << e.Velocity() << '\n';
    });
    
    // Open device with id 0.
    in.Open({.device = 0 });
    
    // Receive events for 10 seconds.
    std::this_thread::sleep_for(std::chrono::seconds(10));
    
    // Close the device.
    in.Close();

    MidiOut out;

    out.Open({ .device = 0 });

    out.Message(NoteOn{ Note::C5, 127 });
    std::this_thread::sleep_for(std::chrono::seconds(1));
    out.Message(NoteOff{ Note::C5, 127 });

    out.Close();
}

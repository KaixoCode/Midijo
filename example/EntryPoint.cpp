#include "Midijo/Midijo.hpp"

using namespace Midijo;

int main()
{
    MidiIn midi;
    
    // Register a callback for any event type.
    midi.Callback([](const Event& e)
    {
        std::cout << 
            (int)e.byte1 << ", " << (int)e.byte2 << ", " << 
            (int)e.byte3 << ", " << (int)e.byte4 << '\n';
    });
    
    // Register a callback for a specific event type.
    midi.Callback([](const NoteOn& e) 
    {
        std::cout << e.Note() << ", " << e.Velocity() << '\n';
    });
    
    midi.Api();

    // Open device with id 0 and start.
    midi.Open({.device = 0 });
    midi.Start();
    
    // Receive events for 10 seconds.
    std::this_thread::sleep_for(std::chrono::seconds(10));
    
    // Close the device.
    midi.Close();
}

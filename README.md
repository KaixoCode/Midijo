# Midijo
Simple midi library for modern C++. It requires C++20! Currently only supports Window's midi api.

Documentation: https://code.kaixo.me/Midijo/

## Some quick examples
Input
```cpp
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

midi.Open({.device = 0 });

{
    // Add a scoped callback
    Callback c = in.ScopedCallback([](const CC& e)
    {
        std::cout << e.Number() << ", " << e.Value() << '\n';
    });

    // Added callback gets remove when it goes out of scope 5 seconds later.
    // This is useful when registering callbacks in objects, since it automatically
    // removes the callback when the object is destroyed.
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

std::this_thread::sleep_for(std::chrono::seconds(5));

midi.Close();
```
Output
```cpp
MidiOut out;

out.Open({ .device = 0 });

// Set note on and off message.
out.Message(NoteOn{ Note::C5, 127 });
std::this_thread::sleep_for(std::chrono::seconds(1));
out.Message(NoteOff{ Note::C5, 127 });

out.Close();
```

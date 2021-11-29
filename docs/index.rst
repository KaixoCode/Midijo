Welcome to Midijo's documentation!
===================================

Midijo repository: https://github.com/KaixoCode/Midijo


.. toctree::
   :maxdepth: 10
   :caption: Contents:



Content
=======

- Documentation_
	- :ref:`Midi`
		- Midi_
		- MidiIn_
		- MidiOut_
	- :ref:`Events`
		- Event_
		- NoteOn_
		- NoteOff_
		- Aftertouch_
		- CC_
		- ProgramChange_
		- ChannelAftertouch_
		- PitchBend_
	- :ref:`Structs`
		- MidiParameters_
		- DeviceInfo_
	- :ref:`Enums`
		- Api_
		- Error_
- Examples_
	- :ref:`Midi input`

Documentation
==============

Midi
----

.. _Midi:
.. doxygenclass:: Midijo::Midi
	:members:
	
.. _MidiIn:
.. doxygenclass:: Midijo::MidiIn
	:members:

.. _MidiOut:
.. doxygenclass:: Midijo::MidiOut
	:members:

Events
------

.. _Event:
.. doxygenstruct:: Midijo::Event
    :members:

.. _NoteOn:
.. doxygenstruct:: Midijo::NoteOn
    :members:

.. _NoteOff:
.. doxygenstruct:: Midijo::NoteOff
    :members:

.. _Aftertouch:
.. doxygenstruct:: Midijo::Aftertouch
    :members:

.. _CC:
.. doxygenstruct:: Midijo::CC
    :members:

.. _ProgramChange:
.. doxygenstruct:: Midijo::ProgramChange
    :members:

.. _ChannelAftertouch:
.. doxygenstruct:: Midijo::ChannelAftertouch
    :members:

.. _PitchBend:
.. doxygenstruct:: Midijo::PitchBend
    :members:

Structs
-------

.. _MidiParameters:
.. doxygenstruct:: Midijo::MidiParameters
    :members:

.. _DeviceInfo:
.. doxygenstruct:: Midijo::DeviceInfo
    :members:

Enums
-----

.. _Api:
.. doxygenenum:: Midijo::Api
    :outline:

.. _Error:
.. doxygenenum:: Midijo::Error
    :outline:

Examples
========

Midi input
----------

.. code-block:: cpp
	
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
        
        // Open device with id 0 and start.
        midi.Open({.device = 0 });
        midi.Start();
        
        // Receive events for 10 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(10));
        
        // Close the device.
        midi.Close();
    }

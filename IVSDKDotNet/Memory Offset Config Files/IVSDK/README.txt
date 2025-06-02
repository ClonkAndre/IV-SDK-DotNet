- What is this folder for?

This folder contains configuration (.ini) files for different versions of GTA IV, each storing the necessary memory offsets for IV-SDK.

- Adding new offset configuration files

To add support for a new GTA IV version:

   - Duplicate an existing .ini file (e.g., 1080.ini).
   - Rename it to match the GTA IV version you want to support (e.g., 12059.ini).
   - Now you can update all the memory offsets for this version.

The configuration file is built up using section, keys and values which look like this:

[Section]
Key=Value

The name of a section matches the name of a header file e.g. "CPlayerInfo"
The name of a key matches the name of a member e.g. "FindPlayerPed"
The value of a key will be the memory offset for the member in hex (e.g. 0x123456) or a memory pattern e.g. "55 8B EC 83 E4 F0 83 EC 64 53 56 57 BB" (At this point, the option to put in patterns are experimental because you can't adjust the index and offset yet)
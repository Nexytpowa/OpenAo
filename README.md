This is the official code repository for OpenAo project.

DISCLAIMER: the original game was developed by Masangsoft and most of the code is
still untouched. This does not imply our project is not legitimate. We have made
efforts to improve the code quality, performance and stability -all voluntarily.
These efforts, encouraged by our passion for this game and the lack of interest
by the original developers, compose the OpenAo project.

Most noticable design changes can be seen in the new design of CPreIOCPSocket and
AtumProtocolX where type safety and compile time optimizations have been added.
AtumProtocolX files are generated by the "codegen" project. The purpose of these
changes is to reduce redundant code (like packet data validation) by offering
generic code that correctly handles each case without run-time overhead.

Another attempt to improve the game performance is the ParticleRendering.cpp,
which uses geometry instancing to draw sprites and trail effects. In addition,
missile collision detection has been parallelized using OpenMP but it seems to
introduce bugs to some users right now.


Last but not least, removing "useless" funcionality is another key point of this
project, even though it's harder than it sounds. For example, after removing
server IDs, some stuff (arena has not been tested at all yet) does not work correctly.

# Build settings:
Visual Studio 2022 Project
DevX ou DevX_arena

# Compile Order:

## Server:

1. ProjectsServer/XmlRpc (once built you must build only if it has been updated)
2. ProjectsServer/ZipArchive (once built you must build only if it has been updated)
3. ProjectsServer/GameServer

## Client: depends on QuestLoaderLib built in GameServer

4. ProjectAtum/BaseClasses (once built you must build only if it has been updated)
5. ProjectAtum/ProjectAtum

# Some guidelines

1. Use util::zero instead of memset; it's simpler, generic and with just 1 argument.
2. Use range-for loop instead of old c++ style iterations (UNLESS there is an erase inside the loop). It makes the code more readable.
3. Replace NULL with nullptr and TRUE/FALSE with true/false. These keywords are the standard nowadays.

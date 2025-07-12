#ifndef REGISTRYBLOCKER_H
#define REGISTRYBLOCKER_H

#include <string>

// Blocks the given executable path by creating an IEFO Debugger registry entry
bool BlockApp(const std::wstring &appPath);

// Unblocks the given executable by removing its IEFO Debugger registry entry
bool UnblockApp(const std::wstring &appPath);

// Exports the IEFO registry key to the given output path
// outPath will be set to the .reg file path
bool BackupRegistry(std::wstring &outPath);

// Imports the IEFO registry key from the given .reg file path
int RestoreRegistry(const std::wstring &inPath);

#endif // REGISTRYBLOCKER_H

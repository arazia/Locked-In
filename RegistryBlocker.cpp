#include "RegistryBlocker.h"
#include <windows.h>
#include <cstdlib>

static const std::wstring IEFO_SUBKEY = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options";

static std::wstring ExtractFileName(const std::wstring &path) {
    size_t pos = path.find_last_of(L"\\/");
    return (pos == std::wstring::npos) ? path : path.substr(pos + 1);
}

bool BlockApp(const std::wstring &appPath) {
    std::wstring exeName = ExtractFileName(appPath);
    HKEY hKey;
    LONG res = RegCreateKeyExW(
        HKEY_LOCAL_MACHINE,
        (IEFO_SUBKEY + L"\\" + exeName).c_str(),
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_SET_VALUE | KEY_WOW64_64KEY,
        NULL,
        &hKey,
        NULL
        );
    if (res != ERROR_SUCCESS) return false;
    const std::wstring debugger = L"cmd.exe /c exit";
    res = RegSetValueExW(
        hKey,
        L"Debugger",
        0,
        REG_SZ,
        reinterpret_cast<const BYTE*>(debugger.c_str()),
        static_cast<DWORD>((debugger.size() + 1) * sizeof(wchar_t))
        );
    RegFlushKey(hKey);
    RegCloseKey(hKey);
    return (res == ERROR_SUCCESS);
}

bool UnblockApp(const std::wstring &appPath) {
    std::wstring exeName = ExtractFileName(appPath);
    HKEY hKey;
    LONG res = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        (IEFO_SUBKEY + L"\\" + exeName).c_str(),
        0,
        KEY_SET_VALUE | KEY_WOW64_64KEY,
        &hKey
        );
    if (res != ERROR_SUCCESS) return false;
    RegDeleteValueW(hKey, L"Debugger");
    RegFlushKey(hKey);
    RegCloseKey(hKey);
    return true;
}

bool BackupRegistry(std::wstring &outPath) {
    std::wstring cmd =
        L"reg export \"HKLM\\" + IEFO_SUBKEY + L"\" \"" + outPath + L"\" /y";
    int code = _wsystem(cmd.c_str());
    return (code == 0);
}

int RestoreRegistry(const std::wstring &inPath) {
    DWORD attrs = GetFileAttributesW(inPath.c_str());
    if (attrs == INVALID_FILE_ATTRIBUTES || (attrs & FILE_ATTRIBUTE_DIRECTORY)) {
        return -1;
    }
    std::wstring cmd = L"reg import \"" + inPath + L"\"";
    return _wsystem(cmd.c_str());
}

# Custom-GetModuleHandleW
This is the Custom Implementation of The GetModuleHandleW() function in Windows API 

# Explanation
GetModuleHandleW is a function in the Windows API, defined in kernel32.dll. It is used to retrieve the module handle for a specified module that has been loaded into the address space of the calling process. 
Essentially, it provides a way to get the base address of a loaded DLL or executable without having to pass its handle when the module was loaded.

# Use of GetModuleHandleW()

GetModuleHandleW is widely used in legitimate software development, but it is also leveraged by malware for various purposes. 
Malware developers often use GetModuleHandleW to get the base address of specific system DLLs (like kernel32.dll, user32.dll, etc.) to dynamically resolve the addresses of functions they want to call without directly importing them. 
This helps in evading static analysis performed by Anti-Virus (AV) engines.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

internal void *
Reserve(u64 Size) {
    void *Memory = VirtualAlloc(0, Size, MEM_RESERVE, PAGE_NOACCESS);
    return Memory;
}

internal void
Release(void *Memory) {
    VirtualFree(Memory, 0, MEM_RELEASE);
}

internal void
Commit(void *Memory, u64 Size) {
    VirtualAlloc(Memory, Size, MEM_COMMIT, PAGE_READWRITE);
}

internal void
Decommit(void *Memory, u64 Size) {
    VirtualFree(Memory, Size, MEM_DECOMMIT);
}

internal b32
ReadFileAndNullTerminate(memory_arena *Arena, char *Path, char **Data, i64 *DataSize) {
    b32 Result = false;
    
    HANDLE FileHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (FileHandle != INVALID_HANDLE_VALUE) {
        u32 FileSize = GetFileSize(FileHandle, 0);
        
        if (FileSize) {
            *Data = (char *)Push(Arena, FileSize);
            DWORD BytesRead = 0;
            
            ReadFile(FileHandle, *Data, FileSize, &BytesRead, 0);
            (*Data)[FileSize] = 0;
            
            *DataSize = FileSize;
            
            Result = true;
        }
        
        CloseHandle(FileHandle);
    }
    
    return Result;
}

internal void
WriteStdOut(char *Text, i64 Size) {
    if (Size < 0) {
        Size = StringLength(Text);
    }
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    DWORD BytesWritten;
    WriteFile(Handle, Text, Size, &BytesWritten, 0);
}
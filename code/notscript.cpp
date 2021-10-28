#include "common.h"
#include "memory.h"
#include "platform.h"

#include "memory.cpp"
#include "tokenizer.cpp"
#include "parser.cpp"

#ifdef NS_PLATFORM_WINDOWS
#include "impl_win32.cpp"
#else
#error "Unsupported platform."
#endif

int main(int ArgumentCount, char **Arguments) {
    memory_arena Arena = InitializeMemoryArena();
    
    char *FileData;
    i64 FileSize;
    
    if (ReadFileAndNullTerminate(&Arena, Arguments[1], &FileData, &FileSize)) {
        string FileString = {FileData, FileSize};
        ast_node *Root = GenerateASTFromString(FileString, &Arena);
    }
    
    return 0;
}
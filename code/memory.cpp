#define MEMORY_ARENA_MAX Gigabytes(1)
#define MEMORY_ARENA_COMMIT_SIZE Kilobytes(4)

internal memory_arena
InitializeMemoryArena() {
    memory_arena Arena = {};
    Arena.Max = MEMORY_ARENA_MAX;
    Arena.Base = Reserve(Arena.Max);
    Arena.AllocPosition = 0;
    Arena.CommitPosition = 0;
    
    return Arena;
}

internal void *
Push(memory_arena *Arena, u64 Size) {
    void *Memory = 0;
    if (Arena->AllocPosition + Size + Arena->CommitPosition) {
        u64 CommitSize = Size;
        CommitSize += MEMORY_ARENA_COMMIT_SIZE - 1;
        CommitSize -= CommitSize % MEMORY_ARENA_COMMIT_SIZE;
        Commit((u8 *)Arena->Base + Arena->CommitPosition, CommitSize);
        Arena->CommitPosition += CommitSize;
    }
    
    Memory = (u8 *)Arena->Base + Arena->AllocPosition;
    Arena->AllocPosition += Size;
    
    return Memory;
}

internal void *
PushZero(memory_arena *Arena, u64 Size) {
    void *Memory = Push(Arena, Size);
    MemorySet(Memory, 0, Size);
    
    return Memory;
}

internal void
Pop(memory_arena *Arena, u64 Size) {
    if (Size > Arena->AllocPosition) {
        Size = Arena->AllocPosition;
    }
    
    Arena->AllocPosition -= Size;
}

internal void
Clear(memory_arena *Arena) {
    Pop(Arena, Arena->AllocPosition);
}

internal void
Release(memory_arena *Arena) {
    Release(Arena->Base);
}
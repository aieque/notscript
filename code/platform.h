internal void *Reserve(u64 Size);
internal void Release(void *Memory);
internal void Commit(void *Memory, u64 Size);
internal void Decommit(void *Memory, u64 Size);
internal b32 ReadFileAndNullTerminate(memory_arena *Arena, char *Path, char **Data, i64 *DataSize);
internal void WriteStdOut(char *Text, i64 Size = -1);
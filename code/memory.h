struct memory_arena {
    void *Base;
    u64 Max;
    u64 AllocPosition;
    u64 CommitPosition;
};
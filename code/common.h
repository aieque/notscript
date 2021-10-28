#define global static
#define internal static
#define local_persist static
#define ArrayCount(a) (sizeof(a) / sizeof((a)[0]))
#define Bytes(n)      (n)
#define Kilobytes(n)  (n << 10)
#define Megabytes(n)  (n << 20)
#define Gigabytes(n)  (((u64)n) << 30)
#define Terabytes(n)  (((u64)n) << 40)
#define PI (3.1415926535897f)

#include <stdint.h>

#include <xmmintrin.h>
#include <emmintrin.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef u32 b32;

#define StrLit(Str) Str, strlen(Str)
#define Assert(Statement) {if(!(Statement)) WriteStdOut("Assertion failed " #Statement); __debugbreak();}

struct string {
    char *Data;
    i64 Size;
};

internal void
__MemorySet(void *Dest, int Value, size_t Count) {
    for (int I = 0; I < Count; ++I) {
        ((char *)Dest)[I] = Value;
    }
}

internal void
MemorySet(void *Dest, int Value, size_t Count) {
    __m128i Value16 = _mm_set_epi8(Value, Value, Value, Value,
                                   Value, Value, Value, Value,
                                   Value, Value, Value, Value,
                                   Value, Value, Value, Value);
    
    size_t Offset = ((intptr_t) Dest) % 16;
    size_t IterationCount = (Count - Offset) / 16;
    size_t Remaining = Count - IterationCount * 16 - Offset;
    
    u8 *Pointer = (u8 *)Dest;
    
    __MemorySet(Pointer, Value, Offset);
    Pointer += Offset;
    
    for (size_t I = 0; I < IterationCount; ++I) {
        _mm_store_si128((__m128i *)Pointer, Value16);
        Pointer += 16;
    }
    
    __MemorySet(Pointer, Value, Remaining);
}

internal i64
StringLength(char *String) {
    i64 Result = 0;
    while (*String++) Result++;
    return Result;
}

inline b32
IsWhitespace(char Char) {
    return (Char == ' ' || Char == '\t' || Char == '\r' || Char == '\n');
}

inline b32
IsLetter(char Char) {
    return ((Char >= 'a' && Char <= 'z') ||
            (Char >= 'A' && Char <= 'Z'));
}

inline b32
IsDigit(char Char) {
    return (Char >= '0' && Char <= '9');
}

inline b32
IsValidIdentifierStartChar(char Char) {
    return IsLetter(Char) || IsDigit(Char);
}

inline b32
IsValidIdentifierChar(char Char) {
    return IsValidIdentifierStartChar(Char) || Char == '_';
}

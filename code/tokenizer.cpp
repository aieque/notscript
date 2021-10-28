struct tokenizer {
    char *At;
};

enum token_type {
    // For single character tokens, they simply use their corresponding ASCII-code.
    
    TokenType_Invalid = 0x100,
    TokenType_EndOfFile,
    TokenType_Identifier,
    TokenType_Number,
    TokenType_String,
    TokenType_Annotation, // @ + identifier
    TokenType_Comment,
    TokenType_DoubleColon,
    TokenType_TripleDots,
};

struct token {
    token_type Type;
    
    string EntireToken;
    
    union {
        string StringValue;
        i64 IntegerValue;
    };
};

internal token
GetToken(tokenizer *Tokenizer) {
    token Token = {};
    Token.Type = TokenType_Invalid;
    
    while (IsWhitespace(Tokenizer->At[Token.EntireToken.Size])) {
        Tokenizer->At += 1;
    }
    
    Token.EntireToken.Data = Tokenizer->At;
    Token.EntireToken.Size = 1;
    
#define SingleChar(Character) case Character: {Token.Type = (token_type)Character;} break;
    
    switch (Tokenizer->At[0]) {
        SingleChar('(');
        SingleChar(')');
        SingleChar('[');
        SingleChar(']');
        SingleChar('{');
        SingleChar('}');
        SingleChar(';');
        SingleChar('$');
        SingleChar('=');
        SingleChar(',');
        
        case '.': {
            if (Tokenizer->At[1] == '.' &&
                Tokenizer->At[2] == '.') {
                Token.Type = TokenType_TripleDots;
                Token.EntireToken.Size = 3;
            } else {
                Assert(!"Expected triple dots.");
            }
        } break;
        
        case ':': {
            if (Tokenizer->At[1] == ':') {
                Token.Type = TokenType_DoubleColon;
                Token.EntireToken.Size = 2;
            } else {
                Assert(!"Expected double colon.");
            }
        } break;
        
        case '\0': {
            Token.Type = TokenType_EndOfFile;
        } break;
        
        case '/': {
            if (Tokenizer->At[1] == '/') {
                while (Tokenizer->At[Token.EntireToken.Size] != '\n' &&
                       Tokenizer->At[Token.EntireToken.Size] != '\r' &&
                       Tokenizer->At[Token.EntireToken.Size] != '\0') {
                    Token.EntireToken.Size += 1;
                }
                
            }
        } break;
        
        case '@': {
            while (IsValidIdentifierChar(Tokenizer->At[Token.EntireToken.Size])) {
                Token.EntireToken.Size += 1;
            }
            
            Token.StringValue.Size = Token.EntireToken.Size - 1;
            Token.StringValue.Data = Token.EntireToken.Data + 1;
        } break;
        
        case '"': {
            Token.Type = TokenType_String;
            
            while (Tokenizer->At[Token.EntireToken.Size] != '"') {
                Token.EntireToken.Size += 1;
            }
            
            Token.EntireToken.Size += 1;
            
            Token.StringValue.Data = Token.EntireToken.Data + 1;
            Token.StringValue.Size = Token.EntireToken.Size - 2;
        } break;
        
        default: {
            // Assume it's an identifier.
            
            if (IsValidIdentifierStartChar(Tokenizer->At[0])) {
                Token.Type = TokenType_Identifier;
                
                while (IsValidIdentifierChar(Tokenizer->At[Token.EntireToken.Size])) {
                    Token.EntireToken.Size += 1;
                }
                
                Token.StringValue = Token.EntireToken;
            } else {
                Assert(!"Unknown token!");
            }
            
        } break;
    }
    
    Tokenizer->At += Token.EntireToken.Size;
    
    return Token;
}

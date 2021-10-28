enum ast_node_type {
    ASTNode_Invalid,
    
    ASTNode_
};

struct ast_node {
    
};

internal ast_node *
GenerateASTFromString(string Data, memory_arena *Arena) {
    tokenizer Tokenizer = {};
    Tokenizer.At = Data.Data;
    
    token Token;
    while ((Token = GetToken(&Tokenizer)).Type != TokenType_EndOfFile) {
        
    }
    
    return 0;
}
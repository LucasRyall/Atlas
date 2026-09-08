# What is this?
This is a silly little language that I am making, for no reason other than it seemed like a fun project. 
The current plan is for this to be a purely functional language in the same vein as Haskel

# Where does the name come from?
My cat

# Why C?
I wanted to get better at writing C code.

# Why has x been done this way?
Because so far very little forethought has been put into any features.

# Why is the syntax like x?
Idk, read above.

# AI
Strictly no AI written code. (I ethically steal from forums)

# Doesn't work on my system
If it doesn't work elsewhere feel free to make a PR/ submit an issue.

# Current Syntax

this is very much up to changing, but I needed to settle on somehting to get things moving. Don't think this is finished yet or will even represent what I want it to. also forgive the strange syntax, some of it doesn't make sense, will get fixed later

<Block> ::= <Declaration>*
<Declaration> ::= "include" "string" | "const" <Identifier> "::=" <Expression> | "fn" <Function>
<Function> ::= <Identifier> (<Identifier> ("," <Identifier>)*)* ":" (<Statement> | <PatternMatch>+)
<PatternMatch> ::= "|" <Expression> ("," <Expression>)* "->" <Statement>
<Identifier> ::= [a-zA-Z_][a-zA-Z0-9_]*
<Statement> ::= <Identifier>? <Expression> ("," <Expression>)* | "if" <Expression> "then" <Statement> "else" <Statement>
<Expression> ::= <Factor> ("BINARY_OP" <Expression>)?
<Factor> ::= "UNARY_OP"? (<Identifier> | <Number>)
<Number> ::= [0-9]+

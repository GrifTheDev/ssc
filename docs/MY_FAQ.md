# My FAQ

During this journey, I've had some questions of my own, I will be leaving them here as well as the answers I've been able to gather to hopefully help anyone facing the same issues.

# Questions
## 1. Why do we need to keep two copies of basically the same enum, one for lexical analisis and one for the AST?
> They are not going to be the same for long! Remember, an AST is just an **abstract** representation of the CST. This means that we are going to drop some tokens eventually (like () or ,) since they do not contribute to the, let's call it important, meaning the parser has to examine. Also, one lexical token can mean many things in the AST depending on the context (bitwise and [&] or the address of operator [&]), mappings aren't always 1:1!
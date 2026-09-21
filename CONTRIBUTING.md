If you want to contribute to C^4, fork the repository, make your changes, and open a pull request.
## Commit Syntax
Commits should follow this format:
```
category(thing): message
```
Available categories:
```
improve   Improvements to existing functionality
feat      New functionality or language features
clean     Code cleanup, refactoring, or technical debt
errors    Changes to diagnostics, warnings, or error handling / adding more errors, warnings, notes, help, suggestions, etc
fix       Bug fixes
```
For example:
```
feat(parser, compiler): add modifier support
errors(warnings, diagnostics, help, suggestions): add help suggestions to warnings
clean(compiler): simplify type checking
fix(codegen): handle missing returns in main
improve(lexer): reduce tokenization overhead
```
If your commit is about multiple catagories, comma-seperate.
```
errors(warnings),feat(cli-flags): added warnings & -W flags
```
If you forgot something in a previous commit, i like to use
```
oops(README): forgot to re-add README.md

Only contribute something if it is a bug or a crash, it's on the roadmap, it's obviously important or wanted, or you've been told it's good in the discussions or it fits the core ideals of the language: I don't want people wasting their time on things that don't fit the idea of the language.
```

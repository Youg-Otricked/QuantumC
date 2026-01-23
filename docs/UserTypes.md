<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# User Types

[Back to Home](./index.md)

### Types of User Types:

|////|Use|Syntax|Pro/Con|
|----|---|------|-------|
|Struct|Storing a group of variables|struct name { field-type field-name; ...};|Very useful and simple|
|Union |Defines a set of types or literals that a varibale of this type can be|type union-name = type-orliteral1 | type-orliteral2.....;|Amazingly powerfull for much more than just making a varibale of multiple types|
|Alias |Aliases a type to a name|type alias-name = type-to-alias;|Simple, just aliasing a name|
|Enum  |Stores a collection of name -> literal mappings|enum name = { fieldone = value; .....};|Can do somthing similar with unions, however enums are more usefull and explicit for this use.|

### Syntax And examples
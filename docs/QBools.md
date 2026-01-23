<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# QBools

[Back to Home](./index.md)

### QBools are another important feature of Quantum C. They are booleans with 4 states. While this is simple to understand, beign able to assign both both and none along with qtrue and qfalse, what is complex is their logical operators, which they have 8 of.

|Logical operator|Name|Syntax |Use (Truth tables below)|
|----------------|----|-------|------------------------|
|&&&             |QAND|L &&& R|&& for QBools           |
|\|\|\|          |QOR |L \|\|\| R|\|\| for QBools      |
|&zwj;^^         |QXOR|L ^^ R |&zwj;^ for QBools       |
|!!              |QNOT|!!A    |! For QBools            |
|&\|&            |Collapse AND|L &\|& R|Convert QBool to bool|
|\|&\|           |Collapse OR|L \|&\| R|Convert QBool to bool|
|===             |Quantum Equals|L === R|If L is R: both, otherwise none|
|!==             |Quantum Inequal|L !== R|If L is not R: both, otherwise none|

#### Quantum Logic truth tables

|&&&|none|qfalse|qtrue|both|
|---|----|------|-----|----|
|**none**|none|qfalse|qfalse|qfalse|
|**qfalse**|qfalse|qfalse|qfalse|qfalse|
|**qtrue**|qfalse|qfalse|qtrue|both|
|**both**|qfalse|qfalse|both|both|

|\|\|\||none|qfalse|qtrue|both|
|---|----|------|-----|----|
|**none**|none|qfalse|qtrue|both|
|**qfalse**|qfalse|qfalse|both|both|
|**qtrue**|qtrue|both|qtrue|both|
|**both**|both|both|both|both|

|!!|none|qfalse|qtrue|both|
|--|----|------|-----|----|
|  |both|qtrue|qfalse|none|

Sorry this one is a bit confusing
|^^|none|qfalse|qtrue|both|
|--|----|------|-----|----|
|**none**|none|none|both|both|
|**qfalse**|none|none|both|both|
|**qtrue**|both|both|qfalse|both|
|**both**|both|both|both|qfalse| 

|&\|&|none|qfalse|qtrue|both|
|----|----|------|-----|----|
|**none**|false|false|false|false|
|**qfalse**|false|false|false|false|
|**qtrue**|false|false|true|true|
|**both**|false|false|true|true|

|\|&\||none|qfalse|qtrue|both|
|----|----|------|-----|----|
|**none**|false|false|true|true|
|**qfalse**|false|false|true|true|
|**qtrue**|true|true|true|true|
|**both**|true|true|true|true|

# And thats the core of quantum booleans.


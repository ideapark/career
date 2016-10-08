Welcome to Railroad Diagram Generator!
======================================

This is a tool for creating syntax diagrams, also known as railroad
diagrams, from context-free grammars specified in EBNF. Syntax
diagrams have been used for decades now, so the concept is well-known,
and some tools for diagram generation are in existence. The features
of this one are:

* usage of the W3C's EBNF notation
* web-scraping of grammars from W3C specifications
* online editing of grammars
* diagram presentation in SVG
* and it was completely written in web language (XQuery, XHTML, CSS,
  JavaScript)
  
Notation
========

For the original description of the EBNF notaion as it is used here,
please refer to "A.1.1 Notation" in the XQuery recommendation. The XML
recommendation contains a similar section, "6 Notation". Below is a
self-describing grammar for the EBNF notation.

```
 Grammar                 ::= Production*
 Production              ::= NCName '::=' ( Choice | Link )
 NCName                  ::= [http://www.w3.org/TR/xml-names/#NT-NCName]
 Choice                  ::= SequenceOrDifference ( '|' SequenceOrdifference )*
 Sequenceordifference    ::= (Item ( '-' Item | Item* ))?
 Item                    ::= Primary ( '?' | '*' | '+' )?
 Primary                 ::= NCName | StringLiteral | CharCode | CharClass | '(' Choice ')'
 Stringliteral           ::= '"' [^"]* '"' | "'" [^']* "'"
 CharCode                ::= '#x' [0-9a-fA-F]+
 CharClass               ::= '[' '^'? ( Char | CharCode | CharRange | CharCodeRange )+ ']'
 Char                    ::= [http://www.w3.org/TR/xml#NT-Char]
 CharRange               ::= Char '-' ( Char - ']' )
 CharCodeRange           ::= CharCode '-' CharCode
 Link                    ::= '[' URL ']'
 URL                     ::= [^#x5D:/?#]+ '://' [^#x5D#]+ ('#' NCName)?
 Whitespace              ::= S | Comment
 S                       ::= #x9 | #xA | #xD | #x20
 Comment                 ::= '/*' ( [^*] | '*'+ [^*/] )* '*'* '*/'
```

For viewing railroad diagrams of this very grammar, either

* select "EBNF Notation" from the "Get Grammar" tab
* or copy and paste the above grammer to the "Edit Grammar" tab

and then proceed to the "View Diagram" tab, Or just click here for a shortcut.

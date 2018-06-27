# YAML Ain't Markup Language (YAML) Version 1.2

## Abstract

YAML (rhymes with "camel") is a human-friendly, cross language, Unicode based
data serialization language designed around the common native data types of
agile programming languages. It is broadly useful for programming needs ranging
from configuration files to Internet messaging to object persistence to data
auditing. Together with the Unicode standard for characters, this specification
provides all the information necessary to understand YAML Version 1.2 and to
create programs that process YAML information.

## Chapter 1. Introduction

"YAML Ain't Markup Language" (abbrieviated YAML) is a data serialization
language disigned to be human-friendly and work well with modern programming
languages for common everyday tasks. This specification is both an introcution
to the YAML language and the concpets supporting it, and also a complete
specification of the information needed to develop applications for processing
YAML.

Open, ineroperable and readily understandable tools have advanced computing
immensely. YAML was designed from the start to be useful and friendly to people
working with data. It uses Unicode printable characters, some of which provide
structual information and the rest containing the data itself. YAML achieves a
unique cleanness by minimizaing the amount of structural characters and allowing
the data to show itself in a natural and meaningful way. For example,
indentation may be used for structure, colons separate key: value pairs, and
dashes are used to create "bullet" lists.

The are myriad flavors of data structures, but they can all be adequately
represented with three basic primitives: mappings (hashes/dictionaries),
sequences (arrays/lists) and scalars (strings/numbers). YAML leverages these
primitives, and adds a simple typing system and aliasing mechanism to form a
complete language for seializaing any native data structure. While most
programming languages can use YAML for data serialization, YAML excels in
working with those languages that are fundamentally built around the three basic
primitives. These include the new wave of agile languages such as Perl, Python,
PHP, Ruby, and Javascript.

There are hundreds of different languages for programming, but only a handful of
languages for storing and transferring data. Even though its potential is
virtually boundless, YAML was specifically created to work well for common use
cases such as: configuration files, log files, interprocess messaging,
cross-language data sharing, object persistence, and debugging of complex data
structures. When data is easy to view and understand, programming becomes a
simpler task.

### Goals

The design goals for YAML are, in decreasing priority:

- YAML is easily readable by humans.
- YAML data is portable between programming languages.
- YAML meatches the native data structures of agile languages.
- YAML has a consistent model to support generic tools.
- YAML supports one-pass processing.
- YAML is expressive and extensible.
- YAML is easy to implement and use.

### Prior Art

YAML's initial direction was set by the data serialization and markup language
discussions among SML-DEV members. Later on, it directly incorporated experience
from Ingy dot Net's Perl module Data::Denter. Since then, YAML has matured
through ideas and support from its user community.

YAML integrates and builds upon concepts described by C, Java, Perl, Python,
Ruby, RFC0822 (MAIL), RFC1866 (HTML), RFC2045 (MIME), RFC2396 (URI), XML, SAX,
SOAP, and JSON.

The syntax of YAML was motivated by Internet Mail (RFC0822) and remains
partially compatible with that standard. Further, borrowing from MIME (RFC2045),
YAML's top-level production is a stream of independent documents, ideal from
message-based distributed processing systems.

YAML’s indentation-based scoping is similar to Python’s (without the
ambiguities caused by tabs). Indented blocks facilitate easy inspection of the
data’s structure. YAML’s literal style leverages this by enabling formatted
text to be cleanly mixed within an indented structure without troublesome
escaping. YAML also allows the use of traditional indicator-based scoping
similar to JSON’s and Perl’s. Such flow content can be freely nested inside
indented blocks.

YAML’s double-quoted style uses familiar C-style escape sequences. This enables
ASCII encoding of non-printable or 8-bit (ISO 8859-1) characters such as
“\x3B”. Non-printable 16-bit Unicode and 32-bit (ISO/IEC 10646) characters are
supported with escape sequences such as “\u003B” and “\U0000003B”.

Motivated by HTML’s end-of-line normalization, YAML’s line folding employs an
intuitive method of handling line breaks. A single line break is folded into a
single space, while empty lines are interpreted as line break characters. This
technique allows for paragraphs to be word-wrapped without affecting the
canonical form of the scalar content.

YAML’s core type system is based on the requirements of agile languages such as
Perl, Python, and Ruby. YAML directly supports both collections (mappings,
sequences) and scalars. Support for these common types enables programmers to
use their language’s native data structures for YAML manipulation, instead of
requiring a special document object model (DOM).

Like XML’s SOAP, YAML supports serializing a graph of native data structures
through an aliasing mechanism. Also like SOAP, YAML provides for
application-defined types. This allows YAML to represent rich data structures
required for modern distributed computing. YAML provides globally unique type
names using a namespace mechanism inspired by Java’s DNS-based package naming
convention and XML’s URI-based namespaces. In addition, YAML allows for private
types specific to a single application.

YAML was designed to support incremental interfaces that include both input
(“getNextEvent()”) and output (“sendNextEvent()”) one-pass interfaces.
Together, these enable YAML to support the processing of large documents (e.g.
transaction logs) or continuous streams (e.g. feeds from a production machine).

### Relation to JSON

Both JSON and YAML aim to be human readable data interchange formats. However,
JSON and YAML have different priorities. JSON’s foremost design goal is
simplicity and universality. Thus, JSON is trivial to generate and parse, at the
cost of reduced human readability. It also uses a lowest common denominator
information model, ensuring any JSON data can be easily processed by every
modern programming environment.

In contrast, YAML’s foremost design goals are human readability and support for
serializing arbitrary native data structures. Thus, YAML allows for extremely
readable files, but is more complex to generate and parse. In addition, YAML
ventures beyond the lowest common denominator data types, requiring more complex
processing when crossing between different programming environments.

YAML can therefore be viewed as a natural superset of JSON, offering improved
human readability and a more complete information model. This is also the case
in practice; every JSON file is also a valid YAML file. This makes it easy to
migrate from JSON to YAML if/when the additional features are required.

JSON's RFC4627 requires that mappings keys merely “SHOULD” be unique, while
YAML insists they “MUST” be. Technically, YAML therefore complies with the
JSON spec, choosing to treat duplicates as an error. In practice, since JSON is
silent on the semantics of such duplicates, the only portable JSON files are
those with unique keys, which are therefore valid YAML files.

It may be useful to define a intermediate format between YAML and JSON. Such a
format would be trivial to parse (but not very human readable), like JSON. At
the same time, it would allow for serializing arbitrary native data structures,
like YAML. Such a format might also serve as YAML’s "canonical format".
Defining such a “YSON” format (YSON is a Serialized Object Notation) can be
done either by enhancing the JSON specification or by restricting the YAML
specification. Such a definition is beyond the scope of this specification.

### Relation to XML

Newcomers to YAML often search for its correlation to the eXtensible Markup
Language (XML). Although the two languages may actually compete in several
application domains, there is no direct correlation between them.

YAML is primarily a data serialization language. XML was designed to be
backwards compatible with the Standard Generalized Markup Language (SGML), which
was designed to support structured documentation. XML therefore had many design
constraints placed on it that YAML does not share. XML is a pioneer in many
domains, YAML is the result of lessons learned from XML and other technologies.

It should be mentioned that there are ongoing efforts to define standard
XML/YAML mappings. This generally requires that a subset of each language be
used. For more information on using both XML and YAML, please visit
http://yaml.org/xml.

### Terminology

This specification uses key words based on RFC2119 to indicate requirement
level. In particular, the following words are used to describe the actions of a
YAML processor:

May     The word may, or the adjective optional, mean that conforming YAML
        processors are permitted to, but need not behave as described.

Should  The word should, or the adjective recommended, mean that there could be
        reasons for a YAML processor to deviate from the behavior described, but
        that such deviation could hurt interoperability and should therefore be
        advertised with appropriate notice

Must    The word must, or the term required or shall, mean that the behavior
        described is an absolute requirement of the specification.

The rest of this document is arranged as follows. Chapter 2 provides a short
preview of the main YAML features. Chapter 3 describes the YAML information
model, and the processes for converting from and to this model and the YAML text
format. The bulk of the document, chapters 4 through 9, formally define this
text format. Finally, chapter 10 recommends basic YAML schemas.

## Chapter 2. Preview

This section provides a quick glimpse into the expressive power of YAML. It is
not expected that the first-time reader grok all of the examples. Rather, these
selections are used as motivation for the remainder of the specification.

### Collections

YAML’s block collections use indentation for scope and begin each entry on its
own line. Block sequences indicate each entry with a dash and space ( “- ”).
Mappings use a colon and space (“: ”) to mark each key: value pair. Comments
begin with an octothorpe (also called a “hash”, “sharp”, “pound”, or
“number sign” - “#”).

- Example 2.1. Sequence of Scalars (ball players)

```yaml
- Mark McGwire
- Sammy Sosa
- Ken Griffey
```

- Example 2.2. Mapping Scalars to Scalars (player statistics)

```yaml
hr:  65    # Home runs
avg: 0.278 # Batting average
rbi: 147   # Runs Batted In
```

- Example 2.3. Mapping Scalars to Sequences (ball clubs in each league)

```yaml
american:
 - Boston Red Sox
 - Detroit Tigers
 - New York Yankees
national:
 - New York Mets
 - Chicago Cubs
 - Atlanta Braves
```

- Example 2.4. Sequence of Mappings (players’ statistics)

```yaml
-
 name: Mark McGwire
 hr: 65
 avg: 0.278
-
 name: Sammy Sosa
 hr: 63
 avg: 0.288
```

YAML also has flow styles, using explicit indicators rather than indentation to
denote scope. The flow sequence is written as a comma separated list within
square brackets. In a similar manner, the flow mapping uses curly braces.

- Example 2.5. Sequence of Sequences

```yaml
- [name        , hr, avg  ]
- [Mark McGwire, 65, 0.278]
- [Sammy Sosa  , 63, 0.288]
```

- Example 2.6. Mapping of Mappings

```yaml
Mark McGwire: {hr: 65, avg: 0.278}
Sammy Sosa: {
    hr: 63,
    avg: 0.288
 }
```

### Structures

YAML uses three dashes (“---”) to separate directives from document content.
This also serves to signal the start of a document if no directives are present.
Three dots ( “...”) indicate the end of a document without starting a new one,
for use in communication channels.

- Example 2.7. Two Documents in a Stream (each with a leading comment)

```yaml
# Ranking of 1998 home runs
---
- Mark McGwire
- Sammy Sosa
- Ken Griffey

# Team ranking
---
- Chicago Cubs
- St Louis Cardinals
```

- Example 2.8. Play by Play Feed from a Game

```yaml
---
time: 20:03:20
player: Sammy Sosa
action: strike (miss)
...

---
time: 20:03:47
player: Sammy Sosa
action: grand slam
...
```

Repeated nodes (objects) are first identified by an anchor (marked with the
ampersand - “&”), and are then aliased (referenced with an asterisk - “*”)
thereafter.

- Example 2.9. Single Document with Two Comments

```yaml
---
hr: # 1998 hr ranking
 - Mark McGwire
 - Sammy Sosa
rbi:
 # 1998 rbi ranking
 - Sammy Sosa
 - Ken Griffey
```

- Example 2.10. Node for “Sammy Sosa” appears twice in this document

```yaml
---
hr:
 - Mark McGwire
 # Following node labeled SS
 - &SS Sammy Sosa
rbi:
 - *SS # Subsequent occurrence
 - Ken Griffey
```

A question mark and space (“? ”) indicate a complex mapping key. Within a
block collection, key: value pairs can start immediately following the dash,
colon, or question mark.

- Example 2.11. Mapping between Sequences

```yaml
? - Detroit Tigers
  - Chicago cubs
:
  - 2001-07-23
? [ New York Yankees,
    Atlanta Braves ]
: [ 2001-07-02, 2001-08-12,
    2001-08-14 ]
```

- Example 2.12. Compact Nested Mapping

```yaml
---
# Products purchased
- item    : Super Hoop
  quantity: 1
- item    : Basketball
  quantity: 4
- item    : Big Shoes
  quantity: 1
```

### Scalars

Scalar content can be written in block notation, using a literal style
(indicated by “|”) where all line breaks are significant. Alternatively, they
can be written with the folded style (denoted by “>”) where each line break is
folded to a space unless it ends an empty or a more-indented line.

- Example 2.13. In literals, newlines are preserved

```yaml
# ASCII Art
--- |
  \//||\/||
  // ||  ||__
```

- Example 2.14. In the folded scalars, newlines become spaces

```yaml
--- >
  Mark McGwire's
  year was crippled
  by a knee injury.
```

- Example 2.15. Folded newlines are preserved for "more indented" and blank lines

```yaml
>
 Sammy Sosa completed another
 fine season with great stats.

   63 Home Runs
   0.288 Batting Average

 What a year!
```

- Example 2.16. Indentation determines scope

```yaml
name: Mark McGwire
accomplishment: >
  Mark set a major league
  home run record in 1998.
stats: |
  65 Home Runs
  0.278 Batting Average
```

YAML’s flow scalars include the plain style (most examples thus far) and two
quoted styles. The double-quoted style provides escape sequences. The
single-quoted style is useful when escaping is not needed. All flow scalars can
span multiple lines; line breaks are always folded.

- Example 2.17. Quoted Scalars

```yaml
unicode: "Sosa did fine.\u263A"
control: "\b1998\t1999\t2000\n"
hex esc: "\x0d\x0a is \r\n"

single: '"Howdy!" he cried.'
quoted: ' # Not a ''comment''.'
tie-fighter: '|\-*-/|'
```

- Example 2.18. Multi-line Flow Scalars

```yaml
plain:
  This unquoted scalar
  spans many lines.

quoted: "So does this
  quoted scalar.\n"
```

### Tags

In YAML, untagged nodes are given a type depending on the application. The
examples in this specification generally use the seq, map and str types from the
fail safe schema. A few examples also use the int, float, and null types from
the JSON schema. The repository includes additional types such as binary, omap,
set and others.

- Example 2.19. Integers

```yaml
canonical: 12345
decimal: +12345
octal: 0o14
hexadecimal: 0xC
```

- Example 2.20. Floating Point

```yaml
canonical: 1.23015e+3
exponential: 12.3015e+02
fixed: 1230.15
negative infinity: -.inf
not a number: .NaN
```

- Example 2.21. Miscellaneous

```yaml
null:
booleans: [ true, false ]
string: '012345'
```

- Example 2.22. Timestamps

```yaml
canonical: 2001-12-15T02:59:43.1Z
iso8601: 2001-12-14t21:59:43.10-05:00
spaced: 2001-12-14 21:59:43.10 -5
date: 2002-12-14
```

Explicit typing is denoted with a tag using the exclamation point (“!”)
symbol. Global tags are URIs and may be specified in a tag shorthand notation
using a handle. Application-specific local tags may also be used.

- Example 2.23. Various Explicit Tags

```yaml
---
not-date: !!str 2002-04-28

picture: !!binary |
 R0lGODlhDAAMAIQAAP//9/X
 17unp5WZmZgAAAOfn515eXv
 Pz7Y6OjuDg4J+fn5OTk6enp
 56enmleECcgggoBADs=
application specific tag: !something |
 The semantics of the tag
 above may be different for
 different documents.
```

- Example 2.24. Global Tags

```yaml
%TAG ! tag:clarkevans.com,2002:
--- !shape
  # Use the ! handle for presenting
  # tag:clarkevans.com,2002:circle
- !circle
  center: &ORIGIN {x: 73, y: 129}
  radius: 7
- !line
  start: *ORIGIN
  finish: { x: 89, y: 102 }
- !label
  start: *ORIGIN
  color: 0xFFEEBB
  text: Pretty vector drawing.
```

- Example 2.25. Unordered Sets

```yaml
# Sets are represented as a
# Mapping where each key is
# associated with a null value
--- !!set
? Mark McGwire
? Sammy Sosa
? Ken Griff
```

- Example 2.26. Ordered Mappings

```yaml
# Ordered maps are represented as
# A sequence of mappings, with
# each mapping having one key
--- !!omap
- Mark McGwire: 65
- Sammy Sosa: 63
- Ken Griffy: 58
```

### Full Length Example

Below are two full-length examples of YAML. On the left is a sample invoice; on
the right is a sample log file.

- Example 2.27. Invoice

```yaml
--- !<tag:clarkevans.com,2002:invoice>
invoice: 34843
date   : 2001-01-23
bill-to: &id001
    given  : Chris
    family : Dumars
    address:
        lines: |
            458 Walkman Dr.
            Suite #292
        city   : Royal Oak
        state  : MI
        postal : 48046
ship-to: *id001
product:
    - sku         : BL394D
      quantity    : 4
      description : Basketball
      price       : 450.00
    - sku         : BL4438H
      quantity    : 1
      description : Super Hoop
      price       : 2392.00
tax : 251.42
total: 4443.52
comments:
    Late afternoon is best.
    Backup contact is Nancy
    Billsmer @ 338-4338.
```

- Example 2.28. Log File

```yaml
---
Time: 2001-11-23 15:01:42 -5
User: ed
Warning:
  This is an error message
  for the log file
---
Time: 2001-11-23 15:02:31 -5
User: ed
Warning:
  A slightly different error
  message.
---
Date: 2001-11-23 15:03:17 -5
User: ed
Fatal:
  Unknown variable "bar"
Stack:
  - file: TopClass.py
    line: 23
    code: |
      x = MoreObject("345\n")
  - file: MoreClass.py
    line: 58
    code: |-
      foo = bar
```

## Chapter 3. Processing YAML Information

YAML is both a text format and a method for presenting any native data structure
in this format. Therefore, this specification defines two concepts: a class of
data objects called YAML representations, and a syntax for presenting YAML
representations as a series of characters, called a YAML stream. A YAML
processor is a tool for converting information between these complementary
views. It is assumed that a YAML processor does its work on behalf of another
module, called an application. This chapter describes the information structures
a YAML processor must provide to or obtain from the application.

YAML information is used in two ways: for machine processing, and for human
consumption. The challenge of reconciling these two perspectives is best done in
three distinct translation stages: representation, serialization, and
presentation. Representation addresses how YAML views native data structures to
achieve portability between programming environments. Serialization concerns
itself with turning a YAML representation into a serial form, that is, a form
with sequential access constraints. Presentation deals with the formatting of a
YAML serialization as a series of characters in a human-friendly manner.

### Processes

Translating between native data structures and a character stream is done in
several logically distinct stages, each with a well defined input and output
data model, as shown in the following diagram:

- Figure 3.1. Processing Overview

![Processing Overview](file://overview2.png)

A YAML processor need not expose the serialization or representation stages. It
may translate directly between native data structures and a character stream
(dump and load in the diagram above). However, such a direct translation should
take place so that the native data structures are constructed only from
information available in the representation. In particular, mapping key order,
comments, and tag handles should not be referenced during composition.

#### Dump

Dumping native data structures to a character stream is done using the following
three stages:

- Representing Native Data Structures

YAML represents any native data structure using three node kinds: sequence - an
ordered series of entries; mapping - an unordered association of unique keys to
values; and scalar - any datum with opaque structure presentable as a series of
Unicode characters. Combined, these primitives generate directed graph
structures. These primitives were chosen because they are both powerful and
familiar: the sequence corresponds to a Perl array and a Python list, the
mapping corresponds to a Perl hash table and a Python dictionary. The scalar
represents strings, integers, dates, and other atomic data types.

Each YAML node requires, in addition to its kind and content, a tag specifying
its data type. Type specifiers are either global URIs, or are local in scope to
a single application. For example, an integer is represented in YAML with a
scalar plus the global tag “tag:yaml.org,2002:int”. Similarly, an invoice
object, particular to a given organization, could be represented as a mapping
together with the local tag “!invoice”. This simple model can represent any
data structure independent of programming language.

- Serializing the Representation Graph

For sequential access mediums, such as an event callback API, a YAML
representation must be serialized to an ordered tree. Since in a YAML
representation, mapping keys are unordered and nodes may be referenced more than
once (have more than one incoming “arrow”), the serialization process is
required to impose an ordering on the mapping keys and to replace the second and
subsequent references to a given node with place holders called aliases. YAML
does not specify how these serialization details are chosen. It is up to the
YAML processor to come up with human-friendly key order and anchor names,
possibly with the help of the application. The result of this process, a YAML
serialization tree, can then be traversed to produce a series of event calls for
one-pass processing of YAML data.

- Presenting the Serialization Tree

The final output process is presenting the YAML serializations as a character
stream in a human-friendly manner. To maximize human readability, YAML offers a
rich set of stylistic options which go far beyond the minimal functional needs
of simple data storage. Therefore the YAML processor is required to introduce
various presentation details when creating the stream, such as the choice of
node styles, how to format scalar content, the amount of indentation, which tag
handles to use, the node tags to leave unspecified, the set of directives to
provide and possibly even what comments to add. While some of this can be done
with the help of the application, in general this process should be guided by
the preferences of the user.

#### Load

Loading native data structures from a character stream is done using the
following three stages:

- Parsing the Presentation Stream

Parsing is the inverse process of presentation, it takes a stream of characters
and produces a series of events. Parsing discards all the details introduced in
the presentation process, reporting only the serialization events. Parsing can
fail due to ill-formed input.

- Composing the Representation Graph

Composing takes a series of serialization events and produces a representation
graph. Composing discards all the details introduced in the serialization
process, producing only the representation graph. Composing can fail due to any
of several reasons, detailed below.

- Constructing Native Data Structures

The final input process is constructing native data structures from the YAML
representation. Construction must be based only on the information available in
the representation, and not on additional serialization or presentation details
such as comments, directives, mapping key order, node styles, scalar content
format, indentation levels etc. Construction can fail due to the unavailability
of the required native data types.

### Information Models

This section specifies the formal details of the results of the above processes.
To maximize data portability between programming languages and implementations,
users of YAML should be mindful of the distinction between serialization or
presentation properties and those which are part of the YAML representation.
Thus, while imposing a order on mapping keys is necessary for flattening YAML
representations to a sequential access medium, this serialization detail must
not be used to convey application level information. In a similar manner, while
indentation technique and a choice of a node style are needed for the human
readability, these presentation details are neither part of the YAML
serialization nor the YAML representation. By carefully separating properties
needed for serialization and presentation, YAML representations of application
information will be consistent and portable between various programming
environments.

The following diagram summarizes the three information models. Full arrows
denote composition, hollow arrows denote inheritance, “1” and “*” denote
“one” and “many” relationships. A single “+” denotes serialization
details, a double “++” denotes presentation details.

- Figure 3.2. Information Models

![Information Models](model2.png)

#### Representation Graph

YAML’s representation of native data structure is a rooted, connected, directed
graph of tagged nodes. By “directed graph” we mean a set of nodes and directed
edges (“arrows”), where each edge connects one node to another (see a formal
definition). All the nodes must be reachable from the root node via such edges.
Note that the YAML graph may include cycles, and a node may have more than one
incoming edge.

Nodes that are defined in terms of other nodes are collections; nodes that are
independent of any other nodes are scalars. YAML supports two kinds of
collection nodes: sequences and mappings. Mapping nodes are somewhat tricky
because their keys are unordered and must be unique.

- Figure 3.3. Representation Model

![Representation Model](represent2.png)

##### Nodes

A YAML node represents a single native data structure. Such nodes have content
of one of three kinds: scalar, sequence, or mapping. In addition, each node has
a tag which serves to restrict the set of possible values the content can have.

- Scalar

The content of a scalar node is an opaque datum that can be presented as a
series of zero or more Unicode characters.

- Sequence

The content of a sequence node is an ordered series of zero or more nodes. In
particular, a sequence may contain the same node more than once. It could even
contain itself (directly or indirectly).

- Mapping

The content of a mapping node is an unordered set of key: value node pairs, with
the restriction that each of the keys is unique. YAML places no further
restrictions on the nodes. In particular, keys may be arbitrary nodes, the same
node may be used as the value of several key: value pairs, and a mapping could
even contain itself as a key or a value (directly or indirectly).

When appropriate, it is convenient to consider sequences and mappings together,
as collections. In this view, sequences are treated as mappings with integer
keys starting at zero. Having a unified collections view for sequences and
mappings is helpful both for theoretical analysis and for creating practical
YAML tools and APIs. This strategy is also used by the Javascript programming
language.

##### Tags

YAML represents type information of native data structures with a simple
identifier, called a tag. Global tags are URIs and hence globally unique across
all applications. The “tag:” URI scheme is recommended for all global YAML
tags. In contrast, local tags are specific to a single application. Local tags
start with “!”, are not URIs and are not expected to be globally unique. YAML
provides a “TAG” directive to make tag notation less verbose; it also offers
easy migration from local to global tags. To ensure this, local tags are
restricted to the URI character set and use URI character escaping.

YAML does not mandate any special relationship between different tags that begin
with the same substring. Tags ending with URI fragments (containing “#”) are
no exception; tags that share the same base URI but differ in their fragment
part are considered to be different, independent tags. By convention, fragments
are used to identify different “variants” of a tag, while “/” is used to
define nested tag “namespace” hierarchies. However, this is merely a
convention, and each tag may employ its own rules. For example, Perl tags may
use “::” to express namespace hierarchies, Java tags may use “.”, etc.

YAML tags are used to associate meta information with each node. In particular,
each tag must specify the expected node kind (scalar, sequence, or mapping).
Scalar tags must also provide a mechanism for converting formatted content to a
canonical form for supporting equality testing. Furthermore, a tag may provide
additional information such as the set of allowed content values for validation,
a mechanism for tag resolution, or any other data that is applicable to all of
the tag’s nodes.

##### Node Comparison

Since YAML mappings require key uniqueness, representations must include a
mechanism for testing the equality of nodes. This is non-trivial since YAML
allows various ways to format scalar content. For example, the integer eleven
can be written as “0o13” (octal) or “0xB” (hexadecimal). If both notations
are used as keys in the same mapping, only a YAML processor which recognizes
integer formats would correctly flag the duplicate key as an error.

- Canonical Form

YAML supports the need for scalar equality by requiring that every scalar tag
must specify a mechanism for producing the canonical form of any formatted
content. This form is a Unicode character string which also presents the same
content, and can be used for equality testing. While this requirement is
stronger than a well defined equality operator, it has other uses, such as the
production of digital signatures.

- Equality

Two nodes must have the same tag and content to be equal. Since each tag applies
to exactly one kind, this implies that the two nodes must have the same kind to
be equal. Two scalars are equal only when their tags and canonical forms are
equal character-by-character. Equality of collections is defined recursively.
Two sequences are equal only when they have the same tag and length, and each
node in one sequence is equal to the corresponding node in the other sequence.
Two mappings are equal only when they have the same tag and an equal set of
keys, and each key in this set is associated with equal values in both mappings.

Different URI schemes may define different rules for testing the equality of
URIs. Since a YAML processor cannot be reasonably expected to be aware of them
all, it must resort to a simple character-by-character comparison of tags to
ensure consistency. This also happens to be the comparison method defined by the
“tag:” URI scheme. Tags in a YAML stream must therefore be presented in a
canonical way so that such comparison would yield the correct results.

- Identity

Two nodes are identical only when they represent the same native data structure.
Typically, this corresponds to a single memory address. Identity should not be
confused with equality; two equal nodes need not have the same identity. A YAML
processor may treat equal scalars as if they were identical. In contrast, the
separate identity of two distinct but equal collections must be preserved.

#### Serialization Tree

To express a YAML representation using a serial API, it is necessary to impose
an order on mapping keys and employ alias nodes to indicate a subsequent
occurrence of a previously encountered node. The result of this process is a
serialization tree, where each node has an ordered set of children. This tree
can be traversed for a serial event-based API. Construction of native data
structures from the serial interface should not use key order or anchor names
for the preservation of application data.

- Figure 3.4. Serialization Model

![Serialization Model](serialize2.png)

##### Keys Order

In the representation model, mapping keys do not have an order. To serialize a
mapping, it is necessary to impose an ordering on its keys. This order is a
serialization detail and should not be used when composing the representation
graph (and hence for the preservation of application data). In every case where
node order is significant, a sequence must be used. For example, an ordered
mapping can be represented as a sequence of mappings, where each mapping is a
single key: value pair. YAML provides convenient compact notation for this case.

##### Anchors and Aliases

In the representation graph, a node may appear in more than one collection. When
serializing such data, the first occurrence of the node is identified by an
anchor. Each subsequent occurrence is serialized as an alias node which refers
back to this anchor. Otherwise, anchor names are a serialization detail and are
discarded once composing is completed. When composing a representation graph
from serialized events, an alias node refers to the most recent node in the
serialization having the specified anchor. Therefore, anchors need not be unique
within a serialization. In addition, an anchor need not have an alias node
referring to it. It is therefore possible to provide an anchor for all nodes in
serialization.

#### Presentation Stream

A YAML presentation is a stream of Unicode characters making use of of styles,
scalar content formats, comments, directives and other presentation details to
present a YAML serialization in a human readable way. Although a YAML processor
may provide these details when parsing, they should not be reflected in the
resulting serialization. YAML allows several serialization trees to be contained
in the same YAML character stream, as a series of documents separated by
markers. Documents appearing in the same stream are independent; that is, a node
must not appear in more than one serialization tree or representation graph.

- Figure 3.5. Presentation Model

![Presentation Model](present2.png)

##### Node Styles

Each node is presented in some style, depending on its kind. The node style is a
presentation detail and is not reflected in the serialization tree or
representation graph. There are two groups of styles. Block styles use
indentation to denote structure; In contrast, flow styles styles rely on
explicit indicators.

YAML provides a rich set of scalar styles. Block scalar styles include the
literal style and the folded style. Flow scalar styles include the plain style
and two quoted styles, the single-quoted style and the double-quoted style.
These styles offer a range of trade-offs between expressive power and
readability.

Normally, block sequences and mappings begin on the next line. In some cases,
YAML also allows nested block collections to start in-line for a more compact
notation. In addition, YAML provides a compact notation for flow mappings with a
single key: value pair, nested inside a flow sequence. These allow for a natural
“ordered mapping” notation.

- Figure 3.6. Kind/Style Combinations

![Kind/Style Combinations](styles2.png)

##### Scalar Formats

YAML allows scalars to be presented in several formats. For example, the integer
“11” might also be written as “0xB”. Tags must specify a mechanism for
converting the formatted content to a canonical form for use in equality
testing. Like node style, the format is a presentation detail and is not
reflected in the serialization tree and representation graph.

##### Comments

Comments are a presentation detail and must not have any effect on the
serialization tree or representation graph. In particular, comments are not
associated with a particular node. The usual purpose of a comment is to
communicate between the human maintainers of a file. A typical example is
comments in a configuration file. Comments must not appear inside scalars, but
may be interleaved with such scalars inside collections.

##### Directives

Each document may be associated with a set of directives. A directive has a name
and an optional sequence of parameters. Directives are instructions to the YAML
processor, and like all other presentation details are not reflected in the YAML
serialization tree or representation graph. This version of YAML defines a two
directives, “YAML” and “TAG”. All other directives are reserved for future
versions of YAML.

### Loading Failure Points

The process of loading native data structures from a YAML stream has several
potential failure points. The character stream may be ill-formed, aliases may be
unidentified, unspecified tags may be unresolvable, tags may be unrecognized,
the content may be invalid, and a native type may be unavailable. Each of these
failures results with an incomplete loading.

A partial representation need not resolve the tag of each node, and the
canonical form of formatted scalar content need not be available. This weaker
representation is useful for cases of incomplete knowledge of the types used in
the document. In contrast, a complete representation specifies the tag of each
node, and provides the canonical form of formatted scalar content, allowing for
equality testing. A complete representation is required in order to construct
native data structures.

- Figure 3.7. Loading Failure Points

![Loading Failure Points](validity2.png)

#### Well-Formed Streams and Identified Aliases

A well-formed character stream must match the BNF productions specified in the
following chapters. Successful loading also requires that each alias shall refer
to a previous node identified by the anchor. A YAML processor should reject
ill-formed streams and unidentified aliases. A YAML processor may recover from
syntax errors, possibly by ignoring certain parts of the input, but it must
provide a mechanism for reporting such errors.

#### Resolved Tags

Typically, most tags are not explicitly specified in the character stream.
During parsing, nodes lacking an explicit tag are given a non-specific tag:
“!” for non-plain scalars, and “?” for all other nodes. Composing a complete
representation requires each such non-specific tag to be resolved to a specific
tag, be it a global tag or a local tag.

Resolving the tag of a node must only depend on the following three parameters:
(1) the non-specific tag of the node, (2) the path leading from the root to the
node, and (3) the content (and hence the kind) of the node. When a node has more
than one occurrence (using aliases), tag resolution must depend only on the path
to the first (anchored) occurrence of the node.

Note that resolution must not consider presentation details such as comments,
indentation and node style. Also, resolution must not consider the content of
any other node, except for the content of the key nodes directly along the path
leading from the root to the resolved node. Finally, resolution must not
consider the content of a sibling node in a collection, or the content of the
value node associated with a key node being resolved.

These rules ensure that tag resolution can be performed as soon as a node is
first encountered in the stream, typically before its content is parsed. Also,
tag resolution only requires referring to a relatively small number of
previously parsed nodes. Thus, in most cases, tag resolution in one-pass
processors is both possible and practical.

YAML processors should resolve nodes having the “!” non-specific tag as
“tag:yaml.org,2002:seq”, “tag:yaml.org,2002:map” or
“tag:yaml.org,2002:str” depending on their kind. This tag resolution
convention allows the author of a YAML character stream to effectively
“disable” the tag resolution process. By explicitly specifying a “!”
non-specific tag property, the node would then be resolved to a “vanilla”
sequence, mapping, or string, according to its kind.

Application specific tag resolution rules should be restricted to resolving the
“?” non-specific tag, most commonly to resolving plain scalars. These may be
matched against a set of regular expressions to provide automatic resolution of
integers, floats, timestamps, and similar types. An application may also match
the content of mapping nodes against sets of expected keys to automatically
resolve points, complex numbers, and similar types. Resolved sequence node types
such as the “ordered mapping” are also possible.

That said, tag resolution is specific to the application. YAML processors should
therefore provide a mechanism allowing the application to override and expand
these default tag resolution rules.

If a document contains unresolved tags, the YAML processor is unable to compose
a complete representation graph. In such a case, the YAML processor may compose
a partial representation, based on each node’s kind and allowing for
non-specific tags.

#### Recognized and Valid Tags

To be valid, a node must have a tag which is recognized by the YAML processor
and its content must satisfy the constraints imposed by this tag. If a document
contains a scalar node with an unrecognized tag or invalid content, only a
partial representation may be composed. In contrast, a YAML processor can always
compose a complete representation for an unrecognized or an invalid collection,
since collection equality does not depend upon knowledge of the collection’s
data type. However, such a complete representation cannot be used to construct a
native data structure.

#### Available Tags

In a given processing environment, there need not be an available native type
corresponding to a given tag. If a node’s tag is unavailable, a YAML processor
will not be able to construct a native data structure for it. In this case, a
complete representation may still be composed, and an application may wish to
use this representation directly.

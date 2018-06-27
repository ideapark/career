# YAML Ain't Markup Language (YAML) Version 1.2

## Abstract

YAML (rhymes with "camel") is a human-friendly, cross language, Unicode based
data serialization language designed around the common native data types of
agile programming languages. It is broadly useful for programming needs ranging
from configuration files to Internet messaging to object persistence to data
auditing. Together with the Unicode standard for characters, this specification
provides all the information necessary to understand YAML Version 1.2 and to
create programs that process YAML information.

## Chapter1. Introduction

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

## Chapter2. Preview

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

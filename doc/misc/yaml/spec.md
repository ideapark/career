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

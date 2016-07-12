# Pipes

Counting the number of files in the current directory:

        ls | wc -l

The ls command lists all files in the current directory, one per line,
and wc -l counts the number of lines.

Counting the number of files that do not contain "foo" in their name:

        ls | grep -v foo | wc -l

Here, the list of files is filtered by grep to remove all lines that
contain "foo". The rest equals the previous example.

Finding the five largest entries in the current directory:

        du -s * | sort -nr | sed 5q

du -s * returns the recursively summed sizes of all files in the current
directory - no matter if they are regular files or directories. sort -nr
sorts the list numerically in reverse order (descending). Finally, sed 5q
quits after it has printed the fifth line.

The presented command lines are examples of what Unix people would use
to get the desired output. There are other ways to get the same output;
it is the user's decision which way to go.

The examples show that many tasks on a Unix system are accomplished by
combining several small programs. The connection between the programs is
denoted by the pipe operator '|'.

Pipes, and their extensive and easy use, are one of the great achievements
of the Unix system. Pipes were possible in earlier operating systems, but
never before have they been such a central part of the concept. In the
early seventies when Doug McIlroy introduced pipes into the Unix system,
"it was this concept and notation for linking several programs together
that transformed Unix from a basic file-sharing system to an entirely new
way of computing."


# Interface Design

Unix is, first of all, simple - everything is a file. Files are sequences
of bytes, without any special structure. Programs should be filters, which
read a stream of bytes from standard input (stdin) and write a stream of
bytes to standard output (stdout). If the files are sequences of bytes, and
the programs are filters on byte streams, then there is exactly one data
interface. Hence it is possible to combine programs in any desired way.
Even a handful of small programs yields a large set of combinations, and
thus a large set of different functions. This is leverage! If the programs
are orthogonal to each other - the best case - then the set of different
functions is greatest. Programs can also have a separate control interface
in addition to their data interface. The control interface is often called
the "user interface", because it is usually designed to be used by humans.
The Unix Philosophy discourages the assumption that the user will be human.
Interactive use of software is slow use of software, because the program
waits for user input most of the time. Interactive software also requires
the user to be in front of the computer, occupying his attention during
usage. Now, back to the idea of combining several small programs to perform
a more specific function: If these single tools were all interactive, how
would the user control them? It is not only a problem to control several
programs at once if they run at the same time; it is also very inefficient
to have to control each program when they are intended to act in concert.
Hence, the Unix Philosophy discourages designing programs which demand
interactive use. The behavior of programs should be defined at invocation.
This is done by specifying arguments to the program call (command line
switches). Non-interactive use is also an advantage for testing during
development. Testing interactive programs is much more complicated than
testing non-interactive counterparts.

# The Toolchest approach

Toolchest is a set of tools. Instead of one big tool for all tasks, there
are many small tools, each for one task. Difficult tasks are solved by
combining several small, simple tools. The Unix toolchest is a set of small,
(mostly) non-interactive programs that are filters on byte streams. They
are, to a large extent, unrelated in their function. Hence, the Unix
toolchest provides a large set of functions that can be accessed by
combining the programs in the desired way. The act of software development
benefits from small toolchest programs, too. Writing small programs is
generally easier and less error-prone than writing large programs. Hence,
writing a large set of small programs is still easier and less error-prone
than writing one large program with all the functionality included. If the
small programs are combinable, then they offer even an even larger set of
functions than the single monolithic program. Hence, one gets two
advantages out of writing small, combinable programs: They are easier to
write and they offer a greater set of functions through combination.

There are also two main drawbacks of the toolchest approach. First, one
simple, standardized interface has to be sufficient. If one feels the need
for more "logic" than a stream of bytes, then a different approach might
be required. Also, a design where a stream of bytes is sufficient, might
not be conceivable. By becoming more familiar with the "Unix style of
thinking", developers will more often and easier find simple designs
where a stream of bytes is a sufficient interface. The second drawback of
the toolchest approach concerns the users. A toolchest is often more
difficult to use because it is necessary to become familiar with each tool
and be able to choose and use the right one in any given situation.
Additionally, one needs to know how to combine the tools in a sensible way.
The issue is similar to having a sharp knife - it is a powerful tool in the
hand of a master, but of no value in the hand of an unskilled person.
However, learning single, small tools of a toolchest is often easier than
learning a complex tool. The user will already have a basic understanding
of an as yet unknown tool if the tools of a toolchest have a common,
consistent style. He will be able to transfer knowledge of one tool to
another. This second drawback can be removed to a large extent by adding
wrappers around the basic tools. Novice users do not need to learn several
tools if a professional wraps complete command lines into a higher-level
script. Note that the wrapper script still calls the small tools; it is
just like a skin around them. No complexity is added this way, but new
programs can be created out of existing one with very little effort. A
wrapper script for finding the five largest entries in the current
directory might look like this:

        #!/bin/sh

        du -s * | sort -nr | sed 5q

The script itself is just a text file that calls the commands that a
professional user would type in directly. It is probably beneficial to make
the program flexible in regard to the number of entries it prints:

        #!/bin/sh

        num=5
        [ $# -eq 1 ] && num="$1"
        du -sh * | sort -nr | sed "${num}q"

This script acts like the one before when called without an argument, but
the user can also specify a numerical argument to define the number of
lines to print. One can surely imagine even more flexible versions; however,
they will still rely on the external programs which actually do the work.

# A Powerfull Shell

The Unix shell provides the ability to combine small programs into large
ones. But a powerful shell is a great feature in other ways, too; for
instance, by being scriptable. Control statements are built into the shell
and the functions are the normal programs of the system. As the programs
are already known, learning to program in the shell becomes easy. Using
normal programs as functions in the shell programming language is only
possible because they are small and combinable tools in a toolchest style.
The Unix shell encourages writing small scripts, by combining existing
programs because it is so easy to do. This is a great step towards
automation. It is wonderful if the effort to automate a task equals the
effort to do the task a second time by hand. If this holds, then the user
will be happy to automate everything he does more than once.

Small programs that do one job well, standardized interfaces between them,
a mechanism to combine parts to larger parts, and an easy way to automate
tasks will inevitably produce software leverage, achieving multiple times
the benefit of the initial investment. The shell also encourages rapid
prototyping. Many well known programs started as quickly hacked shell
scripts, and turned into "real" programs later written in C. Building a
prototype first is a way to avoid the biggest problems in application
development. Fred Brooks explains in "No Silver Bullet". The hardest
single part of building a software system is deciding precisely what to
build. No other part of the conceptual work is so difficult as
establishing the detailed technical requirements. No other part of the
work so cripples the resulting system if done wrong. No other part is more
difficult to rectify later. Writing a prototype is a great method for
becoming familiar with the requirements and to run into real problems
early. Prototyping is often seen as a first step in building software.
This is, of course, good. However, the Unix Philosophy has an additional
perspective on prototyping: After having built the prototype, one might
notice that the prototype is already good enough. Hence, no
reimplementation in a more sophisticated programming language might be of
need, at least for the moment. Maybe later, it might be necessary to
rewrite the software, but not now. By delaying further work, one keeps
the flexibility to react on changing requirements. Software parts that
are not written will not miss the requirements. Well known is Gordon
Bell's classic saying: "The cheapest, fastest, and most reliable
components are those that aren't there."

# Worse Is Better

The Unix Philosophy aims for the 90% solution; others call it the "Worse is better"
approach. Experience from real life projects shows:

(1) It is almost impossible to define the requirements completely and correctly the
first time. Hence one should not try to; one will fail anyway.

(2) Requirements change during time. Hence it is best to delay requirement-based
design decisions as long as possible. Software should be small and flexible as
long as possible in order to react to changing requirements. Shell scripts, for
example, are more easily adjusted than C programs.

(3) Maintenance work is hard work. Hence, one should keep the amount of code as
small as possible; it should only fulfill the current requirements. Software parts
that will be written in the future do not need maintenance until that time.

Starting with a prototype in a scripting language has several advantages:

o As the initial effort is low, one will likely start right away.
o Real requirements can be identified quickly since working parts are available sooner.
o When software is usable and valuable, it gets used, and thus tested. This ensures
that problems will be found in the early stages of development.
o The prototype might be enough for the moment; thus, further work can be delayed
until a time when one knows about the requirements and problems more thoroughly.
o Implementing only the parts that are actually needed at the moment introduces less
programming and maintenance work.
o If the situation changes such that the software is not needed anymore, then less
effort was spent on the project than it would have been if a different approach had
been taken.

# Upgrowth and Survival of Software

Although "writing" and "building" are just verbs, they do imply a specific
view on the work process they describe. A better verb would be to "grow".
Creating software in the sense of the Unix Philosophy is an incremental process.
It starts with an initial prototype, which evolves as requirements change. A
quickly hacked shell script might become a large, sophisticated, compiled program
this way. Its lifetime begins with the initial prototype and ends when the
software is not used anymore. While alive, it will be extended, rearranged,
rebuilt. Growing software matches the view that "software is never finished.
It is only released.

Software can be seen as being controlled by evolutionary processes. Successful
software is software that is used by many for a long time. This implies that the
software is necessary, useful, and better than the alternatives. Darwin describes
"the survival of the fittest." Inrelation to software, the most successful
software is the fittest; the one that survives. (This may be at the level of one
creature, or at the level of one species.) The fitness of software is affected
mainly by four properties: portability of code, portability of data, range of
usability, and reusability of parts.

(1) "Portability of code" means using high-level programming languages,
sticking to the standard, and avoiding optimizations that introduce
dependencies on specific hardware. Hardware has a much shorter lifespan
than software. By chaining software to specific hardware, its lifetime
is limited to that of this hardware. In contrast, software should be easy
to port - adaptation is the key to success.

(2) "Portability of data" is best achieved by avoiding binary representations
to store data, since binary representations differ from machine to machine.
Textual representation is favored. Historically, ASCII was the character
set of choice; for the future, UTF-8 might be the better way forward.
Important is that it is a plain text representation in a very common
character set encoding. Apart from being able to transfer data between
machines, readable data has the great advantage that humans are able to
directly read and edit it with text editors and other tools from the Unix
toolchest.

(3) A large "range of usability" ensures good adaptation, and thus good
survival. It is a special distinction when software becomes used in fields
of endeavor, the original authors never imagined. Software that solves
problems in a general way will likely be used for many kinds of similar
problems. Being too specific limits the range of usability. Requirements change
through time, thus use cases change or even vanish. As a good example of
this point, All man identifies flexibility to be one major reason for
sendmail's success. Second, I limited myself to the routing function.
This was a departure from the dominant thought of the time. Third, the
sendmail configuration file was flexible enough to adapt to a rapidly
changing world. Successful software adapts itself to the changing world.

(4) "Reusability of parts" goes one step further. Software may become obsolete
and completely lose its field of action, but the constituent parts of the
software may be general and independent enough to survive this death. If
software is built by combining small independent programs, then these parts
are readily available for reuse. Who cares that the large program is a failure,
if parts of it become successful instead?

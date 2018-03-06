# Unix Tools Hints

## Consume input from stdin, product output to stdout

Put another way, your program should be a filter. Filters are easily integrated
into shell pipelines, arguably the most import utility for Unix tools
composition.


## Output should be free from headers or other decoration

Superflous output will frustrate users who are trying to parse tool output.
Headers and decoration tend to be less regular and more idiosyncratic than the
structured data you're really trying to get at. Don't do it.


## Output should be simple to parse and compose

This usually means representing each record as a single, plain-text formatted
line of output whose columns are separated by whitespace. (No JSON, please.)
Most venerable Unix tools -- grep, sort and sed among them -- assume this.


## Treat a tool's output as an API

Your tool will be used in contexts beyond your own imagination. If a tool's
output format is changed, other tools that compose or otherwise build on its
output will invariably break -- you have broken the API contract.


## Place diagnositics output on stderr

Diagnostics output includes anything that is not the primary data output of your
tool. Among these are: progress indicators, debugging output, log messages,
error messages, and usage information. When diagnostics output is intermingled
with data, it is very difficult to parse, and thus compose, the tool's output.
What's more, stderr makes diagnositics redirected, stderr keeps printing to the
user's terminal -- the ultimate target of diagnositics output.


## Signal failure with an exit status

If your tool fails, exit with a status other than 0. This allows for simple
integration shells, and also error handling in scripts. Consider the difference
between two tools that build binaries. We'd like to build upon this tool to
execute the built binary only if the build succeeds. Badbuild prints the word
'FAILED' as the last line when it fails.


## Make a tool's output portable

Put another way, a tool's output should stand on its own, requiring as little
context as possible to parse and interpret. For example, you should use absolute
paths to represent files, and bully qualified hostnames to name internet hosts.
Portable output is directly usable by other tools without further context. A
frequent violator of this is build tools. For example, both the GCC and Clang
compilers try to be clever by reporting paths that are relative to your working
directory.


## Omit needless diagnostics

Resist the temptation to inform the user of everything that is being done. (But
if you must, do it on stderr.) A good tool is quiet when all is well, but
produces use full diagnostics output when things go wrong. Excessive diagnostics
conditons users to ignore all diagnostics; useful diagnostics output does not
require the user to grub around in endless log files to discern what went wrong,
and where. There's nothing wrong with having a verbose mode (Typically enabled
by a '-v' flag) in order to aid development and debugging, but do not make this
the default.


## Avoid making interactive programs

Tools should be usable without user interaction beyond what's provided by the
user's shell. Unix programs are expected to run without user input: it allows
programs to be run in non-interactively by cron, or to be easily distributed for
excecution by a remote machine. Even a single interaction forfeits this very
useful capability. Interactivity also makes composition more difficult. Since
Unix's program composition model does not distinguish the output of the various
program involved, it isn't always clear which program a user is even interacting
with. A common use of interactive programs is to ask the user to confirm some
dangerous action. This is easily avoided by asking the user intead to supply a
flag on the command line to the appropriate tool.

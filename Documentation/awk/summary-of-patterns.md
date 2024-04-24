# Summary of Patterns

## BEGIN { statements }

The statements are executed once before any input has been read.

## END { statements }

The statements are executed once after all input has been read.

## expreession { statements }

The statements are executed at each input line where the expression is
true, that is, nonzero or nonnull.

## /regular expression/ { statements }

The statements are executed at each input line that contains a string
matched by the regular expression.

## compound pattern { statements }

A compound pattern combines expressions with && (AND), || (OR), !
(NOT), and parentheses; the statements are executed at each input line
where the compound pattern is true.

## pattern_1, pattern_2 { statements }

A range pattern matches each input line from a line matched by
pattern_1 to the next line matched by pattern_2, inclusive; the
statements are executed at each matching line.

BEGIN and END do not combine with other patterns. A range pattern
cannot be part of any other pattern. BEGIN and END are the only
patterns that require an action.

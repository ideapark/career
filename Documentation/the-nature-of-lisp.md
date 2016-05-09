The Nature of Lisp
==================

[Original copy](http://www.defmacro.org/ramblings/lisp.html)


Introduction
------------

When I first stumbled into lisp advocacy on various corners of the web
I was already an experienced programmer.  At that point I  had grokked
what seemed at the time a wide range of programming languages.  I  was
proud to have the usual suspects (C++, Java, C#, etc.) on  my  service
record and was under impression that I know everything there is to know
about programming languages. I couldn't have  possibly been more wrong.

My initial attempt to learn Lisp came to a crashing halt as soon as I
saw some sample  code. I suppose the same thought ran through my mind
that  ran  through thousands of other minds who were ever in my shoes:
"Why on Earth would  anyone want to use a language with such horrific
syntax?!" I couldn't be bothered  to learn a language if its creators
couldn't be bothered  to give it a  pleasant syntax. After all, I was
almost blinded by the infamous Lisp parentheses!

The moment I regained my sight I communicated my frustrations to some
members of the  Lisp sect.  Almost  immediately  I was bombarded by a
standard set of  responses: Lisp's parentheses are only a superficial
matter,  Lisp has a huge benefit of code and data being  expressed in
the same manner (which,  obviously, is  a huge improvement over XML),
Lisp has tremendously powerful  metaprogramming facilities  that allow
programs to write code and modify themselves, Lisp allows for creation
of mini-languages specific to  the  problem  at  hand,  Lisp blurs the
distinction between  run  time  and  compile time, Lisp, Lisp, Lisp...
The list was very  impressive.  Needless to say none of it made sense.
Nobody could illustrate the usefulness of these features with specific
examples because these techniques are supposedly only userful in large
software  systems.  After  many  hours  of debating that conventional
programming languages do the job just fine. I gave up. I wasn't about
to invest months into  learning a language  with a terrible syntax in
order to  understand obscure features that had no useful examples. My
time was not yet come.

For many months  the Lisp advocates pressed on. I  was  baffled. Many
extremely  intelligent  people  I  knew and had much respect for ware
praising  Lisp  with  almost  religious  dedication.  There had to be
something there, something  I couldn't afford not to get my hands on!
Eventually my thrist for knowledge won me over.  I  took  the plunge,
bit the bullet, got my hands dirty, and began months of mind bending
exercises. It was a journey on  an  endless  lake  of frustration. I
turned my mind inside out, rinsed it, and  put  it back  in place. I
went through seven rings of hell  and  came  back. And them I got it.

The elightenment came instantaneously. One moment I understood nothing,
and the next memont  everything  clicked  into  place. I've achieved
nirvana. Dozens of times  I heard  Eric Raymond's statment quoted by
different  people: "Lisp  is   worth   learning   for  the  profound
enlightenment experience you will have when you finally get it; that
experience will make you a  better  programmer for  the rest of your
days, even  if  you  never  actually use Lisp itself a lot." I never
understood  this  statment.  I  never believed it could be true. And
finally, after  all  the pain,  it  made sense! There was more truth
to it than I ever could have imagined. I've achieved an almost divine
state of mind, an instantaneous enlightenment experience that truend
my view of computer science on its head in less than a single second.

That very second I became a member of the Lisp cult. I felt something
a ninjitsu master must feel: I had to spread my newfound knowledge to
at least ten lost souls in the course of my lifttime. I took the usual
path. I was rehashing the same arguments that were given to me for
years (only now they actually made sense!), hoping to convert
unsuspecting bystanders. It didn't work. My persistence sparked a few
people's interest but their curiosity dwindled at the mere sight of
sample Lisp code. Perhaps years of advocacy would forge a few new
Lispers. but I wasn't satisfied. There had to be a better way.

I gave the matter careful thought. Is there something inherently hard
about Lisp that prevents very intelligent, experienced programmers
from understanding it? No, there isn't. After all, I got it, and if
I can do it, anybody can. Then what is it that makes Lisp so hard to
understand? The answer, as such things usually do, came unexpectedly.
Of course! Teaching anybody anything involves building advanced
concepts on top of concepts they already understand! If the process
is made interesting and the matter is aided their understanding. That
was the problem! Metaprogramming, code and data in one representation,
self-modifying programs, domain specific mini-languages, none of the
explanations for these concepts referenced familiar territory. How
could I expect anyone to understand them! No wonder people wanted
specific examples. I could as well have been speaking in Martian!

I shared my ideas with fellow Lispers. "Well, of course these
concepts aren't explained in terms of faniliar territory", they said:
"There are so different, they're unlike anyting these people have
learned before." This was a poor excuse. "I do not believe this to
be true", I said. The response was unanimous: "Why don't you give it
a try?" So I did. This article is a product of my efforts. It is my
attempt to explain Lisp in familiar, intuitive concepts. I urge
brave souls to read on. Grab your favorite drink. Take a deep breath.
Prepare to be blown away. Oh, and may the Force be with you.


XML Reloaded
------------

A thousand mile journey starts with a single step. A journey to
enlightenment is no exception and our first step just happens to be
XML. What more could possibly be said about XML that hasn't already
been said? It turns out, quite a bit. While there's nothing
particularly interesting about XML itself, its relationship to Lisp
is fascinating to regular programmers. So let's revive the dead horse,
take out the stick, and venture into XML wilderness that no one dared
venture into before us. It's time to see the all too familiar moon
from the other side.

Superficially XML is nothing more than a standardized syntax used to
express arbitrary hierarchical data in human readable form. To-do
lists, web pages, medical records, auto insurance claims,
configuration files are all examples of potential XML use. Let's use
a simple to-do list as an example (in a couple of sections you'll
see it in a whole new light):

```
<todo name="housework">
    <item priority="high">Clean the house.</item>
    <item priority="medium">Wash the dishes.</item>
    <item priority="medium"></item>
</todo>
```

What happens if we unleash our favorite XML parser on this to-do list?
Once the data is parsed, how is it represented in memory? The most
natural representation is, of course, a tree - a perfect data structure
for hierarchical in memory? The most natural representation is, of
course, a tree - a perfect data structure for hierarchical data. After
all is said and done, XML is really just a tree serialized to a human
readable form. Anything that can be represented in a tree can be
represented in XML and vice versa. I hope you understand this idea.
It's very important for what's coming next.

Let's make this a little further. What other type of data is often
represented as a tree? At this point the list is as good as infinite so
I'll give you a hint at what I'm getting at - try to remember your old
compiler course. If you have a vague recollection that source code is
stored in a tree after it's parsed, you're on the right track. Any
compiler inevitably parses the source code into an abstract syntax
tree. This isn't surprising since source code is hierarchical:
functions contain arguments and blocks of code. Blocks of code contain
expressions and statements. Expressions contain variables and
operators. And so it goes.

Let's apply our corollary that any tree can easily be serialized into
XML to this idea. If all source code is eventually represented as a
tree, and any tree can be serialized into XML, then all source code
can be converted to XML, right? Let's illustrate this interesting
property by a simple example. Consider the function below:

```
int add(int arg1, int arg2)
{
    return arg1 + arg2;
}
```

Can you convert this function definition to its XML equivalent? Turns
out, it's reasonably simple. Naturally there are many ways to do this.
Here is one way the resulting XML can look like:

```
<define-function return-type="int" name="add">
    <arguments>
        <argument type="int">arg1</argument>
        <argument type="int">arg2</argument>
    </arguments>
    <body>
        <return>
            <add value1="arg1" value2="arg2"/>
        </return>
    </body>
</define-function>
```

We can go through this relatively simple exercise with any language. We
can turn any source code into XML, and we can transform the resulting
XML back to original source code. We can write a converter that turns
Java into XML and a converter that turns XML back to Java. We could do
the same for C++. (In case you're wondering if anyone is crazy enough
to do it, take a look at GCC-XML). Furthermore, for languages that share
common features but use different syntax (which to some extent is true
about most mainstream languages) we could convert source code from one
language to another using XML as an intermediary representation. We
could use our Java2XML converter to convert a Java program to XML. We
could then run XML2CPP converter on the resulting XML and turn it into
C++ code. With any luck (if we avoid using features of Java that don't
exist in C++) we'll get a working C++ program. Neat, eh?

All this effectively means that we can use XML for generic storage of
source code. We'd be able to create a whole class of programming
languages that use uniform syntax, as well as write transformers that
convert existing source code to XML. If we were to actually adopt this
idea, compilers for different languages wouldn't need to implement
parsers for their specific grammars - they'd simply use an XML parser
to turn XML directly into an abstract syntax tree.

By now you're probably wondering why I've embarked on the XML crusade
and what is has to do with Lisp (after all, Lisp was created about
thirty years before XML). I promise that everyting will become clear
soon enough. But before we take our second step, let's go through a
small philosophical exercise. Take a good look at the XML version of
our "add" function above. How would you classify it? It is data or
code? If you think about it for a moment you'll realize that there
are good reasons to put this XML snippet into both categories. It's
XML and it's just information encoded in a standardized format. We've
already determined that it can be generated from a tree data structure
in memory (that's effectively what GCC-XML does). It's lying around
in a file with no apparent way to execute it. We can parse it into a
tree of XML nodes and do various transformations on it. It's data.
But wait a moment! When all is said and done it's the same "add"
function written with a different syntax, right? Once parsed, its tree
could be fed into a compiler and we could execute it. We could easily
write a small interpreter for this XML code and we could execute it
directly. Alternatively, we could transform it into Java or C++ code,
compile it, and run it. It's code.

So, where are we? Looks like we've just arrived to an interesting
point. A concept that has traditionally been so hard to understand is
now amazingly simple and intuitive. Code is also always data! Does it
mean that data is also always code? As crazy as this sounds this very
well might be the case. Remember how I promised that you'll see our
to-do list in a whole new light? Let me reiterate on that promise. But
we aren't ready to discuss this just yet. For now let's continue
walking down our path.

A little earlier I mentioned that we could easily write an interpreter
to execute our XML snippet of the add function. Of course this sounds
like a purely theoretical exercise. Who in their right mind would want
to do that for practical purposes? Well, it turns out quite a few
people would disagree. You're likely encountered and used their work
at least once in your career, too. Do I have you out on the edge of
your seat? If so, let's move on!


Ant Reloaded
------------

Now that we've made the trip to the dark side of the moon, let's not
leave quite yet. We may still learn something by exploring it a little
more, so let's take another step. We begin by closing our eyes and
remembering a cold rainy night in the winter of 2000. A prominent
developer by the name of James Duncan Davidson was hacking his way
throught Tomecat servlet container. As the time came to build the
changes he carefully saved all his files and ran make. Errors. Lots of
errors. Something was wrong. After careful examination James exclaimed:
"Is my command not executing because I have a space in front of my
tab?!" Indeed, this was the problem. Again. James has had enough. He
could sense the full moon through the clouds and it made him
adventurous. He created a fresh Java project and quickly hacked
together a simple but surprisingly useful utility. This spark of
genius used Java property files for infromation on how to build the
project. James could now write the equivalent of the makefile in a nice
fromat without worrying about the damned spaces ever again. His utility
did all the hard work by interpreting the property file and taking
appropriate actions to build the project. It was neat, Another Neat
Tool. Ant.

After using Ant to build Tomcat for a few months it became clear that
Java property files are not sufficient to express complicated build
instructions. Files needed to be checked out, copied, compiled, sent
to another machine, and unit tested. In case of failure e-mails needed
to be sent out to appropriate people. In case of success "Bad to the
Bone" needed to be played at the highest possible volume. At the end
of the track volumne had to be restored to its original level. Yes,
Java property files didn't cut it anymore. James needed a more
flexible solution. He didn't feel like writing his own parser (
especially since he wanted an industry standard solution). XML seemed
like a reasonable alternative. In a couple of days Ant was ported to
XML. It was the best thing since sliced bread.

So how does Ant work? It's pretty simple. It takes an XML file with
specific build instructions (you decide if they're data or data) and
interprets them by running specialized Java code for each XML element.
It's actually equivalent name to be loaded and its code to be executed.

```
<copy todir="../new/dir">
    <fileset dir="src_dir"/>
</copy>
```

The snippet above copies a source directory to a destination directory.
Ant locates a "copy" task (a Java class, really), sets appropriate
parameters (todir and fileset) by calling appropriate Java methods and
then executes the task. Ant comes with a set of core tasks and anyone
can extend it with tasks of their own simply by writing Java classes
that follow certain conventions. Ant finds these classes and executes
them whenever XML elements with appropriate names that are encountered.
Pretty simple. Effectively Ant accomplishes what we were talking about
in the previous section: it acts as an interpreter for a language that
uses XML as its syntax by translating XML elements to appropriate Java
instructions. We could write an "add" task and have Ant execute it when
it encounters the XML snippet for addition presented in the previous
section! Considering that ant is an extremely popular project, the
ideas presented in the previous section start looking more sane. After
all, they're being used every day in what probably amounts to thousands
of companies!

So far I've said nothing about why Ant actually goes throught all the
trouble of interpreting XML. Don't try to look for the answer on its
website either - you'll find nothing of value. Nothing relevant to our
discussion, anyway. Let's take another step. It's time to find out why.


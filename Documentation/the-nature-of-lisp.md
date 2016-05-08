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



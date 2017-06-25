The standard similarity algorithm used in Elasticsearch is known as term
frequency/inverse document frequency, or TF/IDF, which takes the following
factors into account:

Term frequency
==============

How often does the term appear in the field? The more often, the more relevant.
A field containing five mentions of the same term is more likely to be relevant
than a field containing just one mention.

Inverse document frequency
==========================

How often does each term appear in the index? The more often, the less relevant.
Terms that appear in many documents have a lower weight than more-uncommon
terms.

Field-length norm
=================

How long is the field? The longer it is, the less likely it is that words in the
field will be relevant. A term appearing in a short title field carries more
weight than the same term appearing in a long content field.

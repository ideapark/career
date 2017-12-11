#!/bin/sh

if [ ! -d wiki_en_output ]; then
   mkdir wiki_en_output
fi

python -m gensim.scripts.make_wiki enwiki-latest-pages-articles.xml.bz2 ./wiki_en_output

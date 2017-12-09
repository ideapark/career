# Cluster: search related posts

# Levenshtein distance (edit distance)
#
# Similar Ratio: the edit counts needed that transfer one word to another
# eg:  machine --> mchiene  DIST: 2

# Bag-of-Word
#
# post1: 'How to format my hard disk'
# post2: 'Hard disk format problems'
#
#  Word        Post2Count        Post2Count
# disk         1                 1
# format       1                 1
# how          1                 0
# hard         1                 1
# my           1                 0
# problems     0                 1
# to           1                 0
#
# Vector:
# post1: [1, 1, 1, 1, 1, 0, 1]
# post2: [1, 1, 0, 1, 0, 1, 0]
#
# Similar Ratio: euler-distance(post1, post2)

import os
from sklearn.feature_extraction.text import CountVectorizer

vectorizer = CountVectorizer(min_df=1)
print(vectorizer)

content = ["How to format my hard disk", " Hard disk format problems "]
X = vectorizer.fit_transform(content)
print vectorizer.get_feature_names()
print(X.toarray().transpose())

DIR = '.'

posts = [open(os.path.join(DIR, f)).read() for f in os.listdir(DIR)]
X_train = vectorizer.fit_transform(posts)
num_samples, num_features = X_train.shape
print('#samples: %d, #features: %d' % (num_samples, num_features))
print(vectorizer.get_feature_names())

# feature vector
print(X_train.getrow(3).toarray())
print(X_train.getrow(4).toarray())

# stem extract
import nltk.stem

s = nltk.stem.SnowballStemmer('english')
print s.stem("graphics")
print s.stem("imaging")
print s.stem("image")
print s.stem("imagination")
print s.stem("imagine")

# NLTK stemmed CountVectorizer
english_stemmer = nltk.stem.SnowballStemmer('english')
class StemmedCountVectorizer(CountVectorizer):
    def build_analyzer(self):
        analyzer = super(StemmedCountVectorizer, self).build_analyzer()
        return lambda doc: (english_stemmer.stem(w) for w in analyzer(doc))
vectorizer = StemmedCountVectorizer(min_df=1, stop_words='english')
print(vectorizer)

# stop word boost (TF-IDF)
import math
import scipy as sp

def tfidf(term, doc, docset):
    tf = float(doc.count(term))/sum(doc.count(w) for w in docset)
    idf = math.log(float(len(docset))/(len([doc for doc in docset if term in doc])))
    return tf * idf

a, abb, abc = ["a"], ["a", "b", "b"], ["a", "b", "c"]
D = a + abb + abc
print(tfidf("a", a, D))
print(tfidf("b", abb, D))
print(tfidf("a", abc, D))
print(tfidf("b", abc, D))
print(tfidf("c", abc, D))

# Cluster
#
# flat cluster
# hierarchy cluster
#
# sklearn.cluster
# http://scikit-learn.org/dev/modules/clustering.html

from sklearn.feature_extraction.text import TfidfVectorizer
class StemmedTfidfVectorizer(TfidfVectorizer):
    def build_analyzer(self):
        analyzer = super(TfidfVectorizer, self).build_analyzer()
        return lambda doc: (english_stemmer.stem(w) for w in analyzer(doc))
vectorizer = StemmedTfidfVectorizer(min_df=1,
                                    stop_words='english')
print vectorizer

from gensim import corpora, models, similarities

corpus = corpora.BleiCorpus('./ap/ap.dat', './ap/vocab.txt')
model = models.ldamodel.LdaModel(corpus,
                                 num_topics=100,
                                 id2word=corpus.id2word,
                                 alpha=0.5)
topics = [model[c] for c in corpus]
print topics[0]

import numpy as np

# make matrix
dense = np.zeros((len(topics), 100), float)
for ti, t in enumerate(topics):
    for tj, v in t:
        dense[ti, tj] = v

from scipy.spatial import distance

# matrix distance
# sum((dense[ti] - dense[tj])**2)
pairwise = distance.squareform(distance.pdist(dense))
largest = pairwise.max()
# handle matrix diagonal
for ti in range(len(topics)):
    pairwise[ti, ti] = largest+1

def closest_to(doc_id):
    return pairwise[doc_id].argmin()

print closest_to(1)

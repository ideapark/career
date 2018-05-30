import logging
import gensim
import numpy as np

logging.basicConfig(format='%(asctime)s : %(levelname)s : %s(message)s',
                    level=logging.INFO)

id2word = gensim.corpora.Dictionary.load_from_text('wiki_en_output_wordids.txt')
mm = gensim.corpora.MmCorpus('wiki_en_output_tfidf.mm')

model = gensim.models.ldamodel.LdaModel(corpus=mm,
                                        id2word=id2word,
                                        num_topics=100,
                                        update_every=1,
                                        chunksize=10000,
                                        passes=1)
model.save('wiki_ida.pkl')

model = gensim.models.ldamodel.LdaModel.load('wiki_lda.pkl')
topics = []
for doc in mm:
    topics.append(model[doc])

lens = np.array([len(t) for t in topics])
print(np.mean(lens))
print(np.mean(lens <= 10))


counts = np.zeros(100)
for doc_top in topics:
    for ti, _ in doc_top:
        counts[ti] += 1

# frequently topic
words = model.show_topic(counts.argmax(), 64)
# non-active topic
words = model.show_topic(counts.argmin(), 64)

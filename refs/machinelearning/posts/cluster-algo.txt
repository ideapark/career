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

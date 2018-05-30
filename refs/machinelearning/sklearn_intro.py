# Feature Engineering
#
# Cluster
#
# 1) model architecture
# 2) search progress
# 3) loss estimation function

from matplotlib import pyplot as plt
from sklearn.datasets import load_iris

data = load_iris()
features = data['data']
feature_names = data['feature_names']
target = data['target']

for t, marker, c in zip(range(3), ">ox", "rgb"):
    plt.scatter(features[target == t, 0],
                features[target == t, 1],
                marker=marker,
                c=c)
plt.grid()
plt.show()

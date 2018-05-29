# https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.pearsonr.html

# scipy.stats.pearsonr(x, y)[source]

# Calculate a Pearson correlation coefficient and the p-value for testing
# non-correlation.

# The Pearson correlation coefficient measures the linear relationship between
# two datasets. Strictly speaking, Pearson’s correlation requires that each
# dataset be normally distributed, and not necessarily zero-mean. Like other
# correlation coefficients, this one varies between -1 and +1 with 0 implying
# no correlation. Correlations of -1 or +1 imply an exact linear relationship.
# Positive correlations imply that as x increases, so does y. Negative
# correlations imply that as x increases, y decreases.

# The p-value roughly indicates the probability of an uncorrelated system
# producing datasets that have a Pearson correlation at least as extreme as the
# one computed from these datasets. The p-values are not entirely reliable but
# are probably reasonable for datasets larger than 500 or so.

# Parameters:
# x : (N,) array_like
# Input
# y : (N,) array_like
# Input

# Returns:
# r : float
# Pearson’s correlation coefficient
# p-value : float
# 2-tailed p-value

from scipy import stats

a = np.array([0, 0, 0, 1, 1, 1, 1])
b = np.arange(7)

print(stats.pearsonr(a, b))
print(stats.pearsonr([1, 2, 3, 4, 5], [5, 6, 7, 8, 7]))

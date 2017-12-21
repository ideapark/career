# scipy.stats.spearmanr(a, b=None, axis=0, nan_policy='propagate')

# Calculates a Spearman rank-order correlation coefficient and the p-value to
# test for non-correlation.

# The Spearman correlation is a nonparametric measure of the monotonicity of
# the relationship between two datasets. Unlike the Pearson correlation, the
# Spearman correlation does not assume that both datasets are normally
# distributed. Like other correlation coefficients, this one varies between -1
# and +1 with 0 implying no correlation. Correlations of -1 or +1 imply an
# exact monotonic relationship. Positive correlations imply that as x
# increases, so does y. Negative correlations imply that as x increases, y
# decreases.

# The p-value roughly indicates the probability of an uncorrelated system
# producing datasets that have a Spearman correlation at least as extreme as
# the one computed from these datasets. The p-values are not entirely reliable
# but are probably reasonable for datasets larger than 500 or so.

# Parameters:
# a, b : 1D or 2D array_like, b is optional

# One or two 1-D or 2-D arrays containing multiple variables and observations.
# When these are 1-D, each represents a vector of observations of a single
# variable. For the behavior in the 2-D case, see under axis, below. Both
# arrays need to have the same length in the axis dimension.

# axis : int or None, optional

# If axis=0 (default), then each column represents a variable, with
# observations in the rows. If axis=1, the relationship is transposed: each row
# represents a variable, while the columns contain observations. If axis=None,
# then both arrays will be raveled.

# nan_policy : {‘propagate’, ‘raise’, ‘omit’}, optional

# Defines how to handle when input contains nan. ‘propagate’ returns nan,
# ‘raise’ throws an error, ‘omit’ performs the calculations ignoring nan
# values. Default is ‘propagate’.

# Returns:
# correlation : float or ndarray (2-D square)

# Spearman correlation matrix or correlation coefficient (if only 2 variables
# are given as parameters. Correlation matrix is square with length equal to
# total number of variables (columns or rows) in a and b combined.

# pvalue : float

# The two-sided p-value for a hypothesis test whose null hypothesis is that two
# sets of data are uncorrelated, has same dimension as rho.

from scipy import stats
import numpy as np

print stats.spearmanr([1, 2, 3, 4, 5], [5, 6, 7, 8, 7])

np.random.seed(1234321)

x2n = np.random.randn(100, 2)
y2n = np.random.randn(100, 2)

print stats.spearmanr(x2n)
print stats.spearmanr(x2n[:,0], x2n[:,1])

rho, pval = stats.spearmanr(x2n, y2n)

print rho
print pval

rho, pval = stats.spearmanr(x2n.T, y2n.T, axis=1)

print rho
print pval

print stats.spearmanr(x2n, y2n, axis=None)
print stats.spearmanr(x2n.ravel(), y2n.ravel())

xint = np.random.randint(10, size=(100, 2))
print stats.spearmanr(xint)

import scipy as sp

data = sp.genfromtxt('./web_traffic.tsv', delimiter='\t')

# check data read ok
print(data[:10])

# preprocess and data clean
x = data[:,0]
y = data[:,1]

# y contains invalid value
print sp.sum(sp.isnan(y))

# clean nan
x = x[~sp.isnan(y)]
y = y[~sp.isnan(y)]

# visualize cleaned data
import matplotlib.pyplot as plt
plt.scatter(x, y)
plt.title('Web traffic over the last month')
plt.xlabel('Time')
plt.ylabel('Hits/hour')
plt.xticks([w*7*24 for w in range(10)], ['week %i' % w for w in range(10)])
plt.autoscale(tight=True)

# error estimation
def error(f, x, y):
    return sp.sum((f(x)-y)**2)

# FIRST-ORDER fit
fp1 = sp.polyfit(x, y, 1)
print("Model parameters: %s" % fp1)
# FIT: f(x) = 2.59619213 * x + 989.02487106

f1 = sp.poly1d(fp1)
print(error(f1, x, y))
fx = sp.linspace(0, x[-1], 1000)
plt.plot(fx, f1(fx), linewidth=4)

# SECOND-ORDER fit
fp2 = sp.polyfit(x, y, 2)
print(fp2)
# FIT: f(x) = 0.015322215 * x**2 - 5.26545650 * x + 1974.76082
f2 = sp.poly1d(fp2)
print(error(f2, x, y))
plt.plot(fx, f2(fx), linewidth=4)

# treat data another way
inflection = int(3.5*7*24)
xa = x[:inflection]
ya = y[:inflection]
xb = x[inflection:]
yb = y[inflection:]

fa = sp.poly1d(sp.polyfit(xa, ya, 1))
fb = sp.poly1d(sp.polyfit(xb, yb, 1))

fa_error = error(fa, xa, ya)
fb_error = error(fb, xb, yb)
print("Error inflection=%f" % (fa_error+fb_error))

fax = fx[:inflection]
fbx = fx[inflection:]
plt.plot(fax, fa(fax), linewidth=4)
plt.plot(fbx, fb(fbx), linewidth=4)

# underfitting
# overfitting

plt.grid()
plt.show()

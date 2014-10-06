#!/usr/bin/env python
import sys
from scipy.stats import spearmanr

def rho(v1, v2):
        """ Computes Spearman's rho for two lists of observations with no ties

                Parameters:
                        v1:        list of observations
                        v2:        list of observations
        """
	n = len(v1)
	nu1 = sum(v1)*1.00/n
	nu2 = sum(v2)*1.00/n
	sumd1 = 0
	sumd2 = 0
	sumN = 0

	for i in xrange(n):
		sumN += (v1[i]-nu1)*(v2[i]-nu2)
		sumd1 += (v1[i]-nu1)**2 
		sumd2 += (v2[i]-nu2)**2
	return sumN/((sumd1*sumd2)**0.5)


human = []
predict = []
for line in open(sys.argv[1]):
    l = line.strip().split()
    human.append(float(l[2]))
    predict.append(float(l[3]))
#print rho(human,predict)
x,y = spearmanr(human,predict)
print max(x,y),353-len(human)

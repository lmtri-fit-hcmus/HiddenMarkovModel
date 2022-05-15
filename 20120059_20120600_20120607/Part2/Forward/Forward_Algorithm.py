from array import array
import numpy as np


def Forward(O, A, B, Pi):
    N = A.shape[0]
    T = O.shape[0]
    print(N,T)
    alpha = np.zeros((N, T))
    for s in range(0, N):
        alpha[s, 0] = Pi[s] * B[s, O[0]]
    for t in range(1, T):
        for s in range(0, N):
            sum = 0
            for s_comma in range(0, N):
                sum += alpha[s_comma, t - 1] * A[s_comma, s] * B[s, O[t]]
            alpha[s, t] = sum
    result = 0
    for s in range(0, N):
        result += alpha[s, T-1]
    return result

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
def main():
    A = np.array([[0.8, 0.2], [0.7, 0.3]])
    B = np.array([[1/6, 1/6, 1/6, 1/6, 1/6, 1/6], [0.1, 0.1, 0.1, 0.1, 0.1, 0.5]])
    Pi = np.array([0.5, 0.5])
    O = np.array([5, 2, 3, 5, 2, 5, 5, 0, 2, 5, 4, 1, 5, 4, 1, 3, 3, 5, 4, 2, 1, 5, 5, 2, 0, 5, 2, 3, 4, 3, 3, 5, 1, 3, 5, 2, 3, 3, 5, 0, 5, 2, 4, 2, 0, 3, 0, 2, 1, 2, 3, 2, 2, 1, 5, 0, 2, 0, 2, 4, 4, 5, 1, 3, 1, 2, 3, 3, 3, 3, 4, 0, 5, 0, 4, 4, 4, 1, 1, 3, 2, 1, 5, 4, 2, 3, 5, 5, 4, 2, 4, 3, 3, 2, 4, 5, 3, 4, 5, 4])
    print(Forward(O,A,B,Pi))

if __name__ == "__main__":
    main()

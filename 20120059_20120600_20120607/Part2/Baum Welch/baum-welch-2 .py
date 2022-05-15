import pandas as pd
import numpy as np
import random

#____________________________--Hàm tiến forward--_______________________________
def forward(V, a, b, initial_distribution):
    alpha = np.zeros((V.shape[0], a.shape[0]))
    alpha[0, :] = initial_distribution * b[:, V[0]]
    for t in range(1, V.shape[0]):
        for j in range(a.shape[0]):
            # Matrix Computation Steps
            #                  ((1x2) . (1x2))      *     (1)
            #                        (1)            *     (1)
            alpha[t, j] = alpha[t - 1].dot(a[:, j]) * b[j, V[t]]
 
    return alpha
 
#____________________________--Hàm quay lui backward--___________________________
def backward(V, a, b):
    beta = np.zeros((V.shape[0], a.shape[0]))
 
    # setting beta(T) = 1
    beta[V.shape[0] - 1] = np.ones((a.shape[0]))
 
    # Loop in backward way from T-1 to
    # Due to python indexing the actual loop will be T-2 to 0
    for t in range(V.shape[0] - 2, -1, -1):
        for j in range(a.shape[0]):
            beta[t, j] = (beta[t + 1] * b[:, V[t + 1]]).dot(a[j, :])
 
    return beta

#_________________________--Hàm thuật toán Baum-Welch--____________________________
def baum_welch(V, a, b, initial_distribution, n_iter=100):
    M = a.shape[0]
    T = len(V)

    for n in range(n_iter):
        # Tìm alpha và beta
        alpha = forward(V, a, b, initial_distribution)
        beta = backward(V, a, b)

        # Thực hiện tính toán giá trị xi
        xi = np.zeros((M, M, T - 1))
        for t in range(T - 1):
            denominator = np.dot(np.dot(alpha[t, :].T, a) * b[:, V[t + 1]].T, beta[t + 1, :])
            for i in range(M):
                numerator = alpha[t, i] * a[i, :] * b[:, V[t + 1]].T * beta[t + 1, :].T
                xi[i, :, t] = numerator / denominator

        # Tính giá trị gamma
        gamma = np.sum(xi, axis=1)

        # Cập nhật ma trận xác suất chuyển tiếp
        a = np.sum(xi, 2) / np.sum(gamma, axis=1).reshape((-1, 1))

        # Thâm phần tử thứ T và ma trận gamma
        gamma = np.hstack((gamma, np.sum(xi[:, :, T - 2], axis=0).reshape((-1, 1))))

        K = b.shape[1]

        # Cập nhật mẫu số
        denominator = np.sum(gamma, axis=1)

        # Cập nhật ma trận xác suất phát xạ
        for l in range(K):
            b[:, l] = np.sum(gamma[:, V == l], axis=1)

        b = np.divide(b, denominator.reshape((-1, 1)))

    return {"a":a, "b":b,"gamma":gamma,"alpha":alpha}

#____________main_function__________________________________________
# Đọc dữ liệu từ file 
data = pd.read_csv('ObservationData.csv')
V = data['Visible'].values

# Ma trận xác suất chuyển tiếp
a = np.array(((0.8,0.2), (0.7,0.3)))
a = a / np.sum(a, axis=1).reshape((-1, 1))

# Ma trận xác suất phát xạ
b = np.array(((1,1,1,1,1,1), (1,1,1,1,1,5)))
b = b / np.sum(b, axis=1).reshape((-1, 1))

# Xác suất khởi tạo ban đầu
initial_distribution = np.array((0.5,0.5))
result=baum_welch(V, a, b, initial_distribution, n_iter=100)

#______________________________________________________________________
# Ma trận xấc suất chuyển tiếp
print("Transition Probabilities:")
y=result['a']
print(y)
print("_____________________________")
print("")
# Ma trận xác suất phát xạ
print("Emission Probabilities:")
z=result['b']
print(z)
print("_____________________________")
print("")
# Trich ma trận xác suất tìm thấy các quan sát y_1,y_2,...,y_t và đang ở trạng thái i tại thời điểm t.
u=result['alpha']
print("Chain: ")
for i in range(0,100):
    if(u[i][0]>u[i][1]):
        print("     Balance")
    else:
        print("     Inbalance")

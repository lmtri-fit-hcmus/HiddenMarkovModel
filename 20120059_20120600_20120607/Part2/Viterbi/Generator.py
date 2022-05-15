from re import L
import numpy as np

def generator(n):
    ba = "BA" #Balanced
    im = "IM" #Imbalanced
    trans_matrix = np.array([[0.8,0.2],[0.7, 0.3]])
    emiss_matrix = np.array([[1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/6], [0.1, 0.1, 0.1, 0.1, 0.1, 0.5]])
    print(trans_matrix)
    state = np.random.choice((ba,im),p=[0.5,0.5])
    dice_face = 0
    if state == ba:
        dice_face = np.random.choice(range(1,7), p = emiss_matrix[0])
    else:
        dice_face = np.random.choice(range(1,7), p =emiss_matrix[1])
    sample = list()
    sample.append(tuple((dice_face,state)))
    prev_state = state
    print(sample)
    for i in range(0,n-1):
        if prev_state ==ba:
            state = np.random.choice((im, ba),p=[0.2, 0.8])
        elif prev_state == im:
            state = np.random.choice((im,ba),p= [0.3, 0.7])
        if state == ba:
            dice_face = np.random.choice(range(1,7), p =emiss_matrix[0])
        else:
            dice_face = np.random.choice(range(1,7), p =emiss_matrix[1])
        sample.append(tuple((dice_face,state)))
        prev_state = state

    file = open("sample.txt","w")
    file_test = open("test.txt","w")
    for tup in sample:
        file.write(str(tup[0]) +" "+ str(tup[1]) + "\n")
        file_test.write(str(tup[0]-1) + ", ")
    file.close()


if __name__ == "__main__":
    generator(100)









- Thư mục Data chứa các ma trận(transision, emission, initial) được huấn luyện từ tập dữ liệu train
- Thư mục Test chứa file dữ liệu test để đánh giá mô hình
- viterbiAlgorithm.cpp và viterbiAlgorithm.h là 2 file implement code thuật toán viterbi, hoàn toàn giống phần 2
- SupportFunctions.cpp và SupportFunctions.h là 2 file hỗ trợ việc tách token, đọc file, lấy các ma trận (transision, emission, initial)
- Makefile.cpp: Đọc file từ file Test, sau đó lưu kết quả dự đoán vào file PredictionData trong EvaluationData. Đồng thời đưa nhãn thực của từ đó vào
TaggedData trong thư mục EvaluationData
- Evaluation.h và Evaluation.cpp là file đánh giá mô hình(tính toán các con số: precision,recall, f1_score)
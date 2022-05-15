import sys
from Utils import parser
from Utils import float_to_str

def Init():
    tag_tag_dict = dict()
    word_tag_dict = dict()
    tags_count_dict = dict()

    return tag_tag_dict, word_tag_dict, tags_count_dict

def init_probability(tag_tag_dict, tags_count_dict):
    init_prob = dict()
    for tag,value in tags_count_dict.items():
        init_prob[tag] = 0
    for tag_tag, value in tag_tag_dict.items():
        temp = tag_tag.split("/")
        prev_tag = temp[0]
        cur_tag = temp[-1]
        if prev_tag=="<s>":
            init_prob[cur_tag] = float(tag_tag_dict[tag_tag])/tags_count_dict[prev_tag]
        else:
            continue
    return init_prob
def transition_probability(tag_tag_dict, tags_count_dict):
    trans_prob = dict()
    for tag_tag, value in tag_tag_dict.items():
        temp = tag_tag.split("/")
        prev_tag = temp[0]
        if prev_tag!="<s>":
            trans_prob[tag_tag] =float(tag_tag_dict[tag_tag])/tags_count_dict[prev_tag]
        else:
             continue
    return trans_prob


def emission_probability(word_tag_dict,tags_count_dict):
    emiss_prob = dict()
    for word_tag, value in word_tag_dict.items():
        temp = word_tag.split("/")
        tag = temp[-1]
        emiss_prob[word_tag] = (float)(value)/tags_count_dict[tag]
    return emiss_prob

def save_model(init_prob, trans_prob, emiss_prob):
    file = open("model.txt","w")
    
    file.write("INITIAL PROBABILITIES:" + "\n")
    for st, prob in init_prob.items():
        file.write(st +" "+ float_to_str(prob) + "\n")
    file.write("\n")

    file.write("TRANSITION PROBABILITIES:" + "\n")
    for st, prob in trans_prob.items():
        file.write(st +" "+ float_to_str(prob) + "\n")
    file.write("\n")

    file.write("EMISSION PROBABILITIES:" + "\n")
    for st, prob in emiss_prob.items():
        file.write(st +" "+ float_to_str(prob) + "\n")
    file.write("\n")

    file.close()


def train(file_name):
    tag_tag_dict,word_tag_dict, tags_count_dict = Init()
    with open(file_name, encoding='utf8') as file:
        lines = file.readlines()
        for line in lines:
            parser(tags_count_dict, word_tag_dict, tag_tag_dict, line)
    init_prob = init_probability(tag_tag_dict, tags_count_dict)
    trans_prob = transition_probability(tag_tag_dict, tags_count_dict)
    emiss_prob = emission_probability(word_tag_dict, tags_count_dict)
    save_model(init_prob, trans_prob, emiss_prob)

if __name__ == "__main__":
    file_name = "en_train_tagged.txt"
    train(file_name)




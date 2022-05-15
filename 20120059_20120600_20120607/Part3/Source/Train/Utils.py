import sys
import decimal

def parser(tags_count_dict,word_tag_dict,tag_tag_dict, sentence):
    previous = "<s>"
    previous = previous.strip()

    if previous not in tags_count_dict:
        tags_count_dict[previous] = 0
    tags_count_dict[previous] +=1

    word_tags = sentence.split(' ') #List of (word/tag)

    for i, word_tag in enumerate(word_tags):
        word_tag = word_tag.strip()
        temp = word_tag.split('/')
        tag = temp[-1]
        tag=tag.strip()
        
        if tag not in tags_count_dict:
            tags_count_dict[tag] =0
        tags_count_dict[tag] += 1

        if word_tag not in word_tag_dict:
            word_tag_dict[word_tag] = 0
        word_tag_dict[word_tag] +=1

        tag_tag = previous + "/" + tag
        if tag_tag not in  tag_tag_dict:
            tag_tag_dict[tag_tag] = 0
        tag_tag_dict[tag_tag] += 1
       

        previous = tag
    
    # if previous + "/<~s>" not in tag_tag_dict:
    #     tag_tag_dict[previous + "/<~s>"] = 0
    # tag_tag_dict[previous + "/<~s>"] += 1



def float_to_str(f):
    # create a new context for this task
    ctx = decimal.Context()

    # 20 digits should be enough for everyone :D
    ctx.prec = 20
    """
    Convert the given float to a string,
    without resorting to scientific notation
    """
    d1 = ctx.create_decimal(repr(f))
    return format(d1, 'f')




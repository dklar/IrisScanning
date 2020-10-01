import matplotlib.pyplot as plt


def compare(str1,str2):
    hd = 0
    str1 = str1.replace("4","")
    str2 = str2.replace("4","")
    for x,y in zip(str1,str2):
        if x != y:
            if x!= "4":
                hd +=1
            else:
                print("TEST")
    return hd/2048




def test_all():
    ref = open("gabor_all_high_1.txt", "r")
    ref2 = open("gabor_fix_5_iter_1.txt","r")
    str1_ref = ref.readline()
    str2_ref = ref2.readline()
    hd1 = []
    hd2 = []
    for i in range(2,100):
        str2 = open("gabor_all_high_"+str(i)+".txt","r").readline()
        str2_fix = open("gabor_fix_5_iter_"+str(i)+".txt","r").readline()
        tmp1 = compare(str1_ref,str2)
        tmp2 = compare(str2_ref,str2_fix)
        hd1.append(tmp1)
        hd2.append(tmp2)
        print(tmp2)


    n, bins, patches = plt.hist(hd1, 7, density=1, facecolor='g', alpha=0.75)

    plt.xlabel('Smarts')
    plt.ylabel('Probability')
    plt.title('Histogram of IQ')

    plt.ylim(0, 30)
    #plt.axis([0, 1, 0, 2])
    plt.grid(True)
    plt.show()

    n, bins, patches = plt.hist(hd2, 7, density=1, facecolor='g', alpha=0.75)

    plt.xlabel('Smarts')
    plt.ylabel('Probability')
    plt.title('Histogram of IQ')

    plt.ylim(0, 30)
    #plt.axis([0, 1, 0, 2])
    plt.grid(True)
    plt.show()

def test_one():
    ref = open("gabor_all_high_1.txt", "r").readline()#all high
    ref2 = open("gabor_fix_5_iter_1.txt","r").readline()#float 5 iterations
    ref3 = open("gabor_fix_1.txt","r").readline()#10 iterations
    print("high to 10:")
    print(compare(ref,ref2))
    print("high to 5:")
    print(compare(ref,ref3))
    

test_one()

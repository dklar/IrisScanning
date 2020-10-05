import matplotlib.pyplot as plt
import os

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
    ref = "gabor_acc_001_1_1.txt"
    code_ref = open("Results/Gabor/"+ref)
    hd1 = []
    #hd2 = []
    str1 = code_ref.readline()

    for filename in os.listdir("Results/Gabor"):
        if filename != ref:
            code_file = open("Results/Gabor/"+filename)
            str2 = code_file.readline()

            tmp1 = compare(str1,str2)
            hd1.append(tmp1)
            #hd2.append(tmp2)
            #print(tmp1)
    return hd1

    # ref = open("gabor_all_high_1.txt", "r")
    # ref2 = open("gabor_fix_5_iter_1.txt","r")
    # str1_ref = ref.readline()
    # str2_ref = ref2.readline()
    # hd1 = []
    # hd2 = []
    # for i in range(2,100):
    #     str2 = open("gabor_all_high_"+str(i)+".txt","r").readline()
    #     str2_fix = open("gabor_fix_5_iter_"+str(i)+".txt","r").readline()
    #     tmp1 = compare(str1_ref,str2)
    #     tmp2 = compare(str2_ref,str2_fix)
    #     hd1.append(tmp1)
    #     hd2.append(tmp2)
    #     print(tmp2)

def show_hist(hd,max):
    plt.hist(hd, 10, density=1, facecolor='g', alpha=0.75)
    plt.title('Histogram of Hamming distance')

    plt.ylim(0, max)
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

def hamming(code1,code2):
    codetemp1 = []
    codetemp2 = []

    for el in code1:
        if el==1:
            codetemp1.append(1)
        if el==0:
            codetemp1.append(0)

    for el in code2:
        if el==1:
            codetemp2.append(1)
        if el==0:
            codetemp2.append(0)

    hd = 0
    for x,y in zip(codetemp1,codetemp2):
        if x!=y:
            hd+=1
    
    return hd/2048


def compareAprox():
    """ 
    Compare value first with other values in the same database
    """
    size = os.path.getsize("Results/Gabor/gaborcodes_acc.dat")
    file_acc = open("Results/Gabor/gaborcodes_4bit_5iter.dat","rb")
       
    code = bytearray(file_acc.read(2048))
    hd =[]
    for i in range(2048,size,2048):
        file_acc.seek(i,0)
        code2 = bytearray(file_acc.read(2048))
        hammingDistance = hamming(code,code2)
        hd.append(hammingDistance)
        print(hammingDistance)
    show_hist(hd,20)
        
def compareAprox2():
    """ Compare accurate value with aprox. value
    """
    size = os.path.getsize("Results/Gabor/gaborcodes_acc.dat")
    file_acc = open("Results/Gabor/gaborcodes_acc.dat","rb")
    file_aprox = open("Results/Gabor/gaborcodes_4bit_5iter.dat","rb")    
    
    hd =[]
    for i in range(0,size,2048):
        file_aprox.seek(i,0)
        file_acc.seek(i,0)
        code1 = bytearray(file_acc.read(2048))
        code2 = bytearray(file_aprox.read(2048))
        hammingDistance = hamming(code1,code2)
        print(hammingDistance)
        hd.append(hammingDistance)
    show_hist(hd,45)

def compareAprox3():
    """ Compare value 1 with other values in database
    """
    size = os.path.getsize("Results/Gabor/gaborcodes_16bit_10it.dat")
    file_acc = open("Results/Gabor/gaborcodes_16bit_10it.dat","rb")
    file_aprox = open("Results/Gabor/gaborcodes_16bit_5it.dat","rb")    

    hd =[]
    for i in range(0,size,2048):
        file_acc.seek(i,0)
        code1 = bytearray(file_acc.read(2048))
        for j in range(i+2048,size,2048):
            file_aprox.seek(j,0)
            code2 = bytearray(file_aprox.read(2048))
            hammingDistance = hamming(code1,code2)
            hd.append(hammingDistance)
            #print(hammingDistance)
        print("One set complete")
        
    show_hist(hd,30)


compareAprox()
# hamming_dist = test_all()
# show_hist(hamming_dist)

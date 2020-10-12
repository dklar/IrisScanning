import cv2
import os

f = open("eye.txt")
os.mkdir("Test")

for line in f:
    values = line.split("#")
    nr = int(values[0])
    x  = int(values[1])
    y  = int(values[2])
    r  = int(values[3])
    r2  = int(values[4])
    if ( nr < 10):
        path = "C:/Users/Dennis/Desktop/Iris/CASIA1/"+values[0]+"/00"+values[0]+"_1_1.jpg"
    else:
        path = "C:/Users/Dennis/Desktop/Iris/CASIA1/"+values[0]+"/0"+values[0]+"_1_1.jpg"
    image = cv2.imread(path)
    cv2.circle(image,(x,y),r,(0,255,0),2)
    cv2.circle(image,(x,y),r2,(0,255,0),2)
    cv2.imwrite("Test/"+values[0]+".jpg",image)

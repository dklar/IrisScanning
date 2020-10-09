from math import log10, sqrt 
import cv2 
import numpy as np 
  
def PSNR(original, compressed): 
    mse = np.mean((original - compressed) ** 2) 
    if(mse == 0):  # MSE is zero means no noise is present in the signal . 
                  # Therefore PSNR have no importance. 
        return 100
    max_pixel = 255.0
    psnr = 20 * log10(max_pixel / sqrt(mse)) 
    return psnr 
  
def main():
    for i in range(1,99): 
        path1 = str(i)+"_cord_16_10.jpg"
        path2 = str(i)+"high.jpg"
        original = cv2.imread(path1) 
        compressed = cv2.imread(path2) 
        value = PSNR(original, compressed) 
        print(str(value)) 
       
if __name__ == "__main__": 
    main() 

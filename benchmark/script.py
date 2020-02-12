import subprocess
import numpy as np


dim=[1e4,2e4,5e4,1e5,2e5,5e5,1e6,2e6,5e6]

def stdev(x):
    avg=sum(x)/len(x)
    temp=0
    for i in x:
        temp+=(i-avg)*(i-avg)
    return [avg, np.sqrt(temp/(len(x)+1))]
    
unbalanced_out=[]
balanced_out=[]
std_map_out=[]
for i in range(len(dim)):
    unbalanced_in=[]
    balanced_in=[]
    std_map_in=[]
    for j in range(10):#10 executions of the program
        temp=subprocess.check_output(["./benchmark.x",  "%d"%dim[i]])
        print(temp)
        temp2=[]
        temp2=temp.split()
        unbalanced_in.append(float(temp2[4].decode()))
        balanced_in.append(float(temp2[9].decode()))
        std_map_in.append(float(temp2[13].decode()))
    unbalanced_out.append(stdev(unbalanced_in))
    balanced_out.append(stdev(balanced_in))
    std_map_out.append(stdev(std_map_in))
    print(unbalanced_out)
    print(balanced_out)
    print(std_map_out)
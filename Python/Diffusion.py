import numpy as np
import time
import matplotlib.pyplot as plt
import os

class Diffusion:
    def __init__(self, E, S):
        self.__N_Ensemble = E
        self.__N_Steps = S
        self.__MSD = []
        self.__Tvals = []
        self.__rng = np.random.default_rng(int(time.time()))

    def __FindMSD(self):
        SQX = [0.0]*self.__N_Ensemble
        for i in range(0, self.__N_Ensemble):
            x = 0
            t = 0
            for j in range(0, self.__N_Steps):
                rnd = self.__rng.uniform(0, 1)
                SQX[j] += x*x

                if (i == 0):
                    self.__Tvals.append(t)

                if ((rnd >= 0) and (rnd < 0.5)):
                    x -= 1
                else:
                    x += 1
                
                t += 1
        
        for i in range(0, len(SQX)):
            self.__MSD.append(SQX[i]/self.__N_Ensemble)

    def plot(self):
        self.__FindMSD()
        fig = plt.figure(figsize=(19.2, 10.8))
        ax = fig.add_subplot(1, 1, 1)
        ax.plot(self.__Tvals, self.__MSD, color="blue", linewidth=2)
        ax.set_title("Diffusion MSD/time Graph.", fontdict={"family":"Times New Roman", "size":30, "color":"red"})
        ax.set_xlabel("Time (s)", fontdict={"family":"Times New Roman", "size":18, "color":"black"})
        ax.set_xlim(0, self.__N_Ensemble)
        ax.set_ylabel("MSD", fontdict={"family":"Times New Roman", "size":18, "color":"black"})
        ax.grid(True, color="gray", linewidth=0.5)
        plt.savefig("Diffusion.png")
        plt.close()

print("This Program will plot a graph of MSD vs time for 1D Random walk.")
EnN = int(input("Enter the number of ensembles you want:- "))
StpN = int(input("Enter the number of steps per Ensemble you want:- "))
start = time.perf_counter()
A = Diffusion(EnN, StpN)
A.plot()
os.startfile("Diffusion.png")
end = time.perf_counter()
elapsed = end - start
print(f"Time Elapsed: {elapsed:.4f} seconds")
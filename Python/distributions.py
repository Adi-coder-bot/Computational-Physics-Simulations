import numpy as np
import time
import matplotlib.pyplot as plt
from pathlib import Path
import subprocess
import os

class Distributions:
    __rng = np.random.default_rng(int(time.time()))
    __limit = pow(10, 7)
    __name = "Binomial"
    __min, __max = 0, 100
    __binw = (__max - __min)/100.0

    __frequency = np.zeros(100, dtype=int)
    __x = []

    def __data(self):
        for i in range(0, self.__limit):
            rnd = self.__rng.binomial(100, 0.6)
            if(rnd >= self.__min and rnd < self.__max):
                A = int((rnd - self.__min)/self.__binw)
                self.__frequency[A]+= 1

            if (i%(self.__limit/len(self.__frequency)) == 0):
                self.__x.append((((self.__max - self.__min)*i)/(self.__limit - 1)) + self.__min + (0.5*self.__binw))
            else:
                continue

    def plot(self):
        self.__data()
        fig = plt.figure(figsize=(19.2, 10.8))
        ax1 = fig.add_subplot(1, 1, 1)
        ax1.bar(self.__x, self.__frequency, color="orange", width=self.__binw, align="center")
        ax1.set_title(f"{self.__name} distribution.", fontdict={"name":"Arial", "size":30, "color":"red"})
        ax1.set_xlabel("bins", fontdict={"name":"Arial", "size":18, "color":"black"})
        ax1.set_xlim(self.__min, self.__max)
        ax1.set_ylabel("frequencies", fontdict={"family":"Arial", "size":18, "color":"black"})
        ax1.grid(True, linewidth=0.5, color="gray")
        plt.savefig(f"graphs/{self.__name} distribution.png")
        plt.close()

print("This program will plot graphs of distributions of different random number generators.")
Path("graphs").mkdir(parents=True, exist_ok=True)
RND = Distributions()
RND.plot()
subprocess.run(['cmd', '/c', 'start', '', 'graphs\\Binomial distribution.png'])
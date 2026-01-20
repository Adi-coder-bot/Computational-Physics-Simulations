import random
import time
import matplotlib.pyplot as plt
class RW:
    def __init__(self):
        self.__p1 = 0
        self.__p2 = 1
        self.__rng1 = random.Random()
        self.__rng2 = random.Random()
        self.__iterations = [0]
        self.__positions = []

    def npos(self):
        self.__iterations = [0]
        self.__positions = []
        p1pos = [self.__p1]
        p2pos = [self.__p2]
        count = 1

        while(count < 10000000):
            rn1 = self.__rng1.uniform(0.0, 1.0)
            rn2 = self.__rng2.uniform(0.0, 1.0)
            if(rn1 >= 0 and rn1 < 0.5):
                self.__p1 -= 1
            elif(rn1 >= 0.5 and rn1 < 1):
                self.__p1 += 1

            p1pos.append(self.__p1)

            if(rn2 >= 0 and rn2 < 0.5):
                self.__p2 -= 1
            elif(rn2 >= 0.5 and rn2 < 1):
                self.__p2 += 1
                
            p2pos.append(self.__p2)

            self.__iterations.append(count)
            count += 1

            if (self.__p1 == self.__p2):
                break

        self.__positions.append(p1pos)
        self.__positions.append(p2pos)

        if (self.__p1 != self.__p2):
            return f"The iteration was too large ({count}), ended the program early..."
        else:
            return f"The position at which the p1 and p2 meet are {self.__p1}."

    def plot(self):
        plt.title("Graph of position of p1 and p2 till they meet", color="red", fontsize=30)
        plt.xlabel("Iterations", color="black", fontsize=18)
        plt.ylabel("positions", color="black", fontsize = 18)
        plt.grid(True, color="gray", linestyle="--", linewidth=1)
        plt.plot(self.__iterations, self.__positions[0], color="blue", linewidth=2, label = "positions of p1")
        plt.plot(self.__iterations, self.__positions[1], color="green", linewidth=2, label = "positions of p2")
        plt.legend(loc="upper left")
        plt.show()

print(f"This program will give the point at which 2 1D random walkers meet after a certain amount of time...")
obj1 = RW()
result = obj1.npos()
print(result)
obj1.plot()

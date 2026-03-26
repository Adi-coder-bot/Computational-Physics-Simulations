from scipy.integrate import solve_ivp
import numpy as np
import matplotlib.pyplot as plt

class deterministic:
    __c1X1, __c2X2, __c3, __c4 = 5000, 50, 0.00005, 5

    def __f(self, t, Y):
        Y1, Y2 = Y
        A = self.__c1X1 - self.__c2X2*Y1 + (self.__c3/2)*Y1*Y1*Y2 - self.__c4*Y1
        B = self.__c2X2*Y1 - (self.__c3/2)*Y1*Y1*Y2
        vals = [A, B]
        return vals
    
    def plot(self):
        t_range = (0, 10)
        t_eval = np.arange(0, 10, 0.001)
        Y0 = [1000, 1000]
        sol = solve_ivp(self.__f, t_range, Y0, method="RK45", t_eval = t_eval)

        fig = plt.figure(figsize=(19.2, 10.8))

        ax1 = fig.add_subplot(1, 2, 1)
        ax1.plot(sol.t, sol.y[0], color="blue", label="Y1")
        ax1.plot(sol.t, sol.y[1], color="green", label="Y2")
        ax1.set_title("Brusselator Model", fontdict={"family":"Times New Roman", "color":"red", "size":30})
        ax1.set_xlabel("time (s)", fontdict={"family":"Times New Roman", "color":"red", "size":18})
        ax1.set_ylabel("Number of Molecules", fontdict={"family":"Times New Roman", "color":"red", "size":18})
        ax1.grid(True, color="gray", linewidth=0.2)
        ax1.legend(loc="upper right")
        
        ax2 = fig.add_subplot(1, 2, 2)
        ax2.plot(sol.y[0], sol.y[1], color="blue")
        ax2.set_title("Brusselator Model Phase", fontdict={"family":"Times New Roman", "color":"red", "size":30})
        ax2.set_xlabel("Y1 Molecules", fontdict={"family":"Times New Roman", "color":"red", "size":18})
        ax2.set_ylabel("Y2 Molecules", fontdict={"family":"Times New Roman", "color":"red", "size":18})
        plt.tight_layout()
        fig.savefig("Graphs/Brusselator Model.png")

print("This Program will plot a Deterministic Graph")
obj = deterministic()
obj.plot()
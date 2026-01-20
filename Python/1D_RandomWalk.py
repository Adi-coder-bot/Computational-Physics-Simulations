import random as rnd
import subprocess as sp
class RW:
    def __init__(self, i, s):
        self.__position = 0
        self.__iterations = i
        self.__step = s
        rnd.seed()

    def direction(self, r):
        if (r >= 0 and r < 0.5):
            self.__position -= 1

        elif (r >= 0.5 and r < 1):
            self.__position += 1
    
    def steps(self):
        positions = [] 
        for j in range(0, self.__iterations):
            row = []
            self.__position = 0
            for k in range(0, self.__step):
                r = rnd.uniform(0, 1)
                row.append(self.__position)
                self.direction(r)

            positions.append(row)

        return positions

    
print("This program will find plot the position of a 1D random walker over many iterations and also plot a distribution curve.")

steps = int(input("Enter the number of steps you want the random walker to take per iteration:- "))
iterations = int(input("Enter the number of iterations for the random walker:- "))

obj = RW(iterations, steps)
data1 = obj.steps()
time = 0
data2 = []
for l in range(0, len(data1[0])):
    data2.append(time)
    time += 1

data = [data2] + data1

try:
    with open("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES Python/1D Random Walk/data.txt", "w") as file:
        for m in range(0, len(data[0])):
            for n in range(0, len(data)):
                file.write(str(data[n][m]) + "\t")

            file.write("\n")

except Exception as e:
    print("Error: ", e)

try:
    with open("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES Python/1D Random Walk/1DRW.gp", "w") as gp:
        gp.write("set terminal window enhanced font 'Arial, 18'\n\n")
        gp.write("set label '1D Random Walk Graph' at screen 0.5, 0.95 center font ', 30' tc rgb 'red'\n")
        gp.write("set xlabel 'time(seconds)'\n")
        gp.write("set ylabel 'position(meters)'\n\n")
        gp.write("set tmargin 3\n")
        gp.write("set bmargin 3\n")
        gp.write("set lmargin 10\n")
        gp.write("set rmargin 5\n")
        gp.write("set grid lt 1 lw 2 lc rgb 'gray'\n\n")
        gp.write("set style line 1 lt 1 lw 2 lc rgb 'violet'\n")
        gp.write("set style line 2 lt 1 lw 2 lc rgb 'purple'\n")
        gp.write("set style line 3 lt 1 lw 2 lc rgb 'blue'\n")
        gp.write("set style line 4 lt 1 lw 2 lc rgb 'green'\n")
        gp.write("set style line 5 lt 1 lw 2 lc rgb 'yellow'\n")
        gp.write("set style line 6 lt 1 lw 2 lc rgb 'orange'\n")
        gp.write("set style line 7 lt 1 lw 2 lc rgb 'red'\n\n")
        gp.write(f"plot for [i = 2:{len(data) - 1}] 'data.txt' u 1:i w l ls ((i % 7)+1) notitle\n")
        gp.write("pause mouse")

except Exception as e1:
    print("Error: ", e1)

Data = []
count = -((len(data)-1)/2)
Data1 = []
count1 = 0
Data2 = []
while (count < ((len(data) - 1)/2)):
    Data1.append(count)
    count1 = 0
    for o in range(1, len(data)):
        if (data[o][len(data[1]) - 1] < (count + int((1/10)*((len(data) - 1)/2))) and data[o][len(data[1]) - 1] >= count):
            count1 += 1
    
    Data2.append(count1)
    count += int((1/10)*((len(data) - 1)/2))

Data = [Data1] + [Data2]

try:
    with open("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES Python/1D Random Walk/data1.txt", "w") as file1:
        for p in range(0, len(Data[0])):
            file1.write(f"{Data[0][p]} \t {Data[1][p]} \n")

except Exception as e2:
    print("Error: ", e2)

try:
    with open("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES Python/1D Random Walk/1DRW_dist.gp", "w") as gp:
        gp.write("set terminal window enhanced font 'Arial, 18'\n\n")
        gp.write("set label '1D Random Walk Graph distribution' at screen 0.5, 0.95 center font ', 30' tc rgb 'red'\n")
        gp.write("set xlabel 'distance from center (meters)'\n")
        gp.write("set ylabel 'frequency'\n\n")
        gp.write("set tmargin 3\n")
        gp.write("set bmargin 3\n")
        gp.write("set lmargin 10\n")
        gp.write("set rmargin 5\n")
        gp.write("set grid lt 1 lw 2 lc rgb 'gray'\n\n")
        gp.write("set style fill solid 1.0 border -1\n")
        gp.write(f"set boxwidth {int((1/10)*((len(data) - 1)/2))} absolute\n\n")
        gp.write(f"plot 'data1.txt' u 1:2 w boxes lc rgb 'skyblue' notitle\n")
        gp.write("pause mouse")

except Exception as e3:
    print("Error: ", e3)

sp.run(["gnuplot", "1DRW.gp"])
sp.run(["gnuplot", "1DRW_dist.gp"])
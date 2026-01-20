import matplotlib.pyplot as plt
print("This Program finds the best fitting straingt line for a data set that you provide")
size=int(input("So, How many points of data will you enter?:- "))
Data=[[],[]]
SumXY = 0
for i in range(0, size):
    X = float(input(f"Enter the X value in Sr.no {i + 1} :- "))
    Y = float(input(f"Enter the Y value in Sr.no {i + 1} :- "))
    Data[0].append(X)
    Data[1].append(Y)

    SumXY+=Data[0][i] * Data[1][i]

SumX=sum(Data[0])
SumY=sum(Data[1])
SumXsq=sum(pow(x,2) for x in Data[0])

slope=((size*SumXY)-(SumX*SumY))/((size*SumXsq)-pow((SumX),2)) 
Y_intercept=((SumY-(SumX*slope))/size)
Y_fit=[]
print(f"Value of Slope is {slope} and value of Y-intercept is {Y_intercept}")
print(f"{'Sr.no':>10}{'X':>10}{'Y':>10}{'Y-fit':>10}")
for j in range(0, len(Data[0])):
    Y_fit.append(slope*Data[0][j] + Y_intercept)
    print(f"{j+1:>10.4f}{Data[0][j]:>10.4f}{Data[1][j]:>10.4f}{Y_fit[j]:>10.4f}")

plt.title("Least Square Fitting of given Data")
plt.xlabel("X values")
plt.ylabel("Y values")
plt.scatter(Data[0], Data[1], color="blue", marker="o", label="Data given by you")
plt.plot(Data[0], Y_fit, color="red", label="Least Square Fit of your data")
plt.grid(True)
plt.legend(loc="upper left")
plt.show()
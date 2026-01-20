class solution:
    def __init__(self, l, u):
        self.__x0 = l
        self.__x1 = u
        self.__e = pow(10, -6)

    def __f(self, x):
        return pow(x, 2) - 25
    
    def check(self):
        if((self.__f(self.__x0)*self.__f(self.__x1)) < 0):
            return True
        else:
            return False
    
    def root(self):
        x0 = self.__x0
        x1 = self.__x1
        X0 = []
        X1 = []
        X2 = []
        fX0 = []
        fX1 = []
        fX2 = []
        while True:
            x2 = (x0 + x1)/2
            X0.append(x0)
            X1.append(x1)
            X2.append(x2)
            fX0.append(self.__f(x0))
            fX1.append(self.__f(x1))
            fX2.append(self.__f(x2))
            if (abs(self.__f(x2)) < self.__e):
                Z = []
                Z.append(X0)
                Z.append(X1)
                Z.append(X2)
                Z.append(fX0)
                Z.append(fX1)
                Z.append(fX2)
                return Z
            
            else:
                if(self.__f(x2) < 0):
                    x0 = x2
                else:
                    x1 = x2


print("This program will find the root of x^2 - 25 = 0 using Bisection Method. For this it will use a range in which you want to find the root.")
while True:
    lr = float(input("Enter your lower limit of range:- "))
    ur = float(input("Enter your upper limit of range:- "))

    obj = solution(lr, ur)

    if(obj.check() == False):
        print("The root of the solution doesn't exist in the given range, try another range.")
    else:
        break

values = obj.root()

try:
    with open("C:/Users/lenovo/OneDrive/Desktop/Coding/SIES Python/Bisection Method/table_of_values.txt", "w") as file:
        count = 0
        file.write("{:^5} {:>10} {:>10} {:>10} {:>10} {:>10} {:>10}".format("Sr.no", "X0", "X1", "X2", "f(X0)", "f(X1)", "f(X2)"))
        file.write("\n")
        for i in range(0, len(values[0])):
            file.write(f"{count:>5} {values[0][i]:>10.4f} {values[1][i]:>10.4f} {values[2][i]:>10.4f} {values[3][i]:>10.4f} {values[4][i]:>10.4f} {values[5][i]:>10.4f}\n")
            count += 1

        file.write(f"\nRoot of the Equation x^2 - 25 = 0, in the range {lr} to {ur} is {values[2][len(values[2]) - 1]:.4f}")
except Exception as e:
    print("Error:", e)


print(f"Root of the Equation x^2 - 25 = 0, in the range {lr} to {ur} is {values[2][len(values[2]) - 1]:.4f}")

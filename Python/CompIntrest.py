class interest:
    def __init__(self, P, R, T):
        self.__p = P
        self.__roi = R
        self.__t = T

    def CI(self):
        price = self.__p
        for i in range(0, self.__t):
            price += (self.__roi/100)*price

        return price
            
    
print("This Program will find the compound interest after a certain years, for a particular Principle amount, and rate of interest per year.")
Principle = float(input("Enter the principle amount:- "))
roi = float(input("Enter the rate of interest in percentage per annum:- "))
time = int(input("Enter time in years:- "))

compound = interest(Principle, roi, time)

print(f"The amount of Rs.{Principle}/-, after {time} years will become Rs.{compound.CI():.4f}/- for the rate of interest of {roi} p.c.p.a.")

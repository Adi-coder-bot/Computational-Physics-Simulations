class Convert:
    def __init__(self, num):
        self.__val = num

    def DtoB(self):
        a = []
        N = self.__val
        while (N != 0):
            a.append(N % 2)
            N //= 2
        
        val = 0
        for i in range(0, len(a)):
            val += a[i]*pow(10, i)

        return val
    
    def BtoD(self):
        b = []
        M = self.__val
        while (M != 0):
            b.append(M % 10)
            M //= 10

        val = 0
        for i in range(0, len(b)):
            val += b[i]*pow(2, i)

        return val

    def IsBinary(self):
        c = []
        O = self.__val
        while (O != 0):
            c.append(O % 10)
            O //= 10

        d = [2, 3, 4, 5, 6, 7, 8, 9]
        for num in d:
            if num in c:
                return False

        else:
            return True



print("This Program will COnvert a Binary number to decimal and vice-versa.")
number = int(input("Enter the number:- "))

num = Convert(number)

if(num.IsBinary() == False):
    print("This is a Decimal number, its Binary equivaluent is", num.DtoB())
else:
    option = input("Enter which operation you want to perfrom(Enter 'B or b' to convert into Binary and 'D or d' to convert into Decimal):- ")
    if(option.lower() == 'b'):
        print("The Binary equivaluent of", number, "is", num.DtoB())
    elif(option.lower() == 'd'):
        print("The Decimal equivaluent of", number, "is", num.BtoD())
    else:
        print("Thankyou for using this program!")
        
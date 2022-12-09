def square(x):
    return x * x

def twoDigit(tens,ones):
    number = tens * 10 + ones
    return number

def report(number):
    message = "The square of that digit repeated is "
    message += str(square(number))
    message += "."
    print(message)
    return
    
def get():
    digit = int(input("Please enter a digit: "))
    return twoDigit(digit,digit)

value = get()
report(value)

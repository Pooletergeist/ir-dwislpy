def primesUpTo(number : int) :
    print(2)
    count : int = 2
    skip : bool = True
    while count <= number:
        if not skip and isPrime(number):
            print(count)
        count += 1
        skip = not skip
    return

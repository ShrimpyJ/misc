def largest_prime_factor(num):
    i = 0
    while num != 1 and i < num:
        i += 1
        if num % i == 0:
            num = num / i
    return num

num = 40000
arr = []
for i in range(num):
    ans = largest_prime_factor(i)
    arr.append(ans)

print(arr[32])

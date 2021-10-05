print("This is a fun program\nWe can skate, dance, or sing")
while True:
    getThing = raw_input("What fun thing do you want to do?\n")
    if getThing.lower() == "skate":
	    print("Let's skate away! Down Santa Monica today!")
    break
    elif getThing.lower() == "dance":
	    print("Let's dance!")
    break
    elif getThing.lower() == "sing":
	    print ("Do Re Mi Fa So La Ti Do")
    break
    else:
        print ("What was that? Try again.")

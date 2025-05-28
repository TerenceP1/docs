def attempt1(a,b):
    res=False
    for i in range(len(b)-len(a)+1):
        if b[i:i+len(a)] == a:
            res=True
    return res



#tests
if __name__ == "__main__":
    print("Test 1")
    while input("type 'q' to quit: ") != "q":
        try:
            if attempt1(input("\na:"),input("\nb:")) == bool(int(input("if True, type 1\nif False, type 0\n"))):
                print("Test passed☺!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
            else:
                print("test failed:(😞!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
        except ValueError as e:
            print(f"ValueError: {e}")

print("thanks for testing")
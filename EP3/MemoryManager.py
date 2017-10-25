

with open("trace.txt") as file:
    line = file.readline()
    words = line.split()

    total = words[0]
    virt = words[1]
    s = words[2]
    p = words[3]

    print total, virt, s, p, "\n"

    for line in file:
        words = line.split()
        t0 = int(words[0])
        tf = int(words[1])
        nome = words[2]
        b = int(words[3])
        print t0, tf, nome, b
        for i in xrange(4, len(words), 2):
            pi = int(words[i])
            ti = int(words[i+1])
            print pi, ti

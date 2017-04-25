allsquare = range(0, 81)
cols = [[9*j  + i for j in range(0,9)] for i in range(0, 9)]
lines = [[9*j  + i for i in range(0,9)] for j in range(0, 9)]
kongs = [[(k / 3 * 3 + g / 3 ) * 9 + k % 3 * 3 + g % 3 for g in range(0,9) ] for k in range(0,9)]

if(0):
    print "peers = {"
    for j in range(0,9):
        for i in range(0,9):
            print "{",
            peers = set()
            peers = peers | set(set(cols[i]) - set([cols[i][j]]))
            peers = peers | set(set(lines[j]) - set([lines[j][i]]))
            peers = peers | [set(k) - set([lines[j][i]])  for k in kongs if (lines[j][i] in k)][0]
            print ",".join(str(x) for x in peers),
            #print peers
            print "},"
    print "}"

if(1):
    print "units = {"
    for j in range(0,9):
        for i in range(0,9):
            unit = []
            print "{",
            print "{",
            print ",".join(str(x) for x in cols[i]),
            print "},{",
            print ",".join(str(x) for x in lines[j]),
            print "},{",
            print ",".join(str(x) for x in (k for k in kongs if lines[j][i] in k).next()),
            print "}",
            print "},"
    print "}"


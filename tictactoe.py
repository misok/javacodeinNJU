


b="".join(raw_input() for _ in range(3))
w=[[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]]

W=lambda x:any(all(b[v] == x for v in r) for r in w)

X = b.count("X")
O = b.count("O")

F = W("X")
S = W("O")

if not 0 <= X - O < 2 or F and S:
	print "illegal"
elif F:
	print ["the first player won","illegal"][X != O + 1]
elif S:
	print ['the second player won','illegal'][X != O]
elif X + O == 9:
	print 'draw'
else:
	print ['first','second'][X > O]


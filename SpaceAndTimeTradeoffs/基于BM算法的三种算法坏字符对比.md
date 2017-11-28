╔
0 1 2 3 4 5 6 7 8 9 ...
a	b	c	a	b	d	a	a	c	b	a
b	c	a	a	b	 	 	 	 	 	 
 	b	c	a	a	b
(a)   Boyer-Moore

0 1 2 3 4 5 6 7 8 9 ...
a	b	c	a	b	d	a	a	c	b	a
b	c	a	a	b	 	 	 	 	 	 
 	 	 	 	b	c	a	a	b	
(b)   Horspool

0 1 2 3 4 5 6 7 8 9 ...
a	b	c	a	b	d	a	a	c	b	a
b	c	a	a	b	 	 	 	 	 	 
 	 	 	 	 	 	b	c	a	a	b
(c)   Sunday
 	 	 	 	 
 
In this example, t0, ..., t4 =  a b c a b is the current text window that is compared with the pattern. Its suffix a b has matched, but the comparison c-a causes a mismatch. The bad-character heuristics of the Boyer-Moore algorithm (a) uses the "bad" text character c to determine the shift distance. The Horspool algorithm (b) uses the rightmost character b of the current text window. The Sunday algorithm (c) uses the character directly right of the text window, namely d in this example. Since d does not occur in the pattern at all, the pattern can be shifted past this position.
╝
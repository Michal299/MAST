# MAST
Console application implements an algorithm that reads a set of n rooted trees in the NEWICK format, and then for each pairs of trees reurn the minimum number of leaves whose removal from both trees will make them isomorphic.


Example of use
Enter number of trees and n tree in NEWICK format

*INPUT*
4					                                
(1,5,(10,6,3),(2,(8,7)),(9,4));
((7,(3,(4,9,(1,2)))),8,(5,(10,6)));  
(7,((6,(9,5),(8,3)),(1,(2,10,4))));  
(7,(8,3,4,6,1),(9,5,10),2);  

*OUTPUT*
5
7
6
6
6
6

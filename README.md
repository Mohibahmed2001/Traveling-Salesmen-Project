Mohib Ahmed 
Proj 3 Report
Nearest Neighbor and GreedyTSP

Num of Cities	Country	    Nearest N Distance	Nearest N Time(ms)	GreedyTSP Distance	GreedyTSP Time(ms)	Best Known Distance	Solution time
194	          Qatar	      10982.6	            43.5	              15321.1	            128.1	              9352	              2.09 secs
734	          Ururguay	  98358	              2073	              203001	            5554.1	            79114              	3507secs
980	          Luxembourg	14041	              4034	              16,342	            14051	              11344	              1681.secs
1979	        Oman	      114932	            35238.6	            103,023	            95600	              86891	              98029secs


So some of the biggest takeaways I had for this project was how efficient nearest neighbor is as well as how close it gets to the most optimal 
difference majority of the time. In a situation where you are in a time crunch, I believe nearest neighbor is a good outcome to pick. The only
big issue I have seen is that it relies heavily on the starting node which is very essential to how optimal the tour will end up becoming. As well 
as it doesn’t focus on global optimization. While what I noticed for greedyTSP is that it is overall efficient, but it is heavily reliant on the 
order that edges are considered resulting in its approximation in the way I implemented it to be not as close to the optimal solution as nearest neighbor
was. As well as my time efficiency was much slower. The coolest thing I learned about the TSP was how people attempted to code it optimally. As well as 
how quickly the time required becomes exponential such as for China in which it required 5 full days to find the optimal solution. Which shows how quicky
the computing can go from 1000 to 70000. It also illustrates issue of how we are limited in bigger data structures becomes when a problem become exponential 
to solve it becomes a NP problem. Overall I really enjoyed the project it help teached me a lot about graph algorithms.


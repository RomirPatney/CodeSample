# CodeSample

This is one of the QAP (quadratic assignment problem) test problems of Nugent et al.
20 departments are to be placed in 20 locations with five in each row (see below). The objective is to
minimize costs between the placed departments. The cost is (flow * rectilinear distance), where both flow
and distance are symmetric between any given pair of departments. The flow and distance matrices are
attached to this assignment. The optimal solution is 1285 (or 2570 if you double the flows)


A simple TS (TabuSearch) is used to solve the problem. To do this, the problem is encoded as a permutation,
a neighborhood and a move operator are defined, a tabu list size is set and a stopping criterion is selected. 
The default neighborhood function checks the whole neighborhood.

The following changes are implemented on the TS code (one by one)

- Change the initial starting point (initial solution) 10 times
- Change the tabu list size twice – once smaller and once larger than your original choice
- Change the tabu list size to a dynamic one – an easy way to do this is to choose a range and
	generate a random uniform integer between this range every so often (i.e., only change the tabu
	list size infrequently)
- Add 2 aspiration criteria in 2 separate experiments: best solution so far, best solution in the
neighborhood
- Use less than the whole neighborhood to select the next solution
- Add a frequency based tabu list to encourage the search to diversify


TabuSearch is an metaheuristic search algorithm
https://en.wikipedia.org/wiki/Tabu_search#:~:text=Tabu%20Search%20Vignettes.-,Basic%20description,limit%20or%20a%20score%20threshold).

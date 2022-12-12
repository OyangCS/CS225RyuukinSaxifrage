The algorithms we chose were BFS, Floyd-Warshall, and Betweenness Centrality. We were able to set up each
algorithm, though we ended using subsets of the dataset to run and test for some cases, especially Floyd-Warshall and Betweenness Centrality which does not work efficiently for the colossal size of the entire dataset. 

Although we said in our proposal that BFS and Floyd-Warshall would be used to construct the shortest path, BFS 
was the only one we use to achieve our project goal. By using a queue of vectors to record all possible paths to the destination, we then compared each possible path by the total distance traveled. The minimum distance traveled vector is returned as the output. The output, a vector of strings, represent the shortest path by containing the steps to travel in order. For our BFS tests, we looked at the graph and checked to see if the output represents a path that exists and if it compares against other possible paths.

Floyd-Warshall and Betweenness Centrality were the algorithms that we did not have great success with. Compared 
to BFS that we can run with the entire dataset though it can take a while, we learned that Floyd-Warshall and Betweenness Centrality are much less forgiving due to the vast size of our dataset. 

Floyd-Warshall constructs a matrix a number of times depending on the number of vertices. To help visualize the
problem, our directed graph has 3,199 vertices out of the dataset's 3321 airports, so Floyd-Warshall will need to adjust a matrix that is 3199x3199 in size 3199 times (the algorithm's O(n^3)). The number of vertices do not match up with the number of airports in the route dataset because some airports do not have any routes where they are the starting airport. In other words, they have no edges because it is a directed graph.  

For Betweenness centrality, we try our best to implement the most efficient algorithm as we can. The time complexity is O(VE) which is much more efficient than the previous implemented algorithm(the commented ones in graph.cpp and graph.h). However, it still goes for about 15 minutes for calculateBC() to proccess the whole data set which contains over 3000(3101 to be specific) airports in the undirected graph. Fortunately, in the end, we get the top five airports with highest betweenness centrality:

                                        Los Angeles International Airport with centrality: 814176
                                        Charles de Gaulle International Airport with centrality: 698667
                                        London Heathrow Airport with centrality: 605456
                                        Dubai International Airport with centrality: 559456
                                        Beijing Capital International Airport with centrality: 549351

We looked up these airports and found that they are indeed very busy and important airports in the world, which also shows the effectiveness of our code. Thus, with this program, we can get the busiest airports of a large database. If we have more time, we want to make it more efficient, or we might add a pretty progress bar to let users know they are not in infinite loop and they do wait for something.

Correctness of Betweenness centrality:
to check the correctness of betweenness centrality, we test it in a small scale, where we can make sure the true bc(betweenness centrality) of a node. If users run ./test, one of the test case is to calculate the graph below:
A - B - D - F
     \ / \ /
      C - E
    retrieved from https://blog.csdn.net/houzhizhen/article/details/109316236
we can make sure that:
bc of A : 0
bc of B : 8
bc of C : 2
bc of D : 7
bc of E : 1
bc of F : 0
and when we run our code, we get the same output. Thus, we can believe the correctness of our code.
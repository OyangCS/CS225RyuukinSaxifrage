The algorithms we chose were BFS, Floyd-Warshall, and Betweenness Centrality. We were able to set up each
algorithm, though we ended using subsets of the dataset to run and test for some cases, especially Floyd-Warshall and Betweenness Centrality which does not work efficiently for the colossal size of the entire dataset. 

Although we said in our proposal that BFS and Floyd-Warshall would be used to construct the shortest path, BFS 
was the only one we use to achieve our project goal. By using a queue of vectors to record all possible paths to the destination, we then compared each possible path by the total distance traveled. The minimum distance traveled vector is returned as the output. The output, a vector of strings, represent the shortest path by containing the steps to travel in order. For our BFS tests, we looked at the graph and checked to see if the output represents a path that exists and if it compares against other possible paths.

Floyd-Warshall and Betweenness Centrality were the algorithms that we did not have great success with. Compared 
to BFS that we can run with the entire dataset though it can take a while, we learned that Floyd-Warshall and Betweenness Centrality are much less forgiving due to the vast size of our dataset. 

Floyd-Warshall constructs a matrix a number of times depending on the number of vertices. To help visualize the
problem, our directed graph has 3,199 vertices out of the dataset's 3321 airports, so Floyd-Warshall will need to adjust a matrix that is 3199x3199 in size 3199 times. The number of vertices do not match up with the number of airports in the route dataset because some airports do not have any routes where they are the starting airport. In other words, they have no edges because it is a directed graph.  

Talk About Betweenness Centrality Here
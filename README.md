# CS225RyuukinSaxifrage

# Team Contract

## Communication
1. **Team Meetings** 
We will try to meet at least once a week. This meeting can be in person or over zoom. The length of the meeting will vary depending on how much each member needs to report on their progress. During this meeting, we will also talk about our next tasks and split these tasks. After the meeting, we will post the next task for each member in the group chat as a reminder, for which we will use WeChat for this. 

2. **Assistance** 
We will mostly communicate through WeChat. We are aware that each of us may have unforeseen problems and things to take care of, so we do not expect each of us to respond very quickly. We will give 24 hours of time for a response if the matter of discussion is not urgent. 

3. **Respect** 
To facilitate meetings, we will give each team member an opportunity to speak. After all, we do want a report on our progress and completion of tasks. Every group member’s suggestions will be respected and taken into consideration. We were acquainted with each other before the creation of this group, so we do not believe that many problems will arise during meetings. 

## Collaboration

4. **Work Distribution** 
During team meetings or through our group chat, we will talk about what is up next to be done and split these tasks. Each team member will be allowed to pick the task that they want to do, so the tasks can accommodate their strengths and desires. Depending on the perceived difficulty of each task, certain tasks might be assigned to be worked together by more than one person. If unforeseen complications appear and a member is unable to finish their assigned task, we will see if another member is available to finish the task. If not, our only choice will most likely be to delay the task. 

5. **Time Commitment** 
As we said in work distribution, harder tasks will be completed together rather than being delegated to a single member. This not only helps us make progress but also eases each member’s time commitment per week. Members are expected to attend meetings and group discussions. That being said, outside of time spent on meetings and discussions, members should devote at least 1-2 hours per week to the project. We will address and resolve problems through our group chat.   

6. **Conflict Resolution** 
Disagreement will be resolved by discussion and communication. All conflicts should be resolved quickly as it happens. We encourage each other to ask for help or clarification in the group chat. The situation that one is habitually late or absent will be reported to the mentor, but we will first try to ask them to explain the situation and try to solve it ourselves. 

## Signatures
Qinghuai Yao (qyao6) 
Yuhao Cheng (yuhaoc7) 
Owen Yang (oweny2)

# Project Proposal 

## Leading Question 
For our project, we will be using the OpenFlights dataset to develop an algorithm to find the shortest path between two airports. Within the OpenFlights dataset, we will be using the routes and airport datasets. The routes dataset gives us the information for the edges of the graphs and in our case, the paths between two airports/vertices. For the algorithms to find the shortest path, we will use BFS and Floyd-Warshall. As per the instructions for the project, we will read the data and convert it into a directed graph, where the airports are the vertices and the routes are the edges. We believe that distance is the best factor to use for the weights of the graph. This is where we will use the airport dataset to calculate the distance by treating longitude/latitude as XY coordinates. If this conversion does not work, we will find another method. To ease up storage, we will ignore certain aspects that are not necessary to our implementations, such as altitude, timezone, equipment, and codeshare. For the third algorithm of our project, we selected the betweenness centrality algorithm, which does not completely relate to our goal. 

## Dataset Acquisition

## Data Format
The dataset we are using is from OpenFights. More specifically, the airport and route data from OpenFlights. The input format of the dataset involves separate entries for each airport/route, where the aspects of each airport/route are split by commas (CSV files). Currently, we believe that it is best to utilize all of the necessary parts of each data file. If we exclude certain airports or routes, we will be creating an imperfect version, which is not what we want. 

## Data Correction
We have experience reading CSV files and inputting the information into data structures. To test that the data is correctly read, we can print out the information for a few entries or create test cases. For our project, values that are invalid can be a nonexistent airport/destination/starting point (for instance, the arguments for the shortest path can be a starting airport and a destination airport). We will also need to consider cases that involve some form of a tie; in other words, implementing a tie-breaker. 

## Data Storage
As of right now, we see ourselves creating a class and a struct within that class similar to the design of some previous assignments. This struct will be a node/airport struct, containing data for a specific airport and representing the vertices of the graph. It will also contain a vector of neighboring nodes to represent edges/routes. The class itself will have a data structure to contain all of these nodes, which would be the starting points of routes. Considering that our node format is similar to an adjacency list, the estimate of the total storage is (at least) O(n+m), where n is the number of airports/vertices and m is the number of routes/edges.

## Algorithm
We are working with a directed graph (assuming that each flight is one-way and not round-trips unless stated otherwise), so we do need to convert the CSV file to a directed graph. We mentioned the layout of this graph above. Our primary goal is to find the shortest path, so inputs can be two arguments: the starting place and destination. As for Betweenness Centrality, we are not sure about the input as it finds the airport that is involved the most in the set of shortest paths. We currently understand this algorithm to give the same output regardless of input. 
    For the shortest path, the output can be stored in an array/vector of visited airports, similar to the
    solveMaze function from MP Mazes. As for Betweenness Centrality, it will most likely return a data
    structure of nodes/airports indicating its influence/importance in the directed graph. 

## Timeline
Our first few tasks are straightforward; we need to read the dataset and convert it into a directed graph. From there, we will design the algorithms. We may work on the proposed algorithms together instead of splitting the work. For the order of algorithms to be completed, BFS will most likely be our first choice because we are familiar with it. Next, we will focus on the Floyd-Warshall algorithm; this algorithm answers our leading question. Lastly, we will work on the betweenness centrality algorithm. It is important to complete our primary goal before working on something that can be considered secondary, such as betweenness centrality. 

# Logic-Circuit-Evaluator

Main idea is to first parse all the nodes into the Node struct and store array of all these nodes

Have 2^(number of inputs) loops 
Before the loop have a function that takes in number of input nodes and then outputs a array of every possible combination
Then in the loop you first set the input values
Then 

In each loop set the input val to every combination possible, and add it to the hashmap by id and val
Then iterate through the array of nodes you have and anytime you have a node with no val, check if all its inputs have something in hashmap and if so then calculate its val based on type and store in hashtable, have a function for each that given the array of inputs it will call the hashmap and return the val

Once this loop is done print out the line from the Node array, probably add the vals as instances to the Node struct



some specifics in how I implement the function: 
    if type is input skip
    for every node in nodes[j].input check if the inputs val is not -1 in val
    if one of them is -1 in val continue to next iteration
    if both of the inputs val is not -1, then evaluate and store in val
    count how many times continue is done, if it is 0, then exit and you print output



My program consists of three files, bayes.h, bayes.cpp and Makefile.

bayes.h:
It defines a Bayes class which has the implementaions of
1. Bayes Theorem that calculates Pr(object | adjectives) (Bayes Formula: P(F|E) = P(E|F)*P(F)/(P(E|F)*P(F) + P(E|~F)*P(~F)))
2. the calculation of Pr(adjective | object) which is needed by 1
3. the calculation of Pr(object) which is needed by 1
4. a training method to intake an object and its adjectives and train itself with the data
5. a classify method to classify a set of adjectives to an object

bayes.cpp:
It defines the main function that will 
1. create a Bayes instance
2. parse in a training data file and input the data to the Bayes instance for training
3. parse in a classify data file whose data needs classificaiton
4. call Bayes instance's method to classify each line of the classify file
5. output result to an output file

To run my program:
1. Put all three files under the same directory
2. Run `make`
3. Run `./bayes <train file path> <classify file path> <output file path>`
4. Run with memory check `valgrind --tool=memcheck --leak-check=yes ./bayes <train file path> <classify file path> <output file path>`
5. The results will be stored in the designated output file

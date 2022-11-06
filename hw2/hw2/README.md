In this project, I implemented a new simple Amazon store that let users to search 
products, add products to cart, and check out cart.

The files I created in addition to the skeleton code are book.h, book.cpp, clothing.h,
clothing.cpp, movie.h, movie.cpp, mydatastore.h, mydatastore.cpp

The way to complie and run my program is:
1. Put all files including Makefile under the same directory
2. run 'make clean'
3. run 'make'
4. run './amazon <the datastore file you want>'

notes:
1. I assumed when cart is empty, we wouldn't show anything to user. So when you do VIEWCART on empty cart, nothing will be printed.
2. I assumed when if an user tries to add a hit to their cart with a non-existant index, we would consider it an invalid request and show user an error message "Invalid request". For example, there were 3 hits with in the last search (with indices 1, 2, 3), if user input ADD <username> 4, my program will show user "Invalid request".
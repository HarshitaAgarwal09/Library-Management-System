# Library-Management-System
<b>Pre-requisites: </b>basic C++, file management in C++, Object Oriented Programming.

In comparison to other library management softwares avaiable in the market, this software has many unique abilities due to which is stands unique among others. Before diving inside the methods used in the software, it is crucial to know about the two major objects used tremendously by different functionalities inside the software.

<b>Book</b>: A Book object represents a real life book with the following attributes: Title, Author name, Number of copies owned by the library and the number of copies currently present inside the library for issue.

<b>Student</b>: A student object is the virtualisation of a physical library student having the following attributes: Roll Number, Number of books issued to the student and the details regarding the time of issue, date of issue and the title of book issued, all these details are packed together in form of an structure object <i>IshDetails</i>.

Both of the above objects and the structure object <i>IshDetails</i> can be found in [class.h](class.h).

Now follows a brief introduction of varios methods used in the software.

<b>AddBook()</b>: Adds a single book into the book database of the library. After reading the title of the book to be uploaded the function smartly checks for any pre-existance of the book, if the book already exists in the database, only number of copies of the book is incremented. The function requires <b>O(log(N))</b> time in case book already exists (<i>using binary search</i>), and <b>log(N)</b> time in case its a new book. Here N is the total number of books present in the database of books.

<b>searchBook()</b>: Searches for a book in the book database using the title of the book. The function requires <b>O(log(N)></b> time for its job (<i>using binary search</i>).

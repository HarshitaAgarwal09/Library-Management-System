# Library-Management-System
<b>Pre-requisites: </b>basic C++, file management in C++, Object Oriented Programming.

In comparison to other library management softwares avaiable in the market, this software has many unique abilities due to which is stands unique among others. Before diving inside the methods used in the software, it is crucial to know about the two major objects used tremendously by different functionalities inside the software.

<b>Book</b>: A Book object represents a real life book with the following attributes: Title, Author name, Number of copies owned by the library and the number of copies currently present inside the library for issue.

<b>Student</b>: A student object is the virtualisation of a physical library student having the following attributes: Roll Number, Number of books issued to the student and the details regarding the time of issue, date of issue and the title of book issued, all these details are packed together in form of an structure object <i>IshDetails</i>.

Both of the above objects and the structure object <i>IshDetails</i> can be found in [class.h](class.h).

Now follows a brief introduction of varios methods used in the software.
(<i>in the following time considerations N represents the total number of students/books present in the respective database</i>)

<b>AddBook()</b>: Adds a single book into the book database of the library. After reading the title of the book to be uploaded the function smartly checks for any pre-existance of the book, if the book already exists in the database, only number of copies of the book is incremented. The function requires <b>O(log(N))</b> time in case book already exists (<i>using binary search</i>), and <b>log(N)</b> time in case its a new book.

<b>searchBook()</b>: Searches for a book in the book database using the title of the book. The function requires <b>O(log(N)</b> time for its job (<i>using binary search</i>).

<b>viewBooks()</b>: If database of books exists (<i>books.txt</i>), it simply prints the complete database of the books in <b>O(N)</b> time. Otherwise, an error message is shown. 

<b>UploadBooks()</b>: Uploads multiple books (<i>say M</i>) at once, into the book database. The list of books to be uploaded is to be provided (<i>not necessarily sorted</i>) in <i>bookdata.txt</b> in [this](howToUploadBooks.txt) format. Make sure not to repeat any book in <i>bookdata.txt</i> as it will corrupt the book database. For faster processing the list of books is converted into a vector object, hence, the maximum number of books which can be uploaded at once will depend on your machine. This vector object is then sorted on the basis of book titles in <b>O(log(M))</b> time (<i>using quicksort</i>) and is then merged with the book database in <b>O(N + M)</b> time.



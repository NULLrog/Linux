#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
struct Books {
   char  title[50];
   char  author[50];
   int   book_id;
};
void printBook( struct Books *book ) {
   printf( "Book title : %s\n", book->title);
   printf( "Book author : %s\n", book->author);
   printf( "Book book_id : %d\n", book->book_id);
}

void readBook( struct Books *book ) {
   printf( "Book title :");
   scanf( "%s", book->title);
   printf( "Book author : ");
   scanf( "%s", book->author);
   printf( "Book book_id : ");
   scanf( "%d", &book->book_id);
}

int main( ) {
   struct Books *book = malloc(sizeof(struct Books)); 
   readBook( book );
   printBook( book );
   free(book);
   return 0;
}


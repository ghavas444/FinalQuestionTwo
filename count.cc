#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdarg.h>

using namespace std;


typedef unsigned long count_t;  /* Counter type */

/* Current file counters: chars, words, lines */
count_t ccount;
count_t wcount;
count_t lcount;

/* Totals counters: chars, words, lines */
count_t total_ccount = 0;
count_t total_wcount = 0;
count_t total_lcount = 0;

/* Print error message and exit with error status. If PERR is not 0,
   display current errno status. */
static void
error_print (int perr, const char *fmt, va_list ap)
{
  vfprintf (stderr, fmt, ap);
  if (perr)
    perror (" ");
  else
    fprintf (stderr, "\n");
  exit (1);  
}

/* Print error message and exit with error status. */
static void
errf (const char *fmt, ...)
{
  va_list ap;
  
  va_start (ap, fmt);
  error_print (0, fmt, ap);
  va_end (ap);
}

/* Print error message followed by errno status and exit
   with error code. */
static void
perrf (const char *fmt, ...)
{
  va_list ap;
  
  va_start (ap, fmt);
  error_print (1, fmt, ap);
  va_end (ap);
}

/* Output counters for given file */
void
report (const char *file, count_t ccount, count_t wcount, count_t lcount)
{
  printf ("%6lu %6lu %6lu %s\n", lcount, wcount, ccount, file);
}

/* Return true if C is a valid word constituent */
static int
isword (unsigned char c)
{
  return isalpha (c);
}

/* Increase character and, if necessary, line counters */
#define COUNT(c)       \
      ccount++;        \
      if ((c) == '\n') \
        lcount++;

/* Get next word from the input stream. Return 0 on end
   of file or error condition. Return 1 otherwise. */
int
getword (FILE *fp)
{
  int c;
  int word = 0;
  
  if (feof (fp))
    return 0;
      
  while ((c = getc (fp)) != EOF)
    {
      if (isword (c))
        {
          wcount++;
          break;
        }
      COUNT (c);
    }

  for (; c != EOF; c = getc (fp))
    {
      COUNT (c);
      if (!isword (c))
        break;
    }

  return c != EOF;
}
      
/* Process file FILE. */
unsigned long
counter (const char *file)
{
  FILE *fp = fopen (file, "r");
  
  if (!fp)
    perrf ("cannot open file `%s'", file);

  ccount = wcount = lcount = 0;
  while (getword (fp))
    ;
  fclose (fp);

  report (file, ccount, wcount, lcount);
  total_ccount += ccount;
  total_wcount += wcount;
  total_lcount += lcount;
  return ccount;
}

/*
*   @brief: Counts the number of lines in a given string
*   @param: entry - the string entered to be analyzed
*   @return: Returns an integer which represents the number
*       of lines in the string
*/
int countLine(string entry);

/*
*   @brief: Counts the number of characters in a given string
*   @param: entry - the string entered to be analyzed
*   @return: Returns an integer which represents the number
*       of characters in the string
*/
int countChar(string entry);

/*
*   @brief: Main function which executes the functions above and below
*   @param: argc - the number of command line arguments
*           argv - hold the command line arguments
*   @return: returns 0 when done
*/
int main(int argc, char **argv)
{

    int i;
  
    if (argc < 2)
        errf ("usage: wc FILE [FILE...]");
    
    for (i = 1; i < argc; i++)
        counter (argv[i]);
    
    if (argc > 2)
        report ("total", total_ccount, total_wcount, total_lcount);

    string test = "Ohio University";
    string testTwo = "Athens";

    int line = countLine(test);
    int character = countChar(test);

    cout<<line<<" Lines"<<endl;
    cout<<character<<" Characters"<<endl;

    return 0;
}

int countLine(string entry)
{
    int count = 0;
    int size = entry.length();

    for(int i = 0; i < size; i++)
    {
        if(entry[i] == '\n')
        {
            count++;
        }
    }
    return count;
}

int countChar(string entry)
{
    int n = entry.length();
    return n;
}
// This program updates a date and time structure by one second

#include <stdio.h>
#include <stdbool.h>

// Define Structures
struct sdate {
int day;
int month;
int year;
};

struct stime {
int seconds;
int minutes;
int hours;
};

struct dateAndTime {
struct sdate date;
struct stime time;
};

// Declare Functions
struct sdate getDate (void);
struct stime getTime (void);
struct dateAndTime getDateAndTime (void);

bool isLeapYear(int);
bool updateTime (struct stime*);
void updateDate (struct sdate*);
struct dateAndTime updateDateAndTime (struct dateAndTime);


void printDate (struct sdate);
void printTime (struct stime);
void printDateAndTime (struct dateAndTime);





int main(void) {
  
  // Initialize today
  struct dateAndTime today = getDateAndTime ();

  // Update by one second
  today = updateDateAndTime (today);

  // Print new date and time
  printDateAndTime (today);
  
  return 0;
}





struct sdate getDate (void) {
  struct sdate output;
  
  printf ("Enter date mm/dd/yyyy: ");
  scanf ("%d/%d/%d", &output.month, &output.day, &output.year);

  return output;
}

struct stime getTime (void) {
  struct stime output;
  
  printf ("Enter time ss:mm:hh: ");
  scanf ("%d:%d:%d", &output.seconds, &output.minutes, &output.hours);

  return output;
}

struct dateAndTime getDateAndTime (void) {
  struct dateAndTime output;

  output.date = getDate ();
  output.time = getTime ();

  return output;
}

bool isLeapYear(int year) {
  if ((year % 4 == 0 && year %100 != 0) || year % 400 == 0)
    return true;
  else 
    return false;
}

bool updateTime (struct stime* input) {
  bool overflow = false;

  input->seconds++;
  if (input->seconds == 60) {
    input->seconds = 0;
    input->minutes++;
    if (input->minutes == 60) {
      input->minutes = 0;
      input->hours++;
      if (input->hours == 24) {
        input->hours = 0;
        overflow = true;
      }
    }
  }
  
  return overflow;
}

void updateDate (struct sdate* input) {
  int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  if (isLeapYear(input->year)) {
    daysPerMonth[2] = 29;
  }

  if (input->day != daysPerMonth[input->month - 1]) {
    input->day++;
  }
  else if (input->month == 12) {
    input->day = 1;
    input->month = 1;
    input->year++;
  }
  else {
    input->day = 1;
    input->month++;
  }
}


struct dateAndTime updateDateAndTime (struct dateAndTime input) {
  if (updateTime (&input.time)) {
    updateDate (&input.date);
  }
  return input;  
}

void printDate (struct sdate input) {
  printf ("%.2d/%.2d/%.4d", input.month, input.day, input.year);
}

void printTime (struct stime input) {
  printf ("%.2d:%.2d:%.2d", input.seconds, input.minutes, input.hours);
}

void printDateAndTime (struct dateAndTime input) {
  printf ("Date and time is: ");
  printDate (input.date);
  printf ("  ");
  printTime (input.time);
  printf ("\n");
}
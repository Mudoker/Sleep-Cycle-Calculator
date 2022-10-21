#include <iostream> // inputs & outputs
#include <string.h> // string functions
#include <string> // string functions
#include <math.h> // rounding number
#include <unistd.h> // Delaying the program
#include <time.h> // take current time as string
#include <iomanip> // input and output manipulator
using namespace std;

// Prototypes

// Commands from user
string command {};

// Store time in hour and minute
string current_time[3] {};

// Dealing with current time
void time(void) ;

// Convert time to double - form
double time_to_double(string current_time[3]);

// Showing intro
void intro (void);

// Functions
void sleep_now();
void sleep_at(); 
void wake_up();

// exit program
void program_exit(); 


int main ()
{
    // Show intro
    intro();
    cout << ">> ";
    cin >> command;

    // Infinite loop
    while (true) {

        // Show info of the program
        if (command == "info") {
            intro();
            cout << ">> ";
            cin >> command;
        }

        // Program Functions
        else if (command == "1") {
            wake_up();
            cout << ">> ";
            cin >> command;
        }
        else if (command == "2") {
            sleep_at();
            cout << ">> ";
            cin >> command;
        }
        else if (command == "3") {
            sleep_now();
            cout << ">> ";
            cin >> command;
        }

        // exit program
        else if (command == "exit") {
            program_exit();
            return 0;
        }

        // invalid command
        else {
            cout << "Invalid command! Try again. \n";
            cout << ">> ";
            cin >> command;
        }
    }
    return 0;
}

void intro (void) {
    std::cout << R"(                                                                                             __________________________________________________________
                       .-'`/                                                                //Sleep Cycle Calculator: A brief guide to a healthy life!\\ 
                   .-'`  _/                                                                ||                                _-Powered by Quoc Doan-_  ||
               .-'`    _/                                                                  \\__________________________________________________________//  
            .-'       /                                                                     Program's Menu:
         .-'         /                                                                      1. Type '1': I want to wake up at......................................................
       .'           (                                                                       2. Type '2': I will sleep at...........................................................
     .'       ,,////)                                                                       3. Type '3': Sleep now.................................................................
    .         __,-^/                                                                        4. Type 'exit' to exit the program.....................................................
   .           \()(                                                                         5. Type 'info' to see the program information..........................................
   :               \                                                                        
   :             _  \ 
   :            (____\  __________________________________
   :              (    /                                  \ 
   `          )-.__) -    Be oi ngu di, dem da khuya roi...|
    `              )   \__________________________________/                                    
     `.           (
       `.          \ 
         `-.        \
            `-.      \_
               `'-.    \_
cjr                `'-.  \_
17apr00                `'-.\      image's source: https://www.asciiart.eu/space/moons
)" << '\n';
}


void time_input() {
    // check for valid datatype (integer input)
    while (true) {
        cout << "Enter hour (between 0 - 24): ";
        cin >> current_time[0]; 
        // stoi will throw an exception if failed
        try {
            int tmp = stoi (current_time[0]);
            while (tmp < 0 || tmp > 24) {
                cout << "Hour should be in between 0-24!: ";
                cin >> current_time[0]; 
                tmp = stoi (current_time[0]);
            }
            break;
        }
        // catch the throw and continue to loop
        catch (...) {
            cout << "Invalid Input!" << endl;
            continue;
        }
    }

    // Check for valid datatype
    while (true) {
        cout << "Enter minute (between 0 - 59): ";
        cin >> current_time[1]; 
        try {
            int tmp = stoi (current_time[1]);
            while (tmp < 0 || tmp > 59) {
                cout << "Minute should be in between 0-59: ";
                cin >> current_time[1]; 
                tmp = stoi (current_time[1]);
            }
            break;
        }
        catch (...) {
            cout << "Invalid Input!" << endl;
            continue;
        }
    }

    
}

void time (void) {
    // time variable
    time_t raw_time;


    struct tm * time_info;

    // Current hour
    char hour[3];

    // Current minute
    char minute[3];

    // Current time
    time (&raw_time);

    // Current time
    time_info = localtime (&raw_time);

    // assign current hour to hour-array
    // %H store hour in 24h format
    strftime (hour,3,"%H",time_info);

    // assign current minute to minute-array
    strftime (minute,3,"%M",time_info);

    // Assign value to current time variable
    current_time[0] = hour;
    current_time[1] = minute;
}

double time_to_double (string current_time[3]) {
    double time_double = stoi(current_time[0]) + (stoi (current_time[1]))/ 60.0;
    return time_double;
}

// Print out time with format
void print_time(int i, double tmp) {
    cout << i + 1 << " Sleep Cycle: " << floor(tmp) << ":";
    int temp = (tmp - floor(tmp)) * 60;

    // Print time with 0 preceding or following 
    if (temp == 0) {
        cout << '0' << temp;
    }
    else if (temp < 10) {
        cout << '0' << temp;
    }
    else {
        cout << temp;
    }
    cout << endl;
}


void sleep_now() {

    // find current time
    time();

    // convert current time to double form
    double tmp = time_to_double(current_time);

    // interfaces
    cout << "By Sleeping now, you should wake up at.... \n";
    for (int i = 0; i < 6; i++) {

        // adding tmp by 1.5 hours
        tmp = tmp + 1.5;

        // if tmp > 24 then tmp go back to 0 as indication for a new day
        if (tmp > 24) {
            tmp = tmp - 24;
        }
        print_time(i,tmp);
    }
    // Notes
    cout << "'Please keep in mind that you should be waking up at these times. The average human takes fourteen minutes to wake up, so plan accordingly!' - SLEEPOPOLIS" << endl;
}


void sleep_at() {
    time_input();

    // Convert time to decimal form
    double tmp = time_to_double(current_time);

    // print minute with double 0 when needed
    if (stoi(current_time[0]) < 10) {
        current_time[0] = "0" + current_time[0];
    }
    if (stoi(current_time[1]) < 10) {
        current_time[1] = "0" + current_time[1];
    }
    cout << "By Sleeping at " << current_time[0] << ":" << current_time[1] << ", you should wake up at.... \n";

    for (int i = 0; i < 6; i++) {
        // still wake up at this time
        tmp = tmp + 1.5;
        if (tmp > 24) {
            tmp = tmp - 24;
        }
        print_time(i,tmp);
    }
    cout << "'Please keep in mind that you should be waking up at these times. The average human takes fourteen minutes to wake up, so plan accordingly!' - SLEEPOPOLIS" << endl;
}

void wake_up() {
    time_input();

    // convert time to decimal form
    double tmp = time_to_double(current_time);

    // print minute with double 0 when needed
    if (stoi(current_time[0]) < 10) {
        current_time[0] = "0" + current_time[0];
    }
    if (stoi(current_time[1]) < 10) {
        current_time[1] = "0" + current_time[1];
    }

    cout << "Try the following bedtime to wake up at " << current_time[0] << ":" << current_time[1] << endl;

    for (int i = 0; i < 6; i++) {
        tmp = tmp - 1.5;
        if (tmp < 0) {
            tmp = tmp + 24;
        }
        print_time(i,tmp);
    }
    cout << "'Please keep in mind that you should be waking up at these times. The average human takes fourteen minutes to wake up, so plan accordingly!' - SLEEPOPOLIS" << endl;

}

// exit program
void program_exit() {
    // This process is delayed on purpose to make it seems cooler

    cout << "Ending Program.....\n";
    cout << "..";

    // delay for 1 second
    sleep(1);
    cout << "....";

    // delay for 1 second
    sleep(1);
    cout << ".......................................\n";
    cout << "Program ended.....!" << endl;
}
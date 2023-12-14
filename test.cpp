// Übung 2
# include <iostream>
# include <unistd.h>

using namespace std;

int main() {
    cout << "Das ist der Beginn vom Prozess." << endl;
    execl("/bin/date", "date", nullptr); // Use nullptr as a sentinel value
    cout << "Das ist der Rest vom Prozess." << endl;
    exit(0);
}

// anderer Befehl, LS als Beispiel

#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    cout << "Das ist der Beginn vom Prozess." << endl;

    // Try to execute the "ls" command
    if (execl("/bin/ls", "ls", nullptr) == -1) {
        // If execl fails, print an error message
        perror("execl failed");
    }

    // This code will only be reached if execl fails
    cout << "Das ist der Rest vom Prozess." << endl;
    exit(0);
}



//Verweister Prozess
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t childPid = fork();

    if (childPid == 0) {
        // Child process
        cout << "Child process (PID: " << getpid() << ") created." << endl;
        sleep(2);
        cout << "Child process exiting." << endl;
    } else if (childPid > 0) {
        // Parent process
        cout << "Parent process (PID: " << getpid() << ") created." << endl;
        cout << "Parent process waiting for 5 seconds..." << endl;
        sleep(5);
        cout << "Parent process exiting." << endl;
    } else {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    return 0;
}




// 	Parent Prozess herausfinden - ps -p pid

// # Find the parent process ID of the C++ program
// ps -p <pid> -o ppid

// Replace <pid> with the actual process ID of the C++ program. You can obtain the process ID from the output of the program or by checking with the ps command.

// Keep in mind that the parent process ID may be displayed as 1 if the orphan process is adopted by the init process (with PID 1) after its original parent exits.




// --- verweisten Prozess verhindern (wait)

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t childPid = fork();

    if (childPid == 0) {
        // Child process
        cout << "Child process (PID: " << getpid() << ") created." << endl;
        sleep(2);
        cout << "Child process exiting." << endl;
    } else if (childPid > 0) {
        // Parent process
        cout << "Parent process (PID: " << getpid() << ") created." << endl;

        // Wait for the child to exit
        int status;
        pid_t terminatedChild = waitpid(childPid, &status, 0);

        if (terminatedChild == -1) {
            cerr << "Error waiting for child process." << endl;
            return 1;
        }

        cout << "Parent process exiting." << endl;
    } else {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    return 0;
}


//-------------------Zombie Prozess

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t childPid = fork();

    if (childPid == 0) {
        // Child process
        cout << "Child process (PID: " << getpid() << ") created." << endl;
        // Child process does some work and then exits
        sleep(5);
        cout << "Child process exiting." << endl;
    } else if (childPid > 0) {
        // Parent process
        cout << "Parent process (PID: " << getpid() << ") created." << endl;
        // Parent process exits immediately without waiting for the child
        exit(0);
    } else {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    return 0;
}



// To observe the zombie process, you can run the program and then use tools like ps or top in the terminal. For example:


# Check the process status using ps
ps aux | grep zombie_process


alternativ: tcgetpgrp

//-----------Signal abfangen

#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

// Function to handle the Ctrl+C signal
void signalHandler(int signum) {
    cout << "Ctrl+C received. Exiting gracefully." << endl;
    exit(signum);
}

int main() {
    // Register the signal handler for SIGINT
    signal(SIGINT, signalHandler);

    for (int i = 0; i < 10; i++) {
        cout << "Berechnung wird durchgeführt..." << endl;
        sleep(1);
    }

    return 0;
}

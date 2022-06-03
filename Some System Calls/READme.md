# Types of System Calls

- System calls can be grouped into five major categories:
    - Process Control
    - File Manipulation
    - Device Management
    - Information Maintenance
    - Communications

    ## Process Control

        - End, abort
        - Load, execute
        - Create process, terminate process
        - Get process attributes, set process attributes
        - Wait for time
        - Wait event, signal event
        - Allocate and free memory

    ## File Manipulation

        - Create file, delete file
        - Open, close
        - Read, write, reposition
        - Get file attributes, set file attributes 

    ## Device Management

        - Request device, release device
        - Read, write, reposition
        - Get device attributes, set device attributes
        - Logically attach or detach devices

    ## Information Maintenance

        - Get time or date, set time or date
        - Get system data, set system data
        - Get process, file, or device attributes
        - Set process, file, or device attributes

    ## Communications

        - Create, delete communication connection
        - Send, receive messages
        - Transfer status information
        - Attach or detach remote devices

# Métodos

**creat()**, **open()**, **close()** -> *Managing I/O channels*

**read()**. **write()** -> *Handling input and output operations*

**exec()**, **fork()**, **wait()**, **exit()** -> *For process control*

**getuid()** -> *For process ownership*

**getpid()** -> *For process ID*

**time()**, **gettimer(**), **settimer()**, **settimeofday()**, **alarm()** -> *Time management functions*

**pipe()** -> *For creating inter-process communication*

- `#include <sys/stat.h>` -> Provides the following constants that can be used to set permissions
    - **S_IREAD**  --- *Read permission for the owner*
    - **S_IWRITE** --- *Read permission for the owner* 
    - **S_IEXEC**  --- *Execute/Search permission for the owner*
    - **S_IRWXU**  --- *Read, Write, Execute permission for the owner*

    - **S_IRGRP**  --- *Read for group*
    - **S_IWGRP**  --- *Write for group*
    - **S_IXGRP**  --- *Execute for group*
    - **S_IRWXG**  --- *Read, Write, Execute for the group*

    - **S_IROTH**  --- *Read for others*
    - **S_IWOTH**  --- *Write for others*
    - **S_IXOTH**  --- *Execute for others*
    - **S_IRWXO**  --- *Read, Write, Execute for others*

    >`creat("myfile", S_IREAD | S_IWRITE)` - Creates a files with read and write permissions only to user

- `Open System call` -> **int open(char* filename, int flags, int mode)*
    - The flags are:
        - **O_RDONLY** --- *Opens file for read only*
        - **O_WRONLY** --- *Opens file for write only*
        - **O_RDWR**   --- *Opens file for reading and writing*
        - **O_NDELAY** --- *Prevents possible blocking*
        - **O_APPEND** --- *Opens the file for appending*
        - **O_CREAT**  --- *Creates the file if it does not exists*       
        - **O_TRUNC**  --- *Truncates the size to zero*       
        - **O_EXCL**   --- *Produces an error if the O_CREAT bit is on and file exists*   

        >`open("filename", O_RDONLY | O_TRUNC, 0)` - Open a file for read and truncates the size to zero  
 
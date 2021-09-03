#include <sys/types.h>
#include <dirent.h>
// #include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Helper function to check if a struct dirent from /proc is a PID folder.
struct Answer
{
    int pid;
    char processName[100];
    long unsigned uTime;
    long unsigned xTime;
    
};
int is_pid_folder(const struct dirent *entry) {
    const char *p;

    for (p = entry->d_name; *p; p++) {
        if (!isdigit(*p))
            return 0;
    }

    return 1;
}

int main(void) {
    printf("JJI1");
    DIR *procdir;
    FILE *fp;
    struct dirent *entry;
    char path[256 + 5 + 5]; // d_name + /proc + /stat
    int pid;
    unsigned long maj_faults;
    unsigned long u_time;
    unsigned long s_time;
    int N = 10;
    int counter=0;
    struct Answer ans[10000];

    // Open /proc directory.
    procdir = opendir("/proc");
    if (!procdir) {
        perror("opendir failed");
        return 1;
    }

    // Iterate through all files and folders of /proc.
    while ((entry = readdir(procdir))) {
        // Skip anything that is not a PID folder.
        if (!is_pid_folder(entry))
            continue;

        // Try to open /proc/<PID>/stat.
        snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);
        fp = fopen(path, "r");

        if (!fp) {
            perror(path);
            continue;
        }

        // Get PID, process name and number of faults.
        fscanf(fp, "%d %s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %lu %lu",
            &pid, &path, &u_time, &s_time
        );

        ans[counter].pid=pid;
        // ans[counter].processName=path;
        ans[counter].uTime=u_time;
        ans[counter].xTime=s_time;
        counter++;
        // Pretty print.
        // printf("%5d %-20s: %lu\n", pid, path, maj_faults);

        fclose(fp);
    }
    printf("JJI2");

    // for(int i=0;i<10;i++) {
    //     printf("%5d, %lu\n", ans[i].pid, ans[i].uTime);
    // }

    int op = counter;

    struct Answer sortedAnswer[counter+1];

    for(int i=0;i<counter;i++) {
        int maxValue = -1;
        int maxIndex = 0;
        for(int  j=i+1;j<counter;j++) {
            if(ans[j].uTime+ans[j].xTime > ans[i].uTime+ans[i].xTime) {
                struct Answer temp;
                temp.pid = ans[i].pid;
                temp.xTime = ans[i].xTime;
                temp.uTime = ans[i].uTime;
                ans[i].pid = ans[j].pid;
                ans[i].xTime = ans[j].xTime;
                ans[i].uTime = ans[j].uTime;

                ans[j] = temp;
            }
        }
    }



printf("JJI");
    char sentence[1000];

    // creating file pointer to work with files

    // opening file in writing mode
    FILE * fil;

   fil = fopen ("file.txt", "w+");
   fprintf(fil, "%s %s %s %d", "We", "are", "in", 2012);
   
   fclose(fil);

    closedir(procdir);
    return 0;
}
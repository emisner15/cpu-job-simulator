#include <cstdlib>
#include <sstream>
#include <iostream>
#include <queue>
#include <functional>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "Job.h"

using namespace std;

int main()
{
    int cpus, time;
    int tick = 1;
    int total_cpus;
    int available_cpu;
    int jobs_in_queue = 0;
    string job_names;
    string line;
    vector<Job> jobs;
    vector<Job> current_jobs_active;
    vector<Job> finished_jobs;
    priority_queue<Job, vector<Job>, greater<Job>> min_pq{};

// reads data from our job.txt
    ifstream infile;
    infile.open("jobs.txt");

    if(infile.is_open() == true)
    {
        getline(infile, line);
        istringstream iss(line);

        total_cpus = atoi(line.c_str());
        available_cpu = total_cpus;

        while(infile.good() == true)
        {
            getline(infile, line);
            istringstream iss(line);
            while(iss >> job_names>> cpus >> time)
            {
                Job job_object;
                job_object.setName(job_names);
                job_object.setCPU(cpus);
                job_object.setStartDuration(time);
                job_object.setCurrentDuration(time);
                jobs.push_back(job_object);
            }
        }
    }
    infile.close();
//loop that does everything
    do
    {
        // Checks to put jobs in queue
        if(jobs.size() != jobs_in_queue)
        {
            // If jobs name is NULL skip
            if(jobs[jobs_in_queue].getName() == "NULL")
            {

            }
            // If jobs CPU requirement is too large, exit program
            else if(jobs[jobs_in_queue].getCPU() > total_cpus)
            {
                cout << "Error, Job requires too many CPUs. Exiting";
                exit(0);
            }
            // Add job to queue
            else
            {
                jobs[jobs_in_queue].setStartTick(tick);
                min_pq.push(jobs[jobs_in_queue]);
                jobs_in_queue++;
            }
        }

        // Adds the possible number of jobs to cpu.
        while(!min_pq.empty() && min_pq.top().getCPU() <= available_cpu)
        {
            available_cpu = available_cpu - min_pq.top().getCPU();
            current_jobs_active.push_back(min_pq.top());
            min_pq.pop();
        }

        // Decrements duration of jobs
        for(int i = 0; i < current_jobs_active.size(); i++)
        {
            current_jobs_active[i].setCurrentDuration(current_jobs_active[i].getCurrentDuration() - 1);
            if(current_jobs_active[i].getCurrentDuration() == 0)
            {
                available_cpu = available_cpu + current_jobs_active[i].getCPU();
                current_jobs_active[i].setEndTick(tick);
                finished_jobs.push_back(current_jobs_active[i]);
                current_jobs_active.erase(current_jobs_active.begin() + i);
            }
        }
        tick++;
    }
    while(jobs.size() != finished_jobs.size());

// creates CSV file and out puts information

    ofstream myfile;

    myfile.open("Results.csv");

    myfile << "Job Name" << ","
           << "Starting Tick" << ","
           << "Ending Tick" << ","
           << "Duration" << endl;

    for(int i = 0; i < finished_jobs.size(); i++)
    {
        myfile << finished_jobs[i].getName() << ","
               << finished_jobs[i].getStartTick() << ","
               << finished_jobs[i].getEndTick() << ","
               << finished_jobs[i].getEndTick() - finished_jobs[i].getStartTick() << endl;
    }

    myfile.close();

    return 0;
}

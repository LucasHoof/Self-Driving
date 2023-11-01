# CSCI 3081W Project

## Getting Started

Here is a quick overview of how to run the visualization (These steps are similar in each build environment.  See below for environment details.):

    
    # Go to the project directory
    cd /path/to/repo/project
    
    # Clean the project
    make clean
    
    # Build the project
    make -j
    
    # Run the project (./build/web-app <port> <web folder>)
    build/bin/transit_service 8081 apps/transit_service/web/
    
    
Navigate to http://127.0.0.1:8081 and you should see a visualization.  
Navigate to http://127.0.0.1:8081/schedule.html and you should see a a page to schedule the trips. To view the entities, click on the right top of the visualization page (not the schedule page) and choose the entity to view such as drone or (robot name) that you give in the schedule page.

### Docker Instructions [for personal machines]

We recommend using Docker when developing on your own personal machine.  Here are the steps on how to setup docker

#### Docker Pre-requisites
  * Windows 10 Home
    * Install [wsl2 and Ubuntu](https://www.youtube.com/watch?v=ilKQHAFeQR0&list=RDCMUCzLbHrU7U3cUDNQWWAqjceA&start_radio=1&t=7) and [Windows 10 Doc](https://docs.microsoft.com/en-us/windows/wsl/install-manual)
    * For [Windows 11](https://docs.microsoft.com/en-us/windows/wsl/install) 
  * Install [Docker Desktop](https://www.docker.com/products/docker-desktop) from [Docker Hub](https://hub.docker.com/)
  * Linux
    * Use [docker group instead of sudo](https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-18-04)

#### Getting Started with Docker ([after cloning the repository](#download-the-repository))

On Windows use the "Git Bash" terminal.

1. Build docker image
    ```bash
    bin/build-env.sh
    ```
2. Run docker image
    ```bash
    #Usage bin/run-env.sh <port - optional(default 8081)>
    bin/run-env.sh
    ```

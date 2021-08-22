# Affine Physics Development Environment

# Lean-Based Project Builder

You're here because you want (someone) to build an Ubuntu and VSCode-based development environment, backed by your own GitHub repository, for professional writing and analyzing of logic and mathematics using the Lean Prover, with none of the daunting re-configuration of your local computer sometimes required to set up fully working environments. The good news is that you can have it all with just a few clicks of the mouse and keys, as long as you have VSCode and DockerDesktop running properly on Windows 10 (footnote below) or OSX machine. This work is intended to make Lean accessible to as many early students as possible, in part by removing all of the mundane but often complex, error-prone, and off-putting system administering tasks required to get a working environment set up. Simply follow these steps and in a few minutes you should have a GitHub-repo-backed, VSCode-provided IDE opened to edit a fork of this repository cloned into your own local Docker container, configured according to our specifications to provide a first-rate, trouble-free Lean Development Experience. 

## What To Do
- Update your operating system:
  - If MacOS: Be sure your OS is completely up-to-date (current version of Big Sur, currently 11.5.2 as of this writing).
  - If Windows 10 Home: Update to Windows 10 Education (Windows 10 Home won't do). If you're a UVa student, updating to Windows 10 Education is free.
    1. Get OS Windows Update license key from ITS: https://virginia.service-now.com/its/.  
    2. Click Software in the left-hand navigation. Select the *latest* Windows 10 Education version. Get an update key.
    3. After obtaining the OS key, copy and paste it in to the Windows Activation page (same screen as Windows Update).
    4. Reboot your machine. You can check the Windows *System Information* app to confirm that your OS is updated.
- Have a GitHub account. Create one for yourself if necessary. It's free: https://github.com/
- Install Docker Desktop: https://www.docker.com/products/docker-desktop.
- Install VSCode: https://code.visualstudio.com/download.
- Launch Docker Desktop and watch for it to complete its start-up procedures. While it starts up, continue on to the remaining instructions. 
- Use GitHub to fork this repository now. 
  - Be logged in to your GitHub account.
  - Visit this very repository on GitHub (which is probably where you're reading this)
  - Fork this repo using the *Fork* button in the upper right corner. 
  -   This will create a copy of this entire repository in *your* GitHub account. Visit your GitHub page to confirm that you now have a clone of this repository. 
  -   Select the green Code button, then HTTPS, then copy the URL that is provided. This will be the GitHub URL of your newly forked copy of the respository.
- Open our Lean Development Environment directly from your new GitHub repository
  - Launch a *new* VSCode window. 
  - Use CTRL/CMD-SHIFT-P to bring up the VSCode command palatte. 
  - Search for and select *Clone Repository in Container Volume*
  - Paste the URL of your new repository as the argument.
  - If it asks, select *unique repository*.
- Wait for your development environment to completely "boot up" before taking any further actions.
- Check to see that everything is working
  - Open the test.lean file (src/test/test_lean_mathlib.lean)
  -Check that the conditions described therein are satisfied.

## How It Works
We deliver a Lean development environment via VSCode and its *Remote-Containers* capabilities. In a nutshell, when you ask VSCode to clone our repository, it will actually fork it and then clone your fork into the container that it launches to provide the programming platform you will then use to develop your solutions. It is very important to commit changes you make to your container-local repository, but then also to push them to your GitHub repo to back them up and because that should be the main respository for your project. You can log into it by simply opening a Terminal in VSCode. The clone of your repo is in the /workspaces folder within the container file system (or storage *volume*, as it's called).

## Risk Alert and Avoidance
It is important to understand that commits made to git are stored in the Docker container serving up the develop environment.  if you delete the container or its storage volume (which you could do through Docker Desktop), this will erase the work stored in the container. To make your container-local changes persistent, stage/add and then commit your local changes to the local repo, then push your container-repo-local changes to your repository on GitHub. 

## Help Make It Even Better
Let us know what you think. Better yet, make it better and send us a PR. You'll be completely set up to do that by the results of this procedure. 


## Legal and contact
Copyright: © 2021 By the Rector and Visitors of the University of Virginia.
Supervising Author: Kevin Sullivan. UVa CS Dept. sullivan@virginia.edu. 
Acknowledgements: Thank you to multiple students for read, test, and fixing.


## Old version

- Fork this repository (won't get submodules)
- Open VSCode Remote Containers on it (won't populate submodules)
- Launch terminal
- Configure git for yourself in terminal/container
  - git config --global user.name "Kevin Sullivan"
  - git config --global user.email sullivan.kevinj@gmail.com
- Copy the container's public key (~/.ssh/ed25519.pub) to your GitHub SSH keys
- In terminal / container:
  - git submodule init
  - git submodule update

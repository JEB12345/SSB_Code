This is where all the SSB Sensor Board code should go.

The project is created using MPLabX for the dsPIC33EP128GP506.

We are also using a submodule for the MPU60x0 IMU. A submodule is an external git repo that is mantained else by someone else and we use a certain commit from their repo. This does not imply we are using the latest version of the external repo, so please do not pull the module directly.

In order to pull this submodule, you will need to call:
"git submodule init" then,
"git submodule update"

Please read this blog post on submodules. It is a good quick overview of their basic usage: http://www.arlocarreon.com/blog/git/git-repo-inside-a-git-repo/ 

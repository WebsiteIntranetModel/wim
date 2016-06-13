# Website Intranet Model #

[![Build Status](https://travis-ci.org/WebsiteIntranetModel/wim.svg?branch=master)](https://travis-ci.org/WebsiteIntranetModel/wim)

Check [wimgemeenten.nl](http://www.wimgemeenten.nl) for more information. Please note that this website is in Dutch.

Useful links for developers:
- [Travis CI](https://travis-ci.org/WebsiteIntranetModel/wim/builds)
- [Docker Hub](https://hub.docker.com/r/goalgorilla/wim/builds/)

# Installation #

## Prerequisites ##
Download and install the [Docker Toolbox](https://www.docker.com/products/docker-toolbox).

Note that the docker projects have to be somewhere under your home directory in order to work (limitation for Mac and Windows).


## Steps ##

1. Start a docker machine (docker quickstart icon).

2. Clone this repository to the directory of your choice (within your home directory):
    ```
    git clone git://github.com/WebsiteIntranetModel/wim.git profiles/wim
    ```

3. Go inside the folder in which you cloned this repository (where the docker-compose.yml file is).

4. Build and start the docker containers.
    ```
    docker-compose up -d
    ```

    This will build multiple containers (see the Dockerfile in docker_build/) and all the dependencies.

5. Add wim.dev and mailcatcher.wim.dev to your /etc/hosts file based on the ip of the docker machine.

    If necessary you can find the IP with this command on your host machine:
    ```
    docker-machine ls
    ```

6. Run the install script on the docker web container, the name could be slightly different on your machine, in the example below the name is wim_web_1.

    Add _include_ as second parameter to include local development settings to the settings.php file. Skip it if you don't want this.
    ```
    docker exec -it wim_web_1 bash /root/dev-scripts/install/install-script.sh install include
    ```

7. Running into trouble?

    **wim_db_1 port in use**
    Edit the docker-compose.yml file in the root of the repo and change the database port mapping `3308:3006` to for example `3309:3306` or another unused port.

## Usage ##

**If you want to see which containers are running:**
```
docker ps
```

**SSH into the container:**
```
docker exec -it wim_web_1 bash
```
Here you can use _drush_ and _drupal list_.

**If you want to re-install, use the install script with the _reinstall_ parameter:**

Add _include_ as second parameter to include local development settings to the settings.php file. Skip it if you don't want this.

```
docker exec -it wim_web_1 bash /root/dev-scripts/install/install-script.sh reinstall include
```

**If you want to check coding standards:**

Add _full_ as parameter if you want to see a detailed list of errors, skip it to see just a summary of files with issues.

```
docker exec -it wim_web_1 bash /root/dev-scripts/check-coding-standards.sh full
```

**To view emails go to:**
```
mailcatcher.wim.dev
```

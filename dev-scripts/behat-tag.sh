#!/bin/bash

PROJECT_FOLDER=/var/www/html/profiles/wim/behat

behat --version

echo $PROJECT_FOLDER/config/behat.yml;

if [ $1 != "" ]
then
  echo "RUNNING TESTS WITH TAG: $1"

  behat $PROJECT_FOLDER --config $PROJECT_FOLDER/config/behat.yml --tags "$1" --colors
fi

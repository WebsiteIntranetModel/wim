#!/usr/bin/env bash

drush en wim_fixtures -y

# Check if first argument given is "remove". In that case we remove demo content,
if [ ${1:-"add"} = "remove" ]; then
 drush mr --group=WIMMigrate
 else
 drush mi --group=WIMMigrate
fi

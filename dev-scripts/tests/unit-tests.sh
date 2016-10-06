#!/bin/sh

drush en simpletest -y;

# Run simple tests for WIM.
php /var/www/html/scripts/run-tests.sh WIM
php /var/www/html/scripts/run-tests.sh --class "XMLSitemapUnitTest,XMLSitemapMenuFunctionalTest,XMLSitemapNodeFunctionalTest"

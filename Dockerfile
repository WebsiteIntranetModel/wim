FROM php:7.1-apache
MAINTAINER devel@goalgorilla.com

RUN a2enmod rewrite

# install the PHP extensions we need
RUN apt-get update && apt-get install -y \
  libpng-dev \
  libjpeg-dev \
  libpq-dev \
  libmcrypt-dev \
  zip unzip \
  mysql-client \
  git \
  ssmtp \
  nano \
  vim \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/* \
  && docker-php-ext-configure gd --with-png-dir=/usr --with-jpeg-dir=/usr \
  && docker-php-ext-install gd mbstring mcrypt pdo pdo_mysql pdo_pgsql zip

RUN apt-get update -qq && apt-get install -y unzip

WORKDIR /var/www/html

ADD docker_build/mailcatcher-ssmtp.conf /etc/ssmtp/ssmtp.conf

RUN echo "hostname=goalgorilla.com" >> /etc/ssmtp/ssmtp.conf
RUN echo 'sendmail_path = "/usr/sbin/ssmtp -t"' > /usr/local/etc/php/conf.d/mail.ini

ADD docker_build/php.ini /usr/local/etc/php/php.ini

RUN docker-php-ext-install zip

# Install bcmath
RUN docker-php-ext-install bcmath

# Install Composer.
RUN curl -sS https://getcomposer.org/installer | php
RUN mv composer.phar /usr/local/bin/composer

# Install composer dependencies.
ADD docker_build/composer.json /root/.composer/composer.json
ADD docker_build/composer.lock /root/.composer/composer.lock
RUN composer global install --prefer-dist

# Unfortunately, adding the composer vendor dir to the PATH doesn't seem to work. So:
RUN ln -s /root/.composer/vendor/bin/drush /usr/local/bin/drush

ADD . /var/www/html/profiles/wim
RUN chown -R www-data:www-data *

RUN if [ ! -f /root/.composer/vendor/drush/drush/lib/Console_Table-1.1.3/Table.php ]; then pear install Console_Table; fi

# Fix shell.
RUN echo "export TERM=xterm" >> ~/.bashrc

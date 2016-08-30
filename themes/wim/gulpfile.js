'use strict';

// ===================================================
// Required packages
// ===================================================

var gulp          = require('gulp'),
    postcss       = require('gulp-postcss'),
    sass          = require('gulp-sass'),
    sourcemaps    = require('gulp-sourcemaps'),
    autoprefixer  = require('autoprefixer'),
    mqpacker      = require('css-mqpacker'),
    precss        = require('precss'),
    rucksack      = require('gulp-rucksack'),
    jade          = require('gulp-jade'),
    importOnce    = require('node-sass-import-once'),
    path          = require('path'),
    rename        = require('gulp-rename'),
    fs            = require('fs'),
    concat        = require('gulp-concat'),
    notify        = require('gulp-notify'),
    gutil         = require('gulp-util'),
    connect       = require('gulp-connect'),
    plumber       = require('gulp-plumber'),
    deploy        = require('gulp-gh-pages'),
    gulpignore    = require('gulp-ignore');

    var options = {};

// ===================================================
// CONFIG
// Edit these paths and options
// ===================================================

// The root paths are used to construct all the other paths in this
// configuration. The "theme" root path is where this gulpfile.js is located.

options.rootPath = {
  theme       : __dirname + '/',
  dist        : __dirname + '/dist/',
};

options.theme = {
  name       : 'wim',
  root       : options.rootPath.theme,
  components : options.rootPath.theme + 'components/',
  build      : options.rootPath.theme + 'css/',
  css        : options.rootPath.theme + 'css/',
  js         : options.rootPath.theme + 'js/',
  styleguide : options.rootPath.theme + 'jade/',
  images     : options.rootPath.theme + 'images/',
  content    : options.rootPath.theme + 'content/',
  //font       : options.rootPath.theme + 'font/',
  bootstrap  : options.rootPath.theme + 'node_modules/bootstrap-sass/assets/'
};

// Set the URL used to access the Drupal website under development. This will
// allow Browser Sync to serve the website and update CSS changes on the fly.
options.drupalURL = '';
// options.drupalURL = 'http://localhost';

// Define the node-sass configuration. The includePaths is critical!
options.sass = {
  importer: importOnce,
  includePaths: [
    options.theme.components
  ],
  outputStyle: 'expanded'
};


// Define the paths to the JS files to lint.
options.eslint = {
  files  : [
    options.rootPath.project + 'gulpfile.js',
    options.theme.js + '**/*.js',
    '!' + options.theme.js + '**/*.min.js',
    options.theme.components + '**/*.js',
    '!' + options.theme.build + '**/*.js'
  ]
};

options.styleguide = {
  files  : [options.theme.styleguide + '/**/*.jade', '!/**/_*.jade'] // '**/*.jade', '!' + options.theme.styleguide + '**/_*.jade'
};

var onError = function(err) {
  notify.onError({
    title:    "Gulp error in " + err.plugin,
    message:  "<%= error.message %>",
    sound: "Beep"
  })(err);
  this.emit('end');
};

// ===================================================
// Build CSS.
// ===================================================

var sassFiles = [
  options.theme.components + '**/*.scss',
  // Do not open Sass partials as they will be included as needed.
  '!' + options.theme.components + '**/_*.scss'
];

var sassProcessors = [
  autoprefixer({browsers: ['> 1%', 'last 2 versions']}),
  mqpacker({sort: true})
];

gulp.task('styles', function () {
  return gulp.src(sassFiles)
    .pipe( sourcemaps.init() )
    .pipe( plumber({ errorHandler: onError }) )
    .pipe( sass(options.sass) )
    .pipe( postcss(sassProcessors) )
    .pipe( rucksack() )
    .pipe( rename({dirname: ''}))
    .pipe( sourcemaps.write('.') )
    .pipe( gulp.dest(options.theme.css) )
    .pipe( gulp.dest(options.rootPath.dist + '/css') )
    .pipe( connect.reload() );
});

// ===================================================
// Template file (Jade)
// ===================================================

gulp.task('styleguide', function() {

  return gulp.src(options.styleguide.files)
    .pipe(plumber({
      handleError: onError
    }))
    .pipe(jade({
      pretty: true
    })) // pipe to jade plugin
    .pipe(gulp.dest(options.rootPath.dist)); // tell gulp our output folder
});

// ===================================================
// Scripts
// ===================================================

// get component scripts used for styleguide only
gulp.task('styleguide-components', function() {
  return gulp.src([
  ])
  .pipe( concat('styleguide.js') )
  .pipe( gulp.dest(options.theme.js) );
});

// get component scripts and make available for dist in one file
gulp.task('script-components', function() {
  return gulp.src([
      options.theme.js + "components/waves.js",
    ])
    .pipe( concat('components.js') )
    .pipe( gulp.dest(options.theme.js) );
});

// get project scripts and make available for dist in one file
gulp.task('script-materialize', function() {
  return gulp.src([
    ])
    .pipe( concat('materialize.js') )
    .pipe( gulp.dest(options.theme.js) );
});

//copy vendor scripts from drupal to make them available for the styleguide
gulp.task('script-vendor', function() {
  return gulp.src([
    options.rootPath.drupalcore + 'assets/vendor/jquery/jquery.min.js',
  ])
  .pipe( concat('vendor.js') )
  .pipe( gulp.dest(options.rootPath.dist + '/js') );
});

// ===================================================
// Copy assets to dist folder
// ===================================================

gulp.task('images', function() {
  return gulp.src(options.theme.images + '**/*')
  .pipe( gulp.dest(options.rootPath.dist + 'images') );
});

gulp.task('content', function() {
  return gulp.src(options.theme.content + '**/*')
  .pipe( gulp.dest(options.rootPath.dist + 'content') );
});

//gulp.task('font', function() {
//  return gulp.src(options.theme.font + '**/*')
//  .pipe( gulp.dest(options.rootPath.dist + 'font') );
//});

gulp.task('libs', function() {
  return gulp.src(options.theme.libs + '**/*')
  .pipe( gulp.dest(options.rootPath.dist + 'libs') );
});

// ===================================================
// Import Bootstrap assets
// ===================================================

gulp.task('bootstrap-sass', function() {
  return gulp.src(options.theme.bootstrap + 'stylesheets/bootstrap/' + '**/*.scss' )
    .pipe( gulp.dest(options.theme.components + '/contrib/bootstrap') );
});

gulp.task('bootstrap-js', function() {
  return gulp.src(options.theme.bootstrap + 'javascripts/bootstrap.min.js')
    .pipe( gulp.dest(options.theme.js) );
});


// ===================================================
// Lint Sass and JavaScript
// ===================================================
var sassFilesToLint = [
  options.theme.components + '**/*.scss',
  // Do not open Sass partials as they will be included as needed.
  '!' + options.theme.components + 'contrib/**/*.scss'
];


gulp.task('lint', ['lint:sass', 'lint:js']);

// Lint JavaScript.
gulp.task('lint:js', function () {
  return gulp.src(options.eslint.files)
    .pipe($.eslint())
    .pipe($.eslint.format());
});

// Lint Sass.
gulp.task('lint:sass', function () {
  return gulp.src(sassFilesToLint + '**/*.scss')
    .pipe($.sassLint())
    .pipe($.sassLint.format());
});

// ===================================================
// Set up a server
// ===================================================

gulp.task('connect', function() {
  connect.server({
    root: [options.rootPath.dist],
    livereload: true,
    port: 5000
  });
});


// ===================================================
// Watch and rebuild tasks
// ===================================================

gulp.task('default', ['watch:css', 'watch:styleguide', 'watch:content', 'watch:js', 'connect']);

gulp.task('watch:css', ['styles'], function () {
  return gulp.watch(options.theme.components + '**/*.scss', ['styles']);
});

gulp.task('watch:styleguide', ['styleguide'], function () {
  return gulp.watch([
    options.theme.root + '**/*.jade',
  ], ['styleguide']);
});

gulp.task('scripts', ['script-vendor']);

gulp.task('watch:js', function () {
  return gulp.watch(options.eslint.files, ['scripts'] );
});

gulp.task('watch:content', ['content'], function () {
  return gulp.watch(options.theme.content + '**/*', ['content']);
});

// ===================================================
// Deploy to github pages branch
// ===================================================
gulp.task('build', ['styles', 'styleguide' , 'scripts','images', 'content']);

gulp.task('deploy', ['build'], function() {
  return gulp.src([options.rootPath.dist + '/**/*'])
    .pipe( deploy() );
});


// ===================================================
// Run this one time when you install the project so you have all files in the dist folder
// ===================================================
gulp.task('init', ['images', 'content', 'libs', 'bootstrap-js', 'bootstrap-sass']);

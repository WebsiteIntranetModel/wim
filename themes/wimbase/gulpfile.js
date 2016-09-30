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
    importOnce    = require('node-sass-import-once'),
    path          = require('path'),
    rename        = require('gulp-rename'),
    fs            = require('fs'),
    concat        = require('gulp-concat'),
    notify        = require('gulp-notify'),
    gutil         = require('gulp-util'),
    connect       = require('gulp-connect'),
    plumber       = require('gulp-plumber'),
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
};

options.theme = {
  name       : 'wimbase',
  root       : options.rootPath.theme,
  components : options.rootPath.theme + 'components/',
  build      : options.rootPath.theme + 'css/',
  css        : options.rootPath.theme + 'css/',
  js         : options.rootPath.theme + 'js/',
  bootstrap  : options.rootPath.theme + 'node_modules/bootstrap-sass/assets/'
};


// Define the node-sass configuration. The includePaths is critical!
options.sass = {
  importer: importOnce,
  includePaths: [
    options.theme.components
  ],
  outputStyle: 'expanded'
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
    .pipe( connect.reload() );
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

gulp.task('lint', ['lint:sass']);

// Lint Sass.
gulp.task('lint:sass', function () {
  return gulp.src(sassFilesToLint + '**/*.scss')
    .pipe($.sassLint())
    .pipe($.sassLint.format());
});

// ===================================================
// Run this one time when you install the project so you have all files in the dist folder
// ===================================================
gulp.task('init', ['bootstrap-js', 'bootstrap-sass']);
gulp.task('build', ['styles']);

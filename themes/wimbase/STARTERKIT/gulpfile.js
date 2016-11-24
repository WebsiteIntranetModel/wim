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
  theme       : __dirname + '/'
};

options.theme = {
  name       : 'COE',
  root       : options.rootPath.theme,
  components : options.rootPath.theme + 'components/',
  build      : options.rootPath.theme + 'css/',
  css        : options.rootPath.theme + 'css/',
  js         : options.rootPath.theme + 'js/',
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
// Lint Sass
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
// Watch and rebuild tasks
// ===================================================

gulp.task('default', ['watch:css']);

gulp.task('watch:css', ['styles'], function () {
  return gulp.watch(options.theme.components + '**/*.scss', ['styles']);
});

const {src, dest, parallel} = require('gulp');
const less = require('gulp-less');
const pug = require('gulp-pug');
const babel = require('gulp-babel')
const cleanCSS = require('gulp-clean-css');
const uglify = require('gulp-uglify');

paths = { // Настройка путей
    less: {
        src: 'src/less/*.less',
        dest: 'build_gulp/css'
    },
    pug: {
        src: 'src/view/*.pug',
        dest: 'build_gulp/html'
    },
    js:{
        src: 'src/js/*.js',
        dest: 'build_gulp/js'
    }
}

function build_less() {
    return src(paths.less.src)
        .pipe(less()) // Обработать LESS
        .pipe(cleanCSS()) // Минификация CSS
        .pipe(dest(paths.less.dest));
}
function build_pug(){
    return src(paths.pug.src)
        .pipe(pug())
        .pipe(dest(paths.pug.dest));
}
function build_js(){
    return src(paths.js.src)
        .pipe(babel())
        .pipe(uglify())
        .pipe(dest(paths.js.dest));
}

exports.default = parallel(build_less, build_pug, build_js)
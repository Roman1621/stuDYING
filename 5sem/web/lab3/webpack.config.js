const webpack = require("webpack");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const path = require("path");
const fs = require("fs");

const pages = fs.readdirSync("./src_webpack/view").filter(name => name.endsWith(".pug"))

module.exports = {
    mode: "development",
    devtool: false,
    entry: {
        main: "./src_webpack/main.webpack.js",
        info: "./src_webpack/info.webpack.js",
        news: "./src_webpack/news.webpack.js"
    },
    output: {
        path: path.resolve(__dirname, "build_webpack"),
        filename: "./js/[name].js"
    },
    module: {
        rules: [
            {
                test: /\.less$/,
                use: [
                    "style-loader",
                    "css-loader",
                    "less-loader"
                ],
                exclude: /node_modules/
            },
            {
                test: /\.pug$/,
                use: [
                    "pug-loader"
                ],
                exclude: /node_modules/
            },
            {
                test: /\.js$/,
                exclude: /(node_modules|bower_components)/,
                use: {
                    loader: "babel-loader",
                    options: { presets: ["@babel/preset-env"] }
                }
            }
        ]
    },
    plugins: [
        ...pages.map(file => new HtmlWebpackPlugin({
            template: `./src_webpack/view/${file}`,
            filename: `./html/${file.replace(/\.pug/,'.html')}`,
            inject: 'body',
            chunks: [file.replace(/\.pug/, "")]
        }))
    ]
}
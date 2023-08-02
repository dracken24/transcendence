const webpack = require('webpack');
const nodeExternals = require('webpack-node-externals');

module.exports = function(options) {
	return {
		...options,
		entry: ['webpack/hot/poll?100', './src/main.ts'],
		watch: true,
		externals: [
		nodeExternals({
			allowlist: ['webpack/hot/poll?100'],
		}),
		],
		plugins: [
		...options.plugins,
		new webpack.HotModuleReplacementPlugin(),
		],
		watchOptions: {
		ignored: /node_modules/,
		aggregateTimeout: 300,
		poll: 1000,
		},
	};
};
module.exports = {
    filenameHashing: false,
    productionSourceMap: false,
    css:{
        extract : false
    },
    configureWebpack:{
        optimization: {
          splitChunks: false
        }
      },
      pluginOptions: {
        compression:{
          gzip: {
            filename: '[file].gz[query]',
            algorithm: 'gzip',
            include: /\.(js|css|html|svg|json|ico)(\?.*)?$/i,
            minRatio: 0.8,
          }
        }
      }

  }
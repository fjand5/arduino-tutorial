import WifiSelector from './views/WifiSelector'
import store from './store'
let ServicePlugin = {
    install : function (Vue) {
        Vue.prototype.$showWifiSelector = function () {
            let WifiSelectorClass= Vue.extend(WifiSelector)
            let instance = new WifiSelectorClass({store: store})
            instance.$mount()
        }
      }
}
export default ServicePlugin;
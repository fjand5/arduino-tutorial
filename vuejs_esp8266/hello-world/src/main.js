import Vue from 'vue'
import App from './App.vue'
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';
import store from './store';
import ServicePlugin from './sevice'
Vue.use(ElementUI);
Vue.use(ServicePlugin);
Vue.config.productionTip = false

new Vue({
  render: h => h(App),
  store: store
}).$mount('#app')

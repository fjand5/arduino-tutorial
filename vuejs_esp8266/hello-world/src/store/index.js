import Vue from 'vue'
import Vuex from 'vuex'
import wifi from './modules/wifi'

Vue.use(Vuex)

const store = new Vuex.Store({
    modules: [
        wifi
    ]
})
export default store
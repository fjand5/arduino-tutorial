import api from '../../api'
const wifi = {
    state: () => ({
        nearWifi: []
    }),
    mutations: {
        setNeartWifi: function(state, data){
            state.nearWifi = data
        }
    },
    actions: {
        updateNearWifi: function(context){
            return api.get('/scanwifi')
            .then((data)=>{
                context.commit('setNeartWifi', data)
                return Promise.resolve(true)
            })
        },
        setWifi: function(context,{_ssid,_sspw}){
            return api.post('/setwifi',{_ssid,_sspw})
        }
    },
    getters: {
        getNearWifi: function(state){
            return state.nearWifi
        }
    }
  }
export default wifi
  